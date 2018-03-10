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
	//}}AFX_DATA_INIT
	m_parent = parent;
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;
	m_startEvent = PCL_TMODE_DISABLE;
	m_stopEvent = PCL_TMODE_DISABLE;
	m_trgThread = NULL;
	m_trgRleThread = NULL;

}

CTrgGrab::CTrgGrab()
: CPropertyPage(CTrgGrab::IDD)
{
}

CTrgGrab::~CTrgGrab()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	if (m_trgRleThread) {
		delete m_trgRleThread;
		m_trgRleThread = NULL;
	}
	((CPCLine*)(theapp->m_iCap))->SetAcqTriggerEvents(PCL_TMODE_DISABLE ,PCL_TMODE_DISABLE);
}

void CTrgGrab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrgGrab)
	DDX_Radio(pDX, IDC_TRIG_START_DISABLE, m_TrigStartEvent);
	DDX_Radio(pDX, IDC_TRIG_END_DISABLE, m_TrigEndEvent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrgGrab, CPropertyPage )
	//{{AFX_MSG_MAP(CTrgGrab)
	ON_BN_CLICKED(IDC_TRGSTART, OnTrgstart)
	ON_BN_CLICKED(IDC_TRGSTOP, OnTrgstop)
	ON_BN_CLICKED(IDC_TRGTIME, OnTrgtime)
	ON_BN_CLICKED(IDC_TRGSTART_RLE, OnTrgStartRle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab message handlers

void CTrgGrab::OnTrgstart() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	

	UpdateData(TRUE);
	// Delete any pre-existing trigger thread
	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	if (m_trgRleThread) {
		delete m_trgRleThread;
		m_trgRleThread = NULL;
	}

	if (m_TrigStartEvent != 0)
		m_startEvent = (PCL_TRIG_MODE_TYPE)(m_TrigStartEvent+1);
	else 
		m_startEvent = PCL_TMODE_DISABLE;

	if (m_TrigEndEvent != 0)
		m_stopEvent = (PCL_TRIG_MODE_TYPE)(m_TrigEndEvent+1);
	else 
		m_stopEvent = PCL_TMODE_DISABLE;

	((CPCLine*)(theapp->m_iCap))->SetAcqTriggerEvents(m_startEvent ,m_stopEvent);
	// start a thread which will cause a frame snap to occur every time 
	// a trigger happens
	m_trgThread = new CTrgThrd(m_parent);
	
}


void CTrgGrab::OnTrgstop() 
{
	CSeqsnapApp *theApp=(CSeqsnapApp*)AfxGetApp();	
	// Stop any existing trigger thread

	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	if (m_trgRleThread) {
		delete m_trgRleThread;
		m_trgRleThread = NULL;
	}
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


void CTrgGrab::OnTrgStartRle() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	

	UpdateData(TRUE);
	// Delete any pre-existing trigger thread

	if (m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
	}
	if (m_trgRleThread) {
		delete m_trgRleThread;
		m_trgRleThread = NULL;
	}


	if (m_TrigStartEvent != 0)
		m_startEvent = (PCL_TRIG_MODE_TYPE)(m_TrigStartEvent+1);
	else 
		m_startEvent = PCL_TMODE_DISABLE;

	if (m_TrigEndEvent != 0)
		m_stopEvent = (PCL_TRIG_MODE_TYPE)(m_TrigEndEvent+1);
	else 
		m_stopEvent = PCL_TMODE_DISABLE;

	((CPCLine*)(theapp->m_iCap))->SetAcqTriggerEvents(m_startEvent ,m_stopEvent);
	// start a thread which will cause a frame snap to occur every time 
	// a trigger happens
	m_trgRleThread = new CProcessThread(m_parent->m_vparent);		
}
