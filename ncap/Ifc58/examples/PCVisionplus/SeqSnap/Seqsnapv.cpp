/******************************************************************************
 *
 * MODULE
 *    seqsnapV.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/SEQSNAPV.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 4/22/02 10:28a $
 *
 * ABSTRACT
 *    PCVisionplus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000-2002 Imaging Technology, Inc.  All rights reserved.
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
	ON_COMMAND(ID_CMDS_INPORT, OnCmdsInport)
	ON_COMMAND(ID_CMDS_OUTPORT, OnCmdsOutport)
	ON_COMMAND(ID_CMDS_WINDOWGEN, OnCmdsWindowgen)
	ON_COMMAND(ID_CMDS_HWZOOM, OnCmdsHwzoom)
	ON_COMMAND(ID_CMDS_SWOVERLAY, OnCmdsSwoverlay)
	ON_COMMAND(ID_BRD_PARAMS, OnBrdParams)
	ON_COMMAND(ID_CMDS_COLOR, OnCmdsColor)
	ON_COMMAND(ID_CMDS_OVERSAMPLE, OnCmdsOverSample)
	ON_UPDATE_COMMAND_UI(ID_CMDS_OVERSAMPLE, OnUpdateOverSampleUI)
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

	// TODO: add draw code for native data here
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
//	CreateImageServer(NULL);
	
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
	
	if(m_ImgConn)
	{
		DelImageServer();
	}

	pCamera->Freeze();
	pCamera->Grab();

	if(pCamera->GetAcqParam(P_SCAN_MODE_STAT) == IFC_ILACED)
	{
		m_ImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | Flags, ICAP_INTR_EOF);
	}
	else
	{
		m_ImgConn = new CImgConn(pCamera, m_hWnd, IFC_LIVE_IMAGE | Flags, ICAP_INTR_VB);
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
                "BMP Files (*.bmp)|*.bmp|"
                "JPG Files (*.jpg)|*.jpg|"
                "RAW Files (*.raw)|*.raw|"
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
                "BMP Files (*.bmp)|*.bmp|"
                "JPG Files (*.jpg)|*.jpg|"
                "RAW Files (*.raw)|*.raw|"
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
		
		// Write the image to a TIFF file
		if(!IfxWriteImgFile(fname.GetBuffer(80), m_imgBuf, m_areaDx, m_areaDy, (WORD)attr.dwBitsPerPixel))
			MessageBox("Error on writing File.");
		
		GlobalFreePtr(m_imgBuf);
	}

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
	CreateImageServer(NULL);
	MessageBox(msg,"Performance");
}

DWORD IFCAPI CSeqsnapView::LutInvert(DWORD arg, DWORD* constants)
{
	return ((PCP_NUM_LUT_ENTRIES - 1) - arg);
}

void CSeqsnapView::OnLutInvert() 
{
	CSeqsnapApp *theApp=(CSeqsnapApp*)AfxGetApp();	
	DWORD numEntries = PCP_NUM_LUT_ENTRIES;
	theApp->m_cam->SetLutFunction(INPUT_LUT1, CSeqsnapView::LutInvert, &numEntries, LUT_FULL_WORD);
	ClearView();
	CreateImageServer(NULL);
}

void CSeqsnapView::OnLutLinear() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	theApp->m_cam->LinearizeLut(INPUT_LUT1, LUT_FULL_WORD);
	ClearView();
	CreateImageServer(NULL);
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

	CLutThrsh dg(this, PCP_NUM_LUT_ENTRIES-1);

	if(dg.DoModal() == IDOK)
	{
		DWORD floor = dg.m_lutThresh;

		theApp->m_cam->SetLutFunction(INPUT_LUT1, CSeqsnapView::LutFloor, &floor);
		ClearView();
		CreateImageServer(NULL);
	}
}


void CSeqsnapView::OnCmdsInport() 
{
	char msg[200];
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();

	theApp->m_iCap->InportMode(FALSE, IFC_FALLING_EDGE);

	WORD parallelIO = theApp->m_iCap->InportVal();

	sprintf(msg,"The In Port value is: 0x%x ",parallelIO);
	MessageBox(msg,"Input Ports");
}



void CSeqsnapView::OnCmdsOutport() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
	COutPort dg(this);	

	if(dg.DoModal() == IDOK)
	{
		theApp->m_iCap->OutportVal(dg.m_outport_val);

		if(dg.m_genstrobe)
		{
			theApp->m_iCap->OutportStrobeVal(IFC_LEVEL_HIGH);
			theApp->m_iCap->OutportStrobeVal(IFC_LEVEL_LOW);
		}
	}		
}


void CSeqsnapView::OnCmdsWindowgen() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CDlgwin dg(this);

	if(dg.DoModal() == IDOK)
	{
		if(dg.m_iOrigin)	// Absolute Origin.
		{
			theApp->m_cam->SetWindowGen((short) dg.m_iHOffset, (short) dg.m_iVOffset,
										(short) dg.m_uWidth,   (short) dg.m_uHeight);
		}
		else				// Relative Origin.
		{
			theApp->m_cam->RelativeHOffsetSet(dg.m_iHOffset);
			theApp->m_cam->RelativeVOffsetSet(dg.m_iVOffset);
			theApp->m_cam->SetAcqParam(P_WIDTH_PIXELS, dg.m_uWidth);
			theApp->m_cam->SetAcqParam(P_HEIGHT_PIXELS, dg.m_uHeight);
		}
	}

	InvalidateRect(NULL,TRUE);
	CreateImageServer(NULL);  	
}

void CSeqsnapView::OnCmdsHwzoom() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CHwZoom dg(this);
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theApp->m_cam->GetAttr(&attr);
	
	if( dg.DoModal()==IDOK && ((int)(attr.dwWidth*dg.m_xzoom) % 8  ) == 0) {
		DelImageServer();
		InvalidateRect(NULL,TRUE);
		theApp->m_cam->SetZoom(dg.m_xzoom, dg.m_yzoom);
		CreateImageServer(NULL);
		MessageBox("Click OK to Close the Zoomed Image.", "Zoom");
		
		DelImageServer();
		InvalidateRect(NULL,TRUE);
		theApp->m_cam->SetZoom(1.0, 1.0);
		CreateImageServer(NULL);
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
	for( ; i<60; i++)
	{
		Sleep(100);
		hdc = m_ImgConn->GetOverlayDC();

		COLORREF color = syscolors[i%20];
		CDC::FromHandle(hdc)->Draw3dRect(RND(400), RND(300), 10+RND(150), 10+RND(150), color, color);

		m_ImgConn->ReleaseOverlayDC(hdc);
	}

	MessageBox("Click OK to Close the Software Overlay.", "Software Overlay");

	CreateImageServer(NULL);
	InvalidateRect(NULL,TRUE);
}


void CSeqsnapView::OnBrdParams() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	DWORD BrdSerialNum;
	char msg[120];
	theapp->m_iCap->IfxGetBoardParam(IFC_HW_SERIAL_NUM,&BrdSerialNum);
	sprintf(msg,"Your HW module's serial number is %d",BrdSerialNum);
	MessageBox(msg,"Board Parameters");	
}

void CSeqsnapView::OnCmdsColor() 
{
	CColorDlg dlg(this);
	dlg.DoModal();
	InvalidateRect(NULL,TRUE);
}


void CSeqsnapView::OnCmdsOverSample()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();

	DelImageServer();

	if ((theapp->m_cam->GetAcqParam(PCP_OVERSAMPLE_MODE) == IFC_DISABLE))
	{
		theapp->m_cam->SetAcqParam(PCP_OVERSAMPLE_MODE, IFC_ENABLE);
		theapp->m_cam->SetAcqParam(P_PIXEL_CLK_FREQ, theapp->m_cam->GetAcqParam(P_PIXEL_CLK_FREQ) * 2);
		theapp->m_cam->SetAcqParam(P_HORZ_OFF, m_iHorOff * 2);
		theapp->m_cam->SetAcqParam(P_WIDTH_PIXELS, m_iImgWidth * 2);
		theapp->m_cam->SetZoom(0.5, 1);
		
	}else
	{
		theapp->m_cam->SetZoom(1.0, 1.0);
		theapp->m_cam->SetAcqParam(PCP_OVERSAMPLE_MODE, IFC_DISABLE);
		theapp->m_cam->SetAcqParam(P_PIXEL_CLK_FREQ, theapp->m_cam->GetAcqParam(P_PIXEL_CLK_FREQ) / 2);
		theapp->m_cam->SetAcqParam(P_HORZ_OFF, m_iHorOff);
		theapp->m_cam->SetAcqParam(P_WIDTH_PIXELS, m_iImgWidth );		
	}

	CreateImageServer(NULL);
	ClearView();	

}


void CSeqsnapView::OnUpdateOverSampleUI(CCmdUI* pCmdUI)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();
	if ((theapp->m_cam->GetAcqParam(PCP_OVERSAMPLE_MODE) == IFC_ENABLE))
	{
		pCmdUI->SetCheck(1);
	}
	else
	{
		pCmdUI->SetCheck(0);
	}

}
