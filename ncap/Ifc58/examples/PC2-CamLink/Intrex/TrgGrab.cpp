// TrgGrab.cpp : implementation file
//

#include "stdafx.h"
#include "intrex.h"
#include "TrgGrab.h"
#include "LineTrig.h"
#include "FrameTrig.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab property page



CTrgGrab::CTrgGrab(CWnd* pParent /*=NULL*/)
: CDialog(CTrgGrab::IDD, pParent)
{
	CIntrExApp *theapp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	m_debounceParamid= ((DWORD)cam->GetAcqParam(P_FEN_ENABLE)==IFC_ENABLE)?P_TRIGGER_DEBOUNCE:P_VFRAME_TRIGGER_DEBOUNCE;
	m_trigEnableParamid= ((DWORD)cam->GetAcqParam(P_FEN_ENABLE)==IFC_ENABLE)?P_TRIGGER_ENABLE:P_VFRAME_TRIGGER_ENABLE;
	m_trigPolParamid= ((DWORD)cam->GetAcqParam(P_FEN_ENABLE)==IFC_ENABLE)?P_TRIGGER_POLARITY:P_VFRAME_TRIGGER_POLARITY;

	//{{AFX_DATA_INIT(CTrgGrab)
	m_trigEnable = (DWORD)theapp->m_cam->GetAcqParam(m_trigEnableParamid);
	m_trigPolarity = (DWORD)theapp->m_cam->GetAcqParam(m_trigPolParamid);
	m_trigDebounce = (DWORD)theapp->m_cam->GetAcqParam(m_debounceParamid);
	//}}AFX_DATA_INIT
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;

}


CTrgGrab::~CTrgGrab()
{
	CIntrExApp *theapp=(CIntrExApp*)AfxGetApp();	
}

void CTrgGrab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrgGrab)
	DDX_Control(pDX, IDC_LINE_TRIG, m_ctlLineTrig);
	DDX_Control(pDX, IDC_FRAME_TRIG, m_ctlFrameTrig);
	DDX_Radio(pDX, IDC_TRIG_ENABLE, m_trigEnable);
	DDX_Radio(pDX, IDC_TRIG_POL, m_trigPolarity);
	DDX_Text(pDX, IDC_TRIG_DEBOUNCE, m_trigDebounce);
	DDV_MinMaxUInt(pDX, m_trigDebounce, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrgGrab, CDialog )
	//{{AFX_MSG_MAP(CTrgGrab)
	ON_BN_CLICKED(IDC_SW_TRIG, OnSwTrig)
	ON_BN_CLICKED(IDC_FRAME_TRIG, OnFrameTrig)
	ON_BN_CLICKED(IDC_LINE_TRIG, OnLineTrig)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab message handlers





BOOL CTrgGrab::OnInitDialog() 
{
	CIntrExApp *theapp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theapp->m_cam;
	CDialog::OnInitDialog();
	
	if ( (DWORD)cam->GetAcqParam(P_FEN_ENABLE)==IFC_ENABLE) {
		m_ctlLineTrig.EnableWindow(FALSE);
	}
	else {
		m_ctlFrameTrig.EnableWindow(FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTrgGrab::OnOK() 
{
	UpdateData(TRUE);

	OnApplyTrig();
	
	CDialog ::OnOK();
}

void CTrgGrab::OnSwTrig() 
{
	CIntrExApp *theapp=(CIntrExApp*)AfxGetApp();	
	theapp->m_cam->SetAcqParam(P_GEN_SW_TRIGGER,0);
	
}

void CTrgGrab::OnFrameTrig() 
{
	CFrameTrig dg(this);
	dg.DoModal();
	
}

void CTrgGrab::OnLineTrig() 
{
	CLineTrig dg(this);
	dg.DoModal();
	
}

void CTrgGrab::OnApplyTrig() 
{
	CIntrExApp *theapp=(CIntrExApp*)AfxGetApp();
	UpdateData(TRUE);

	theapp->m_cam->SetAcqParam(m_trigEnableParamid,m_trigEnable);
	theapp->m_cam->SetAcqParam(m_trigPolParamid,m_trigPolarity);
	theapp->m_cam->SetAcqParam(m_debounceParamid,m_trigDebounce );
	
}
