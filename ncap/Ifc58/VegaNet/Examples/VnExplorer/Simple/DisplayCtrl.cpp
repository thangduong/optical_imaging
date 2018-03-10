// DisplayCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Simple.h"
#include "DisplayCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define KEY_COLOR_INDEX 3

/////////////////////////////////////////////////////////////////////////////
// CDisplayCtrl

IMPLEMENT_DYNCREATE(CDisplayCtrl, CScrollView)

CDisplayCtrl::CDisplayCtrl()
{
	m_pIVideoSource  = NULL;
	m_pIImageDisplay = NULL;
	m_pIVideoStream  = NULL;

	m_bLocalVideoSource = TRUE;

	m_dwExStyle	= 0;
	m_dwStyle	= WS_CHILD; // Must be a child window.
}

CDisplayCtrl::~CDisplayCtrl()
{
}


BEGIN_MESSAGE_MAP(CDisplayCtrl, CScrollView)
	//{{AFX_MSG_MAP(CDisplayCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//

BOOL CDisplayCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;

	if(!wndStatic.SubclassDlgItem(nID, pParent))
	{
		return FALSE;
	}
	
	RECT rect;

	// Get static control rect and styles, convert rect to parent's client coords.

	wndStatic.GetWindowRect(&rect);

	m_dwStyle	|= GetWindowLong(wndStatic.m_hWnd, GWL_STYLE);
	m_dwExStyle	 = GetWindowLong(wndStatic.m_hWnd, GWL_EXSTYLE);
	
	pParent->ScreenToClient(&rect);
	
	wndStatic.DestroyWindow();

	// Create control
	return Create(NULL,		// Class name
				  NULL,		// Title
				  NULL,		// Style
				  rect,		// Rectangle
				  pParent,	// Parent
				  nID,		// Control ID
				  NULL);	// Frame/doc context not used
}

BOOL CDisplayCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	// Copy static control styles to this control.
	cs.style	 = m_dwStyle;
	cs.dwExStyle = m_dwExStyle;

	cs.lpszClass = AfxRegisterWndClass( NULL,												// Class Styles
										LoadCursor(NULL, IDC_ARROW),						// Arrow Cursor
										CreateSolidBrush(PALETTEINDEX(KEY_COLOR_INDEX)),	// Background Brush
										LoadIcon(NULL, IDI_APPLICATION) );					// Icon (Can be NULL)

	return CScrollView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CDisplayCtrl message handlers

int CDisplayCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if(CScrollView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	OnInitialUpdate();

	return 0;
}

void CDisplayCtrl::OnInitialUpdate() 
{
	CScrollView::OnInitialUpdate();
	
	CSize sizeTotal;

	RECT rect;
	GetClientRect(&rect);

	sizeTotal.cx = (long) rect.right;
	sizeTotal.cy = (long) rect.bottom;

	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CDisplayCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);

	if(!m_pIVideoSource)
	{
		CSize sizeTotal;

		sizeTotal.cx = cx;
		sizeTotal.cy = cy;

		SetScrollSizes(MM_TEXT, sizeTotal);
	}
}

void CDisplayCtrl::OnDraw(CDC* pDC)
{
	if(m_pIImageDisplay)
	{
		CPoint sp = GetScrollPosition();
		m_pIImageDisplay->SetSrcAoiPos((WORD) sp.x, (WORD) sp.y);
	}
}

int CDisplayCtrl::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg)
{
	// Bypass CView handler
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, msg);
}

void CDisplayCtrl::OnDestroy() 
{
	DeleteDisplay(TRUE);

	// Bypass CView handler
	CWnd::OnDestroy();
}

void CDisplayCtrl::PostNcDestroy() 
{
	// Do nothing. Don't let CView get it.
}

void CDisplayCtrl::ClearView()
{
	if(IsWindow(m_hWnd))
	{
		SendMessage(WM_ERASEBKGND, (WPARAM) ::GetDC(m_hWnd), (LPARAM) 0);
	}
}

void CDisplayCtrl::DeleteDisplay(BOOL bClose)
{
	if(m_pIImageDisplay)
	{
		m_pIImageDisplay->Close();
		m_pIImageDisplay->Release();
		m_pIImageDisplay = NULL;
	};

	if(m_pIVideoStream)
	{
		m_pIVideoStream->Close(0);
		m_pIVideoStream->Release();
		m_pIVideoStream = NULL;
	};

	if(m_pIVideoSource)
	{
		m_pIVideoSource->Freeze(0);

		if(bClose)
		{
			m_pIVideoSource->Close(0);
			m_pIVideoSource->Release();
			m_pIVideoSource = NULL;
		}
	}

	ClearView();
}

void CDisplayCtrl::CreateDisplay()
{
	if(m_pIVideoSource)
	{
		VS_CAM_ATTR camAttrib;
		m_pIVideoSource->GetAttr(&camAttrib,TRUE);

		m_pIVideoSource->Freeze(0);

		if(m_bLocalVideoSource)
		{
			m_pIImageDisplay = VsCreateVideoSrcDisplay( m_pIVideoSource,
														m_hWnd,
														VS_LIVE_IMAGE_FLAG,
														VS_ICAP_INTR_EOF, 1);
		}
		else
		{
			VS_STREAM_PARAMS vsParam;

			vsParam.numIframes = 6;
			
			if (camAttrib.color != VS_MONO) 
			{
				vsParam.desiredFramesPerSecond = 10;
				vsParam.encodeKind = VS_FRAME_JPEG_ENCODE;
			}
			else 
			{
				vsParam.desiredFramesPerSecond = 24;
				vsParam.encodeKind = VS_FRAME_DJPEG_ENCODE;
			}


			m_pIVideoStream		= VsCreateVideoStream(m_pIVideoSource, &vsParam);
			m_pIImageDisplay	= VsCreateDisplayNode(m_hWnd, 0, NULL, 0);

			m_pIVideoStream->ConnectOutputTo(m_pIImageDisplay);
		}

		m_pIVideoSource->GrabOn();
	}
}

void CDisplayCtrl::SetVideoSource(IVideoSrc *pIVideoSource, BOOL bIsLocal)
{
	DeleteDisplay(TRUE);

	m_bLocalVideoSource = bIsLocal;
	m_pIVideoSource = pIVideoSource;

	CSize sizeTotal;

	if(m_pIVideoSource)
	{
		VS_CAM_ATTR camAttrib;
		m_pIVideoSource->GetAttr(&camAttrib,TRUE);
		
		sizeTotal.cx = (long) camAttrib.dwWidth;
		sizeTotal.cy = (long) camAttrib.dwHeight;
	}
	else
	{
		RECT rect;
		GetClientRect(&rect);

		sizeTotal.cx = (long) rect.right;
		sizeTotal.cy = (long) rect.bottom;
	}

	SetScrollSizes(MM_TEXT, sizeTotal);

	CreateDisplay();
}
