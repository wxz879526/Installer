#pragma once

#include "base/callback/callback.h"

//投递任务到UI线程
void Post2UI(const StdClosure &closure);
void Post2UI(const StdClosure &closure, nbase::TimeDelta delay);

//投递任务到辅助线程
void Post2Background(const StdClosure &closure);
