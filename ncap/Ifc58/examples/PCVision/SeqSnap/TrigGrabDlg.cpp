// TrigGrabDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "TrigGrabDlg.h"
#include <windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define FRAMES_IN_HOSTBUFF 5

/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg dialog


CTrigGrabDlg::CTrigGrabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrigGrabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrigGrabDlg)
	m_iTrigEnable		= -1;
	m_iTrigSrc			= -1;
	m_iTrigPolarity		= -1;
	m_iStrobeEnable		= -1;
	m_iStrobeMode		= -1;
	m_iStrobePolarity	= -1;
	m_iStrobeDelay		= -1;
	m_iFrameMode		= -1;
	m_iFramePolarity	= -1;
	m_iFrameSize		= -1;
	m_iFrameDelay		= -1;

	//}}AFX_DATA_INIT
	m_vParent = (CSeqsnapView*) pParent;
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;
	m_trgThread = NULL;
}

CTrigGrabDlg::~CTrigGrabDlg()
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;
	OnTrgstop();
	cam->SetAcqParam(P_TRIGGER_ENABLE, IFC_DISABLE);
}


void CTrigGrabDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CTrigGrabDlg)
	DDX_Radio(pDX, IDC_TRIGGER_DISABLE,		m_iTrigEnable);
	DDX_Radio(pDX, IDC_SW_TRIG,				m_iTrigSrc);
	DDX_Radio(pDX, IDC_FALLING_EDGE,		m_iTrigPolarity);
	DDX_Radio(pDX, IDC_STROBE_DISABLE,		m_iStrobeEnable);
	DDX_Radio(pDX, IDC_FASTSTROBE,			m_iStrobeMode);
	DDX_Radio(pDX, IDC_STROBE_POL_LOW,		m_iStrobePolarity);
	DDX_Radio(pDX, IDC_FRAME_DISABLE,		m_iFrameMode);
	DDX_Radio(pDX, IDC_FRAME_SIZE_PERIOD,	m_iFrameSize);
	DDX_Radio(pDX, IDC_FRAME_POL_LOW,		m_iFramePolarity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrigGrabDlg, CDialog)
	//{{AFX_MSG_MAP(CTrigGrabDlg)
	ON_BN_CLICKED(IDC_TRGSTART,	OnTrgstart)
	ON_BN_CLICKED(IDC_TRGSTOP,	OnTrgstop)
	ON_BN_CLICKED(IDC_TRGTIME,	OnTrgtime)
	ON_BN_CLICKED(IDOK,			OnExit)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg message handlers

BOOL CTrigGrabDlg::OnInitDialog()
{
	char str[10];
	CEdit* pEdit = NULL;
	CSliderCtrl* pSliderCtrl = NULL;

	CDialog::OnInitDialog();
	RefreshDialogFromCamParams();
	UpdateData(FALSE);

	pSliderCtrl = (CSliderCtrl*) GetDlgItem(IDC_STROBE_DELAY);

	ASSERT(pSliderCtrl);
    pSliderCtrl->SetRange(0, 63, FALSE);
	pSliderCtrl->SetPos(m_iStrobeDelay - 1);

	pEdit = (CEdit*) GetDlgItem(IDC_STROBE_DELAY_E);

	ASSERT(pEdit);
	wsprintf(str, "%d", m_iStrobeDelay);
	pEdit->SetWindowText(str);


	pSliderCtrl  = (CSliderCtrl*) GetDlgItem(IDC_FRAME_DELAY);

	ASSERT(pSliderCtrl);
    pSliderCtrl->SetRange(0, 255, FALSE);
	pSliderCtrl->SetPos(m_iFrameDelay - 1);


	pEdit  = (CEdit*) GetDlgItem(IDC_FRAME_DELAY_E);

	ASSERT(pEdit);
	wsprintf(str, "%d", m_iFrameDelay);
	pEdit->SetWindowText(str);

	m_vParent->DelImageServer();
	m_vParent->ClearView();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTrigGrabDlg::RefreshDialogFromCamParams()
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
	CICamera *cam = theApp->m_cam;

	m_iTrigEnable		= (int) cam->GetAcqParam(P_TRIGGER_ENABLE);
	m_iTrigSrc			= (int) cam->GetAcqParam(P_TRIGGER_SRC);
	m_iTrigPolarity		= (int) cam->GetAcqParam(P_TRIGGER_POLARITY);

	m_iStrobeEnable		= (int) cam->GetAcqParam(P_STROBE_ENABLE);
	m_iStrobeMode		= (int) cam->GetAcqParam(P_STROBE_MODE);
	m_iStrobePolarity	= (int) cam->GetAcqParam(P_STROBE_POLARITY);
	m_iStrobeDelay		= (int) cam->GetAcqParam(P_STROBE_DELAY);

	m_iFrameMode		= (int) cam->GetAcqParam(P_FRAME_RESET_MODE);
	m_iFramePolarity	= (int) cam->GetAcqParam(P_FRAME_RESET_POLARITY);
	m_iFrameSize		= (int) cam->GetAcqParam(P_FRAME_RESET_SIZE);
	m_iFrameDelay		= (int) cam->GetAcqParam(P_FRAME_RESET_OFFSET);
}

