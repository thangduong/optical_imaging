/********************************************************************
 *
 * MODULE
 *    overlayv.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/Overlay/overlayv.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/16/01 9:33a $
 *
 * ABSTRACT
 *    IFC Overlay example program file
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999-2001, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/

// overlayv.h : interface of the COverlayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OVERLAYVIEW_H__ECEE69FC_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
#define AFX_OVERLAYVIEW_H__ECEE69FC_3E85_11D1_A000_00A0246D9D39__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class COverlayView;

#include <VnVidSrc.h> 
#include <VnBase.h>
#include <VnImgCon.h>

#include "overlayd.h"
#include "procthrd.h"

class COverlayView : public CScrollView
{
protected: // create from serialization only
	COverlayView();
	DECLARE_DYNCREATE(COverlayView)

// Attributes
public:
	COverlayDoc* GetDocument();
	BOOL m_bErrorConfiguring;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COverlayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	IImgDisplay *GetConnection() { return m_nodeDisplay;};
	virtual ~COverlayView();
	void InitiateGrabWithOverlay();
	void KillOpenConnections();
	void RestartConnection();
	void CalculateZoomVal(float *pfZoomX, float *pfZoomY);
	void DeletePenAndBrush();
	void DeleteTransparentPenAndBrush();
	void ReCreatePenAndBrush();
	void ReCreateTransparentPenAndBrush();
	void SetScrollLimits();
	void RepaintOverlay(CDC *pOverlayDC, float fZoomX, float fZoomY);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COverlayView)
	afx_msg void OnOverlaySoftware();
	afx_msg void OnZoomStretchToFit();
	afx_msg void OnZoom2();
	afx_msg void OnZoom1();
	afx_msg void OnDrawingRectangle();
	afx_msg void OnDrawingCircle();
	afx_msg void OnDrawingText();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawingNone();
	afx_msg void OnImagesourceFrame();
	afx_msg void OnImagesourceHostbuff();
	afx_msg void OnOverlaydrawingFreedrawing();
	afx_msg void OnZoom05();
	afx_msg void OnOverlayOnPrimary();
	afx_msg void OnOverlayPrimaryRemap();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClearoverlay();
	afx_msg void OnColorChange(UINT);
	afx_msg void OnDestroy();
	afx_msg void OnImageSourceImgnode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void CleanAllOpen();
	void ColorFillCDC(COLORREF color, CDC *pCDC);
	void ResizeClientArea();
	void SetClientWndSize(int iWidth, int iHeight);

public:
	DWORD    m_nCurdx;
	DWORD	m_nCurdy;
	VS_CAM_ATTR m_camAttrib;
	IVideoSrc *m_vidSrc;
	BOOL m_VideoSrcIsLocal;
	PIVideoStream m_vStream;

	IImgDisplay *m_nodeDisplay;
	PROCTHRD *m_procthrd;
	HVSGRAB m_grabID;

	HANDLE m_hThread;
	HMETAFILE m_hMeta;
	BYTE *m_pBuffer;
	DWORD m_numImgAreas;	
	CPen *m_pPen;
	CPen *m_pScalledPen;
	CPen	*m_pPen1;
	CBrush	*m_pBrush;
	COlayElem *m_pCurrentElem;
	CPoint  m_LButtonDownPoint;
	CPoint  m_LastMousePoint;
	BOOL	m_bDrawingActive;
	int		m_iLineThickness;
	COLORREF	m_CurrentColor;
	COLORREF	m_TransparentColor;
	CPen	*m_pTransparentThickPen;
	CPen	*m_pTransparentPen;
	CBrush	*m_pTransparentBrush;

private:

};

#ifndef _DEBUG  // debug version in overlayView.cpp
inline COverlayDoc* COverlayView::GetDocument()
   { return (COverlayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERLAYVIEW_H__ECEE69FC_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
