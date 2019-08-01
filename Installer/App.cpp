#include "stdafx.h"
#include "base/util/cmd_line_args.h"
#include "app_dump.h"
#include "MainForm.h"
#include "App.h"

// Ƥ���ļ����ط�ʽ 
#define RES_TYPE 0  //���ļ��м���
//#define RES_TYPE 1  //��PE�ļ���Դ����
//#define RES_TYPE 2  //��zip���м���

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	PreMessageLoop();

	comMgr2_ = std::make_unique<SComMgr2>(COM_IMGDECODER);

	BOOL bLoaded = FALSE;
	SOUI::CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory; //Ĭ��ʹ��gdip����ͼƬ
	SOUI::CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
	bLoaded = comMgr2_->CreateRender_GDI((IObjRef**)&pRenderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("render_gdi"));
	bLoaded = comMgr2_->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
	SASSERT_FMT(bLoaded, _T("load interface imgdecoder failed!"));

	pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

	SApplication *theApp = new SApplication(pRenderFactory, m_hInstance);
	//theApp->RegisterWindowClass<SToolbox>();

	//�����Ҫ�ڴ�����ʹ��R::id::namedid���ַ�ʽ��ʹ�ÿؼ�����Ҫ��һ�д��룺2016��2��2�գ�R::id::namedXmlID����uiresbuilder ����-h .\res\resource.h idtable ��3�����������ɵġ�
	//theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);

	if (0 == RES_TYPE)
	{
		SStringT strResDir = theApp->GetAppDir();
		//strResDir += _T("\\..\\demo");
		SetCurrentDirectory(strResDir);
		//SOUIϵͳ���Ǵ�appdirȥ������Դ
		theApp->SetAppDir(strResDir);
	}
	

	SOUI::CAutoRefPtr<SOUI::IResProvider> pResProvider;
#if	(0 == RES_TYPE)
	CreateResProvider(SOUI::RES_FILE, (IObjRef**)&pResProvider);
	if (!pResProvider->Init((LPARAM)_T("uires"), 0))
	{
		SASSERT(0);
		//goto exit;
	}
#elif (1 == RES_TYPE)
	CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
	pResProvider->Init((WPARAM)m_hInstance, 0);
#elif	 
	bLoaded = pComMgr->CreateResProvider_ZIP((IObjRef**)&pResProvider);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));

	ZIPRES_PARAM param;
	param.ZipFile(pRenderFactory, _T("uires.zip"), "souizip");
	bLoaded = pResProvider->Init((WPARAM)&param, 0);
	SASSERT(bLoaded);
#endif
	theApp->AddResProvider(pResProvider);

	//����SOUIĬ��Ƥ����Դ
	SOUI::CAutoRefPtr<SOUI::IResProvider> sysResProvider;
	CreateResProvider(SOUI::RES_PE, (IObjRef**)&sysResProvider);
	sysResProvider->Init((WPARAM)m_hInstance, 0);
	theApp->LoadSystemNamedResource(sysResProvider);

	//���ض����Է���ģ�顣
	CAutoRefPtr<ITranslatorMgr> trans;
	bLoaded = comMgr2_->CreateTranslator((IObjRef**)&trans);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("translator"));
	if (trans)
	{//�������Է����
		theApp->SetTranslator(trans);
		pugi::xml_document xmlLang;
		if (theApp->LoadXmlDocment(xmlLang, _T("lang_cn"), _T("translator")))
		{
			CAutoRefPtr<ITranslator> langCN;
			trans->CreateTranslator(&langCN);
			langCN->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
			trans->InstallTranslator(langCN);
		}
	}

	//��ȡ�Զ�����Ϣ�򲼾�
	pugi::xml_document xmlDoc;
	if (!theApp->LoadXmlDocment(xmlDoc, _T("XML_CUSTOM_MSG_BOX"), _T("LAYOUT")) || !SetMsgTemplate(xmlDoc.child(L"SOUI")))
		return;

	nbase::CmdLineArgs m_cmdArgs(GetCommandLineW());

	// ��ʾ������
	CMainForm::ShowUI();
}

void MainThread::Cleanup()
{
	PostMessageLoop();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();	
}

void MainThread::PreMessageLoop()
{
	backgnd_thread_.reset(new MiscThread(kThreadBackgroud, "Background Thread"));
	backgnd_thread_->Start();
}

void MainThread::PostMessageLoop()
{
	backgnd_thread_->Stop();
	backgnd_thread_.reset(nullptr);
}

int App::InitInstance(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow)
{
	return 0;
}

int App::ExitInstance()
{
	_CrtDumpMemoryLeaks();

	return 0;
}

int App::InitEnvironment(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow)
{
	if (FAILED(::OleInitialize(NULL)))
		return 0;

	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	return 1;
}

int App::UninitEnvironment()
{
	::OleUninitialize();
	return 0;
}

class CMsgDispatcher : public nbase::Dispatcher
{
public:
	virtual bool Dispatch(const MSG &message) override
	{
		SApplication::getSingleton().GetMsgLoop()->OnMsg(const_cast<LPMSG>(&message));
		return true;
	}
};

int App::Exec(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow)
{
	if (InitEnvironment(hInst, hPrevInst, lpszCmdLine, nCmdShow) == 0)
		return 0;

	nbase::AtExitManager at_manager;	

	CMsgDispatcher dispatcher;
	InitInstance(hInst, hPrevInst, lpszCmdLine, nCmdShow);

	// �������߳�
	MainThread(hInst).RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop, &dispatcher); // ִ�����߳�ѭ��
	
	UninitEnvironment();
	ExitInstance();

	return 0;
}
