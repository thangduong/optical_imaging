#if !defined(AFX_NEWCAMERADLG_H__E52ECE6D_D700_11D2_B537_00A0C99ACB20__INCLUDED_)
#define AFX_NEWCAMERADLG_H__E52ECE6D_D700_11D2_B537_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewCameraDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewCameraDlg dialog

class CNewCameraDlg : public CDialog
{
// Construction
public:
	CString GetCamName(CString &strCamName);
	CNewCameraDlg(CWnd* pParent = NULL, PCICapMod pICap = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewCameraDlg)
	enum { IDD = IDD_NEW_CAMERA };
	CButton	m_buttonIDOK;
	CString	m_strNewCameraName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewCameraDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewCameraDlg)
	afx_msg void OnChangeEditNewCameraName();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	PCICapMod m_pICap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWCAMERADLG_H__E52ECE6D_D700_11D2_B537_00A0C99ACB20__INCLUDED_)
