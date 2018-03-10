#if !defined(AFX_NOTAPPL_H__943B26D6_B489_11D3_B147_00105A0F576C__INCLUDED_)
#define AFX_NOTAPPL_H__943B26D6_B489_11D3_B147_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NotAppl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNotAppl dialog

class CNotAppl : public CDialog
{
// Construction
public:
	CNotAppl(CWnd* pParent , CString item, char *reason=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNotAppl)
	enum { IDD = IDD_NOT_APPL };
	CString	m_ReasonNotApplicable;
	CString	m_ItemName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNotAppl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNotAppl)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOTAPPL_H__943B26D6_B489_11D3_B147_00105A0F576C__INCLUDED_)
