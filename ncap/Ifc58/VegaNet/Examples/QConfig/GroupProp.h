#if !defined(AFX_GROUPPROP_H__141EB140_AE3C_11D3_B13D_00105A0F576C__INCLUDED_)
#define AFX_GROUPPROP_H__141EB140_AE3C_11D3_B13D_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GroupProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupProp dialog

class CGroupProp : public CDialog
{
// Construction
public:
	CGroupProp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGroupProp)
	enum { IDD = IDD_GROUP_PROPS };
	CString	m_GroupEnum;
	CString	m_GroupMask;
	CString	m_GroupName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGroupProp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGroupProp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GROUPPROP_H__141EB140_AE3C_11D3_B13D_00105A0F576C__INCLUDED_)
