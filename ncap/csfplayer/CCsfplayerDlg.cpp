// CCsfplayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "csfplayer.h"
#include "CCsfplayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCsfplayerDlg dialog

CCsfplayerDlg::CCsfplayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCsfplayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCsfplayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	state = STATE_NOFILE;
	frame = 0;
}

void CCsfplayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCsfplayerDlg)
	DDX_Control(pDX, IDC_FRAMERATE, m_FrameRate);
	DDX_Control(pDX, IDC_FRAMEID, m_Frame);
	DDX_Control(pDX, IDC_IMG, m_Img);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCsfplayerDlg, CDialog)
	//{{AFX_MSG_MAP(CCsfplayerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_QUIT, OnFileQuit)
	ON_COMMAND(ID_ACTION_PLAY, OnPlay)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_COMMAND(ID_ACTION_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCsfplayerDlg message handlers

BOOL CCsfplayerDlg::OnInitDialog()
{
	m_pData = new unsigned short[256*256];
	m_pFirstData = new unsigned short[256*256];
 
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

void CCsfplayerDlg::OnPaint() 
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
HCURSOR CCsfplayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCsfplayerDlg::OnFileOpen() 
{
	static char BASED_CODE szFilter[] = "Camera stream files (*.csf)|*.csf|All Files (*.*)|*.*||";
	CFileDialog fd(true,0,0,0,szFilter);
	if (fd.DoModal() == IDOK) {
		if (m_Csf.OpenFile(fd.GetPathName(), true, false)) {
			
		}
		else {
			AfxMessageBox("can't open file");
		}
	}
}

void CCsfplayerDlg::OnFileQuit() 
{
	PostQuitMessage(0);	
}

void CCsfplayerDlg::OnPlay() 
{
	// TODO: Add your command handler code here
	last = 0;
	fn = 0;
	SetTimer(0,10,0);
}	

void CCsfplayerDlg::OnTimer(UINT nIDEvent) 
{
	KillTimer(0);
	char temp[512];
	sprintf(temp, "Frame: %d", frame++);
	m_Frame.SetWindowText(temp);
	if (m_Csf.ReadFrame(m_pData, pretime, posttime))
	{
		if (last==0) {
			memcpy(m_pFirstData, m_pData,256*256*2);
		}
		else {
			for (int i = 0; i < 256*256; i++) {
				m_pData[i] -= m_pFirstData[i];
			}
		}
		char fname[512];
		sprintf(fname, "c:\\temp\\junk\\%04d.img", fn++);
		FILE* fp = fopen(fname, "wb");
		unsigned long v[3] = { 256, 256, 12 };
		fwrite(v, 4, 3, fp);
		fwrite(m_pData, 256*256,2,fp);
		fclose(fp);
		if (last != 0)
		{
			sprintf(temp, "Framerate: %0.2f", (double)m_Csf.GetTimeStampFreq().LowPart/((double)(pretime-last)));
			m_FrameRate.SetWindowText(temp);
			SetTimer(0, (1000*(pretime-last))/m_Csf.GetTimeStampFreq().LowPart, 0);
		}
		else
			SetTimer(0, 10, 0);
		last = pretime;
		for (int i = 0; i< 256*256;i++){
			((unsigned long*)m_pBmpData)[i] = (m_pData[i]>>8) + ((m_pData[i]>>8)<<8) + ((m_pData[i]>>8)<<16); 
		}
		bdc.SelectObject(&bmp);
		
		CDC* dc = m_Img.GetDC();
		dc->BitBlt(0,0,256,256,&bdc, 0,0,SRCCOPY);
		m_Img.ReleaseDC(dc);
	}
	CDialog::OnTimer(nIDEvent);
}

void CCsfplayerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	delete m_pData;	
	delete m_pFirstData;
}

int CCsfplayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* dc = GetDC();
	bdc.CreateCompatibleDC(dc);
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	 
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biHeight = 256;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biWidth = 256;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;


	m_pBmpData = 0;
	HBITMAP h = CreateDIBSection(bdc.GetSafeHdc(), &bmi, 0, (void**)&m_pBmpData, 0, 0);
	bmp.Attach(h);
	ReleaseDC(dc);


	return 0;
}

void CCsfplayerDlg::OnStop() 
{
	KillTimer(0);	
}
