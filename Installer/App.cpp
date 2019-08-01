#include "stdafx.h"
#include "base/util/cmd_line_args.h"
#include "app_dump.h"
#include "MainForm.h"
#include "App.h"

// 皮肤文件加载方式 
#define RES_TYPE 0  //从文件中加载
//#define RES_TYPE 1  //从PE文件资源加载
//#define RES_TYPE 2  //从zip包中加载

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);

	PreMessageLoop();

	comMgr2_ = std::make_unique<SComMgr2>(COM_IMGDECODER);

	BOOL bLoaded = FALSE;
	SOUI::CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory; //默认使用gdip解码图片
	SOUI::CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
	bLoaded = comMgr2_->CreateRender_GDI((IObjRef**)&pRenderFactory);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("render_gdi"));
	bLoaded = comMgr2_->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
	SASSERT_FMT(bLoaded, _T("load interface imgdecoder failed!"));

	pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

	SApplication *theApp = new SApplication(pRenderFactory, m_hInstance);
	//theApp->RegisterWindowClass<SToolbox>();

	//如果需要在代码中使用R::id::namedid这种方式来使用控件必须要这一行代码：2016年2月2日，R::id::namedXmlID是由uiresbuilder 增加-h .\res\resource.h idtable 这3个参数后生成的。
	//theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);

	if (0 == RES_TYPE)
	{
		SStringT strResDir = theApp->GetAppDir();
		//strResDir += _T("\\..\\demo");
		SetCurrentDirectory(strResDir);
		//SOUI系统总是从appdir去查找资源
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

	//加载SOUI默认皮肤资源
	SOUI::CAutoRefPtr<SOUI::IResProvider> sysResProvider;
	CreateResProvider(SOUI::RES_PE, (IObjRef**)&sysResProvider);
	sysResProvider->Init((WPARAM)m_hInstance, 0);
	theApp->LoadSystemNamedResource(sysResProvider);

	//加载多语言翻译模块。
	CAutoRefPtr<ITranslatorMgr> trans;
	bLoaded = comMgr2_->CreateTranslator((IObjRef**)&trans);
	SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("translator"));
	if (trans)
	{//加载语言翻译包
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

	//读取自定义消息框布局
	pugi::xml_document xmlDoc;
	if (!theApp->LoadXmlDocment(xmlDoc, _T("XML_CUSTOM_MSG_BOX"), _T("LAYOUT")) || !SetMsgTemplate(xmlDoc.child(L"SOUI")))
		return;

	nbase::CmdLineArgs m_cmdArgs(GetCommandLineW());

	// 显示主界面
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

	// 创建主线程
	MainThread(hInst).RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop, &dispatcher); // 执行主线程循环
	
	UninitEnvironment();
	ExitInstance();

	return 0;
}
