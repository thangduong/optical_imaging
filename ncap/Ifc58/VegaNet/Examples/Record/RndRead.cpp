// RndRead.cpp : implementation file
//

#include "stdafx.h"
#include "Record.h"
#include "RndRead.h"
#include "RecordView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRndRead dialog


CRndRead::CRndRead(CWnd* pParent /*=NULL*/)
	: CDialog(CRndRead::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRndRead)
	m_rndFrameNum = 0;
	m_timeStampStr = _T("");
	//}}AFX_DATA_INIT
	m_vparent = (CMyRecordView*)pParent;
	m_startPos = 0;
	m_inRandomRead = TRUE;
	m_pause = TRUE;

}


void CRndRead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRndRead)
	DDX_Control(pDX, IDC_SLIDER1, m_ctlSlider);
	DDX_Text(pDX, IDC_RND_FRAME_NUM, m_rndFrameNum);
	DDX_Text(pDX, IDC_TIMESTAMP, m_timeStampStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRndRead, CDialog)
	//{{AFX_MSG_MAP(CRndRead)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_FAST, OnFast)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_REWIND, OnRewind)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRndRead message handlers

BOOL CRndRead::OnInitDialog() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	CDialog::OnInitDialog();
	
    m_ctlSlider.SetRange(0, m_vparent->m_randomNumFrames-1, FALSE);
	theApp->m_FileNode->ReadRandom(	0);

	m_nTimer = SetTimer(1, 500, 0);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

static char *months[] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

void CRndRead::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	
	// Get the minimum and maximum scroll-bar positions.
	int minpos=0;
	int maxpos;
	DWORD randomNumFrames;
	maxpos = m_vparent->m_randomNumFrames-1;
	
	// Get the current position of scroll box.
	int curpos = m_ctlSlider.GetPos();
	
	if (!m_inRandomRead) {
		m_pause = TRUE;
		theApp->m_FileNode->StopRead();		
		theApp->m_FileNode->StartRandomRead(m_activeFileName.GetBuffer(80),&randomNumFrames );
		m_inRandomRead = TRUE;
	}	

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
	
	theApp->m_FileNode->ReadRandom(	curpos);
	
	m_rndFrameNum=curpos;

	SYSTEMTIME sysTime;
	if ( m_vparent->m_imgAttr.ArrivalTime) {
		ULONGLONG time = m_vparent->m_imgAttr.ArrivalTime * 10;
		FileTimeToSystemTime((FILETIME*)&time,&sysTime);
	}
	else {
		GetSystemTime(&sysTime);
	}

    m_timeStampStr.Format( "%s %02d, %04d %02d:%02d:%02d.%03d GMT",
		months[sysTime.wMonth-1],
		sysTime.wDay,sysTime.wYear,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds); 

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(FALSE);

}

void CRndRead::OnPlay() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	m_inRandomRead = FALSE;
	theApp->m_FileNode->StopRead();		
	m_startPos = 0;
	m_pause = FALSE;
	theApp->m_FileNode->StartReadFrom(m_activeFileName.GetBuffer(80),m_startPos , 1);		
	
}

void CRndRead::OnFast() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	DWORD fileNumFrames;
	m_pause = FALSE;
	if (m_inRandomRead) {
		m_startPos = m_rndFrameNum;
	}
	else {
		theApp->m_FileNode->GetReadFilePos(&m_startPos, &fileNumFrames);
	}
	m_inRandomRead = FALSE;
	theApp->m_FileNode->StopRead();		
	if (m_startPos >= fileNumFrames)
		m_startPos=0;

	theApp->m_FileNode->StartReadFrom(m_activeFileName.GetBuffer(80), m_startPos, 5);		
	
}

void CRndRead::OnStop() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	m_startPos = 0;
	m_pause = TRUE;
	m_inRandomRead = FALSE;
	theApp->m_FileNode->StopRead();		
	
}

void CRndRead::OnPause() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	DWORD fileNumFrames;
	theApp->m_FileNode->GetReadFilePos(&m_startPos, &fileNumFrames);
	if (m_inRandomRead) {
		m_startPos = m_ctlSlider.GetPos();
	}
	m_inRandomRead = FALSE;
	m_pause ^= 1;
	if (m_pause) {
		theApp->m_FileNode->Pause();		
	}
	else {
		theApp->m_FileNode->Resume();		
	}	
}

void CRndRead::OnRewind() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();
	DWORD fileNumFrames;
	m_pause = FALSE;
	theApp->m_FileNode->GetReadFilePos(&m_startPos, &fileNumFrames);
	if (m_inRandomRead) {
		m_startPos = m_rndFrameNum;
	}
	m_inRandomRead = FALSE;
	if (m_startPos==0 || m_startPos > fileNumFrames)
		m_startPos = fileNumFrames;

	theApp->m_FileNode->StopRead();		
	theApp->m_FileNode->StartReadFrom(m_activeFileName.GetBuffer(80), m_startPos-1, -5);		
	
}

void CRndRead::OnTimer(UINT nIDEvent) 
{
	DWORD fileNumFrames;
	DWORD readPos;
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();

	if (!m_inRandomRead) {
		
		theApp->m_FileNode->GetReadFilePos(&readPos, &fileNumFrames);
		m_rndFrameNum=readPos;
		m_ctlSlider.SetPos(readPos);
		UpdateData(FALSE);
	}	
	SYSTEMTIME sysTime;
	if ( m_vparent->m_imgAttr.ArrivalTime) {
		ULONGLONG time = m_vparent->m_imgAttr.ArrivalTime * 10;
		FileTimeToSystemTime((FILETIME*)&time,&sysTime);
	}
	else {
		GetSystemTime(&sysTime);
	}

    m_timeStampStr.Format( "%s %02d, %04d %02d:%02d:%02d.%03d GMT",
		months[sysTime.wMonth-1],
		sysTime.wDay,sysTime.wYear,
		sysTime.wHour,
		sysTime.wMinute,
		sysTime.wSecond,
		sysTime.wMilliseconds); 

	CDialog::OnTimer(nIDEvent);
}

void CRndRead::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(m_nTimer);   
	
}

void CRndRead::OnOK() 
{
	CRecordApp *theApp = (CRecordApp *) AfxGetApp();	
	CDialog::OnOK();
	theApp->m_FileNode->StopRead();		

	if (theApp->m_vnmFileName[0]) {
	  AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
}
