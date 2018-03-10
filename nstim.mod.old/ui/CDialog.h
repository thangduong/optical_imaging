// CDialog.h: interface for the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CDIALOG_H
#define CDIALOG_H

#include "CWnd.h"
//#include <sipapi.h>

class CDialog  
{
	friend class CWinApp;
protected:
	HWND m_hWnd;
public:
	DWORD m_dwDlgFlags;
public:
	CDialog();
	virtual ~CDialog();

	virtual bool DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual bool CreateIndirect(UINT nID, CWnd* pParent);

	virtual int DoModal(UINT nID, CWnd* pParent = NULL);
	virtual int DoModal(DLGTEMPLATE* pTemplate, CWnd* pParent = NULL);

	HWND GetHwnd();
	virtual bool DestroyWindow();
	virtual int EndDialog(int nResult);
	HWND GetDlgItem(int nIDDlgItem); 


	bool EnableWindow(bool bEnable);

	void GetClientRect(RECT* r);
	void GetWindowRect(RECT* r);
	bool ShowWindow(int nCmdShow);
	bool MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint = TRUE); 

};

#endif // !defined(AFX_CDIALOG_H__A51E9A9E_417C_4C6D_9DCF_69FAC30DC498__INCLUDED_)
