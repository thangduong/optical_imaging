#if !defined(AFX_SETCPORT_H__D6312843_86B9_11D5_B1E9_00105A0F576C__INCLUDED_)
#define AFX_SETCPORT_H__D6312843_86B9_11D5_B1E9_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetCPort.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetCPort dialog

class CSetCPort : public CDialog
{
// Construction
public:
	CSetCPort(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetCPort)
	enum { IDD = IDD_SETCOMPORT };
	UINT	m_commNum;
	CString	m_comPortName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetCPort)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetCPort)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETCPORT_H__D6312843_86B9_11D5_B1E9_00105A0F576C__INCLUDED_)
