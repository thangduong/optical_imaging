/******************************************************************************
 *
 * MODULE
 *    seqsnapV.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/seqsnapv.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 10/09/03 11:20a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 * seqsnapView.cpp : implementation of the CSeqsnapView class
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "seqsnap.h"
#include <windowsx.h>

#include "seqsnapD.h"
#include "seqsnapV.h"
#include "Dlgsnap.h"
#include "camsel.h"
#include "LutThrsh.h"
#include "OutPort.h"
#include "Dlgwin.h"
#include "Procthrd.h"
#include "SetCPort.h"
#include "TrgGrab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView

IMPLEMENT_DYNCREATE(CSeqsnapView, CScrollView)

BEGIN_MESSAGE_MAP(CSeqsnapView, CScrollView)
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
	ON_COMMAND(ID_CMDS_SWOVERLAY, OnCmdsSwoverlay)
	ON_COMMAND(ID_BRD_PARAMS, OnBrdParams)
	ON_COMMAND(ID_SETCOMMPORT, OnSetComPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView construction/destruction

CSeqsnapView::CSeqsnapView()
{
	m_ImgConn = NULL;
	m_numSnapAreas = 10;
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
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView drawing

void CSeqsnapView::OnDraw(CDC* pDC)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSeqsnapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CAM_ATTR attr;
		
	theapp->m_cam->GetAttr(&attr);

	CPoint sp = GetScrollPosition();

	sp.x=min(sp.x, (long)attr.dwWidth - 1);
	sp.y=min(sp.y, (long)attr.dwHeight - 1);


	if (m_ImgConn) {
		m_ImgConn->GetSrc()->SetAoiPos( (WORD)sp.x, (WORD)sp.y);
		m_ImgConn->Display();		
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapView diagnostics

#ifdef _DEBUG
void CSeqsnapView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSeqsnapView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
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
	CScrollView::OnInitialUpdate();

	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CAM_ATTR attr;		
	theapp->m_cam->GetAttr(&attr);
	CSize sizeTotal;
	sizeTotal.cx = (long)attr.dwWidth;
	sizeTotal.cy = (long)attr.dwHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CreateImageServer(NULL);
	
}

void CSeqsnapView::OnCmdsSeqsnap() 
{
	POINT pt={0,0};
	ScrollToPosition(pt);
	CDlgsnap dg(this);
	dg.DoModal();
	InvalidateRect(NULL,TRUE);
}


void CSeqsnapView::OnCmdsTrigops() 
{
	POINT pt={0,0};
	ScrollToPosition(pt);
	DelImageServer();
	CTrgGrab dg(this);	
	dg.DoModal();
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
	m_ImgConn = new CImgConn(theapp->m_cam, m_hWnd,IFC_LIVE_IMAGE | Flags,ICAP_INTR_EOF);

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
				DWORD bytesPerPixel = fileProps.bitsPerPixel / 8;
				if (fileProps.bitsPerPixel & 7)
					bytesPerPixel++;
				// Allocate space for the image 
				m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,(DWORD)m_areaDx * (DWORD)m_areaDy * bytesPerPixel );
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
    			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
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
		if (attr.color == IFC_MONO && attr.dwBitsPerPixel > 16) {
			MessageBox("MONO bit depths greater than 16 not supported.");
		}
		else {			
			IFC_BAYER_FILTER_TYPE bayerFilter= (IFC_BAYER_FILTER_TYPE)(DWORD)theapp->m_cam->GetAcqParam(P_BAYER_FILTER);
			IFFCLASS_TYPE FileColor;
			// Allocate space for the image 
			m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * attr.dwBytesPerPixel);
			// Snap a single image from the camera into memory
			theapp->m_cam->Snap(m_imgBuf);
			if (bayerFilter != IFC_BAYER_NONE) {
				DWORD bayOptions=0;
				if ((DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE) == 10)
					bayOptions |= IFC_BAYOPT_10BIT_SRC;
				else if ((DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE) == 12)
					bayOptions |= IFC_BAYOPT_12BIT_SRC;
				bayOptions |=IFC_BAYOPT_PIX_LEAST_SIG;
				BYTE *fileBuf=(BYTE*)malloc( m_areaDx * m_areaDy *4);
				IfxBayerFilterConvert(bayOptions,bayerFilter, fileBuf, m_imgBuf,m_areaDx, m_areaDy,IFC_RGB_PACK24,NULL);
				IfxWriteImgFile(fname.GetBuffer(80),fileBuf,m_areaDx,m_areaDy,24,IFFCL_RGB);
				free(fileBuf);
			}
			else {
				if (attr.color == IFC_RGB || attr.color == IFC_RGB_PACK24)
					FileColor = IFFCL_RGB;
				else
					FileColor = IFFCL_GRAY;

				if (attr.dwBitsPerPixel > 8 && attr.dwBitsPerPixel <= 16) {
					BYTE *bBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy );
					WORD *wSrc = (WORD*)m_imgBuf;
					BYTE *bDst = bBuf;
					for (DWORD i=0; i < m_areaDx * m_areaDy ;i++)
						*bDst++ = (BYTE)(*wSrc++ >> (attr.dwBitsPerPixel - 8));

					IfxWriteImgFile(fname.GetBuffer(80),bBuf,m_areaDx,m_areaDy,8 , FileColor);
					GlobalFreePtr(bBuf);
				}
				else {								
					IfxWriteImgFile(fname.GetBuffer(80),m_imgBuf,m_areaDx,m_areaDy,(WORD)attr.dwBitsPerPixel,FileColor);
				}
			}
			GlobalFreePtr(m_imgBuf);
		}
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


DWORD IFCAPI CSeqsnapView::LutInvert(DWORD arg, DWORD * constants)
{
	DWORD numEntries=constants[0];
	return (numEntries-1-arg);
}

void CSeqsnapView::OnLutInvert() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	LUTCAP LutCaps;
	// Set the function which the LUT implements to be LutInvert
	
	theapp->m_cam->Freeze();
	theapp->m_cam->GetLUTCaps(&LutCaps);
	for (int i=0;i < LutCaps.numInputLUTs ; i++) {
		DWORD dwPixelSize=(DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE);
		DWORD numEntries= (dwPixelSize < 16) ? 1UL <<dwPixelSize:0x100;		
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
	for (int i=0;i < LutCaps.numInputLUTs ; i++)
		theapp->m_cam->LinearizeLut((LUTID_TYPE)(INPUT_LUT1+i));	
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
	DWORD dwPixelSize=(DWORD)theapp->m_cam->GetAcqParam(P_PIXEL_SIZE);
	DWORD numEntries= (dwPixelSize < 16) ? 1UL <<dwPixelSize:0x100;		
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

void CSeqsnapView::OnSetComPort() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CSetCPort dg(this);	
	if (dg.DoModal() == IDOK) {
		theapp->m_iCap->SetBoardUartToCOMx(dg.m_commNum);
		char msg[200];
		sprintf(msg,"Your PC-CamLink module UART port has been set to COM%d,\nYou must re-boot to complete the operation!",dg.m_commNum);
		MessageBox(msg,"UART Port Name Change",MB_ICONINFORMATION);	
	}

	
}
