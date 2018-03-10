// CTestApp.cpp: implementation of the CTestApp class.
//
//////////////////////////////////////////////////////////////////////

#include "CTestApp.h"
#include "CSmartPtr.h"
#include "CDirect3DWnd.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CTestApp theApp;

CTestApp::CTestApp()
{
	CoInitialize(NULL);

}

CTestApp::~CTestApp()
{

}


bool CTestApp::Init()
{
	CDirect3DWnd::RegisterClass();
	d.Init();
	dw.Create(d,"hi", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 0, 0, 640, 480);
	server.Start((const unsigned char*)"0.0.0.0:21");
/*			dd->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,1.0f), 1.0f, 0 );

			dd->BeginScene();

			// Render geometry here...

			dd->EndScene();
			dd->Present( NULL, NULL, NULL, NULL );
*/
	return true;
}

void CTestApp::MessagePump()
{
	CWinApp::MessagePump();
}

int CTestApp::Cleanup()
{
	return 0;
}
