#ifndef CWND_H
#define CWND_H

#include <windows.h>

#ifndef _T
#define	_T(x)		(x)
#endif
class CDialog;

#include <commctrl.h>
#ifdef _AUTO_SIP_REACTION
#include <aygshell.h>
#include <sipapi.h>
#endif

class CWnd
{
	friend class CWinApp;
protected:
	HWND m_hWnd;
#ifdef _AUTO_SIP_REACTION
	SHACTIVATEINFO m_SipInfo;
#endif
public: 
	CWnd();
	virtual ~CWnd();


	HWND GetHwnd();
	virtual bool Create(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CDialog* pParent, HMENU hMenu); 
	virtual bool Create(LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, CWnd* pParent, HMENU hMenu); 
	virtual bool CreateEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, 
							int nWidth, int nHeight, CWnd* pParent, HMENU hMenu);
	virtual LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


	virtual bool DestroyWindow();

	bool EnableWindow(bool bEnable);

	void GetClientRect(RECT* r);
	void GetWindowRect(RECT* r);
	bool ShowWindow(int nCmdShow);
	bool MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint = TRUE); 
	bool UpdateWindow();
	bool InvalidateRect(const RECT* lpRect, bool erase);


	bool SetWindowText(LPCTSTR text);
	HWND SetFocus();
	LRESULT SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	static LRESULT SendMessage(HWND hwnd,UINT Msg, WPARAM wParam, LPARAM lParam);
};

#endif