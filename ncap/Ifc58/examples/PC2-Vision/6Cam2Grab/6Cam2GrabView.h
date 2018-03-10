// 6Cam2GrabView.h : interface of the C6Cam2GrabView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_6CAM2GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_)
#define AFX_6CAM2GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class C6Cam2GrabView;
#include "6Cam2GrabDoc.h"
#include <ifc.h>

#include "Trgthrd.h"


class C6Cam2GrabView : public CView
{
protected: // create from serialization only
	C6Cam2GrabView();
	DECLARE_DYNCREATE(C6Cam2GrabView)

// Attributes
public:
	C6Cam2GrabDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C6Cam2GrabView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C6Cam2GrabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	CImgConn *m_imgConn;
	DWORD m_viewID;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(C6Cam2GrabView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 6Cam2GrabView.cpp
inline C6Cam2GrabDoc* C6Cam2GrabView::GetDocument()
   { return (C6Cam2GrabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_6CAM2GRABVIEW_H__F27003F7_180D_413A_8029_267C4482C94A__INCLUDED_)
