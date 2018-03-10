#include <windows.h>
#include "CWinApp.h"

#ifndef UI_NO_WINMAIN

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
	CWinApp* pApp = CWinApp::GetApp();

	if (pApp)
	{
		pApp->SetParam(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
		if (pApp->Init())
			pApp->MessagePump();
		return pApp->Cleanup();
	}
	else
	{
		MessageBox(NULL, "This application needs a CWinApp", "Error", 0);
		return 0;
	}
}

#endif