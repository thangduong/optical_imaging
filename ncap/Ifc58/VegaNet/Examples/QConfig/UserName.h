#if !defined(AFX_USERNAME_H__9899BEA3_9EA8_11D4_B152_00105A0F576C__INCLUDED_)
#define AFX_USERNAME_H__9899BEA3_9EA8_11D4_B152_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserName dialog

class CUserName : public CDialog
{
// Construction
public:
	CUserName(CWnd* pParent = NULL, LPTSTR nodeName=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CUserName)
	enum { IDD = IDD_USERNAME };
	CString	m_Domain;
	CString	m_password;
	CString	m_UserName;
	CString	m_NodeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserName)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERNAME_H__9899BEA3_9EA8_11D4_B152_00105A0F576C__INCLUDED_)
