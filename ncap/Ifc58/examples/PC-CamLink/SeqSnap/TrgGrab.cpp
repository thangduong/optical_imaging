// TrgGrab.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "TrgGrab.h"
#include "TrigPro.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab property page

IMPLEMENT_DYNCREATE(CTrgGrab, CPropertyPage)


CTrgGrab::CTrgGrab(CTrgSheet *parent)
: CPropertyPage(CTrgGrab::IDD)
{
	//{{AFX_DATA_INIT(CTrgGrab)
	m_TrigStartEvent = 0;
	m_TrigEndEvent = 0;
	m_continuousSWTrig = TRUE;
	//}}AFX_DATA_INIT
	m_parent = parent;
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;
	m_startEvent = LNK_TMODE_DISABLE;
	m_stopEvent = LNK_TMODE_DISABLE;
	m_trgThread = NULL;

}

CTrgGrab::CTrgGrab()
: CPropertyPage(CTrgGrab::IDD)
{
}

CTrgGrab::~CTrgGrab()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	if (m_trgThread)
		delete m_trgThread;
	((CPCLink*)(theapp->m_iCap))->SetAcqTriggerEvents(LNK_TMODE_DISABLE ,LNK_TMODE_DISABLE);
}

void CTrgGrab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrgGrab)
	DDX_Radio(pDX, IDC_TRIG_START_DISABLE, m_TrigStartEvent);
	DDX_Radio(pDX, IDC_TRIG_END_DISABLE, m_TrigEndEvent);
	DDX_Check(pDX, IDC_CONT_SW_TRIG, m_continuousSWTrig);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrgGrab, CPropertyPage )
	//{{AFX_MSG_MAP(CTrgGrab)
	ON_BN_CLICKED(IDC_TRGSTART, OnTrgstart)
	ON_BN_CLICKED(IDC_TRGSTOP, OnTrgstop)
	ON_BN_CLICKED(IDC_TRGTIME, OnTrgtime)
	ON_BN_CLICKED(IDC_CONT_SW_TRIG, OnContSwTrig)
	ON_BN_CLICKED(IDC_GEN_SW_TRIG, OnGenSwTrig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab message handlers

void CTrgGrab::OnTrgstart() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	

	UpdateData(TRUE);
	// Delete any pre-existing trigger thread
	if (m_trgThread)
		delete m_trgThread;

	if (m_TrigStartEvent != 0)
		m_startEvent = (LNK_TRIG_MODE_TYPE)(m_TrigStartEvent+1);
	else 
		m_startEvent = LNK_TMODE_DISABLE;

	if (m_TrigEndEvent != 0)
		m_stopEvent = (LNK_TRIG_MODE_TYPE)(m_TrigEndEvent+1);
	else 
		m_stopEvent = LNK_TMODE_DISABLE;

	((CPCLink*)(theapp->m_iCap))->SetAcqTriggerEvents(m_startEvent ,m_stopEvent);
	// start a thread which will cause a frame snap to occur every time 
	// a trigger happens
	m_trgThread = new CTrgThrd(m_parent);
	
}


void CTrgGrab::OnTrgstop() 
{
	CSeqsnapApp *theApp=(CSeqsnapApp*)AfxGetApp();	
	// Stop any existing trigger thread
	if (m_trgThread)
		delete m_trgThread;
	m_trgThread = NULL;
}


void CTrgGrab::OnTrgtime() 
{
	char msg[200];
	sprintf(msg,"Frame-to-frame time; Max: %d ms,  Min: %d ms,  Avg: %d ms",
		m_maxTime,m_minTime,m_avgTime);
	MessageBox(msg,"Trigger Frame Time Parameters");
	
}

BOOL CTrgGrab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTrgGrab::OnContSwTrig() 
{
	UpdateData(TRUE);
	
}

void CTrgGrab::OnGenSwTrig() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	cam->SetAcqParam(P_GEN_SW_TRIGGER,0,0);	
}
