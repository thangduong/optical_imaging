#if !defined(AFX_CONVPROG_H__73153A39_0DFE_4301_BA20_5338E56057D6__INCLUDED_)
#define AFX_CONVPROG_H__73153A39_0DFE_4301_BA20_5338E56057D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConvProg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvProg dialog

class CConvProg : public CDialog
{
// Construction
public:
	CConvProg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConvProg)
	enum { IDD = IDD_DG_CONV_PROGRESS };
	CString	m_convText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_cancelRequested;
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvProg)
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVPROG_H__73153A39_0DFE_4301_BA20_5338E56057D6__INCLUDED_)
