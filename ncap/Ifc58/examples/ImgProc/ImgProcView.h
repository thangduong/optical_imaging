// ImgProcView.h : interface of the CImgProcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMGPROCVIEW_H__C2055DD7_88B3_11D3_A228_005004051D9B__INCLUDED_)
#define AFX_IMGPROCVIEW_H__C2055DD7_88B3_11D3_A228_005004051D9B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CImgProcView;
#include "ImgProcDoc.h"
#include <ifc.h>

#include "Trgthrd.h"


class CImgProcView : public CView
{
protected: // create from serialization only
	CImgProcView();
	DECLARE_DYNCREATE(CImgProcView)

// Attributes
public:

	BOOL m_bInvert;
	BOOL m_bDelta;
	BOOL m_bMirror;

	CImgProcDoc* GetDocument();
	LRESULT OnMsgCamChange(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgSelCam(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgAllocError(WPARAM wParam, LPARAM lParam);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProcView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImgProcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	CTrgThrd *m_trgThread;

protected:
	int m_ID;

// Generated message map functions
protected:
	//{{AFX_MSG(CImgProcView)
	afx_msg void OnLutInvert();
	afx_msg void OnLutLinear();
	afx_msg void OnDelta();
	afx_msg void OnMirror();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImgProcView.cpp
inline CImgProcDoc* CImgProcView::GetDocument()
   { return (CImgProcDoc*)m_pDocument; }
#endif
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROCVIEW_H__C2055DD7_88B3_11D3_A228_005004051D9B__INCLUDED_)
