// Grab3View.h : interface of the CGrab3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAB3VIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_GRAB3VIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGrab3View;
#include "Grab3Doc.h"
#include <ifc.h>

#include "Trgthrd.h"


class CGrab3View : public CView
{
protected: // create from serialization only
	CGrab3View();
	DECLARE_DYNCREATE(CGrab3View)

// Attributes
public:
	CGrab3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrab3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGrab3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	CTrgThrd *m_trgThread;
	DWORD m_viewID;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGrab3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Grab3View.cpp
inline CGrab3Doc* CGrab3View::GetDocument()
   { return (CGrab3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAB3VIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
