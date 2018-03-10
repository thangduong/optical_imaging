// ConfiguratorView.h : interface of the CConfiguratorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFIGURATORVIEW_H__5F5B5B3B_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
#define AFX_CONFIGURATORVIEW_H__5F5B5B3B_C772_11D2_B530_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConfiguratorDoc.h"
#include <VnVidSrc.h> 
#include <VnBase.h>
#include <VnImgCon.h>


class CConfiguratorView : public CScrollView
{
protected: // create from serialization only
	CConfiguratorView();
	DECLARE_DYNCREATE(CConfiguratorView)

// Attributes
public:
	CConfiguratorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfiguratorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateDisplay();
	void DeleteDisplay();
	BOOL m_VideoSrcIsLocal;
	virtual ~CConfiguratorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	VS_PARAM_GROUP_TYPE m_currentSelectedGroup;
	IVideoSrc *m_vidSrc;
	char m_vidSrcNodeName[80];
	IImgDisplay *m_nodeDisplay;
	PIVideoStream m_vStream;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CConfiguratorView)
	afx_msg void OnEditConfig();
	afx_msg void OnDestroy();
	afx_msg void OnEditTransform();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in ConfiguratorView.cpp
inline CConfiguratorDoc* CConfiguratorView::GetDocument()
   { return (CConfiguratorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGURATORVIEW_H__5F5B5B3B_C772_11D2_B530_00A0C99ACB20__INCLUDED_)
