// TrigGrabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "TrigGrabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg dialog


CTrigGrabDlg::CTrigGrabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrigGrabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrigGrabDlg)
	m_iTrigPolarity = -1;
	m_iTrigSrc = -1;
	//}}AFX_DATA_INIT
	m_vParent = (CSeqsnapView*) pParent;
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;
	m_trgThread = NULL;
}


void CTrigGrabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrigGrabDlg)
	DDX_Radio(pDX, IDC_FALLING_EDGE, m_iTrigPolarity);
	DDX_Radio(pDX, IDC_SW_TRIG, m_iTrigSrc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrigGrabDlg, CDialog)
	//{{AFX_MSG_MAP(CTrigGrabDlg)
	ON_BN_CLICKED(IDC_TRGSTART, OnTrgstart)
	ON_BN_CLICKED(IDC_TRGSTOP, OnTrgstop)
	ON_BN_CLICKED(IDC_TRGTIME, OnTrgtime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg message handlers

BOOL CTrigGrabDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	RefreshDialogFromCamParams();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTrigGrabDlg::RefreshDialogFromCamParams()
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
	CICamera *cam = theApp->m_cam;
	m_iTrigPolarity = (int) cam->GetAcqParam(P_TRIGGER_POLARITY);
	m_iTrigSrc		= (int) cam->GetAcqParam(P_TRIGGER_SRC);
}

void CTrigGrabDlg::OnTrgstart() 
{
	UpdateData(TRUE);
	// Delete any pre-existing trigger thread
	if (m_trgThread)
		delete m_trgThread;
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;
	cam->Freeze();
	cam->SetAcqParam(P_TRIGGER_POLARITY, m_iTrigPolarity);
	cam->SetAcqParam(P_TRIGGER_SRC, m_iTrigSrc);
	cam->SetAcqParam(PCR_TRIG_CYCLE_LATCH_TRIG, IFC_DISABLE);
	cam->SetAcqParam(P_TRIGGER_ENABLE, IFC_ENABLE);
	m_trgThread = new CTrgThrd(this);
}

void CTrigGrabDlg::OnTrgstop() 
{
	// Stop any existing trigger thread
	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;
	cam->SetAcqParam(P_TRIGGER_ENABLE, IFC_DISABLE);
}

void CTrigGrabDlg::OnTrgtime() 
{
	char msg[200];
	sprintf(msg,"Frame-to-frame time; Max: %d ms,  Min: %d ms,  Avg: %d ms",
		    m_maxTime,m_minTime,m_avgTime);
	MessageBox(msg,"Trigger Frame Time Parameters");
}

void CTrigGrabDlg::OnOK() 
{
	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	
	CDialog::OnOK();
}
