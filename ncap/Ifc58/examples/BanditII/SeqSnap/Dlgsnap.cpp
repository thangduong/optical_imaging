/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/05/02 4:05p $
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
	m_NumFrames = 0;
	//}}AFX_DATA_INIT
	m_vparent = (CSeqsnapView*)pParent;
	m_imgBuf = NULL;
	m_ImgSrc = 0;
	m_ImgSink = 0;
	m_ImgConn = 0;
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
	DDX_Text(pDX, IDC_NUMFRAMES, m_NumFrames);
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

	CSeqsnapApp	*theApp = (CSeqsnapApp*) AfxGetApp();
	char		numf_buffer[20];	
    CEdit		*numframeID = (CEdit*) GetDlgItem(IDC_NUMFRAMES);

	// Set number of frames in slider control.
	numframeID->SetWindowText(itoa(m_vparent->num_snap_areas, numf_buffer, 10));
    m_slider = (CSliderCtrl*) GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_vparent->num_snap_areas-1, FALSE);

	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theApp->m_cam->GetAttr(&attr);
	m_areaDx	= attr.dwWidth;
	m_areaDy	= attr.dwHeight;
	m_bytesPerPixel = attr.dwBytesPerPixel;


	m_vparent->DelImageServer();

	// allocate space for image ring buffer to be the destination of the host seq snap operation
	m_imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->num_snap_areas);

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
	int new_num_img_areas;	
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
    CEdit *numframeID = (CEdit*) GetDlgItem(IDC_NUMFRAMES);
	CEdit *pEdit = NULL;
	CString str((char) ' ', 80);
	DWORD TotalTime, LastTime;

	numframeID->GetWindowText(str);
	new_num_img_areas = atoi(str);

	m_slider->SetPos(0);
	//m_vparent->CreateImageServer();
	m_vparent->DelImageServer();
	Sleep(200);

	if(new_num_img_areas != m_vparent->num_snap_areas)
	{
		MEMORYSTATUS memstat;
		GlobalMemoryStatus(&memstat);

		if((m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas) > (memstat.dwTotalPhys-0x800000))
		{
			MessageBox("You don't have enough memory for this operation.", "Memory Error");
			return;
		}
		else if((m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas) > memstat.dwAvailPhys)
		{
			if(MessageBox("Page swapping will have to occur for this operation to complete, "
				" the snap could take minutes. Are you sure you want to continue?",
				"Memory Alert", MB_OKCANCEL) == IDCANCEL )
			{
				return;
			}

		}

 		m_vparent->num_snap_areas = new_num_img_areas;

		m_slider->SetRange(0, m_vparent->num_snap_areas - 1, TRUE);
		m_slider->SetPos(0);

		if(m_imgBuf)
		{
			GlobalFreePtr(m_imgBuf);
		}

		// allocate space for image ring buffer to be the destination of the host seq snap operation
		m_imgBuf = (BYTE*) GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->num_snap_areas);
	}


	m_ImgConn->GetSrc()->SetBufferAddr(m_imgBuf);
	HCURSOR hcurSave;

	// Set the cursor to the hourglass and save the previous cursor.
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));

	// start the snap operation going
	DWORD dwMilliseconds = 200 * m_vparent->num_snap_areas;

	pEdit = (CEdit*) GetDlgItem(IDC_TOTAL_TIME);
	ASSERT(pEdit);
	LastTime = theApp->m_iCap->m_os->GetSystimeMillisecs();
	
	theApp->m_cam->SeqSnap(m_imgBuf, m_vparent->num_snap_areas, 0, 0, (short) m_areaDx, (short) m_areaDy, dwMilliseconds);


	TotalTime = theApp->m_iCap->m_os->GetSystimeMillisecs() - LastTime;
	str.Format("%d", (int) TotalTime);
	pEdit->SetWindowText (str);

	pEdit = (CEdit*) GetDlgItem(IDC_FRAME_TIME);
	ASSERT(pEdit);
	str.Format("%d", (int) (TotalTime / m_vparent->num_snap_areas));
	pEdit->SetWindowText (str);

	// Restore the previous cursor.
	::SetCursor(hcurSave);

	// Display the processed frame in our client window
	m_ImgConn->Display();
}


void CDlgsnap::OnPlay() 
{
	BYTE *frame_addr;
	int i;

	m_vparent->DelImageServer();

	m_slider->SetRange(0, m_vparent->num_snap_areas - 1, TRUE);

	// play the recorded sequence of frames
	for(i=0; i<m_vparent->num_snap_areas; i++)
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
                "All Files (*.*)|*.*||");
	result = dg.DoModal();
	if (result == IDOK) {
		CString fname= dg.GetFileTitle() ;   // dgf.GetPathName();
		CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
		CAM_ATTR attr;
		
		// Get the current acquisition dimensions
		theapp->m_cam->GetAttr(&attr);
		m_areaDx = attr.dwWidth;
		m_areaDy = attr.dwHeight;
		for(int i=0;i< m_vparent->num_snap_areas;i++) {
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
	CSeqsnapApp	*theApp = (CSeqsnapApp*) AfxGetApp();
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
			IfxSaveToAviFile(m_NumFrames, 1, FName.GetBuffer(FName.GetLength()), m_imgBuf, attr.dwWidth, attr.dwHeight, attr.dwBitsPerPixel, 30L,0,  0,  0, 0, 0 );
		}
	}
}
