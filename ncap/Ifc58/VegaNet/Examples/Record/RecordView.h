// RecordView.h : interface of the CMyRecordView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDVIEW_H__DD858F1F_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
#define AFX_RECORDVIEW_H__DD858F1F_962D_11D5_B1ED_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <VnVidSrc.h> 
#include <VnBase.h>
#include "RecordDoc.h"
#include "RndRead.h"
#include "ConvProg.h"

typedef enum {
	R_IDLE,
	R_RECORDING,
	R_PLAYBACK
} R_MODE_TYPE;


class CMyRecordView : public CView
{
protected: // create from serialization only
	CMyRecordView();
	DECLARE_DYNCREATE(CMyRecordView)

// Attributes
public:
	CRecordDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyRecordView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
	BOOL  ProgressUpdate( DWORD numFramesConverted, DWORD totalNumFrames);

	PIImgDisplay m_ImgDisplay;
	R_MODE_TYPE m_mode;
	HBRUSH m_backBrush;
	DWORD m_nTimer;
	DWORD m_randomNumFrames;
	VS_INODE_IMG_ATTR m_imgAttr;

	DWORD	m_maxFileSize;
	BOOL	m_Sound;

	int		m_stop;
	DWORD	m_TimerCount;
	DWORD	m_fileNum;
	CString m_baseFileName;
	CString m_baseFileExt;
	CRndRead *m_rndDialog;
	VS_FRAME_ENCODE m_frameEncode;
	CConvProg *m_progressInd; 
	BOOL m_isYcrcbDisplay;
	BOOL m_pause;

	int		m_quality;

public:
	virtual ~CMyRecordView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyRecordView)
	afx_msg void OnDestroy();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnStop();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnReadRandom();
	afx_msg void OnConvertToAvi();
	afx_msg void OnSetMaxSize();
	afx_msg void OnQueryAviConvert();
	afx_msg void OnPause();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RecordView.cpp
inline CRecordDoc* CMyRecordView::GetDocument()
   { return (CRecordDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDVIEW_H__DD858F1F_962D_11D5_B1ED_00105A0F576C__INCLUDED_)
