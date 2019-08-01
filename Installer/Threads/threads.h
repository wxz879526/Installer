#ifndef SHARED_THREADS_H_
#define SHARED_THREADS_H_

// thread ids
enum ThreadId
{
	kThreadBegin = -1,//线程ID定义开始
	kThreadUI,			//UI线程（主线程）
	kThreadBackgroud,	//辅助线程
	kThreadEnd,//线程ID定义结束
};

#endif // SHARED_THREADS_H_
