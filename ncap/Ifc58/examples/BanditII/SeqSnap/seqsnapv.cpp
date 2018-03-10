/******************************************************************************
 *
 * MODULE
 *    seqsnapV.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/seqsnapv.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 12/12/02 6:07p $
 *
 * ABSTRACT
 *    BanditII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "seqsnap.h"
#include <windowsx.h>

#include "seqsnapD.h"
#include "seqsnapV.h"
#include "Dlgsnap.h"
#include "TrigGrabDlg.h"
#include "camsel.h"
#include "LutThrsh.h"
#include "OutPort.h"
#include "Dlgwin.h"
#include "HwZoom.h"
#include "Procthrd.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


typedef enum {transparent, dark_red, dark_green, dark_yellow, dark_blue, dark_magenta, dark_cyan, light_gray1,
			  money_green, sky_blue, cream, light_gray2, medium_gray, red, green, yellow, blue, magenta, cyan, white} STATIC_COLOR;

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView

IMPLEMENT_DYNCREATE(CSeqsnapView, CView)

BEGIN_MESSAGE_MAP(CSeqsnapView, CView)
	//{{AFX_MSG_MAP(CSeqsnapView)
	ON_COMMAND(ID_CMDS_SEQSNAP, OnCmdsSeqsnap)
	ON_COMMAND(ID_CMDS_TRIGOPS, OnCmdsTrigops)
	ON_COMMAND(ID_CMDS_SELECTCAM, OnCmdsSelectcam)
	ON_COMMAND(ID_CMDS_READTIFF, OnCmdsReadtiff)
	ON_COMMAND(ID_CMDS_WRITETIFF, OnCmdsWritetiff)
	ON_COMMAND(ID_CMDS_PERFORMANCE, OnCmdsPerformance)
	ON_COMMAND(ID_LUT_INVERT, OnLutInvert)
	ON_COMMAND(ID_LUT_LINEAR, OnLutLinear)
	ON_COMMAND(ID_LUT_THRESH, OnLutThresh)
	ON_COMMAND(ID_CMDS_WINDOWGEN, OnCmdsWindowgen)
	ON_COMMAND(ID_CMDS_HWZOOM, OnCmdsHwzoom)
	ON_COMMAND(ID_CMDS_SWOVERLAY, OnCmdsSwoverlay)
	ON_COMMAND(ID_CMDS_COLOR, OnCmdsColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView construction/destruction

CSeqsnapView::CSeqsnapView()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();

	m_ImgConn = NULL;
	num_snap_areas = 8;
	m_port = 0;
	m_iImgWidth = theapp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
	m_iHorOff = theapp->m_cam->GetAcqParam(P_HORZ_OFF);

}

CSeqsnapView::~CSeqsnapView()
{
	if (m_ImgConn)
		delete m_ImgConn;
}

BOOL CSeqsnapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView drawing

void CSeqsnapView::OnDraw(CDC* pDC)
{
	CSeqsnapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CBrush cbr;
	RECT rect;
	GetClientRect(&rect);
	cbr.CreateSolidBrush(PALETTEINDEX(dark_yellow));
	pDC->FillRect(&rect,&cbr);
	cbr.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView diagnostics

#ifdef _DEBUG
void CSeqsnapView::AssertValid() const
{
	CView::AssertValid();
}

void CSeqsnapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeqsnapDoc* CSeqsnapView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeqsnapDoc)));
	return (CSeqsnapDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView message handlers

void CSeqsnapView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
//	CreateImageServer();
	
}

void CSeqsnapView::OnCmdsSeqsnap() 
{
	CDlgsnap dg(this);
	dg.DoModal();
	InvalidateRect(NULL,TRUE);
}


void CSeqsnapView::OnCmdsTrigops() 
{
	DelImageServer();
	CTrigGrabDlg dlg(this);
	dlg.DoModal();
	InvalidateRect(NULL,TRUE);
}



void CSeqsnapView::CreateImageServer(DWORD Flags)
{
	CSeqsnapApp* theapp = (CSeqsnapApp*) AfxGetApp();
	CICamera* pCamera = theapp->m_cam;
	CAM_ATTR attr;
	pCamera->GetAttr(&attr);
	
	if(m_ImgConn) {
		DelImageServer();
	}

	pCamera->Freeze();
	pCamera->Grab();
	if ( !(Flags & IFC_SW_OVERLAY) && attr.color == IFC_YCRCB) {
		Flags |= IFC_YCRCB_SINK;
	}
	if(pCamera->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED)
	{
		m_ImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | Flags, ICAP_INTR_EOF);
	}
	else
	{
		m_ImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | Flags, ICAP_INTR_VB);
	}
	if (Flags & IFC_YCRCB_SINK) {
		m_ImgConn->GetSink()->SetDestColorKey(dark_yellow);
	}

}


void CSeqsnapView::DelImageServer()
{
	CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();

	if(m_ImgConn)
	{
		delete m_ImgConn;
		m_ImgConn = NULL;
		theapp->m_cam->Freeze();
	}
}

void CSeqsnapView::OnCmdsSelectcam() 
{
	CCamSel dg(this);
	dg.DoModal();
	InvalidateRect(NULL,TRUE);
}

void CSeqsnapView::ClearView()
{
	InvalidateRect(NULL,TRUE);
}


void CSeqsnapView::OnCmdsReadtiff() 
{
	CFileDialog dg(TRUE,"tif",NULL,	OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "JPG Files (*.jpg)|*.jpg|"
                "All Files (*.*)|*.*||");

	DelImageServer(); // Delete Image server, since we'll be displaying a TIFF file
	ClearView();

	if(dg.DoModal() != IDOK)
	{
		return;
	}

	CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
	WORD m_areaDx;	// DX of the image area being processed
	WORD m_areaDy;  // DY of the image area being processed

		// Read the image from the file
	CImgFile *imgFile = IfxCreateImgFile(fname.GetBuffer(80));

	if(imgFile)
	{
		IMGFILEPROPS fileProps;

		if(imgFile->ImageFileProps(&fileProps))
		{
			m_areaDx = (WORD)fileProps.dx;
			m_areaDy = (WORD)fileProps.dy;

			// Allocate space for the image 
			DWORD bytesPerPixel = fileProps.bitsPerPixel;

			if(fileProps.bitsPerPixel & 7)
			{
				bytesPerPixel++;
			}

			m_imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED,(DWORD)m_areaDx * (DWORD)m_areaDy * bytesPerPixel);
			m_ImgConn = new CImgConn(m_imgBuf, m_areaDx, m_areaDy, fileProps.bitsPerPixel, m_hWnd);
			imgFile->ReadFile(m_imgBuf);
			CRect rect(0, 0, m_areaDx, m_areaDy);
			ValidateRect(&rect);
			m_ImgConn->Display();
			delete m_ImgConn;
			m_ImgConn = NULL;
			GlobalFreePtr(m_imgBuf);
		}
		else
		{
			MessageBox("Could not get file properties.");
		}

		delete imgFile;
	}
	else
	{
		MessageBox("Could not open file.");
	}
}


void CSeqsnapView::OnCmdsWritetiff() 
{
	CreateImageServer(); // Create live display from which user can pick image to snap
	int result;
	
	CFileDialog dg(FALSE,"tif",NULL, OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "JPG Files (*.jpg)|*.jpg|"
                "All Files (*.*)|*.*||");
	
	result = dg.DoModal();
	DelImageServer();  // delete the live display now that we've chosen our image

	if(result == IDOK) {
		CString fname = dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();	
		BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
		DWORD m_areaDx;	// DX of the image area being processed
		DWORD m_areaDy; // DY of the image area being processed
		CAM_ATTR attr;
		
		// Get the current acquisition dimensions
		theapp->m_cam->GetAttr(&attr);
		m_areaDx = attr.dwWidth;
		m_areaDy = attr.dwHeight;
		
		// Allocate space for the image 
		m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel);
		
		// Snap a single image from the camera into memory
		theapp->m_cam->Snap(m_imgBuf);
		
		IFFCLASS_TYPE FileColor;			
		if (attr.color == IFC_RGB || attr.color == IFC_RGB_PACK24)
			FileColor = IFFCL_RGB;
		else if (attr.color == IFC_YCRCB)
			FileColor = IFFCL_YCRCB;
		else
			FileColor = IFFCL_GRAY;
		// Write the image file
		if(!IfxWriteImgFile(fname.GetBuffer(80),m_imgBuf, m_areaDx, m_areaDy, (WORD)attr.dwBitsPerPixel,FileColor))
			MessageBox("IfxWriteImgFile failed.");

		

		GlobalFreePtr(m_imgBuf);
	}

	CreateImageServer(); // Create live display from which user can pick image to snap
	InvalidateRect(NULL,TRUE);
}


#define RND(x) (rand()%(x))




void CSeqsnapView::OnCmdsPerformance() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	DelImageServer();
	Sleep(100);
	float mb_per_s = theapp->m_iCap->ReadPerformance();	
	char msg[200];
	sprintf(msg,"The frame buffer read rate is %f MB/s", mb_per_s);
	CreateImageServer();
	MessageBox(msg,"Performance");
}

DWORD IFCAPI CSeqsnapView::LutInvert(DWORD arg, DWORD* constants)
{
	return ((BDT_NUM_LUT_ENTRIES - 1) - arg);
}

void CSeqsnapView::OnLutInvert() 
{
	CSeqsnapApp *theApp=(CSeqsnapApp*)AfxGetApp();	
	DWORD numEntries = BDT_NUM_LUT_ENTRIES;
	theApp->m_cam->Freeze();
	theApp->m_cam->SetLutFunction(INPUT_LUT1, CSeqsnapView::LutInvert, &numEntries, LUT_FULL_WORD);
	theApp->m_cam->SetLutFunction(INPUT_LUT2, CSeqsnapView::LutInvert, &numEntries, LUT_FULL_WORD);
	ClearView();
	CreateImageServer();
}

void CSeqsnapView::OnLutLinear() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	theApp->m_cam->Freeze();
	theApp->m_cam->LinearizeLut(INPUT_LUT1, LUT_FULL_WORD);
	theApp->m_cam->LinearizeLut(INPUT_LUT2, LUT_FULL_WORD);
	ClearView();
	CreateImageServer();
}



DWORD IFCAPI CSeqsnapView::LutFloor(DWORD arg, DWORD * constants)
{
	DWORD floor = constants[0];

	if(arg > floor)
	{
		return arg;
	}
	else
	{
		return floor;
	}
}

void CSeqsnapView::OnLutThresh() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	

	CLutThrsh dg(this, BDT_NUM_LUT_ENTRIES-1);

	if(dg.DoModal() == IDOK)
	{
		DWORD floor = dg.m_lutThresh;

		theApp->m_cam->Freeze();
		theApp->m_cam->SetLutFunction(INPUT_LUT1, CSeqsnapView::LutFloor, &floor);
		theApp->m_cam->SetLutFunction(INPUT_LUT2, CSeqsnapView::LutFloor, &floor);
		ClearView();
		CreateImageServer();
	}
}




void CSeqsnapView::OnCmdsWindowgen() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CDlgwin dg(this);

	if(dg.DoModal() == IDOK) {
		theApp->m_cam->SetWindowGen((short) dg.m_iHOffset, (short) dg.m_iVOffset,
			(short) dg.m_uWidth,   (short) dg.m_uHeight);
	}
	InvalidateRect(NULL,TRUE);
	CreateImageServer();  	
}

void CSeqsnapView::OnCmdsHwzoom() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	ZOOMCAP ZoomCap;
	theApp->m_cam->GetZoomCaps(&ZoomCap);
	CHwZoom dg(this);
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theApp->m_cam->GetAttr(&attr);
	
	if( dg.DoModal()==IDOK ) {
		DelImageServer();
		InvalidateRect(NULL,TRUE);
		theApp->m_cam->SetZoom(dg.m_xZoom, dg.m_yZoom);
		CreateImageServer();
		MessageBox("Click OK to Close the Zoomed Image.", "Zoom");
		
		DelImageServer();
		InvalidateRect(NULL,TRUE);
		theApp->m_cam->SetZoom(1.0, 1.0);
		CreateImageServer();
	}
	else
	{
		MessageBox("The resulting Zoomed width will not be a multiple of 8", "Zoom");
	}
}

void CSeqsnapView::OnCmdsSwoverlay() 
{
	// 20 Windows system colors
	static const COLORREF  syscolors[] =
	{
	RGB(	0x0,	0x0,	0x0		),
	RGB(	0x0,	0x0,	0x80	),
	RGB(	0x0,	0x80,	0x0		),
	RGB(	0x0,	0x80,	0x80	),
	RGB(	0x80,	0x0,	0x0		),
	RGB(	0x80,	0x0,	0x80	),
	RGB(	0x80,	0x80,	0x0		),
	RGB(	0xc0,	0xc0,	0xc0	),
	RGB(	0xc0,	0xdc,	0xc0	),
	RGB(	0xf0,	0xc8,	0xa4	),
	RGB(	0xf0,	0xfb,	0xff	),
	RGB(	0xa4,	0xa0,	0xa0	),
	RGB(	0x80,	0x80,	0x80	),
	RGB(	0x0,	0x0,	0xff	),
	RGB(	0x0,	0xff,	0x0		),
	RGB(	0x0,	0xff,	0xff	),
	RGB(	0xff,	0x0,	0x0		),
	RGB(	0xff,	0x0,	0xff	),
	RGB(	0xff,	0xff,	0x0		),
	RGB(	0xff,	0xff,	0xff	)
	};

	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	

	// Get the current acquisition dimensions

	CreateImageServer(IFC_SW_OVERLAY);

	if(!m_ImgConn)
	{
		MessageBox("Your Video Card does not support Software Overlay.", "SW Overlay Error");
		return;
	}
	
	HDC hdc;
	hdc = m_ImgConn->GetOverlayDC();


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, 0x00ff0000);

	TextOut(hdc, 20, 20, "Software", 8);
	TextOut(hdc, 20, 40, "Overlay Text", 12);

	int i;

	for(i=1; i<10; i++)
	{
		COLORREF color = syscolors[i];
		CDC::FromHandle(hdc)->Draw3dRect(RND(400), RND(300), 10+RND(150), 10+RND(150), color, color);
	}

	// Note you must release the Overlay HDC prior to displaying an image
	// connection which includes the overlay; or starting an image server 
	// which displays the overlay.
	m_ImgConn->ReleaseOverlayDC(hdc);

	// Add some overlay content while the Image server is running 
	// Note: the user must get and release the Overlay HDC around each draw operation
	// since the image connection cannot be updated while we possess the HDC
	for( i=0; i < 30; i++) {
		Sleep(100);
		hdc = m_ImgConn->GetOverlayDC();

		COLORREF color = syscolors[i%20];
		CDC::FromHandle(hdc)->Draw3dRect(RND(400), RND(300), 10+RND(150), 10+RND(150), color, color);

		m_ImgConn->ReleaseOverlayDC(hdc);
	}

	MessageBox("Click OK to Close the Software Overlay.", "Software Overlay");

	CreateImageServer();
	InvalidateRect(NULL,TRUE);
}



void CSeqsnapView::OnCmdsColor() 
{
	CColorDlg dlg(this);
	dlg.DoModal();
	InvalidateRect(NULL,TRUE);
}



