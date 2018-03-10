/******************************************************************************
 *
 * MODULE
 *    seqsnapView.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/seqsnapv.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/19/00 5:07p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 * seqsnapView.h : interface of the CSeqsnapView class
 *
 *
 * Copyright (c) 2000-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/



#if !defined(AFX_SEQSNAPVIEW_H__17D20ADE_3064_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_SEQSNAPVIEW_H__17D20ADE_3064_11D1_AE31_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSeqsnapView;
#include "seqsnapD.h"
#include "camsel.h"
#include "procthrd.h"
#include "blobanlz.h"

class CSeqsnapView : public CScrollView
{
protected: // create from serialization only
	CSeqsnapView();
	DECLARE_DYNCREATE(CSeqsnapView)

// Attributes
public:
	CSeqsnapDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeqsnapView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	//}}AFX_VIRTUAL

// Implementation
public:
	static DWORD IFCAPI LutInvert(DWORD arg, DWORD * constants);
	static DWORD IFCAPI LutFloor(DWORD arg ,DWORD *constants);
	void ClearView(void);
	void DelImageServer();
	void CreateImageServer(DWORD Flags=0);
	void SetScrollLimits(void);
	virtual ~CSeqsnapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CImgConn *m_ImgConn;
	CProcessThread *m_rleThread;
	BlobAnlz *m_BlobDlg;
	int m_numSnapAreas;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSeqsnapView)
	afx_msg void OnCmdsSeqsnap();
	afx_msg void OnCmdsTrigops();
	afx_msg void OnCmdsSelectcam();
	afx_msg void OnCmdsReadtiff();
	afx_msg void OnCmdsWritetiff();
	afx_msg void OnCmdsPerformance();
	afx_msg void OnLutInvert();
	afx_msg void OnLutLinear();
	afx_msg void OnLutThresh();
	afx_msg void OnCmdsInport();
	afx_msg void OnCmdsOutport();
	afx_msg void OnCmdsWindowgen();
	afx_msg void OnCmdsHwzoom();
	afx_msg void OnCmdsSwoverlay();
	afx_msg void OnBrdParams();
	afx_msg void OnFlatField();
	afx_msg void OnRleEncodedGrab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in seqsnapView.cpp
inline CSeqsnapDoc* CSeqsnapView::GetDocument()
   { return (CSeqsnapDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQSNAPVIEW_H__17D20ADE_3064_11D1_AE31_00A0C959E757__INCLUDED_)
