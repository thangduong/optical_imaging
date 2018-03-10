/******************************************************************************
 *
 * MODULE   
 *		IntrDlg.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/IntrEx/INTRDLG.CPP $
 *    $Revision: 1.1 $
 *    $Modtime: 8/24/00 9:52a $
 *
 * ABSTRACT
 *    PCVisionplus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
// IntrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IntrEx.h"
#include "IntrDlg.h"
#include "TrigGrabDlg.h"
#include "IfcIntr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	m_lCounterGotEOT = 0;
	m_lCounterGotINPORT = 0;
	m_lCounterGotSW_TIMER = 0;
	m_lCounterGotACQ_ADRS = 0;
	m_lCounterGotBMDONE = 0;
	m_lCounterGotAM_CASCADE = 0;
	m_lCounterGotEOFRM = 0;
	m_bGrabActive = FALSE;
	m_lCounterGotEVEN_VB = 0;
	m_lCounterGotODD_VB = 0;
	m_lCounterGotVB = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIntrExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIntrExDlg)
	DDX_Control(pDX, IDC_GRAB_ACTIVE, m_GrabAcriveButton);
	DDX_Text(pDX, IDC_EDIT_SOT, m_lCounterGotSOT);
	DDX_Text(pDX, IDC_EDIT_EOT, m_lCounterGotEOT);
	DDX_Text(pDX, IDC_EDIT_INPORT, m_lCounterGotINPORT);
	DDX_Text(pDX, IDC_EDIT_SW_TIMER, m_lCounterGotSW_TIMER);
	DDX_Text(pDX, IDC_EDIT_ACQ_ADRS, m_lCounterGotACQ_ADRS);
	DDX_Text(pDX, IDC_EDIT_BMDONE, m_lCounterGotBMDONE);
	DDX_Text(pDX, IDC_EDIT_AM_CASCADE, m_lCounterGotAM_CASCADE);
	DDX_Text(pDX, IDC_EDIT_EOFRM, m_lCounterGotEOFRM);
	DDX_Check(pDX, IDC_GRAB_ACTIVE, m_bGrabActive);
	DDX_Text(pDX, IDC_EDIT_EVEN_VB, m_lCounterGotEVEN_VB);
	DDX_Text(pDX, IDC_EDIT_ODD_VB, m_lCounterGotODD_VB);
	DDX_Text(pDX, IDC_EDIT_VB, m_lCounterGotVB);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIntrExDlg, CDialog)
	//{{AFX_MSG_MAP(CIntrExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_ENABLE_SOT, IDC_BUTTON_DISABLE_EOFRM, OnButton)
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
	m_pbyImageBuffer = (BYTE*)malloc(iWidth*iHeight*attr.dwBytesPerPixel);

	for (int i=0; i< 33; i++)
	m_TimeStat [i] = 0;


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

	if(nID<=IDC_BUTTON_ENABLE_EOFRM){
		//enable
		iIntr = nID - IDC_BUTTON_ENABLE_SOT;
		pIntr = theApp->m_pIntrObj[iIntr];
		pIntr->Resume();

		EnableButton = (CButton*)CDialog::GetDlgItem(nID);
		DisableButton = (CButton*)CDialog::GetDlgItem(iIntr+IDC_BUTTON_DISABLE_SOT);
		EnableButton->EnableWindow(FALSE);
		DisableButton->EnableWindow(TRUE);
	}else{
		//disable
		iIntr = nID - IDC_BUTTON_DISABLE_SOT;
		pIntr = theApp->m_pIntrObj[iIntr];
		pIntr->Suspend();
		EnableButton = (CButton*)CDialog::GetDlgItem(iIntr+IDC_BUTTON_ENABLE_SOT);
		DisableButton = (CButton*)CDialog::GetDlgItem(nID);
		EnableButton->EnableWindow(TRUE);
		DisableButton->EnableWindow(FALSE);
	}
}
void CIntrExDlg::OnTimer(UINT nIDEvent) 
{
	char buffer[20];
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();

	// update the counters
	m_lCounterGotSOT= theApp->m_ulCounter[THREAD_SOT];
	m_lCounterGotEOT = theApp->m_ulCounter[THREAD_EOT];
	m_lCounterGotINPORT = theApp->m_ulCounter[THREAD_INPORT];
	m_lCounterGotSW_TIMER = theApp->m_ulCounter[THREAD_SW_TIMER];
	m_lCounterGotVB = theApp->m_ulCounter[THREAD_VB];
	m_lCounterGotEVEN_VB = theApp->m_ulCounter[THREAD_EVEN_VB];
	m_lCounterGotODD_VB = theApp->m_ulCounter[THREAD_ODD_VB];

	m_lCounterGotACQ_ADRS = theApp->m_ulCounter[THREAD_ACQ_ADRS];
	m_lCounterGotBMDONE = theApp->m_ulCounter[THREAD_BMDONE];
	m_lCounterGotAM_CASCADE = theApp->m_ulCounter[THREAD_AM_CASCADE];
	m_lCounterGotEOFRM = theApp->m_ulCounter[THREAD_EOFRM];
	
	CDialog::UpdateData(FALSE);	

	for (int i=0; i< 33; i++)
	((CEdit*) CDialog::GetDlgItem(i + IDC_EDIT5))->SetWindowText(_itoa( m_TimeStat [i], buffer, 10 ) );

	
	CDialog::OnTimer(nIDEvent);
}

void CIntrExDlg::OnClose() 
{
	CIntrExApp * theApp = (CIntrExApp*)AfxGetApp();

	KillTimer(ID_TIMER);
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
		theApp->m_cam->Grab(m_pbyImageBuffer,1);
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

	for (i=0; i< 33; i++)
		m_TimeStat [i] = 0;
}


