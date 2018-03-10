/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/LargeAcq/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/22/00 3:06p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "LargeAcq.h"
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
	m_vparent = (CLargeAcqView*)pParent;
}


CDlgsnap::~CDlgsnap()
{
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
	ON_BN_CLICKED(IDC_SSGRAB, OnGrab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap message handlers




BOOL CDlgsnap::OnInitDialog() 
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	CDialog::OnInitDialog();
	char numf_buffer[20];	
    CEdit *numframeID = (CEdit*)GetDlgItem(IDC_NUMFRAMES);
	// Default number of frames in slider control to 8
	numframeID->SetWindowText(itoa( m_vparent->m_numFramesInHostBuf,numf_buffer,10));
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_vparent->m_numFramesInHostBuf-1, FALSE);
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theapp->m_cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_bytesPerPixel = attr.dwBytesPerPixel;

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgsnap::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{

   // Get the minimum and maximum scroll-bar positions.
   int minpos=0;
   int maxpos;
   maxpos = m_vparent->m_numFramesInHostBuf-1;
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);

   // Get the current position of scroll box.
   int curpos = m_slider->GetPos();


   // Determine the new position of scroll box.
   switch (nSBCode)
   {
   case SB_LEFT:      // Scroll to far left.
      curpos = minpos;
      break;

   case SB_RIGHT:      // Scroll to far right.
      curpos = maxpos;
      break;

   case SB_ENDSCROLL:   // End scroll.
      break;

   case SB_LINELEFT:      // Scroll left.
      if (curpos > minpos)
         curpos--;
      break;

   case SB_LINERIGHT:   // Scroll right.
      if (curpos < maxpos)
         curpos++;
      break;

   case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
      curpos = nPos;      // of the scroll box at the end of the drag operation.
      break;

   case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
      curpos = nPos;     // position that the scroll box has been dragged to.
      break;
   }


	m_vparent->m_pHostBuffFrame = m_vparent->m_pImgBuff + curpos * (m_areaDx*m_areaDy*m_bytesPerPixel);
	// Update the address associated with the image source to point to the frame
	// we just processed
	m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(m_vparent->m_pHostBuffFrame);		

	// Display the selected frame in our client window
	m_vparent->m_hImgConn->Display();
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgsnap::OnSnap() 
{
	DWORD new_num_img_areas;	
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
    CEdit *numframeID = (CEdit*)GetDlgItem(IDC_NUMFRAMES);
	CString str((char)' ',80);       
	numframeID->GetWindowText(str);
	new_num_img_areas = atoi(str);
	m_vparent->StopGrab();
	if (new_num_img_areas != m_vparent->m_numFramesInHostBuf) {
		MEMORYSTATUS memstat;
		GlobalMemoryStatus(&memstat);

		if ((m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas) > (memstat.dwTotalPhys-0x1800000)) {
			MessageBox("You don't have enough memory for this operation.", "Memory Error");
			return;
		}
		else if ((m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas) > memstat.dwAvailPhys) {
			if (MessageBox("Page swapping will have to occur for this operation to complete, "
				" the snap could take minutes. Are you sure you want to continue?",
				"Memory Alert",MB_OKCANCEL) == IDCANCEL )
				return;

		}
 		m_vparent->m_numFramesInHostBuf = new_num_img_areas;
		m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
		ASSERT(m_slider);
		m_slider->SetRange(0, m_vparent->m_numFramesInHostBuf-1, FALSE);
		GlobalFreePtr(m_vparent->m_pImgBuff);

		// allocate space for image ring buffer to be the destination of the host seq snap operation
		m_vparent->m_pImgBuff = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->m_numFramesInHostBuf);
		m_vparent->m_pHostBuffFrame = m_vparent->m_pImgBuff;

	}
	m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(m_vparent->m_pHostBuffFrame);
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	// start the snap operation going
	theapp->m_cam->SeqSnap(m_vparent->m_pImgBuff,m_vparent->m_numFramesInHostBuf,0,0,(short)m_areaDx,(short)m_areaDy);

	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	// Display the processed frame in our client window
	m_vparent->m_hImgConn->Display();
}

void CDlgsnap::OnPlay() 
{
	BYTE *frame_addr;
	DWORD i;
	m_vparent->StopGrab();
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
	// play the recorded sequence of frames
	for (i=0;i<m_vparent->m_numFramesInHostBuf;i++) {
		m_slider->SetPos(i);
		frame_addr = m_vparent->m_pImgBuff + i * (m_areaDx*m_areaDy*m_bytesPerPixel);
		m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(frame_addr);
		m_vparent->m_hImgConn->Display();
		Sleep(30);	// Play frames at roughly 30HZ
	}
}


void CDlgsnap::OnGrab() 
{
	if (!m_vparent->m_grabThread)
		m_vparent->m_grabThread = new CTrgThrd(m_vparent);
}
