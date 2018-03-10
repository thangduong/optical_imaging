// CWinioinstallDlg.h : header file
//

#if !defined(AFX_CWINIOINSTALLDLG_H__C61A2437_3286_4DC0_AD6C_63B49D79D1A7__INCLUDED_)
#define AFX_CWINIOINSTALLDLG_H__C61A2437_3286_4DC0_AD6C_63B49D79D1A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinioinstallDlg dialog

class CWinioinstallDlg : public CDialog
{
// Construction
public:
	CWinioinstallDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinioinstallDlg)
	enum { IDD = IDD_WINIOINSTALL_DIALOG };
	CString	m_WinIoSys;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinioinstallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinioinstallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnInstall();
	afx_msg void OnRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CWINIOINSTALLDLG_H__C61A2437_3286_4DC0_AD6C_63B49D79D1A7__INCLUDED_)
