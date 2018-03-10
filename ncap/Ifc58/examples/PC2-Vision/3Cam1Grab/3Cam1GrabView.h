// 3Cam1GrabView.h : interface of the C3Cam1GrabView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_3CAM1GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_)
#define AFX_3CAM1GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class C3Cam1GrabView;
#include "3Cam1GrabDoc.h"
#include <ifc.h>

#include "Trgthrd.h"


class C3Cam1GrabView : public CView
{
protected: // create from serialization only
	C3Cam1GrabView();
	DECLARE_DYNCREATE(C3Cam1GrabView)

// Attributes
public:
	C3Cam1GrabDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3Cam1GrabView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C3Cam1GrabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	CImgConn *m_imgConn;
	DWORD m_viewID;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C3Cam1GrabView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 3Cam1GrabView.cpp
inline C3Cam1GrabDoc* C3Cam1GrabView::GetDocument()
   { return (C3Cam1GrabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3CAM1GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_)
