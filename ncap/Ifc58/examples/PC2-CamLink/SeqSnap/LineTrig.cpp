// LineTrig.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "LineTrig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineTrig dialog


CLineTrig::CLineTrig(CWnd* pParent /*=NULL*/)
	: CDialog(CLineTrig::IDD, pParent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();
	//{{AFX_DATA_INIT(CLineTrig)
	m_trigCycleTime = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_CYCLE_TIME);
	m_lineTrigDebounce = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_DEBOUNCE);
	m_numPhase = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_NUM_PHASE);
	m_lineTrigSrc = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_SRC);
//	m_linesPerTrig = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_MUL_FACTOR);
	m_lineTrigEnable = (DWORD)theapp->m_cam->GetAcqParam(CL2_LINE_TRIG_ENABLE);
	m_vframeStart = (DWORD)theapp->m_cam->GetAcqParam(CL2_VFRAME_TRIG_SOURCE);
	//}}AFX_DATA_INIT
}


void CLineTrig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineTrig)
	DDX_Text(pDX, IDC_LINE_TRIG_CYCLE_TIME, m_trigCycleTime);
	DDV_MinMaxUInt(pDX, m_trigCycleTime, 1, 65535);
	DDX_Text(pDX, IDC_LINE_TRIG_DEBOUNCE, m_lineTrigDebounce);
	DDV_MinMaxUInt(pDX, m_lineTrigDebounce, 0, 255);
	DDX_Text(pDX, IDC_LINE_TRIG_NUM_PHASE, m_numPhase);
	DDV_MinMaxUInt(pDX, m_numPhase, 1, 2);
	DDX_Radio(pDX, IDC_LINE_TRIG_SRC, m_lineTrigSrc);
	DDX_Radio(pDX, IDC_TRIG_ENABLE, m_lineTrigEnable);
	DDX_Radio(pDX, IDC_VFRAME_START, m_vframeStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineTrig, CDialog)
	//{{AFX_MSG_MAP(CLineTrig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineTrig message handlers

BOOL CLineTrig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLineTrig::OnOK() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();
	UpdateData(TRUE);

	theapp->m_cam->SetAcqParam(CL2_VFRAME_TRIG_SOURCE,m_vframeStart);
	theapp->m_cam->SetAcqParam(CL2_LINE_TRIG_ENABLE,m_lineTrigEnable);
	theapp->m_cam->SetAcqParam(CL2_LINE_TRIG_SRC,m_lineTrigSrc);
	theapp->m_cam->SetAcqParam(CL2_LINE_TRIG_NUM_PHASE,m_numPhase);
	theapp->m_cam->SetAcqParam(CL2_LINE_TRIG_DEBOUNCE,m_lineTrigDebounce);
	theapp->m_cam->SetAcqParam(CL2_LINE_TRIG_CYCLE_TIME,m_trigCycleTime);
	
	CDialog::OnOK();
}