void CTrigGrabDlg::OnTrgstart() 
{
	UpdateData(TRUE);

	// Delete any pre-existing trigger thread
	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
	}

	if(m_iTrigEnable)
	{
		CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
		CICamera *cam = theApp->m_cam;

		cam->SetAcqParam(P_TRIGGER_ENABLE,			m_iTrigEnable);
		cam->SetAcqParam(P_TRIGGER_POLARITY,		m_iTrigPolarity);
		cam->SetAcqParam(P_TRIGGER_SRC,				m_iTrigSrc);

		cam->SetAcqParam(P_STROBE_ENABLE,			m_iStrobeEnable);
		cam->SetAcqParam(P_STROBE_MODE,				m_iStrobeMode);
		cam->SetAcqParam(P_STROBE_POLARITY,			m_iStrobePolarity);
		cam->SetAcqParam(P_STROBE_DELAY,			m_iStrobeDelay);

		cam->SetAcqParam(P_FRAME_RESET_MODE,		m_iFrameMode);
		cam->SetAcqParam(P_FRAME_RESET_POLARITY,	m_iFramePolarity);
		cam->SetAcqParam(P_FRAME_RESET_SIZE,		m_iFrameSize);
		cam->SetAcqParam(P_FRAME_RESET_OFFSET,		m_iFrameDelay);

		m_trgThread = new CTrgThrd(this);
	}
	else
	{
		MessageBox("The TRIGGER is currently Disabled. Enable it and press Start", "Trigger State Message", MB_OK);
	}
}

void CTrigGrabDlg::OnTrgstop() 
{
	// Stop any existing trigger thread
	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
	}


	m_vParent->ClearView();
}

void CTrigGrabDlg::OnTrgtime() 
{
	char msg[200];

	sprintf(msg,"Frame-to-frame time; Max: %d ms,  Min: %d ms,  Avg: %d ms",
		    m_maxTime,m_minTime,m_avgTime);

	MessageBox(msg,"Trigger Frame Time Parameters");
}

void CTrigGrabDlg::OnExit() 
{
	CDialog::OnOK();

	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
	}

	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;

	cam->SetAcqParam(P_TRIGGER_ENABLE, IFC_DISABLE);

	m_vParent->CreateImageServer(NULL);
	m_vParent->ClearView();
}

void CTrigGrabDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	char str[10];
	CEdit* pEdit = NULL;
	CSliderCtrl* pSliderCtrl = (CSliderCtrl*) pScrollBar;

	nPos = pSliderCtrl->GetPos();

	if(pSliderCtrl->GetRangeMax() > 63)
	{
		pEdit = (CEdit*) GetDlgItem(IDC_FRAME_DELAY_E);
		m_iFrameDelay = (int) nPos;
		wsprintf(str, "%d", ++m_iFrameDelay);
	}
	else
	{
		pEdit = (CEdit*) GetDlgItem(IDC_STROBE_DELAY_E);
		m_iStrobeDelay = (int) nPos;
		wsprintf(str, "%d", ++m_iStrobeDelay);
	}

	ASSERT(pEdit);
	pEdit->SetWindowText(str);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
