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
	* 虚函数，初始化主线程
	* @return void	无返回值
	*/
	virtual void Init() override;

	/**
	* 虚函数，主线程退出时，做一些清理工作
	* @return void	无返回值
	*/
	virtual void Cleanup() override;

	/**
	* 主线程开始循环前，misc线程先开始循环
	* @return void	无返回值
	*/
	void PreMessageLoop();

	/**
	* 主线程结束循环前，misc线程先结束循环
	* @return void	无返回值
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

