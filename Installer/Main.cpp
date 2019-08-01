// Meta Trader4 Test.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "App.h"
#include <crtdbg.h>

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(571);
	//_CrtSetBreakAlloc(386);
	//_CrtSetBreakAlloc(356);

#ifdef _DEBUG
	AllocConsole();
	FILE *fp = nullptr;
	freopen_s(&fp, "CONOUT$", "w+t", stdout);
	wprintf_s(L"Command: %s\n", lpCmdLine);
#endif

	int ret = App::GetInstance()->Exec(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

#ifdef _DEBUG
	if (fp)
	{
		fclose(fp);
		fp = nullptr;
	}
#endif

	return ret;
}


