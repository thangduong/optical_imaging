/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/seqsnap/Dlgsnap.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/06/03 11:43a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "Dlgsnap.h"
#include <windowsx.h>
#include <PCLink.h>

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
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	if (m_ImgConn)
		delete m_ImgConn;
	if (m_imgBuf) {
		GlobalFreePtr(m_imgBuf);
	}
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap message handlers




BOOL CDlgsnap::OnInitDialog() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CDialog::OnInitDialog();
	char szNumFramesBuffer[20];	
    CEdit *numframeID = (CEdit*)GetDlgItem(IDC_NUMFRAMES);
	// Default number of frames in slider control to 8
	numframeID->SetWindowText(itoa( m_vparent->m_numSnapAreas,szNumFramesBuffer,10));
    m_slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER2);
    ASSERT(m_slider);
    m_slider->SetRange(0, m_vparent->m_numSnapAreas-1, FALSE);
	CAM_ATTR attr;
	
	// Get the current acquisition dimensions
	theapp->m_cam->GetAttr(&attr);
	m_areaDx = attr.dwWidth;
	m_areaDy = attr.dwHeight;
	m_bytesPerPixel = attr.dwBytesPerPixel;
	
	// allocate space for image ring buffer to be the destination of the host seq snap operation
	m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->m_numSnapAreas);
	// Pre-Lock memory so that swapping will not take place when grab is started
	if (m_imgBuf) {
		if (m_memLock=theapp->m_iCap->LockMem(m_imgBuf,m_areaDx * m_areaDy * m_bytesPerPixel * m_vparent->m_numSnapAreas)) {
			theapp->m_iCap->UnLockMem(m_memLock);
			m_memLock=NULL;
		}
	}
	else {
		return FALSE;
	}

	m_ImgConn = new CImgConn(m_imgBuf,(WORD)m_areaDx,(WORD)m_areaDy,(WORD)attr.dwBitsPerPixel, m_vparent->m_hWnd);
	
	m_vparent->CreateImageServer(NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgsnap::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	BYTE *frameAddr;
	
	// Get the minimum and maximum scroll-bar positions.
	int minpos=0;
	int maxpos;
	maxpos = m_vparent->m_numSnapAreas-1;
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
	
		
	frameAddr = m_imgBuf + curpos * (m_areaDx*m_areaDy*m_bytesPerPixel);
	// Update the address associated with the image source to point to the frame
	// we just processed
	m_ImgConn->GetSrc()->SetBufferAddr(frameAddr);		
	
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
	if (new_num_img_areas != m_vparent->m_numSnapAreas) {
		DWORD newBufSize= m_areaDx * m_areaDy * m_bytesPerPixel * new_num_img_areas;
		MEMORYSTATUS memstat;
		GlobalMemoryStatus(&memstat);
		if (newBufSize > (memstat.dwTotalPhys-0x1000000)) {
			MessageBox("You don't have enough memory for this operation.", "Memory Error");
			return;
		}
		else if (newBufSize > memstat.dwAvailPhys) {
			if (MessageBox("Page swapping will have to occur for this operation to complete, "
				" the snap could take minutes. Are you sure you want to continue?",
				"Memory Alert",MB_OKCANCEL) == IDCANCEL )
				return;
		}

		GlobalFreePtr(m_imgBuf);

		// allocate space for image ring buffer to be the destination of the host seq snap operation
		m_imgBuf = (BYTE*)GlobalAllocPtr(GMEM_FIXED,newBufSize);
		if (!m_imgBuf) return;
		// Attempt to Pre-Lock memory so that swapping will not take place when grab is started
		if (m_memLock=theapp->m_iCap->LockMem(m_imgBuf,newBufSize)) {
			theapp->m_iCap->UnLockMem(m_memLock);
			m_memLock=NULL;
		}
		m_vparent->m_numSnapAreas = new_num_img_areas;
		m_slider->SetRange(0, m_vparent->m_numSnapAreas-1, FALSE);
	}

	m_ImgConn->GetSrc()->SetBufferAddr(m_imgBuf);
	HCURSOR hcurSave;
	/* Set the cursor to the hourglass and save the previous cursor. */
	hcurSave = ::SetCursor(::LoadCursor(NULL,  MAKEINTRESOURCE(IDC_WAIT)));
	// start the snap operation going
	((CPCLink*)(theapp->m_iCap))->SetAcqTriggerEvents(LNK_TMODE_DISABLE ,LNK_TMODE_DISABLE);

	BOOL snapResult;
	snapResult=theapp->m_cam->SeqSnap(m_imgBuf,m_vparent->m_numSnapAreas,0,0,(short)m_areaDx,(short)m_areaDy,25000);


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
	for (i=0;i<m_vparent->m_numSnapAreas;i++) {
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
