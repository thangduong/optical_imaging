// CWinApp.cpp: implementation of the CWinApp class.
//
//////////////////////////////////////////////////////////////////////

#include "CWinApp.h"
#include "CWnd.h"
#include "CDialog.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinApp::CWinApp(HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nShowCmd)
{
	// TODO: error check!
	m_pTheApp = this;
	m_hInstance = hInstance;
}

void CWinApp::SetParam(HINSTANCE hInstance, HINSTANCE hPrevInstance,
						 LPSTR lpCmdLine, int nShowCmd)
{
	// TODO: error check!
	m_pTheApp = this;
	m_hInstance = hInstance;
}

CWinApp::~CWinApp()
{
	// TODO: error check!
	m_pTheApp = NULL;
}

bool CWinApp::Init()
{
	return false;
}

void CWinApp::MessagePump()
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

int CWinApp::Cleanup()
{	
	return 0;
}

void CWinApp::AddWnd(HWND hwnd, CWnd* pWnd)
{
	m_WndMap.AddPair(hwnd, pWnd);
}

void CWinApp::RemoveWnd(HWND hwnd)
{
	m_WndMap.Remove(hwnd);
}

CWnd* CWinApp::GetWnd(HWND hwnd)
{
	return (CWnd*)m_WndMap.Map(hwnd);
}


LRESULT CALLBACK CWinApp::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT res;
	CWinApp* pTheApp = GetApp();
	CWnd* pWnd;
	LPCREATESTRUCT pcs;
	switch(uMsg)
	{
	case WM_CREATE:
	case WM_NCCREATE:
		pWnd = pTheApp->GetWnd(hwnd);
		if (!pWnd)
		{
			// attach to a class
			pcs = (LPCREATESTRUCT)lParam;
			if (pcs->lpCreateParams)
			{
				// add to map, and relay message
				pWnd = (CWnd*)pcs->lpCreateParams;
				pTheApp->AddWnd(hwnd, pWnd);

				// TODO: should the next line be ther?? -- it keeps the m_hWnd correct
				// on WM_CREATE
				pWnd->m_hWnd = hwnd;
				res = pWnd->WindowProc(hwnd, uMsg, wParam, lParam);
			}
			else
			{
				// look up which class to create.  not necessary yet.
				// res unknown (may cause warning)
			}
			break;
		}
	default:
		// dispatch to the handler of the specific window class
		pWnd = pTheApp->GetWnd(hwnd);
		if (pWnd)
		{
			res = pWnd->WindowProc(hwnd, uMsg, wParam, lParam);
			if (uMsg == WM_DESTROY)
				CWinApp::GetApp()->RemoveWnd(hwnd);
		}
		break;
	}
	return res;
}

HINSTANCE CWinApp::GetHinstance()
{
	return m_hInstance;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// dialog
////////////////////////////////////////////////////////////////////////////////////////////////////
void CWinApp::AddDialog(HWND hwnd, CDialog* pDlg)
{
	m_DlgMap.AddPair(hwnd, pDlg);
}

void CWinApp::RemoveDialog(HWND hwnd)
{
	m_DlgMap.Remove(hwnd);
}

CDialog* CWinApp::GetDialog(HWND hwnd)
{
	return (CDialog*)m_DlgMap.Map(hwnd);
}

BOOL CALLBACK CWinApp::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	BOOL result = FALSE;
	switch(uMsg)
	{
	case WM_INITDIALOG:
		{
		CDialog* pThis = (CDialog*)lParam;
		CWinApp::GetApp()->AddDialog(hwndDlg, pThis);
			// TODO: should the next line be ther?? -- it keeps the m_hWnd correct
			// on WM_INITDIALOG
		pThis->m_hWnd = hwndDlg;
		result = pThis->DialogProc(hwndDlg, uMsg, wParam, lParam);
		}
		break;
	default:
		{
		CDialog* pThis = CWinApp::GetApp()->GetDialog(hwndDlg);
		if (pThis)
			result = pThis->DialogProc(hwndDlg, uMsg, wParam, lParam);
		if (uMsg == WM_DESTROY)
			CWinApp::GetApp()->RemoveDialog(hwndDlg);
		}
		break;
	};
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Singleton pattern implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
CWinApp* CWinApp::m_pTheApp = NULL;
CWinApp* CWinApp::GetApp()
{
	return m_pTheApp;
}



HMENU CWinApp::LoadMenu(LPCTSTR lpMenuName)
{
	return ::LoadMenu(GetHinstance(), lpMenuName);
}

HICON CWinApp::LoadIcon(LPCTSTR lpIconName)
{
	return ::LoadIcon(GetHinstance(), lpIconName);
}

HBITMAP CWinApp::LoadBitmap(LPCTSTR lpBitmapName)
{
	return ::LoadBitmap(GetHinstance(), lpBitmapName);
}

HCURSOR CWinApp::LoadCursor(LPCTSTR lpCursorName)
{
	return ::LoadCursor(GetHinstance(), lpCursorName);
}

void CWinApp::ShowBusyCursor()
{
	HCURSOR hBusyCursor = LoadCursor(IDC_WAIT);

	SetCursor(hBusyCursor);
	ShowCursor(TRUE);
}

void CWinApp::HideBusyCursor()
{
	ShowCursor(FALSE);
	SetCursor(NULL); 
}


CWnd* CWinApp::FindWindow(HWND hWnd)
{
	return GetWnd(hWnd);
}

CDialog* CWinApp::FindDialog(HWND hWnd)
{
	return GetDialog(hWnd);
}
