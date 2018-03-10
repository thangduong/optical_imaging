// ImgProcView.cpp : implementation of the CImgProcView class
//

#include "stdafx.h"
#include "ImgProc.h"
#include "ChildFrm.h"

#include "ImgProcDoc.h"
#include "ImgProcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgProcView

IMPLEMENT_DYNCREATE(CImgProcView, CView)

BEGIN_MESSAGE_MAP(CImgProcView, CView)
	//{{AFX_MSG_MAP(CImgProcView)
	ON_COMMAND(ID_LUT_INVERT, OnLutInvert)
	ON_COMMAND(ID_LUT_LINEAR, OnLutLinear)
	ON_COMMAND(ID_DELTA, OnDelta)
	ON_COMMAND(ID_MIRROR, OnMirror)
	ON_MESSAGE(ID_MSG_CAMCHANGE, OnMsgCamChange)
	ON_MESSAGE(ID_MSG_SELCAM,	 OnMsgSelCam)
	ON_MESSAGE(ID_MSG_ALLOCERROR,	OnMsgAllocError)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgProcView construction/destruction

CImgProcView::CImgProcView()
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	m_ID		= theApp->GetID();
	m_trgThread = NULL;
	m_bInvert	= FALSE;
	m_bDelta	= FALSE;
	m_bMirror	= FALSE;

	// TODO: add construction code here
}

CImgProcView::~CImgProcView()
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	if(m_trgThread)
	{ 
		delete m_trgThread;
		m_trgThread =  NULL;
		theApp->m_anyTrigThread--;
	}

	theApp->ReturnID(m_ID);
}


BOOL CImgProcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImgProcView drawing

void CImgProcView::OnDraw(CDC* pDC)
{
	CImgProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CImgProcView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();
	CImgProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	theApp->m_hThreads[m_ID] = m_hWnd;

	if(theApp->m_pMod)
	{
		BOOL flag = TRUE;

		theApp->m_dwWidth[m_ID]		= (DWORD) theApp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
		theApp->m_dwHeight[m_ID]	= (DWORD) theApp->m_cam->GetAcqParam(P_HEIGHT_PIXELS);

		CAM_ATTR attr;
		theApp->m_cam->GetAttr(&attr);

		DWORD dwFrameSize  = theApp->m_dwWidth[m_ID] * theApp->m_dwHeight[m_ID] * attr.dwBytesPerPixel;
		DWORD dwImgBufSize = dwFrameSize * FRAMES_IN_HOSTBUFF;
		MEMORYSTATUS memstat;
		GlobalMemoryStatus(&memstat);

		if((dwImgBufSize + (2*dwFrameSize)) > (memstat.dwTotalPhys-0x800000))
		{
			MessageBox("You don't have enough memory for this operation.", "Memory Error");
			::DestroyWindow(m_hWnd);
		}
		else if((dwImgBufSize + (2*dwFrameSize)) > memstat.dwAvailPhys)
		{
			if(MessageBox("Page swapping will have to occur for this operation to complete, "
				" this could take several minutes. Are you sure you want to continue?",
				"Memory Alert", MB_OKCANCEL) == IDCANCEL )
			{
				::DestroyWindow(m_hWnd);
			}

		}

		if(m_trgThread)
		{
			delete m_trgThread;
			m_trgThread = NULL;
			theApp->m_anyTrigThread--;
		}

		m_trgThread = new CTrgThrd(this, m_ID);
		theApp->m_anyTrigThread++;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CImgProcView printing

BOOL CImgProcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgProcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgProcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void CImgProcView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.


	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
		theApp->m_anyTrigThread--;
	}

	CView::OnDestroy();

}


/////////////////////////////////////////////////////////////////////////////
// CImgProcView diagnostics

#ifdef _DEBUG
void CImgProcView::AssertValid() const
{
	CView::AssertValid();
}

void CImgProcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgProcDoc* CImgProcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgProcDoc)));
	return (CImgProcDoc*)m_pDocument;
}
#endif //_DEBUG



/////////////////////////////////////////////////////////////////////////////
// CImgProcView message handlers

LRESULT CImgProcView::OnMsgCamChange(WPARAM wParam, LPARAM lParam)
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	// Delete any pre-existing trigger thread
	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
		theApp->m_anyTrigThread--;
	}

	return 0;
}

LRESULT CImgProcView::OnMsgSelCam(WPARAM wParam, LPARAM lParam)
{
	CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();

	// Delete any pre-existing trigger thread
	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
		theApp->m_anyTrigThread--;
	}

	if(wParam)
	{
		m_bInvert = FALSE;
		m_bDelta  = FALSE;
		theApp->m_dwWidth[m_ID]		= (DWORD) theApp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
		theApp->m_dwHeight[m_ID]	= (DWORD) theApp->m_cam->GetAcqParam(P_HEIGHT_PIXELS);
	}

	m_trgThread = new CTrgThrd(this, m_ID);
	theApp->m_anyTrigThread++;

	return 0;
}

LRESULT CImgProcView::OnMsgAllocError(WPARAM wParam, LPARAM lParam)
{
	char str[80];
	wsprintf(str, "Thread No. %d", m_ID);

	if(wParam)
	{
		MessageBox("You don't have enough memory to perform Delta operation or Mirror Image on this thread\nDelta operation and Mirror Image are disabled on the this thread", str);
	}
	else
	{
		CImgProcApp *theApp = (CImgProcApp*) AfxGetApp();
		MessageBox("You don't have enough memory for any more threads", str);
		if(m_trgThread)
		{
			delete m_trgThread;
			m_trgThread = NULL;
			theApp->m_anyTrigThread--;
		}

		::DestroyWindow(m_hWnd);
	}

	return 0;
}


void CImgProcView::OnLutInvert() 
{
	m_bInvert	= TRUE;
	m_bDelta	= FALSE;
}

void CImgProcView::OnLutLinear() 
{
	m_bInvert	= FALSE;
	m_bDelta	= FALSE;
}

void CImgProcView::OnDelta() 
{
	m_bInvert	= FALSE;
	m_bMirror	= FALSE;

	CChildFrame* pChildFrm = (CChildFrame*) GetParent();

	RECT rect;
	int iIndex = pChildFrm->m_wndToolBar.CommandToIndex(ID_MIRROR);
	pChildFrm->m_wndToolBar.GetItemRect(iIndex, &rect);
	pChildFrm->m_wndToolBar.InvalidateRect(&rect, TRUE);
	pChildFrm->m_wndToolBar.LoadBitmap(IDB_BITMAP1);

	m_bDelta	= !m_bDelta;
}

void CImgProcView::OnMirror() 
{
	m_bDelta	= FALSE;
	m_bMirror	= !m_bMirror;

	CChildFrame* pChildFrm = (CChildFrame*) GetParent();

	if(m_bMirror)
	{
		pChildFrm->m_wndToolBar.LoadBitmap(IDB_BITMAP2);
	}
	else
	{
		pChildFrm->m_wndToolBar.LoadBitmap(IDB_BITMAP1);
	}
}
