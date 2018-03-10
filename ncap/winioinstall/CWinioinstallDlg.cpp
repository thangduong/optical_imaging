// CWinioinstallDlg.cpp : implementation file
//

#include "stdafx.h"
#include "winioinstall.h"
#include "CWinioinstallDlg.h"
#include "WinIo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinioinstallDlg dialog

CWinioinstallDlg::CWinioinstallDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinioinstallDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinioinstallDlg)
	m_WinIoSys = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinioinstallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinioinstallDlg)
	DDX_Text(pDX, IDC_WINIOSYS, m_WinIoSys);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinioinstallDlg, CDialog)
	//{{AFX_MSG_MAP(CWinioinstallDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnBrowse)
	ON_BN_CLICKED(IDC_BUTTON2, OnInstall)
	ON_BN_CLICKED(IDC_BUTTON3, OnRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinioinstallDlg message handlers

BOOL CWinioinstallDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinioinstallDlg::OnPaint() 
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
HCURSOR CWinioinstallDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinioinstallDlg::OnBrowse() 
{
	CFileDialog fd(true);
	if (fd.DoModal() == IDOK) {
		m_WinIoSys = fd.GetPathName();
		UpdateData(false);
	}
}

void CWinioinstallDlg::OnInstall() 
{
	UpdateData(true);
	if (InstallWinIoDriver((char*)LPCSTR(m_WinIoSys), false)) {
		AfxMessageBox("installed");
	}
	else
		AfxMessageBox("failed to install");
}

void CWinioinstallDlg::OnRemove() 
{
	if (RemoveWinIoDriver()) {
		AfxMessageBox("removed");
	}
	else
		AfxMessageBox("failed to remove");
}
