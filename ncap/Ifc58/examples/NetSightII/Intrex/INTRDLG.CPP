/******************************************************************************
 *
 * MODULE   
 *		IntrDlg.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/intrex/INTRDLG.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 9/16/04 4:54p $
 *
 * ABSTRACT
 *    NetSightII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001-2004 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/
// IntrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntrEx.h"
#include "IntrDlg.h"
#include "TrigGrabDlg.h"
#include <NSII.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NUM_RING_FRAMES 3

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntrExDlg dialog

CIntrExDlg::CIntrExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIntrExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIntrExDlg)
	m_lCounterGotSOT = 0;
	m_lCounterGotBMDONE = 0;
	m_lCounterGotEOFRM = 0;
	m_bGrabActive = FALSE;
	m_lCounterGotVB = 0;
	m_lCounterGotStartEven = 0;
	m_lCounterGotStartField = 0;
	m_lCounterGotStartFrame = 0;
	m_lCounterGotStartOdd = 0;
	m_lCounterGotBMDONE2 = 0;
	m_lCounterGotBMDONE3 = 0;
	m_lCounterGotSkipField = 0;
	m_lCounterGotLossOfSync = 0;
	m_lCounterGotInport = 0;
	m_lCounterGotTrigSkip = 0;
	m_lCounterGotSWTimer = 0;
	m_lCounterGotDecisionLate = 0;
	m_lCounterGotDecisionAbsent = 0;
	m_lCounterGotAioFifoOverflow = 0;
	//}}AFX_DATA_INIT
	memset(m_lCounterGotPin,0, sizeof(m_lCounterGotPin));
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIntrExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntrExDlg)
	DDX_Control(pDX, IDC_SOFT_TRIG, m_ctlSoftTrig);
	DDX_Control(pDX, IDC_SETUP_TRIG, m_ctlTrigSetup);
	DDX_Control(pDX, IDC_GRAB_ACTIVE, m_GrabAcriveButton);
	DDX_Text(pDX, IDC_EDIT_SOT, m_lCounterGotSOT);
	DDX_Text(pDX, IDC_EDIT_BMDONE, m_lCounterGotBMDONE);
	DDX_Text(pDX, IDC_EDIT_EOFRM, m_lCounterGotEOFRM);
	DDX_Check(pDX, IDC_GRAB_ACTIVE, m_bGrabActive);
	DDX_Text(pDX, IDC_EDIT_VB, m_lCounterGotVB);
	DDX_Text(pDX, IDC_EDIT_ODD_VB, m_lCounterGotOddVB);
	DDX_Text(pDX, IDC_EDIT_EVEN_VB, m_lCounterGotEvenVB);
	DDX_Text(pDX, IDC_EDIT_START_OF_EVEN, m_lCounterGotStartEven);
	DDX_Text(pDX, IDC_EDIT_START_OF_FIELD, m_lCounterGotStartField);
	DDX_Text(pDX, IDC_EDIT_START_OF_FRAME, m_lCounterGotStartFrame);
	DDX_Text(pDX, IDC_EDIT_START_OF_ODD, m_lCounterGotStartOdd);
	DDX_Text(pDX, IDC_EDIT_BMDONE2, m_lCounterGotBMDONE2);
	DDX_Text(pDX, IDC_EDIT_BMDONE3, m_lCounterGotBMDONE3);
	DDX_Text(pDX, IDC_EDIT_SKIPPED_FIELD, m_lCounterGotSkipField);
	DDX_Text(pDX, IDC_EDIT_LOSS_OF_SYNC, m_lCounterGotLossOfSync);
	DDX_Text(pDX, IDC_EDIT_INPORT, m_lCounterGotInport);
	DDX_Text(pDX, IDC_EDIT_TRIG_SKIP, m_lCounterGotTrigSkip);
	DDX_Text(pDX, IDC_EDIT_ODD_SWT, m_lCounterGotSWTimer);
	DDX_Text(pDX, IDC_EDIT_DECISION_LATE, m_lCounterGotDecisionLate);
	DDX_Text(pDX, IDC_EDIT_DECISION_ABSENT, m_lCounterGotDecisionAbsent);
	DDX_Text(pDX, IDC_EDIT_AIO_FIFO_OVR, m_lCounterGotAioFifoOverflow);
	//}}AFX_DATA_MAP
	for (int i=0; i < NUM_PIN_INTR; i++) {
		DDX_Text(pDX, IDC_EDIT_EVEN_DP0+i, m_lCounterGotPin[i]);
	}

}

BEGIN_MESSAGE_MAP(CIntrExDlg, CDialog)
	//{{AFX_MSG_MAP(CIntrExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_ENABLE_VB, IDC_BUTTON_DISABLE_EVEN_DP7, OnButton)
	ON_BN_CLICKED(IDC_SETUP_TRIG, OnSetupTrig)
	ON_BN_CLICKED(IDC_SOFT_TRIG, OnSoftTrig)
	ON_BN_CLICKED(IDC_GRAB_ACTIVE, OnGrabActive)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntrExDlg message handlers

BOOL CIntrExDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//setup timer used to periodically refresh display
	if(SetTimer(ID_TIMER, 100, NULL) == NULL)
		{
			AfxMessageBox("SetTimer failed", MB_ICONSTOP | MB_OK);
			AfxAbort();
		};

	// allocate space for the host grab 
	// (needed to generate interrupt activity)
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();
	int iWidth = theApp->m_nCurdx[theApp->m_iActiveBoard];
	int iHeight = theApp->m_nCurdy[theApp->m_iActiveBoard];

	CAM_ATTR attr;

	theApp->m_cam->GetAttr(&attr);
	if (!theApp->m_cam->AcqParamSupported(P_TRIGGER_ENABLE)) {
		m_ctlTrigSetup.EnableWindow(FALSE);
	}
	if (!theApp->m_cam->AcqParamSupported(P_GEN_SW_TRIGGER)) {
		m_ctlSoftTrig.EnableWindow(FALSE);
	}	
	m_pbyImageBuffer = (BYTE*)malloc(iWidth*iHeight*attr.dwBytesPerPixel * NUM_RING_FRAMES);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIntrExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIntrExDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIntrExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CIntrExDlg::OnButton(UINT nID) 
{
	int iIntr;
	CIfcInterrupt *pIntr;
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();
	CButton *EnableButton;
	CButton *DisableButton;

	if (nID < IDC_BUTTON_DISABLE_VB) {
		//enable
		iIntr = nID - IDC_BUTTON_ENABLE_VB;
		pIntr = theApp->m_pIntrObj[iIntr];
		pIntr->Resume();

		EnableButton = (CButton*)CDialog::GetDlgItem(nID);
		DisableButton = (CButton*)CDialog::GetDlgItem(iIntr+IDC_BUTTON_DISABLE_VB);
		EnableButton->EnableWindow(FALSE);
		DisableButton->EnableWindow(TRUE);
	}else{
		//disable
		iIntr = nID - IDC_BUTTON_DISABLE_VB;
		pIntr = theApp->m_pIntrObj[iIntr];
		pIntr->Suspend();
		EnableButton = (CButton*)CDialog::GetDlgItem(iIntr+IDC_BUTTON_ENABLE_VB);
		DisableButton = (CButton*)CDialog::GetDlgItem(nID);
		EnableButton->EnableWindow(TRUE);
		DisableButton->EnableWindow(FALSE);
	}
}
void CIntrExDlg::OnTimer(UINT nIDEvent) 
{
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();

	// update the counters
	m_lCounterGotVB = theApp->m_ulCounter[THREAD_VB];
	m_lCounterGotOddVB = theApp->m_ulCounter[THREAD_ODD_VB];
	m_lCounterGotEvenVB = theApp->m_ulCounter[THREAD_EVEN_VB];
	m_lCounterGotEOFRM = theApp->m_ulCounter[THREAD_EOFRM];
	m_lCounterGotSOT= theApp->m_ulCounter[THREAD_SOT];

	m_lCounterGotBMDONE = theApp->m_ulCounter[THREAD_BMDONE];

	m_lCounterGotStartField = theApp->m_ulCounter[THREAD_START_FIELD];
	m_lCounterGotStartOdd = theApp->m_ulCounter[THREAD_START_ODD];
	m_lCounterGotStartEven = theApp->m_ulCounter[THREAD_START_EVEN];
	m_lCounterGotStartFrame = theApp->m_ulCounter[THREAD_START_FRAME];

	m_lCounterGotBMDONE2 = theApp->m_ulCounter[THREAD_BMDONE2];
	m_lCounterGotBMDONE3 = theApp->m_ulCounter[THREAD_BMDONE3];
	m_lCounterGotSkipField = theApp->m_ulCounter[THREAD_SKIPPED_FIELD];

	m_lCounterGotInport  = theApp->m_ulCounter[THREAD_INPORT];
	m_lCounterGotLossOfSync  = theApp->m_ulCounter[THREAD_LOSS_SYNC];
	m_lCounterGotTrigSkip  = theApp->m_ulCounter[THREAD_TRIG_SKIPPED];
	m_lCounterGotSWTimer  = theApp->m_ulCounter[THREAD_SW_TIMER];

	m_lCounterGotAioFifoOverflow = theApp->m_ulCounter[THREAD_AIO_FIFO_OVERFLOW];
	m_lCounterGotDecisionAbsent  = theApp->m_ulCounter[THREAD_AIO_DECISION_ABSENT];
	m_lCounterGotDecisionLate  = theApp->m_ulCounter[THREAD_AIO_DECISION_LATE];

	for (int i=0; i < NUM_PIN_INTR; i++) {
		m_lCounterGotPin[i] =  theApp->m_ulCounter[THREAD_DATAPIN0+i];
	}

	CDialog::UpdateData(FALSE);	
	CDialog::OnTimer(nIDEvent);
}

void CIntrExDlg::OnClose() 
{

	KillTimer(ID_TIMER);
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();
	theApp->m_cam->Freeze();

	free(m_pbyImageBuffer);

	CDialog::OnClose();
}

void CIntrExDlg::OnSetupTrig() 
{
	CTrigGrabDlg dg(this);	
	dg.DoModal();
}

void CIntrExDlg::OnSoftTrig() 
{
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();
	theApp->m_cam->SetAcqParam(P_GEN_SW_TRIGGER,0,0);
}



void CIntrExDlg::OnGrabActive() 
{
	UpdateData(TRUE);
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();

	if (m_bGrabActive) {
		theApp->m_cam->Freeze();
		theApp->m_cam->Grab(m_pbyImageBuffer, NUM_RING_FRAMES);
		m_GrabAcriveButton.SetWindowText("Active");
	}else{
		theApp->m_cam->Freeze();
		m_GrabAcriveButton.SetWindowText("Inactive");
	}
}

void CIntrExDlg::OnReset() 
{
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();
	//set all counters back to zero
	for(int i=0; i<THREAD_LAST;i++)
		theApp->m_ulCounter[i] = 0;
}

