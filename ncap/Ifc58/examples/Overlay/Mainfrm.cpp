/********************************************************************
 *
 * MODULE
 *    MainFrm.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/overlay/MAINFRM.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 5/04/01 4:44p $
 *
 * ABSTRACT
 *    IFC Overlay example program
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "overlay.h"
#include "overlayv.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern STATIC_COLOR CurrentColorEnum;
extern ZOOM nImageZoom; 
extern int nUsedOverlay;
extern int nRemapActive;
extern int nDrawingMode;
extern int nImageSource;


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_SOFTWARE, OnUpdateOverlaySoftware)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_OVERLAYONPRIMARY, OnUpdatePrimary)
	ON_UPDATE_COMMAND_UI(ID_OVERLAY_PRIMARY_REMAP, OnUpdatePrimaryRemap)
	ON_UPDATE_COMMAND_UI(ID_DRAWING_CIRCLE, OnUpdateDrawingCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAWING_NONE, OnUpdateDrawingNone)
	ON_UPDATE_COMMAND_UI(ID_DRAWING_RECTANGLE, OnUpdateDrawingRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAWING_TEXT, OnUpdateDrawingText)
	ON_UPDATE_COMMAND_UI(ID_IMAGESOURCE_FRAME, OnUpdateImagesourceFrame)
	ON_UPDATE_COMMAND_UI(ID_IMAGESOURCE_HOSTBUFF, OnUpdateImagesourceHostbuff)
	ON_UPDATE_COMMAND_UI(ID_OVERLAYDRAWING_FREEDRAWING, OnUpdateOverlaydrawingFreedrawing)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLORS_TRANSPARENT, ID_COLORS_WHITE, OnUpdateColors)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_ITXSTRETCHTOFIT, OnUpdateZoomItxstretchtofit)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_2, OnUpdateZoom2)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_1, OnUpdateZoom1)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_05, OnUpdateZoom05)
	ON_WM_GETMINMAXINFO()
	ON_UPDATE_COMMAND_UI(ID_SOFTWAREOVERLAYWITHREMAP, OnUpdateSoftwareOverlayWithRemap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnUpdateOverlaySoftware(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nUsedOverlay == SOFTWARE_OVERLAY && nRemapActive==0);
}

void CMainFrame::OnUpdatePrimary(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nUsedOverlay == YCRCB_OVERLAY && nRemapActive==0);
}

void CMainFrame::OnUpdatePrimaryRemap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nUsedOverlay == YCRCB_OVERLAY && nRemapActive==1 );
}

void CMainFrame::OnUpdateSoftwareOverlayWithRemap(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(nUsedOverlay == SOFTWARE_OVERLAY  && nRemapActive==1);	
}

void CMainFrame::OnUpdateDrawingCircle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nDrawingMode == ELLIPSE);
}

void CMainFrame::OnUpdateDrawingNone(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nDrawingMode == NONE);
}

void CMainFrame::OnUpdateDrawingRectangle(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nDrawingMode == RECTANGLE);	
}

void CMainFrame::OnUpdateDrawingText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(nDrawingMode == TEXT);
}

void CMainFrame::OnUpdateOverlaydrawingFreedrawing(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		pCmdUI->SetCheck(nDrawingMode == FREE);
	
}

void CMainFrame::OnUpdateImagesourceFrame(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nImageSource == CAM_IMG_SRC);
}

void CMainFrame::OnUpdateImagesourceHostbuff(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(nImageSource == HOSTBUFF_IMGSRC);
	
}

void CMainFrame::OnUpdateZoomItxstretchtofit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(nImageZoom == STRETCH_TO_FIT);
}

void CMainFrame::OnUpdateZoom2(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(nImageZoom == zoom20);
}

void CMainFrame::OnUpdateZoom1(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(nImageZoom == zoom10);
}

void CMainFrame::OnUpdateZoom05(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(nImageZoom == zoom05);
}

void CMainFrame::OnUpdateColors(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck((unsigned)CurrentColorEnum == pCmdUI->m_nID - ID_COLORS_TRANSPARENT);

	if(pCmdUI->m_nID - ID_COLORS_TRANSPARENT == dark_yellow){
		 if(nUsedOverlay == YCRCB_OVERLAY)
			pCmdUI->SetText("Transparent");
		else
			pCmdUI->SetText("Dark Yellow");
	}

	if(pCmdUI->m_nID - ID_COLORS_TRANSPARENT == transparent){
		if(nUsedOverlay == YCRCB_OVERLAY)
			pCmdUI->SetText("Black");
		else
			pCmdUI->SetText("Transparent");
	}
}

// restrict resizing only to frame size (zoom scalled)
void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	CMDIChildWnd *pChild = (CMDIChildWnd *)GetActiveFrame();
	COverlayView *pView = (COverlayView *) pChild->GetActiveView();

	if(pView && nImageZoom != STRETCH_TO_FIT){
        float fZoomX;
        float fZoomY;
		pView->CalculateZoomVal(&fZoomX, &fZoomY);

		int iViewWidth	= (int)(pView->m_nCurdx * fZoomX);
		int iViewHeight = (int)(pView->m_nCurdy * fZoomY);

		CRect wr;
		CRect cr;
		GetWindowRect(&wr);
		GetClientRect(&cr);
		int iWidthAdjust = wr.right  - wr.left - cr.right  + 2*GetSystemMetrics(SM_CXEDGE);
		int iHeightAdjust = wr.bottom - wr.top  - cr.bottom + 2*GetSystemMetrics(SM_CYEDGE); 

		lpMMI->ptMaxSize.x = lpMMI->ptMaxTrackSize.x = iViewWidth + iWidthAdjust;
		lpMMI->ptMaxSize.y = lpMMI->ptMaxTrackSize.y = iViewHeight + iHeightAdjust;
	}
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

