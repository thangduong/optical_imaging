/******************************************************************************
 *
 * MODULE
 *    MainFrm.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/MainFrm.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/24/00 12:08p $
 *
 * ABSTRACT
 *    PCVisionplus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_MAINFRM_H__17D20ADA_3064_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_MAINFRM_H__17D20ADA_3064_11D1_AE31_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17D20ADA_3064_11D1_AE31_00A0C959E757__INCLUDED_)
