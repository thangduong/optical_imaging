// CDialog.cpp: implementation of the CDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "CDialog.h"
#include "CWinApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog::CDialog()
{
	m_hWnd = NULL;
	m_dwDlgFlags = 0;
}

CDialog::~CDialog()
{

}

bool CDialog::DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	bool bResult = false;
	/*
	if ((uMsg == WM_INITDIALOG) && (m_dwDlgFlags))
	{
		SHINITDLGINFO	shidi;
		memset(&shidi, 0, sizeof(SHINITDLGINFO));
		shidi.dwMask = SHIDIM_FLAGS;
		shidi.dwFlags = m_dwDlgFlags; //SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
		shidi.hDlg = hwndDlg;

		SHInitDialog(&shidi);
		::SetForegroundWindow(hwndDlg);

		bResult = true;
	}
	// we're not using SIP (it's WinCE only)
	*/
	return bResult;
}

bool CDialog::CreateIndirect(UINT nID, CWnd* pParent)
{
	// load resource as necessary
	LPCDLGTEMPLATE lpDialogTemplate;
	HGLOBAL hDialogTemplate;
	HINSTANCE hInst = CWinApp::GetApp()->GetHinstance();
	HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(nID), RT_DIALOG);
	
	hDialogTemplate = LoadResource(hInst, hResource);
	lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);

	HWND hParent = NULL;
	if (pParent)
		hParent = pParent->GetHwnd();
	m_hWnd = CreateDialogIndirectParam(hInst, lpDialogTemplate, hParent, CWinApp::DialogProc, (LPARAM)this);

	return (m_hWnd) ? true : false;
}

HWND CDialog::GetHwnd()
{
	return m_hWnd;
}

bool CDialog::DestroyWindow()
{
	return ::DestroyWindow(m_hWnd) ? true : false;
}

int CDialog::DoModal(UINT nID, CWnd* pParent)
{
	// load resource as necessary
	LPCDLGTEMPLATE lpDialogTemplate;
	HGLOBAL hDialogTemplate;
	HINSTANCE hInst = CWinApp::GetApp()->GetHinstance();
	HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(nID), RT_DIALOG);
	
	hDialogTemplate = LoadResource(hInst, hResource);
	lpDialogTemplate = (LPCDLGTEMPLATE)LockResource(hDialogTemplate);

	HWND hParent = NULL;
	if (pParent)
		hParent = pParent->GetHwnd();

	return DialogBoxIndirectParam(
		hInst, lpDialogTemplate,
		hParent, CWinApp::DialogProc,
		(LPARAM)this);
}

int CDialog::DoModal(DLGTEMPLATE* pTemplate, CWnd* pParent)
{
	// load resource as necessary
	HINSTANCE hInst = CWinApp::GetApp()->GetHinstance();
	
	HWND hParent = NULL;
	if (pParent)
		hParent = pParent->GetHwnd();

	return DialogBoxIndirectParam(
		hInst, pTemplate,
		hParent, CWinApp::DialogProc,
		(LPARAM)this);
}


int CDialog::EndDialog(int nResult)
{
	return ::EndDialog(GetHwnd(), nResult);
}

HWND CDialog::GetDlgItem(int nIDDlgItem)
{
	return ::GetDlgItem(GetHwnd(), nIDDlgItem);
}


void CDialog::GetClientRect(RECT* r)
{
	::GetClientRect(GetHwnd(), r);
}

void CDialog::GetWindowRect(RECT* r)
{
	::GetWindowRect(GetHwnd(), r);
}

bool CDialog::ShowWindow(int nCmdShow)
{
	return ::ShowWindow(GetHwnd(), nCmdShow) ? true : false;
}

bool CDialog::MoveWindow(int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
	return ::MoveWindow(GetHwnd(), X, Y, nWidth, nHeight, bRepaint) ? true : false;
}

bool CDialog::EnableWindow(bool bEnable)
{
	return ::EnableWindow(GetHwnd(), bEnable) ? true : false;
}



