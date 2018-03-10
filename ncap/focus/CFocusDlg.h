// CFocusDlg.h : header file
//

#if !defined(AFX_CFOCUSDLG_H__954BF745_FA64_4EA5_BF3A_A6B26934A66B__INCLUDED_)
#define AFX_CFOCUSDLG_H__954BF745_FA64_4EA5_BF3A_A6B26934A66B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFocusDlg dialog

class CFocusDlg : public CDialog
{
// Construction
public:
	CFocusDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFocusDlg)
	enum { IDD = IDD_FOCUS_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFocusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFocusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFOCUSDLG_H__954BF745_FA64_4EA5_BF3A_A6B26934A66B__INCLUDED_)
