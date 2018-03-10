/******************************************************************************
 *
 * MODULE
 *    LargeAcqView.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PiPAcq/LargeAcqView.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/22/99 3:37p $
 *
 * ABSTRACT
 *    PCDig Large Frame Acquisition Example Program
 *	This program shows how the PCDig can be used to acquire very large frames.
 *  To see the power of this program use a line scan camera and set the image height
 *  to a large value, e.g.,
 *  HEIGHT_PIXELS = 8192
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_LARGEACQVIEW_H__EF37B471_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
#define AFX_LARGEACQVIEW_H__EF37B471_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CLargeAcqView;
#include "LargeAcqDoc.h"
#include <ifc.h>
#include "TrgThrd.h"
#include "Dlgsnap.h"



class CLargeAcqView : public CScrollView
{
protected: // create from serialization only
	CLargeAcqView();
	DECLARE_DYNCREATE(CLargeAcqView)

// Attributes
public:
	CLargeAcqDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLargeAcqView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BYTE *m_pImgBuff;
	BYTE *m_pHostBuffFrame;
	CImgConn *m_hImgConn;
	CImgSrc *m_hImgSrc;
	CImgSink *m_hSinkTemplate;
	CImgSink *m_hImgSink;
	CTrgThrd *m_grabThread;
	SINK_KIND m_DrawMode;
	DWORD m_FrameSize;
	DWORD m_numFramesInHostBuf;
	CDlgsnap *m_SnapDialog;

	virtual ~CLargeAcqView();
	void ColorFillCDC(COLORREF color, CDC * pCDC);

	void StopGrab(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif



protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLargeAcqView)
	afx_msg void OnDestroy();
	afx_msg void OnAcquireGrab();
	afx_msg void OnAcquireSnap();
	afx_msg void OnAcquireFreeze();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LargeAcqView.cpp
inline CLargeAcqDoc* CLargeAcqView::GetDocument()
   { return (CLargeAcqDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LARGEACQVIEW_H__EF37B471_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
