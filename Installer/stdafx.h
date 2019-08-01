// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#if defined(_DEBUG)
#error �ݲ�֧��Debug�汾���룬���л���Release
#endif

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


#define SCOM_MASK (scom_mask_render_gdi | scom_mask_imgdecoder_gdip | scom_mask_translator) //ʹ��SOUI��̬��ʱ������ʹ�����mask��ָ��������Щ�⡣

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