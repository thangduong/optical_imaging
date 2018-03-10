#if !defined(AFX_XFORM_H__F2F30173_533A_11D4_B112_00105A0F576C__INCLUDED_)
#define AFX_XFORM_H__F2F30173_533A_11D4_B112_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// xform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransform dialog

class CTransform : public CDialog
{
// Construction
public:
	CTransform(CWnd* pParent = NULL, IVideoSrc *cam=NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTransform)
	enum { IDD = IDD_TRANSFORM };
	CButton	m_ctlRot180;
	CButton	m_ctlMirror;
	CButton	m_ctlFlip;
	int		m_Transform;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	IVideoSrc *m_cam;
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransform)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XFORM_H__F2F30173_533A_11D4_B112_00105A0F576C__INCLUDED_)
