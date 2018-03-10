/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/SEQSNAP/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 1/23/02 10:32a $
 *
 * ABSTRACT
 *    PCRGB Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "Dlgsnap.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap dialog


CDlgsnap::CDlgsnap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgsnap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgsnap)
	//}}AFX_DATA_INIT
	m_vparent = (CSeqsnapView*)pParent;
}


CDlgsnap::~CDlgsnap()
{
	if (m_ImgConn)
		delete m_ImgConn;
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
	ON_BN_CLICKED(IDC_SAVESEQ, OnSaveseq)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap message handlers




BOOL CDlgsnap::OnInitDialog() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CDialog::OnInitDialog();
	char numf_buffer[20];	
    CEdit *numframeID = (CEdit*)GetDlgItem(IDC_NUMFRAMES);
	// Set number of frames in slider control.
	numframeID->SetWindowText(itoa(m_vparent->num_snap_areas, numf_buffer, 10));
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_vparent->num_snap_areas-1, FALSE);
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theapp->m_cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_bytesPerPixel = attr.dwBytesPerPixel;

	
	// allocate space for image ring buffer to be the destination of the host seq snap operation
	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->num_snap_areas);
	m_ImgConn = new CImgConn(m_imgBuf,(WORD)m_areaDx,(WORD)m_areaDy,(WORD)attr.dwBitsPerPixel, m_vparent->m_hWnd);

	
//	m_vparent->CreateImageServer(NULL);
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
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
    CEdit *numframeID = (CEdit*)GetDlgItem(IDC_NUMFRAMES);
	CString str((char)' ',80);       
	numframeID->GetWindowText(str);
	new_num_img_areas = atoi(str);
	m_vparent->DelImageServer();
	if (new_num_img_areas != m_vparent->num_snap_areas) {
		MEMORYSTATUS memstat;
		DWORD newNumBytes = m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas;
		GlobalMemoryStatus(&memstat);
		if (newNumBytes > (memstat.dwTotalPhys-0x800000)) {
			MessageBox("You don't have enough memory for this operation.", "Memory Error");
			return;
		}
		else if (newNumBytes > memstat.dwAvailPhys) {
			if (MessageBox("Page swapping will have to occur for this operation to complete, "
				" the snap could take minutes. Are you sure you want to continue?",
				"Memory Alert",MB_OKCANCEL) == IDCANCEL )
				return;

		}
 		m_vparent->num_snap_areas = new_num_img_areas;
		m_slider->SetRange(0, m_vparent->num_snap_areas-1, FALSE);
		GlobalFreePtr(m_imgBuf);

		// allocate space for image ring buffer to be the destination of the host seq snap operation
		m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,newNumBytes);

	}
	m_ImgConn->GetSrc()->SetBufferAddr(m_imgBuf);
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	// start the snap operation going
	theapp->m_cam->Freeze();
	theapp->m_cam->SeqSnap(m_imgBuf,m_vparent->num_snap_areas,0,0,(short)m_areaDx,(short)m_areaDy);

	/* Restore the previous cursor. */
	::SetCursor(hcurSave);


	// Display the processed frame in our client window
	m_ImgConn->Display();
}

void CDlgsnap::OnPlay() 
{
	BYTE *frame_addr;
	int i;
	m_vparent->DelImageServer();
	// play the recorded sequence of frames
	for (i=0;i<m_vparent->num_snap_areas;i++) {
		m_slider->SetPos(i);
		frame_addr = m_imgBuf + i * (m_areaDx*m_areaDy*m_bytesPerPixel);
		m_ImgConn->GetSrc()->SetBufferAddr(frame_addr);
		m_ImgConn->Display();
		Sleep(30);	// Play frames at roughly 30HZ
	}
}

void CDlgsnap::OnLive() 
{
	m_vparent->CreateImageServer(NULL);	
}

void CDlgsnap::OnSaveseq() 
{
	// TODO: Add your control notification handler code here
	int result;
	CFileDialog dg(FALSE,"tif",NULL,	
    			OFN_HIDEREADONLY,
                "TIF Files (*.tif)|*.tif|"
                "BMP Files (*.bmp)|*.bmp|"
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
		if (attr.color == IFC_MONO && attr.dwBitsPerPixel > 8) {
			MessageBox("MONO bit depths greater than 8 not supported.");
		}
		else {			
		
			for(int i=0;i< m_vparent->num_snap_areas;i++){
				CString imgFileName;
				imgFileName.Format("%s%d.%s",fname.GetBuffer(80),i, dg.GetFileExt().GetBuffer(80));
				fname.ReleaseBuffer();
				dg.GetFileExt().ReleaseBuffer();

				CImgFile *imgFile=IfxCreateImgFile(imgFileName.GetBuffer(80));
				imgFileName.ReleaseBuffer();

				if (imgFile) {
					IFFCLASS_TYPE FileColor;
					
					if (attr.color == IFC_RGB || attr.color == IFC_RGB_PACK24)
						FileColor = IFFCL_RGB;
					else
						FileColor = IFFCL_GRAY;

					// Write images to a TIFF files
					if (!imgFile->WriteFile(m_imgBuf + i * (m_areaDx*m_areaDy*m_bytesPerPixel),m_areaDx,m_areaDy,(WORD)attr.dwBitsPerPixel,FileColor))
						MessageBox("Bit depth not supported.");

					delete imgFile;
				}
				else
					MessageBox("Could not open write file.");
			}
		}
	}
	
}
