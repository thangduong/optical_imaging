#if !defined(AFX_DLGWIN_H__1D9E3B82_5068_11D1_AE4E_00A0C959E757__INCLUDED_)
#define AFX_DLGWIN_H__1D9E3B82_5068_11D1_AE4E_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlgwin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgwin dialog

class CDlgwin : public CDialog
{
// Construction
public:
	CDlgwin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgwin)
	enum { IDD = IDD_DLGWIN };
	UINT	m_dx;
	UINT	m_dy;
	int		m_x;
	UINT	m_y;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgwin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgwin)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIN_H__1D9E3B82_5068_11D1_AE4E_00A0C959E757__INCLUDED_)
