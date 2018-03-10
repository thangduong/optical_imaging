/********************************************************************
 *
 * MODULE
 *    MainFrm.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/mainfrm.h $
 *    $Revision: 1.1 $
 *    $Modtime: 2/09/01 5:55p $
 *
 * ABSTRACT
 *    IFC Overlay example program file
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/

// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__ECEE69F8_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
#define AFX_MAINFRM_H__ECEE69F8_3E85_11D1_A000_00A0246D9D39__INCLUDED_

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

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnUpdateOverlaySoftware(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrimary(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePrimaryRemap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawingCircle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawingNone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawingRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDrawingText(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImagesourceFrame(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImagesourceHostbuff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOverlaydrawingFreedrawing(CCmdUI* pCmdUI);
	afx_msg void OnUpdateColors(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomItxstretchtofit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoom05(CCmdUI* pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnUpdateImageSourceImgnode(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__ECEE69F8_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
