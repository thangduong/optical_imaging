/******************************************************************************
 *
 * MODULE
 *    seqsnapV.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/SEQSNAP/SEQSNAPV.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 4/22/02 10:19a $
 *
 * ABSTRACT
 *    PCRGB Example Program
 *
 * TECHNICAL NOTES
 * seqsnapV.cpp : implementation of the CSeqsnapView class
 *
 *
 * Copyright (c) 1998-2002 Imaging Technology, Inc.  All rights reserved.
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
#include "CscDlg.h"
#include "Config.h"

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
	ON_COMMAND(ID_CMDS_COLOR_SPACE_CONV, OnCmdsColorSpaceConv)
	ON_COMMAND(ID_CONFIG, OnConfig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView construction/destruction

CSeqsnapView::CSeqsnapView()
{
	m_ImgConn = NULL;
	num_snap_areas = 8;
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
	CreateImageServer(NULL);
}



void CSeqsnapView::CreateImageServer(DWORD Flags)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	if (m_ImgConn) {
		DelImageServer();
	}

	theapp->m_cam->Freeze();
	theapp->m_cam->Grab();
	m_ImgConn = new CImgConn(theapp->m_cam, m_hWnd,IFC_LIVE_IMAGE | Flags,ICAP_INTR_VB);

}


void CSeqsnapView::DelImageServer()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	if (m_ImgConn) {
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
	CBrush hbr(RGB(255,255,255));
	RECT rect;
	CClientDC hdc(this);
	GetClientRect(&rect);
	hdc.FillRect(&rect,&hbr);
}


void CSeqsnapView::OnCmdsReadtiff() 
{
	CFileDialog dg(TRUE,"tif",NULL,	
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "BMP Files (*.bmp)|*.bmp|"
                "JPG Files (*.jpg)|*.jpg|"
                "RAW Files (*.raw)|*.raw|"
                "All Files (*.*)|*.*||");
	if (dg.DoModal() == IDOK) {
   		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
		BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
		WORD m_areaDx;	// DX of the image area being processed
		WORD m_areaDy;  // DY of the image area being processed


		DelImageServer(); // Delete Image server, since we'll be displaying a TIFF file
		ClearView();
		// Read the image from the file
		CImgFile *imgFile=IfxCreateImgFile(fname.GetBuffer(80));
		if (imgFile) {
			IMGFILEPROPS fileProps;
			if (imgFile->ImageFileProps(&fileProps)) {
				m_areaDx = (WORD)fileProps.dx;
				m_areaDy = (WORD)fileProps.dy;
				// Allocate space for the image 
				DWORD bytesPerPixel = fileProps.bitsPerPixel >> 3;
				if (fileProps.bitsPerPixel & 7)
					bytesPerPixel++;
				m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,(DWORD)m_areaDx * (DWORD)m_areaDy * bytesPerPixel);
				imgFile->ReadFile(m_imgBuf);
				m_ImgConn = new CImgConn(m_imgBuf,m_areaDx,m_areaDy,fileProps.bitsPerPixel, m_hWnd);
				m_ImgConn->Display();
				delete m_ImgConn;
				m_ImgConn = NULL;
				GlobalFreePtr(m_imgBuf);
			}
			else
				MessageBox("Could not get file properties.");
			
			delete imgFile;
		}
		else
			MessageBox("Could not open file.");
	}
}


void CSeqsnapView::OnCmdsWritetiff() 
{
	CreateImageServer(); // Create live display from which user can pick image to snap
	int result;
	CFileDialog dg(FALSE,"tif",NULL,	
    			OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "BMP Files (*.bmp)|*.bmp|"
                "JPG Files (*.jpg)|*.jpg|"
                "RAW Files (*.raw)|*.raw|"
                "All Files (*.*)|*.*||");
	result = dg.DoModal();
	DelImageServer();  // delete the live display now that we've chosen our image
	if (result == IDOK) {
		CString fname= dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
		BYTE *m_imgBuf;	// Memory space which is the destination of the ITX grab operation
		DWORD m_areaDx;	// DX of the image area being processed
		DWORD m_areaDy;  // DY of the image area being processed
		CAM_ATTR attr;
		
		// Get the current acquisition dimensions
		theapp->m_cam->GetAttr(&attr);
		m_areaDx = attr.dwWidth;
		m_areaDy = attr.dwHeight;
		IFFCLASS_TYPE FileColor;
		// Allocate space for the image 
		m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel);
		// Snap a single image from the camera into memory
		theapp->m_cam->Snap(m_imgBuf);
		
		if (attr.color == IFC_RGB || attr.color == IFC_RGB_PACK24)
			FileColor = IFFCL_RGB;
		else
			FileColor = IFFCL_GRAY;
		// Write the image to a TIFF file
		if (!IfxWriteImgFile(fname.GetBuffer(80),m_imgBuf,m_areaDx,m_areaDy,(WORD)attr.dwBitsPerPixel,FileColor))
			MessageBox("Could not write image file.");
		
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
	sprintf(msg,"The frame buffer read rate is %f MB/s",mb_per_s);
	CreateImageServer(NULL);
	MessageBox(msg,"Performance");
}

DWORD IFCAPI CSeqsnapView::LutInvert(DWORD arg, DWORD* constants)
{
	DWORD numEntries = constants[0];
	return ((numEntries - 1) - arg);
}

void CSeqsnapView::OnLutInvert() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	LUTCAP LutCaps;
	// Set the function which the LUT implements to be LutInvert
	
	theapp->m_cam->Freeze();
	theapp->m_cam->GetLUTCaps(&LutCaps);
	for (int i=0;i < LutCaps.numInputLUTs ; i++) {
		DWORD numEntries= 1 << (int)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE);
		theapp->m_cam->SetLutFunction((LUTID_TYPE)(INPUT_LUT1+i),CSeqsnapView::LutInvert,&numEntries );	
	}
	CreateImageServer(NULL);
	InvalidateRect(NULL,TRUE);
}

void CSeqsnapView::OnLutLinear() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	LUTCAP LutCaps;
	theapp->m_cam->Freeze();
	theapp->m_cam->GetLUTCaps(&LutCaps);
	for (int i = 0; i < LutCaps.numInputLUTs; i++)
		theapp->m_cam->LinearizeLut((LUTID_TYPE) (INPUT_LUT1+i), LUT_FULL_WORD);
	CreateImageServer(NULL);  // Create a live display to view the result of the LUTLinear
	InvalidateRect(NULL,TRUE);
}



DWORD IFCAPI CSeqsnapView::LutFloor(DWORD arg, DWORD * constants)
{
	DWORD floor=constants[0];
	if (arg > floor)
		return arg;
	else
		return floor;
}

void CSeqsnapView::OnLutThresh() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	DWORD numEntries;
	DWORD numBpp=(DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE);
	if (numBpp <= 16)
		numEntries= 1 << numBpp;
	else
		numEntries= 256;
	CLutThrsh dg(this,numEntries-1);	
	if (dg.DoModal() == IDOK) {
		DelImageServer();
		DWORD floor=dg.m_lutThresh;

		// Set the function which the LUT implements to be LutFloor 
		LUTCAP LutCaps;
		theapp->m_cam->GetLUTCaps(&LutCaps);
		for (int i=0;i < LutCaps.numInputLUTs ; i++)
			theapp->m_cam->SetLutFunction((LUTID_TYPE)(INPUT_LUT1+i),CSeqsnapView::LutFloor,&floor );
		CreateImageServer(NULL);  // Create a live display to view the result of the LUTFloor
		InvalidateRect(NULL,TRUE);
	}
}


void CSeqsnapView::OnCmdsInport() 
{
	char msg[200];
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	theapp->m_iCap->InportMode(FALSE, IFC_FALLING_EDGE);
	WORD parallelIO = theapp->m_iCap->InportVal();
	sprintf(msg,"The In Port value is: 0x%x ",parallelIO);
	MessageBox(msg,"Input Ports");
}



void CSeqsnapView::OnCmdsOutport() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	COutPort dg(this);	
	if (dg.DoModal() == IDOK) {
		theapp->m_iCap->OutportVal(dg.m_outport_val);
		if (dg.m_genstrobe) {
			theapp->m_iCap->OutportStrobeVal(IFC_LEVEL_HIGH);
			theapp->m_iCap->OutportStrobeVal(IFC_LEVEL_LOW);
		}			
	}		
}


void CSeqsnapView::OnCmdsWindowgen() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CDlgwin dg(this);	
	DelImageServer();
	if (dg.DoModal() == IDOK) {
		theapp->m_cam->SetWindowGen(dg.m_x,dg.m_y,dg.m_dx,dg.m_dy);
	}
	InvalidateRect(NULL,TRUE);
	CreateImageServer(NULL);  	
}

void CSeqsnapView::OnCmdsHwzoom() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CHwZoom dg(this);	
	if (dg.DoModal() == IDOK) {
		DelImageServer();
		ClearView();
		theapp->m_cam->SetZoom(dg.m_xzoom,dg.m_yzoom);

		CreateImageServer(NULL);
		MessageBox("Click OK to Close the Zoomed Image.",
			"Zoom");

		DelImageServer();
		InvalidateRect(NULL,TRUE);
		theapp->m_cam->SetZoom(1.0,1.0);
		CreateImageServer(NULL);
	}
}

void CSeqsnapView::OnCmdsSwoverlay() 
{
	/* 20 Windows system colors  */
	static const COLORREF  syscolors[] = {
	RGB( 0x0 , 0x0 , 0x0 ),
	RGB( 0x0 , 0x0 , 0x80 ),
	RGB( 0x0 , 0x80 , 0x0 ),
	RGB( 0x0 , 0x80 , 0x80 ),
	RGB( 0x80 , 0x0 , 0x0 ),
	RGB( 0x80 , 0x0 , 0x80 ),
	RGB( 0x80 , 0x80 , 0x0 ),
	RGB( 0xc0 , 0xc0 , 0xc0 ),
	RGB( 0xc0 , 0xdc , 0xc0 ),
	RGB( 0xf0 , 0xc8 , 0xa4 ),
	RGB( 0xf0 , 0xfb , 0xff ),
	RGB( 0xa4 , 0xa0 , 0xa0 ),
	RGB( 0x80 , 0x80 , 0x80 ),
	RGB( 0x0 , 0x0 , 0xff ),
	RGB( 0x0 , 0xff , 0x0 ),
	RGB( 0x0 , 0xff , 0xff ),
	RGB( 0xff , 0x0 , 0x0 ),
	RGB( 0xff , 0x0 , 0xff ),
	RGB( 0xff , 0xff , 0x0 ),
	RGB( 0xff , 0xff , 0xff )
	};
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	// Get the current acquisition dimensions
	if ((DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_COLOR) == IFC_RGB_PACK24) {
		MessageBox("Software Overlay not supported with color of IFC_RGB_PACK24,"
			" set color to IFC_RGB and retry.",
			"SW Overlay Error");
		return;
	}

	DelImageServer();
	CreateImageServer(IFC_SW_OVERLAY);
	if (!m_ImgConn) {
		MessageBox("Your Video Card does not support Software Overlay.",
			"SW Overlay Error");
		return;
	}
	HDC hdc;
	hdc = m_ImgConn->GetOverlayDC();
	 

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc,0x00ff0000);
	TextOut(hdc,20,20,"Software",8);
	TextOut(hdc,20,40,"Overlay Text",12);
	for (int i=1;i<10;i++) {
		COLORREF color = syscolors[i];
		CDC::FromHandle(hdc)->Draw3dRect(RND(400),RND(300),
		10+RND(150),10+RND(150),color,color);
	}
	// Note you must release the Overlay HDC prior to displaying an image
	// connection which includes the overlay; or starting an image server 
	// which displays the overlay.
	m_ImgConn->ReleaseOverlayDC(hdc);



	// Add some overlay content while the Image server is running 
	// Note: the user must get and release the Overlay HDC around each draw operation
	// since the image connection cannot be updated while we possess the HDC
	for ( ;i<20;i++) {
		Sleep(500);
		hdc = m_ImgConn->GetOverlayDC();
		COLORREF color = syscolors[i];
		CDC::FromHandle(hdc)->Draw3dRect(RND(400),RND(300),
		10+RND(150),10+RND(150),color,color);
		m_ImgConn->ReleaseOverlayDC(hdc);
	}

	MessageBox("Click OK to Close the Software Overlay.",
		"Software Overlay");

	DelImageServer();
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

void CSeqsnapView::OnCmdsColorSpaceConv() 
{
	CCscDlg dlg(this);
	dlg.DoModal();
	InvalidateRect(NULL,TRUE);	
}

void CSeqsnapView::OnConfig() 
{
	CConfigOcx	dlg(this);
	dlg.DoModal();
	InvalidateRect(NULL,TRUE);	
}

