// TrigGrabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "intrex.h"
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
	CIntrExApp *theApp = (CIntrExApp*) AfxGetApp();	
	CICamera *cam = theApp->m_cam;
	//{{AFX_DATA_INIT(CTrigGrabDlg)
	m_iTrigPolarity = (int) cam->GetAcqParam(P_TRIGGER_POLARITY);
	m_iTrigSrc		= (int) cam->GetAcqParam(P_TRIGGER_SRC);
	m_TrigState		= (int) cam->GetAcqParam(P_TRIGGER_ENABLE);
	//}}AFX_DATA_INIT

	m_vParent = (CIntrExDlg*) pParent;
}


void CTrigGrabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CTrigGrabDlg)
	DDX_Radio(pDX, IDC_FALLING_EDGE,	m_iTrigPolarity);
	DDX_Radio(pDX, IDC_SW_TRIG,			m_iTrigSrc);
	DDX_Radio(pDX, IDC_TRG_DISABLE,		m_TrigState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrigGrabDlg, CDialog)
	//{{AFX_MSG_MAP(CTrigGrabDlg)
	ON_BN_CLICKED(IDC_TRG_APPLY, OnTrgApply)
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
	CIntrExApp* theApp = (CIntrExApp*) AfxGetApp();	
	CICamera *cam = theApp->m_cam;

	m_iTrigPolarity	= (int) cam->GetAcqParam(P_TRIGGER_POLARITY);
	m_iTrigSrc		= (int) cam->GetAcqParam(P_TRIGGER_SRC);
	m_TrigState		= (int) cam->GetAcqParam(P_TRIGGER_ENABLE);
}



void CTrigGrabDlg::OnTrgApply() 
{
	UpdateData(TRUE);
	CIntrExApp* theApp = (CIntrExApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;

	cam->SetAcqParam(P_TRIGGER_POLARITY,	m_iTrigPolarity);
	cam->SetAcqParam(P_TRIGGER_SRC,			m_iTrigSrc);	
	cam->SetAcqParam(P_TRIGGER_ENABLE,		m_TrigState);	
}
