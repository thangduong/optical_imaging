/******************************************************************************
 *
 * MODULE
 *    PulseGenDlg.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/PulseGen/PulseGenDlg.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/10/00 8:50a $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "PulseGen.h"
#include "PulseGenDlg.h"

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
	CButton	m_Inital;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	CBitmap m_PriBitmap;

protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_BUTTON1, m_Inital);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulseGenDlg dialog

CPulseGenDlg::CPulseGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPulseGenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPulseGenDlg)
	m_Frequency = 20.0;
	m_PulseWidth = 1000;
	m_NumPulses = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPulseGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPulseGenDlg)
	DDX_Text(pDX, IDC_FREQUENCY, m_Frequency);
	DDV_MinMaxDouble(pDX, m_Frequency, 1.e-003, 15000.);
	DDX_Text(pDX, IDC_PULSE_WIDTH, m_PulseWidth);
	DDV_MinMaxUInt(pDX, m_PulseWidth, 1, 1000000);
	DDX_Text(pDX, IDC_NUM_PULSES, m_NumPulses);
	DDV_MinMaxUInt(pDX, m_NumPulses, 1, 1000000);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPulseGenDlg, CDialog)
	//{{AFX_MSG_MAP(CPulseGenDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONTINUOUS, OnContinuous)
	ON_BN_CLICKED(IDC_FIREONE, OnFireOne)
	ON_BN_CLICKED(IDC_INTR_COUNT, OnIntrCount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPulseGenDlg message handlers

BOOL CPulseGenDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization here
	m_vixnTime = NULL;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPulseGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPulseGenDlg::OnPaint() 
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
HCURSOR CPulseGenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

#define MAX_PULSE_AS_PERCENT_OF_CYCLE 0.60

void CPulseGenDlg::OnContinuous() 
{
	CPulseGenApp *theapp=(CPulseGenApp*)AfxGetApp();	
	UpdateData(TRUE);
	
	if (m_vixnTime) {
		delete m_vixnTime;
		m_vixnTime = NULL;
	}
	if (m_Frequency * m_PulseWidth > MAX_PULSE_AS_PERCENT_OF_CYCLE*1000000) {
		char str[300];
		UINT maxPulseWidthAtFreq= (UINT)(MAX_PULSE_AS_PERCENT_OF_CYCLE*1000000.0 / m_Frequency);
		sprintf(str,"The pulse width ( %d microSeconds) is too great for the frequency ( %f HZ). "
			"The longest pulse width supported at this frequency is %d microSeconds. "
			"Would you like the pulse width to be set to %d microSeconds?",
			m_PulseWidth,m_Frequency, maxPulseWidthAtFreq,maxPulseWidthAtFreq);
		if (MessageBox(str,"Pulse Width Error",MB_YESNO|MB_ICONQUESTION) == IDYES) {
			m_PulseWidth = maxPulseWidthAtFreq;
			UpdateData(FALSE);
		}
		else {
			return;
		}
	}
	
	m_vixnTime = new CVixnTimer(theapp->m_pMod,m_Frequency,m_PulseWidth,IFC_VIXN_NONSTOP);
	m_vixnTime->Create();	
}

void CPulseGenDlg::OnFireOne() 
{
	CPulseGenApp *theapp=(CPulseGenApp*)AfxGetApp();	
	UpdateData(TRUE);

	if (m_vixnTime) {
		delete m_vixnTime;
		m_vixnTime = NULL;
	}
	// Create one pulse which is m_PulseWidth microseconds wide
	m_vixnTime = new CVixnTimer(theapp->m_pMod,m_Frequency,m_PulseWidth,m_NumPulses);
	m_vixnTime->Create();
}

void CPulseGenDlg::OnIntrCount() 
{
	if (m_vixnTime ) {
		DWORD interruptCount = VIXNVAL(m_vixnTime->m_intrCount);
		DWORD scheduledCount = VIXNVAL(m_vixnTime->m_ScheduleCount);
		char str[100];
		sprintf(str,"Interrupt Count = %d , Scheduled count =%d",interruptCount,scheduledCount);
		MessageBox(str,"Interrupt Count");
	}		
}

BOOL CPulseGenDlg::DestroyWindow() 
{
	if (m_vixnTime) {
		delete m_vixnTime;
		m_vixnTime = NULL;
	}	
	return CDialog::DestroyWindow();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_PriBitmap.LoadBitmap(IDB_BITMAP1);
	m_Inital.SetBitmap(m_PriBitmap);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
