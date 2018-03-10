/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/FrameDly/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/15/03 11:35a $
 *
 * ABSTRACT
 *    PCVision2 Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001-2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "FrameDly.h"
#include "Dlgsnap.h"
#include <windowsx.h>

#include <vixni.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#define ITEXCALL_DEFAULT /*__declspec( dllexport ) */

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap dialog


CDlgsnap::CDlgsnap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgsnap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgsnap)
	//}}AFX_DATA_INIT
	m_vparent = (CFrameDlyView*)pParent;
	m_imgBuf = NULL;
	m_ImgSrc = 0;
	m_ImgSink = 0;
	m_ImgConn = 0;
	m_NumFrames = m_vparent->m_numCameras;
}


CDlgsnap::~CDlgsnap()
{
	if (m_ImgConn)
		delete m_ImgConn;
	if (m_ImgSink)
		delete m_ImgSink;
	if (m_ImgSrc)
		delete m_ImgSrc;
	if (m_imgBuf)
		GlobalFreePtr(m_imgBuf);
}

void CDlgsnap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgsnap)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgsnap, CDialog)
	//{{AFX_MSG_MAP(CDlgsnap)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SNAP, OnSnap)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_LIVE, OnLive)
	ON_BN_CLICKED(IDOK, OnClose)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVEAVI, OnSaveavi)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap message handlers




BOOL CDlgsnap::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CFrameDlyApp	*theApp = (CFrameDlyApp*) AfxGetApp();

	// Set number of frames in slider control.
    m_slider = (CSliderCtrl*) GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_vparent->m_numCameras-1, FALSE);

	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theApp->m_cam->GetAttr(&attr);
	m_areaDx	= attr.dwWidth;
	m_areaDy	= attr.dwHeight;
	m_bytesPerPixel = attr.dwBytesPerPixel;


	m_vparent->DelImageServer();

	// allocate space for image ring buffer to be the destination of the host seq snap operation
	m_imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->m_numCameras);

	m_ImgConn = IfxCreateImgConn(m_imgBuf,(WORD)m_areaDx,(WORD)m_areaDy,(WORD)attr.dwBitsPerPixel, m_vparent->m_hWnd,attr.color);

	m_vparent->CreateImageServer();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgsnap::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	BYTE *frame_addr;
    switch (nSBCode) {
	case SB_LINELEFT:
	case SB_LINERIGHT:
	case SB_PAGELEFT:
	case SB_PAGERIGHT:
		nPos = m_slider->GetPos();
		// fall thru to thumb code
    case SB_THUMBTRACK:
    case SB_THUMBPOSITION:
		frame_addr = m_imgBuf + nPos * (m_areaDx*m_areaDy*m_bytesPerPixel);
		// Update the address associated with the image source to point to the frame
		// we just processed
		m_ImgConn->GetSrc()->SetBufferAddr(frame_addr);		
        break;
    default:
        break;
    }

	m_vparent->DelImageServer();
	// Display the selected frame in our client window
	m_ImgConn->Display();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}




void CDlgsnap::OnSnap() 
{
	CFrameDlyApp *theApp = (CFrameDlyApp*) AfxGetApp();	
	CEdit *pEdit = NULL;
	CString str((char) ' ', 80);
	DWORD TotalTime, LastTime;
	DWORD timeX;

	m_slider->SetPos(0);
	m_vparent->DelImageServer();


	m_ImgConn->GetSrc()->SetBufferAddr(m_imgBuf);
	HCURSOR hcurSave;

	// Set the cursor to the hourglass and save the previous cursor.
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));

	// start the snap operation going

	pEdit = (CEdit*) GetDlgItem(IDC_TOTAL_TIME);
	ASSERT(pEdit);
	
	theApp->m_cam->SetAcqParam(P_TRIGGER_SRC, m_vparent->m_trigSrc);
	theApp->m_pMod->SetFrameDelaySequence(m_vparent->m_camPortSeq, m_vparent->m_numCameras, m_vparent->m_trigSrc);

	LastTime = theApp->m_pMod->m_os->GetSystimeMillisecs();
	theApp->m_pMod->FrameDelaySnap(m_vparent->m_trigSrc,m_imgBuf, 0, 0, (short) m_areaDx, (short) m_areaDy, 0);
	timeX = theApp->m_pMod->m_os->GetSystimeMillisecs() - LastTime;
	if (m_vparent->m_trigSrc == IFC_SOFT_TRIG) {
		theApp->m_cam->SetAcqParam(P_GEN_SW_TRIGGER, 0);
	}
	theApp->m_pMod->FrameDelayWait(3000);

	TotalTime = theApp->m_pMod->m_os->GetSystimeMillisecs() - LastTime;
	str.Format("%d", (int) TotalTime);
	pEdit->SetWindowText (str);

	pEdit = (CEdit*) GetDlgItem(IDC_FRAME_TIME);
	ASSERT(pEdit);
	str.Format("%d", (int) (TotalTime / m_vparent->m_numCameras));
	pEdit->SetWindowText (str);

	// Restore the previous cursor.
	::SetCursor(hcurSave);

	// Display the processed frame in our client window
	m_ImgConn->Display();
}


