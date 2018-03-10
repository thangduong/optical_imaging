// CImgviewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imgviewer.h"
#include "CImgviewerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImgviewerDlg dialog

CImgviewerDlg::CImgviewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImgviewerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImgviewerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	initialFilename = 0;
}

void CImgviewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImgviewerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CImgviewerDlg, CDialog)
	//{{AFX_MSG_MAP(CImgviewerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_QUIT, OnFileQuit)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImgviewerDlg message handlers

BOOL CImgviewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

		RECT wr, cr;
		int nWidth = 256;
		int nHeight = 256;
		GetWindowRect(&wr);
		GetClientRect(&cr);

		CDC* pDc = GetDC();
		memset(&bmi, 0, sizeof(bmi));
		bmi.bmiHeader.biBitCount = 24;
		bmi.bmiHeader.biPlanes = 1;
		bmi.bmiHeader.biWidth = nWidth;//cr.right - cr.left;
		bmi.bmiHeader.biHeight = nHeight;//cr.bottom - cr.top;
		bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
		bmi.bmiHeader.biCompression = BI_RGB;
		m_pBackImgData = 0;
		m_hBackImg = CreateDIBSection(pDc->GetSafeHdc(), &bmi, DIB_RGB_COLORS, (void**)&m_pBackImgData, 0, 0);

		ReleaseDC(pDc);
//		ReleaseDC(m_hWnd, dc);

		nWidth = nWidth - (cr.right - cr.left) + (wr.right - wr.left);
		nHeight = nHeight - (cr.bottom - cr.top) + (wr.bottom - wr.top);
		MoveWindow(wr.left, wr.top, nWidth, nHeight);

		printf("width = %d height = %d\r\n", bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight);
	OpenFile(initialFilename);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImgviewerDlg::OnPaint() 
{/*
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
	*/
	HDC dc = ::GetDC(GetSafeHwnd());
	HDC hbd = CreateCompatibleDC(0);

	SelectObject(hbd, m_hBackImg);
	BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
	DeleteDC(hbd);
	::ReleaseDC(GetSafeHwnd(), dc);
}
void CImgviewerDlg::Show(short* pData) {

	if (m_pBackImgData) {
		HDC dc = ::GetDC(m_hWnd);
		HDC hbd = ::CreateCompatibleDC(0);

		if (pData) {
			// copy data over!
			char* pOut = m_pBackImgData;
			int i;
			for (i = 0; i < bmi.bmiHeader.biWidth*bmi.bmiHeader.biHeight; i++) {
				pOut[1] = pOut[2] = pOut[0] = ((unsigned)pData[i]&0xfff)>>4;
				pOut += 3;
			}
		}

		SelectObject(hbd, m_hBackImg);
		BitBlt(dc, 0, 0, bmi.bmiHeader.biWidth, bmi.bmiHeader.biHeight, hbd, 0, 0, SRCCOPY);
		::DeleteDC(hbd);
		::ReleaseDC(m_hWnd, dc);
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImgviewerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CImgviewerDlg::OnFileQuit() 
{
	ExitProcess(0);	
}

void CImgviewerDlg::OnFileOpen() 
{
	CFileDialog fd(true);
	if (fd.DoModal() == IDOK) {
		OpenFile(LPCSTR(fd.GetPathName()));
	}
}

void CImgviewerDlg::OpenFile(const char* filename) {
	if (filename == 0)
		return;
	FILE* fp = fopen(filename, "rb");
	if (fp) {
		unsigned long param[3];
			fread(param,3,sizeof(param[0]), fp);
		if ((param[0] == 256) && (param[1] == 256) && (param[2] == 12)) {
			short* temp = new short[param[0]*param[1]];
			fread(temp, 2, param[0]*param[1], fp);
			Show(temp);
			delete [] temp;
		}
		else {
			// invalid file
		}
		fclose(fp);
	}
}

