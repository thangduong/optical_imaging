// BlobViewView.h : interface of the CBlobViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOBVIEWVIEW_H__AD5EF091_01EC_11D5_B181_00105A0F576C__INCLUDED_)
#define AFX_BLOBVIEWVIEW_H__AD5EF091_01EC_11D5_B181_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <VnVidSrc.h> 
#include <VnBase.h>

#include "..\Blobob\BlobOb.h"

class CBlobViewDoc;

class CBlobViewView : public CView
{
protected: // create from serialization only
	CBlobViewView();
	DECLARE_DYNCREATE(CBlobViewView)

// Attributes
public:
	CBlobViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBlobViewView)
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

	BOOL m_VideoSrcIsLocal;
	IVideoSrc *m_pICap;
	char m_vidSrcNodeName[80];

	PIImgDisplay m_ImgDisplay;
	PIProcNode m_ImgProc;
	HPROCESSTHREAD m_hSrvThread;
	IBlobAnlz *m_blobObj;
	BlobAnlz *m_BlobDlg;

	DWORD m_avgBlobArea;
	DWORD m_numDetectedBlobs;

	VS_BLOB_DESC_LIST *m_blobList;

public:

	virtual ~CBlobViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBlobViewView)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BlobViewView.cpp
inline CBlobViewDoc* CBlobViewView::GetDocument()
   { return (CBlobViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOBVIEWVIEW_H__AD5EF091_01EC_11D5_B181_00105A0F576C__INCLUDED_)
