#include "CWnd.h"
#include "CWinApp.h"
#include "CDialog.h"

CWnd::CWnd()
{
	m_hWnd = NULL;
}

CWnd::~CWnd()
{
}

LRESULT CWnd::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef _AUTO_SIP_REACTION
	switch(uMsg)
	{
	case WM_CREATE:
		memset (&m_SipInfo, 0, sizeof(m_SipInfo));
		m_SipInfo.cbSize = sizeof(m_SipInfo);		
		SHHandleWMSettingChange (hwnd, wParam, lParam, &m_SipInfo);
		break;

	case WM_SETTINGCHANGE:
//	case WM_WININICHANGE:
//		switch (wParam) {
//		case SIP_SETSIPINFO:
			SHHandleWMSettingChange (hwnd, wParam, lParam, &m_SipInfo);
//			break;
//		}
		break;

	case WM_ACTIVATE:
		SHHandleWMActivate (hwnd, wParam, lParam, &m_SipInfo, 0);
		break;
	}
#endif
	// do nothing
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool CWnd::Create(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CWnd* pParent, HMENU hMenu)
{
	if (pParent)
		m_hWnd = CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, pParent->GetHwnd(), hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	else
		m_hWnd = CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, 0, hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	return (m_hWnd != 0) ? true : false;
}


bool CWnd::Create(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CDialog* pParent, HMENU hMenu)
{
	if (pParent)
		m_hWnd = CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, pParent->GetHwnd(), hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	else
		m_hWnd = CreateWindow(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, 0, hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	return (m_hWnd != 0) ? true : false;
}

bool CWnd::CreateEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, 
							int nWidth, int nHeight, CWnd* pParent, HMENU hMenu)
{
	if (pParent)
		m_hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, 
							nWidth, nHeight, pParent->GetHwnd(), hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	else
		m_hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, 
							nWidth, nHeight, NULL, hMenu, CWinApp::GetApp()->GetHinstance(), (void*)this);
	return (m_hWnd != 0) ? true : false;
}


HWND CWnd::GetHwnd()
{
	return m_hWnd;
}

bool CWnd::DestroyWindow()
{
	return ::DestroyWindow(GetHwnd()) ? true : false;
}

void CWnd::GetClientRect(RECT* r)
{
	::GetClientRect(GetHwnd(), r);
}

void CWnd::GetWindowRect(RECT* r)
{
	::GetWindowRect(GetHwnd(), r);
}

bool CWnd::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(GetHwnd(), nCmdShow) ? true : false;
}

bool CWnd::MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
	return ::MoveWindow(GetHwnd(), X, Y, nWidth, nHeight, bRepaint) ? true : false;
}

bool CWnd::EnableWindow(bool bEnable)
{
	return ::EnableWindow(GetHwnd(), bEnable) ? true : false;
}

bool CWnd::UpdateWindow()
{
	return ::UpdateWindow(GetHwnd()) ? true : false;
}

bool CWnd::SetWindowText(LPCTSTR text)
{
	return ::SetWindowText(GetHwnd(), text) ? true :false;
}

HWND CWnd::SetFocus()
{
	return ::SetFocus(GetHwnd());
}

LRESULT CWnd::SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(GetHwnd(), Msg, wParam, lParam);
}

LRESULT CWnd::SendMessage(HWND hwnd,UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return ::SendMessage(hwnd, Msg, wParam, lParam);
}

bool CWnd::InvalidateRect(const RECT* lpRect, bool erase)
{
	return ::InvalidateRect(GetHwnd(), lpRect, erase);
}
