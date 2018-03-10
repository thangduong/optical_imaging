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
	UINT	m_uWidth;
	UINT	m_uHeight;
	int		m_iHOffset;
	int		m_iVOffset;
	int		m_iOrigin;
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
	afx_msg void OnRelative();
	afx_msg void OnAbsolute();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	int m_iRelHOffset;
	int m_iRelVOffset;
	int m_iAbsHOffset;
	int m_iAbsVOffset;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWIN_H__1D9E3B82_5068_11D1_AE4E_00A0C959E757__INCLUDED_)
