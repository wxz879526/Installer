#pragma once

#include "base/callback/callback.h"

//Ͷ������UI�߳�
void Post2UI(const StdClosure &closure);
void Post2UI(const StdClosure &closure, nbase::TimeDelta delay);

//Ͷ�����񵽸����߳�
void Post2Background(const StdClosure &closure);
