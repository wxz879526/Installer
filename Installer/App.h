#pragma once

class MainThread :
	public nbase::FrameworkThread
{
public:
	MainThread(HINSTANCE hInstance) : nbase::FrameworkThread("MainThread")
	, m_hInstance(hInstance){}
	virtual ~MainThread() {}

private:
	/**
	* �麯������ʼ�����߳�
	* @return void	�޷���ֵ
	*/
	virtual void Init() override;

	/**
	* �麯�������߳��˳�ʱ����һЩ������
	* @return void	�޷���ֵ
	*/
	virtual void Cleanup() override;

	/**
	* ���߳̿�ʼѭ��ǰ��misc�߳��ȿ�ʼѭ��
	* @return void	�޷���ֵ
	*/
	void PreMessageLoop();

	/**
	* ���߳̽���ѭ��ǰ��misc�߳��Ƚ���ѭ��
	* @return void	�޷���ֵ
	*/
	void PostMessageLoop();

private:
	std::unique_ptr<MiscThread>	backgnd_thread_;

	std::unique_ptr<SComMgr2> comMgr2_;
	std::unique_ptr<SApplication> app_;

	HINSTANCE m_hInstance;
};

class App : public nbase::Singleton<App>
{
	SingletonHideConstructor(App)

private:
	App() = default;
	~App() = default;

public:
	int Exec(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow);

private:
	int InitEnvironment(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow);
	int UninitEnvironment();
	int InitInstance(HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR lpszCmdLine, int nCmdShow);
	int ExitInstance();
};

