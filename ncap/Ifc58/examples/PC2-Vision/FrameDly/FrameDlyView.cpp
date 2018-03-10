// FrameDlyView.cpp : implementation of the CFrameDlyView class
//

#include "stdafx.h"
#include "FrameDly.h"

#include "FrameDlyDoc.h"
#include "FrameDlyView.h"
#include "Dlgsnap.h"
#include "CamSwitchM.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyView

IMPLEMENT_DYNCREATE(CFrameDlyView, CView)

BEGIN_MESSAGE_MAP(CFrameDlyView, CView)
	//{{AFX_MSG_MAP(CFrameDlyView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_FRAMEDELAYSNAP, OnFrameDelaySnap)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyView construction/destruction

CFrameDlyView::CFrameDlyView()
{

	m_ImgConn = NULL;
	m_trigSrc = IFC_SOFT_TRIG;
	m_numCameras = 2;
}

CFrameDlyView::~CFrameDlyView()
{
	if (m_ImgConn) {
		delete m_ImgConn;
	}
}


BOOL CFrameDlyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFrameDlyView drawing

void CFrameDlyView::OnDraw(CDC* pDC)
{
	CFrameDlyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CFrameDlyView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	CFrameDlyApp *theapp=(CFrameDlyApp*)AfxGetApp();	
	CICapMod	*pMod = theapp->m_pMod;
	if (pMod) {
		m_ImgConn = IfxCreateImgConn(theapp->m_cam, m_hWnd,IFC_LIVE_IMAGE ,ICAP_INTR_EOF);
	}

}



void CFrameDlyView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.

	if (m_ImgConn) {
		delete m_ImgConn;
		m_ImgConn = NULL;
	}



   CView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// CFrameDlyView diagnostics

#ifdef _DEBUG
void CFrameDlyView::AssertValid() const
{
	CView::AssertValid();
}

void CFrameDlyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFrameDlyDoc* CFrameDlyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFrameDlyDoc)));
	return (CFrameDlyDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CFrameDlyView message handlers

void CFrameDlyView::CreateImageServer(DWORD Flags)
{
	CFrameDlyApp	*theApp = (CFrameDlyApp*) AfxGetApp();
	CICamera* pCamera = theApp->m_cam;
	CAM_ATTR attr;
	pCamera->GetAttr(&attr);
	
	if(m_ImgConn) {
		DelImageServer();
	}

	pCamera->Freeze();
	pCamera->Grab();
	m_ImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | Flags, ICAP_INTR_EOF);

}


void CFrameDlyView::DelImageServer()
{
	CFrameDlyApp	*theApp = (CFrameDlyApp*) AfxGetApp();

	if(m_ImgConn) {
		delete m_ImgConn;
		m_ImgConn = NULL;
		theApp->m_cam->Freeze();
	}
}



void CFrameDlyView::OnFrameDelaySnap() 
{
	CCamSwitchM camSwitchDlg(P2V_MAX_NUM_CAMERAS,this);
	if(camSwitchDlg.DoModal() == IDOK) {		
		m_numCameras = min( P2V_MAX_NUM_CAMERAS, camSwitchDlg.GetNbCamera());		
		
		for (DWORD i = 0; i < m_numCameras; i++) {
			m_camPortSeq[i] = camSwitchDlg.GetCameraIndex(i) - 1;
		}
		m_trigSrc = (IFC_TRIG_SRC_TYPE)camSwitchDlg.m_trigSrc;
		CDlgsnap dg(this);
		dg.DoModal();
	}
	InvalidateRect(NULL,TRUE);
	
}


