#include "stdafx.h"
#include "threads.h"
#include "base/thread/thread_manager.h"

void Post2UI(const StdClosure &closure)
{
	nbase::ThreadManager::PostTask(kThreadUI, closure);
}

void Post2UI(const StdClosure &closure, nbase::TimeDelta delay)
{
	nbase::ThreadManager::PostDelayedTask(kThreadUI, closure, delay);
}

void Post2Background(const StdClosure &closure)
{
	nbase::ThreadManager::PostTask(kThreadBackgroud, closure);
}