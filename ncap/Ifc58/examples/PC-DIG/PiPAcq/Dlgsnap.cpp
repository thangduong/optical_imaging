/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PiPAcq/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 2/08/01 1:57p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "PipAcq.h"
#include "Dlgsnap.h"
#include <windowsx.h>
#include <pcdig.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


const char *PIPMessage = "End of Part-in-Place Image";

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap dialog


CDlgsnap::CDlgsnap(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgsnap::IDD, pParent)
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	//{{AFX_DATA_INIT(CDlgsnap)
	m_TimeOutTime = 5000;
	m_PipTrigger = 1;
	m_ExsyncMode = (int)theapp->m_cam->GetAcqParam(PCD_EXSYNC_MODE);
	m_numFrames = 1;
	//}}AFX_DATA_INIT
	m_vparent = (CLargeAcqView*)pParent;
	m_SeqSnapBuf=NULL;
}


CDlgsnap::~CDlgsnap()
{
}

void CDlgsnap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgsnap)
	DDX_Text(pDX, IDC_TIMEOUT, m_TimeOutTime);
	DDX_Radio(pDX, IDC_PIP_TRIG, m_PipTrigger);
	DDX_Radio(pDX, IDC_EXSYNC_MODE, m_ExsyncMode);
	DDX_Text(pDX, IDC_NUMFRAMES, m_numFrames);
	DDV_MinMaxUInt(pDX, m_numFrames, 1, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgsnap, CDialog)
	//{{AFX_MSG_MAP(CDlgsnap)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_SNAP, OnSnap)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_SSGRAB, OnGrab)
	ON_BN_CLICKED(IDC_SNAP_SAVE, OnSnapSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap message handlers




BOOL CDlgsnap::OnInitDialog() 
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	CDialog::OnInitDialog();
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_numFrames-1, FALSE);
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
   maxpos = m_numFrames - 1;
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

	if (m_SeqSnapBuf) {
		BYTE *displayAddr = m_SeqSnapBuf + curpos * (m_areaDx*m_areaDy*m_bytesPerPixel);
		// Update the address associated with the image source to point to the frame
		// we just processed
		m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(displayAddr);		

		// Display the selected frame in our client window
		m_vparent->m_hImgConn->Display();
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgsnap::OnSnap() 
{
	SeqSnapAndSave(FALSE);
}

void CDlgsnap::OnSnapSave() 
{
	SeqSnapAndSave(TRUE);	
}

void CDlgsnap::SeqSnapAndSave(BOOL saveTif) 
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();
	DWORD AcquiredDys[1000];
	char tifFile[80];
	CImgFile *imgFile;
	CAM_ATTR attr;
	theapp->m_cam->GetAttr(&attr);
	UpdateData(TRUE);
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_numFrames-1, FALSE);
	DWORD acqDy=m_areaDy;
	m_vparent->StopGrab();

	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));

	theapp->m_cam->SetAcqParam(PCD_EXSYNC_MODE,m_ExsyncMode);
	// start the snap operation going
	if (m_PipTrigger==0)
		((CPCDig*)(theapp->m_pMod))->SetAcqTriggerEvents(PCD_TMODE_HWTRIG0_ASSERT ,PCD_TMODE_HWTRIG0_DEASSERT);
	else if (m_PipTrigger==1)
		((CPCDig*)(theapp->m_pMod))->SetAcqTriggerEvents(PCD_TMODE_HWTRIG1_ASSERT ,PCD_TMODE_HWTRIG1_DEASSERT);
	else
		((CPCDig*)(theapp->m_pMod))->SetAcqTriggerEvents(PCD_TMODE_DISABLE ,PCD_TMODE_DISABLE);

	// Wait to acquire new_num_img_areas frames
	m_SeqSnapBuf=theapp->m_cam->SeqSnapPhys(m_numFrames,0,0,0,(short)m_areaDx,(short)m_areaDy,m_TimeOutTime,AcquiredDys);
	if (m_SeqSnapBuf) {
		DWORD frame_count;
		for (frame_count=0; frame_count < m_numFrames ; frame_count++) {
			BYTE *frameAddr=m_SeqSnapBuf+frame_count*m_areaDx*m_areaDy*attr.dwBytesPerPixel;
			acqDy=AcquiredDys[frame_count];
			if (saveTif) {
				sprintf(tifFile,"img%d.tif",frame_count);
				if (imgFile=IfxCreateImgFile(tifFile)) {
					imgFile->WriteFile(frameAddr,m_areaDx,acqDy,(WORD)attr.dwBitsPerPixel);
					delete imgFile;
				}
			}
			if (acqDy < m_areaDy) {
				memset(frameAddr + m_areaDx * acqDy * m_bytesPerPixel,0,
					m_areaDx * (m_areaDy-acqDy) * m_bytesPerPixel);
			}
		}
		
		m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(m_SeqSnapBuf);
	}
	else {
			MessageBox("Inadequate memory or timeout.","SeqSnap Error");		
	}
	
	((CPCDig*)(theapp->m_pMod))->SetAcqTriggerEvents(PCD_TMODE_DISABLE ,PCD_TMODE_DISABLE);
	theapp->m_cam->Freeze();
	
	/* Restore the previous cursor. */
	::SetCursor(hcurSave);

	
	// Display the processed frame in our client window
	m_vparent->m_hImgConn->Display();
	if (acqDy < m_areaDy) {
		HDC hdc=::GetDC(m_vparent->m_hWnd);
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc,0x00ff0000);
		TextOut(hdc,20,acqDy,PIPMessage,strlen(PIPMessage));
		::ReleaseDC(m_vparent->m_hWnd,hdc);
	}
	
}

void CDlgsnap::OnPlay() 
{
	BYTE *frame_addr;
	DWORD i;
	m_vparent->StopGrab();
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
	// play the recorded sequence of frames
	if (m_SeqSnapBuf) {
		m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(m_SeqSnapBuf);
		for (i=0;i < m_numFrames;i++) {
			m_slider->SetPos(i);
			frame_addr = m_SeqSnapBuf + i * (m_areaDx*m_areaDy*m_bytesPerPixel);
			m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(frame_addr);
			m_vparent->m_hImgConn->Display();
			Sleep(30);	// Play frames at roughly 30HZ
		}
	}
}


void CDlgsnap::OnGrab() 
{
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();	
	UpdateData(TRUE);
	theapp->m_cam->SetAcqParam(PCD_EXSYNC_MODE,m_ExsyncMode);
	m_vparent->m_hImgConn->GetSrc()->SetBufferAddr(m_vparent->m_pImgBuff);

	if (!m_vparent->m_grabThread)
		m_vparent->m_grabThread = new CTrgThrd(m_vparent);
}