void CDlgsnap::OnPlay() 
{
	BYTE *frame_addr;
	DWORD i;

	m_vparent->DelImageServer();

	m_slider->SetRange(0, m_vparent->m_numCameras - 1, TRUE);

	// play the recorded sequence of frames
	for(i=0; i<m_vparent->m_numCameras; i++)
	{
		m_slider->SetPos(i);
		frame_addr = m_imgBuf + i * (m_areaDx * m_areaDy * m_bytesPerPixel);
		m_ImgConn->GetSrc()->SetBufferAddr(frame_addr);
		m_ImgConn->Display();
		Sleep(33);				// Play frames at roughly 30HZ
	}

}

void CDlgsnap::OnLive() 
{
	m_slider->SetPos(0);
	m_vparent->CreateImageServer();
	m_vparent->InvalidateRect(NULL,TRUE);

}

void CDlgsnap::OnClose() 
{
	CDialog::OnOK();

	if(m_imgBuf)
	{
		GlobalFreePtr(m_imgBuf);
		m_imgBuf = NULL;
	}

	m_vparent->CreateImageServer();
	
}

void CDlgsnap::OnSave() 
{
	int result;
	CFileDialog dg(FALSE,"tif",NULL,	
    			OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "JPG Files (*.jpg)|*.jpg|"
                "BMP Files (*.bmp)|*.bmp|"
                "RAW Files (*.raw)|*.raw|"
                "All Files (*.*)|*.*||");
	result = dg.DoModal();
	if (result == IDOK) {
		CString fname= dg.GetFileTitle() ;   // dgf.GetPathName();
		CFrameDlyApp *theapp=(CFrameDlyApp*)AfxGetApp();	
		CAM_ATTR attr;
		
		// Get the current acquisition dimensions
		theapp->m_cam->GetAttr(&attr);
		m_areaDx = attr.dwWidth;
		m_areaDy = attr.dwHeight;
		for(DWORD i=0;i< m_vparent->m_numCameras;i++) {
			CString imgFileName;
			imgFileName.Format("%s%d.%s",fname, i,dg.GetFileExt());

			IFFCLASS_TYPE FileColor;			
			if (attr.color == IFC_RGB || attr.color == IFC_RGB_PACK24)
				FileColor = IFFCL_RGB;
			else if (attr.color == IFC_YCRCB)
				FileColor = IFFCL_YCRCB;
			else
				FileColor = IFFCL_GRAY;
			
			// Write images to a TIFF files
			if (!IfxWriteImgFile(imgFileName.GetBuffer(80),m_imgBuf + i * (m_areaDx*m_areaDy*m_bytesPerPixel),m_areaDx,m_areaDy,(WORD)attr.dwBitsPerPixel,FileColor)) {
				MessageBox("IfxWriteImgFile failed.");
				break;
			}
		}
	}
	
}
	


void CDlgsnap::OnSaveavi() 
{
	
	UpdateData(TRUE);
	
	CAM_ATTR attr;
	CFrameDlyApp	*theApp = (CFrameDlyApp*) AfxGetApp();
	theApp->m_cam->GetAttr(&attr);
	
	int result;
	
	CFileDialog dg(FALSE,"avi",NULL, OFN_HIDEREADONLY,
		"AVI Files (*.avi)|*.avi");
	
	result = dg.DoModal();
	
	if(result == IDOK) {
		CString FName = dg.GetFileTitle() + "." + dg.GetFileExt();   // dgf.GetPathName();
		if (attr.color == IFC_YCRCB) {
			BYTE *rgbBuff=(BYTE*)malloc(m_NumFrames*attr.dwWidth*attr.dwHeight*3);
			CClrSpace::YCrCbToRGB(rgbBuff,m_imgBuf,m_NumFrames*attr.dwWidth*attr.dwHeight*2,IFC_YCRCBTORGB24,TRUE);
			IfxSaveToAviFile(m_NumFrames, FALSE, FName.GetBuffer(FName.GetLength()), rgbBuff, attr.dwWidth, attr.dwHeight, 24, 30L,0,  0,  0, 0, 0 );
			free(rgbBuff);
		}
		else {
			IfxSaveToAviFile(m_NumFrames, 0, FName.GetBuffer(FName.GetLength()), m_imgBuf, attr.dwWidth, attr.dwHeight, attr.dwBitsPerPixel, 30L,0,  0,  0, 0, 0 );
		}
	}
}
