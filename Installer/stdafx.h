// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#if defined(_DEBUG)
#error 暂不支持Debug版本编译，请切换成Release
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#define SCOM_MASK (scom_mask_render_gdi | scom_mask_imgdecoder_gdip | scom_mask_translator) //使用SOUI静态库时，可以使用这个mask来指定加载哪些库。

#include "souistd.h"
#include "commgr2.h"
#include "helper/SMenu.h"
#include "event/NotifyCenter.h"
#include "core/SHostWnd.h"

#include "Resource.h"
#define R_IN_CPP
//#include "bin/res/resource.h"
using namespace SOUI;


#include "base/thread/framework_thread.h"
#include "base/thread/thread_manager.h"
#include "base/memory/singleton.h"
#include "base/util/string_util.h"
#include "base/win32/path_util.h"
#include "base/file/file_util.h"

#include "Threads/threads.h"
#include "Threads/misc_thread.h"