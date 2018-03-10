// FrameTrig.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "FrameTrig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrameTrig dialog


CFrameTrig::CFrameTrig(CWnd* pParent /*=NULL*/)
	: CDialog(CFrameTrig::IDD, pParent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	//{{AFX_DATA_INIT(CFrameTrig)
	m_frameTrigFreq = (float)cam->GetAcqParam(CL2_FRAME_TRIG_FREQ);
	m_frameTrigSrc = (DWORD)cam->GetAcqParam(CL2_FRAME_TRIG_SRC);
	m_framePerTrigger = (DWORD)cam->GetAcqParam(P_FRAMES_PER_TRIGGER);
	//}}AFX_DATA_INIT
}


void CFrameTrig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFrameTrig)
	DDX_Text(pDX, IDC_FRAME_TRIG_FREQ, m_frameTrigFreq);
	DDV_MinMaxFloat(pDX, m_frameTrigFreq, 0.1f, 10000.f);
	DDX_Radio(pDX, IDC_FRAME_TRIG_SRC, m_frameTrigSrc);
	DDX_Text(pDX, IDC_FRAMES_PER_TRIG, m_framePerTrigger);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFrameTrig, CDialog)
	//{{AFX_MSG_MAP(CFrameTrig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameTrig message handlers

void CFrameTrig::OnOK() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	UpdateData(TRUE);

	cam->SetAcqParam(CL2_FRAME_TRIG_SRC, m_frameTrigSrc);
	cam->SetAcqParam(P_FRAMES_PER_TRIGGER, m_framePerTrigger);
	cam->SetAcqParam(CL2_FRAME_TRIG_FREQ, m_frameTrigFreq);
	
	CDialog::OnOK();
}

BOOL CFrameTrig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
