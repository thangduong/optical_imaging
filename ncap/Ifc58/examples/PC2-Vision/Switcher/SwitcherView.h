// SwitcherView.h : interface of the CSwitcherView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWITCHERVIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_SWITCHERVIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CSwitcherView;
#include "SwitcherDoc.h"
#include <ifc.h>

#include "Trgthrd.h"


class CSwitcherView : public CView
{
protected: // create from serialization only
	CSwitcherView();
	DECLARE_DYNCREATE(CSwitcherView)

// Attributes
public:
	CSwitcherDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitcherView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSwitcherView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	CTrgThrd *m_trgThread;
	DWORD m_viewID;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSwitcherView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SwitcherView.cpp
inline CSwitcherDoc* CSwitcherView::GetDocument()
   { return (CSwitcherDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHERVIEW_H__9AFEEA65_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
