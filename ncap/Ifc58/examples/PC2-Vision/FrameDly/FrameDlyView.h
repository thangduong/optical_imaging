// FrameDlyView.h : interface of the CFrameDlyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEDLYVIEW_H__340AE263_4DBA_4015_BAF8_561CD1ED1E01__INCLUDED_)
#define AFX_FRAMEDLYVIEW_H__340AE263_4DBA_4015_BAF8_561CD1ED1E01__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CFrameDlyView;
#include "FrameDlyDoc.h"
#include <ifc.h>
#include <PCVision2.h>



class CFrameDlyView : public CView
{
protected: // create from serialization only
	CFrameDlyView();
	DECLARE_DYNCREATE(CFrameDlyView)

// Attributes
public:
	CFrameDlyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameDlyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFrameDlyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	void DelImageServer();
	void CreateImageServer(DWORD Flags=0);

	CImgConn *m_ImgConn;

	DWORD m_camPortSeq[P2V_MAX_NUM_CAMERAS];
	DWORD m_numCameras;
	IFC_TRIG_SRC_TYPE m_trigSrc;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFrameDlyView)
	afx_msg void OnDestroy();
	afx_msg void OnFrameDelaySnap();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FrameDlyView.cpp
inline CFrameDlyDoc* CFrameDlyView::GetDocument()
   { return (CFrameDlyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEDLYVIEW_H__340AE263_4DBA_4015_BAF8_561CD1ED1E01__INCLUDED_)
