// CDirect3DWnd.cpp: implementation of the CDirect3DWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "CDirect3DWnd.h"
#include "CWinApp.h"
#include "debug.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirect3DWnd::CDirect3DWnd()
{

}

CDirect3DWnd::~CDirect3DWnd()
{

}

void CDirect3DWnd::RegisterClass()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0; //for now
	wc.hCursor = 0; // for now
	wc.hIcon = 0; // for now
	wc.hInstance = CWinApp::GetApp()->GetHinstance();
	wc.lpfnWndProc = CWinApp::WindowProc;
	wc.lpszClassName = DIRECT3DWND_CLASSNAME;
	wc.lpszMenuName = 0; // for now
	wc.style = CS_HREDRAW | CS_VREDRAW; // for now

	::RegisterClass(&wc);
}

bool CDirect3DWnd::Create(const CDirect3D& Direct3D, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CDialog* pParent, HMENU hMenu) 
{
	bool bResult = CWnd::Create(DIRECT3DWND_CLASSNAME, lpWindowName, dwStyle, x, y, nWidth, nHeight, pParent, hMenu);

	if (bResult) {

		RECT wr, cr;
		GetWindowRect(&wr);
		GetClientRect(&cr);

		nWidth = nWidth - (cr.right - cr.left) + (wr.right - wr.left);
		nHeight = nHeight - (cr.bottom - cr.top) + (wr.bottom - wr.top);
		MoveWindow(x, y, nWidth, nHeight);

		D3DCAPS9 d3dCaps;

		if( FAILED( Direct3D->GetDeviceCaps( D3DADAPTER_DEFAULT, 
										   D3DDEVTYPE_HAL, &d3dCaps ) ) )
		{
			// TO DO: Respond to failure of GetDeviceCaps
			bResult = false;
		}

		DWORD dwBehaviorFlags = 0;

		bool useHardwareVertex = true;
		int bits[] = { 0, 1, 3, 4, 5, 6, 7 };
		for (int i = 0; i < (sizeof(bits)/sizeof(bits[0])); i++) {
			if ((d3dCaps.VertexProcessingCaps & (1<<bits[i])) == 0) {
				useHardwareVertex = false;
				break;
			}
		}
		if (useHardwareVertex)
			dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

//		D3DPRESENT_PARAMETERS d3dpp;
		memset(&d3dpp, 0, sizeof(d3dpp));

		d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;
		d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
		d3dpp.Windowed               = TRUE;
		d3dpp.EnableAutoDepthStencil = FALSE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;//D3DPRESENT_INTERVAL_IMMEDIATE;

		IDirect3DDevice9* pTempDevice = NULL;
		if( FAILED( Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetHwnd(),
										  dwBehaviorFlags, &d3dpp, &pTempDevice ) ) )
		{
			bResult = false;
		}
		else  {

			m_Direct3DDevice = pTempDevice;
			pTempDevice->Release();
		}

	}

    UpdateWindow();

	return bResult;
}

bool CDirect3DWnd::CreateFullscreen(const CDirect3D& Direct3D, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, D3DFORMAT Format, int RefreshRate, CDialog* pParent, HMENU hMenu)
{
	bool bResult = CWnd::Create(DIRECT3DWND_CLASSNAME, lpWindowName, dwStyle, x, y, nWidth, nHeight, pParent, hMenu);

	if (bResult) {

		D3DCAPS9 d3dCaps;

		if( FAILED( Direct3D->GetDeviceCaps( D3DADAPTER_DEFAULT, 
										   D3DDEVTYPE_HAL, &d3dCaps ) ) )
		{
			// TO DO: Respond to failure of GetDeviceCaps
			bResult = false;
		}
		debug.WriteDbgLine("timelog.txt", "numrt = %d", d3dCaps.NumSimultaneousRTs);

		DWORD dwBehaviorFlags = 0;

		bool useHardwareVertex = true;
		int bits[] = { 0, 1, 3, 4, 5, 6, 7 };
		for (int i = 0; i < (sizeof(bits)/sizeof(bits[0])); i++) {
			if ((d3dCaps.VertexProcessingCaps & (1<<bits[i])) == 0) {
				useHardwareVertex = false;
				break;
			}
		}
		if (useHardwareVertex)
			dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
/*		if( d3dCaps.VertexProcessingCaps != 0 )
			dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
		else
			dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
*/
//		D3DPRESENT_PARAMETERS d3dpp;
		memset(&d3dpp, 0, sizeof(d3dpp));

		d3dpp.BackBufferFormat       = Format;
		d3dpp.SwapEffect             = D3DSWAPEFFECT_FLIP;
		d3dpp.Windowed               = FALSE;
		d3dpp.EnableAutoDepthStencil = FALSE;
//		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_ONE;//*/D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferWidth        = nWidth;
		d3dpp.BackBufferHeight       = nHeight;
		d3dpp.FullScreen_RefreshRateInHz = RefreshRate;

		IDirect3DDevice9* pTempDevice = NULL;
		if( FAILED( Direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GetHwnd(),
										  dwBehaviorFlags, &d3dpp, &pTempDevice ) ) )
		{
			bResult = false;
		}

		m_Direct3DDevice = pTempDevice;
		pTempDevice->Release();
	}

    UpdateWindow();

	return bResult;
}


LRESULT CDirect3DWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	switch(uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		/*
	case WM_PAINT:
		if (!m_Direct3DDevice.IsNull()) {
			m_Direct3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
								 D3DCOLOR_COLORVALUE(0.0f,1.0f,0.0f,1.0f), 1.0f, 0 );
			
			m_Direct3DDevice->BeginScene();
			
			// Render geometry here...
			
			m_Direct3DDevice->EndScene();
			m_Direct3DDevice->Present( NULL, NULL, NULL, NULL );
		}
		break;
		*/
	}
	return CWnd::WindowProc(hwnd, uMsg, wParam, lParam);
}
