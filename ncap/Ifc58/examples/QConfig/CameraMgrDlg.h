#if !defined(AFX_CAMERAMGRDLG_H__0E7DB33F_CB2E_11D2_B531_00A0C99ACB20__INCLUDED_)
#define AFX_CAMERAMGRDLG_H__0E7DB33F_CB2E_11D2_B531_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CameraMgrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCameraMgrDlg dialog

class CCameraMgrDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CCameraMgrDlg)

// Construction
public:
	virtual void OnFolderChange();
	CString GetPath(CString &strPath);
	virtual void OnCancel( );


	CCameraMgrDlg(BOOL bOpenFileDialog = TRUE, // TRUE for FileOpen, FALSE for FileSaveAs. Who would want a save with preview?
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		BOOL UserCfg=FALSE);

// Dialog Data
	//{{AFX_DATA(CCameraMgrDlg)
	enum { IDD = IDD_MANAGE_CAMERAS };
	CButton	m_buttonRecursive;
	CButton	m_buttonFilesAsLists;
	CButton	m_buttonAllFiles;
	BOOL	m_bRecursive;
	BOOL	m_bAllFiles;
	BOOL	m_bFilesAsLists;
	BOOL	m_Canceled;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	//}}AFX_VIRTUAL

// Implementation
	BOOL m_UserCfg;
protected:

	// Generated message map functions
	//{{AFX_MSG(CCameraMgrDlg)
	afx_msg void OnRecursive();
	afx_msg void OnAllFiles();
	virtual BOOL OnInitDialog();
	afx_msg void OnFilesAsLists();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SelectAll(BOOL bState = TRUE);

	CString m_strCurPath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMERAMGRDLG_H__0E7DB33F_CB2E_11D2_B531_00A0C99ACB20__INCLUDED_)
