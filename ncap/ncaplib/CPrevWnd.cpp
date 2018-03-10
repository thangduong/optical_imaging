// CPrevWnd.cpp: implementation of the CPrevWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "CPrevWnd.h"
#include "CWinApp.h"
#include "CNCapEngine.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrevWnd::CPrevWnd()
{

}

CPrevWnd::~CPrevWnd()
{

}

void CPrevWnd::RegisterClass()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = 0; //for now
	wc.hCursor = LoadCursor(CWinApp::GetApp()->GetHinstance(), IDC_ARROW); // for now
	wc.hIcon = 0; // for now
	wc.hInstance = CWinApp::GetApp()->GetHinstance();
	wc.lpfnWndProc = CWinApp::WindowProc;
	wc.lpszClassName = PREVWND_CLASSNAME;
	wc.lpszMenuName = 0; // for now
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; // for now

	::RegisterClass(&wc);
}

void CPrevWnd::Show(short* pData) {
	HDC dc = GetDC(m_hWnd);
	HDC hbd = CreateCompatibleDC(0);

	SelectObject(hbd, m_hBackImg);
	BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
	DeleteDC(hbd);
	ReleaseDC(m_hWnd, dc);
}


bool CPrevWnd::Create(LPCTSTR lpWindowName, DWORD dwExStyle, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CWnd* pParent, HMENU hMenu) 
{
	bool bResult = CWnd::CreateEx(dwExStyle, PREVWND_CLASSNAME, lpWindowName, dwStyle, x, y, nWidth, nHeight, pParent, hMenu);

	if (bResult) {

		RECT wr, cr;
		GetWindowRect(&wr);
		GetClientRect(&cr);

		HDC dc = GetDC(m_hWnd);
		memset(&bmi, 0, sizeof(bmi));
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biWidth = nWidth;
		bmi.bmiHeader.biHeight = nHeight;
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biCompression = BI_RGB;
		m_pBackImgData = 0;
		m_hBackImg = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void**)&m_pBackImgData, 0, 0);

		ReleaseDC(m_hWnd, dc);

		nWidth = nWidth - (cr.right - cr.left) + (wr.right - wr.left);
		nHeight = nHeight - (cr.bottom - cr.top) + (wr.bottom - wr.top);
		MoveWindow(x, y, nWidth, nHeight);

		printf("width = %d height = %d\r\n", bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight);
	}

    UpdateWindow();

	return bResult;
}

LRESULT CPrevWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		Show(0);
	}
	else if (uMsg == WM_CLOSE) {
		return 0;
	}
	else if (uMsg == WM_LBUTTONDBLCLK) {
		PostMessage(hwnd, WM_NCE_UI_EVENT, NCE_UI_SNAP, 0);
	}
	else if (uMsg == WM_RBUTTONDBLCLK) {
		PostMessage(hwnd, WM_NCE_UI_EVENT, NCE_UI_SNAP_CUSTOM, 0);
	}
	return CWnd::WindowProc(hwnd, uMsg, wParam, lParam);
}
