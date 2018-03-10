/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVision/Seqsnap/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 12/07/00 1:41p $
 *
 * ABSTRACT
 *    PCDig Example Program
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
	m_imgBuf = NULL;
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
	ON_BN_CLICKED(IDOK, OnClose)
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
	m_ImgConn = new CImgConn(m_imgBuf,(WORD)m_areaDx,(WORD)m_areaDy,(WORD)attr.dwBitsPerPixel, m_vparent->m_hWnd);

	m_vparent->CreateImageServer(NULL);
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
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
    CEdit *numframeID = (CEdit*) GetDlgItem(IDC_NUMFRAMES);
	CString str((char) ' ', 80);

	numframeID->GetWindowText(str);
	new_num_img_areas = atoi(str);

	m_slider->SetPos(0);
	//m_vparent->CreateImageServer(NULL);
	m_vparent->DelImageServer();

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
	DWORD dwMilliseconds = 300 * m_vparent->num_snap_areas;
	theApp->m_cam->SeqSnap(m_imgBuf, m_vparent->num_snap_areas, 0, 0, (short) m_areaDx, (short) m_areaDy, dwMilliseconds);

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
		Sleep(50);				// Play frames at roughly 30HZ
	}

}

void CDlgsnap::OnLive() 
{
	m_slider->SetPos(0);
	m_vparent->CreateImageServer(NULL);
}

void CDlgsnap::OnClose() 
{
	CDialog::OnOK();

	if(m_imgBuf)
	{
		GlobalFreePtr(m_imgBuf);
		m_imgBuf = NULL;
	}

	m_vparent->CreateImageServer(NULL);
	
}
