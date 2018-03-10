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

const int c_nTimerId = 111;
const int c_nMaxData = 2048;

/////////////////////////////////////////////////////////////////////////////
/// CTrigGrabDlg dialog


CTrigGrabDlg::CTrigGrabDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrigGrabDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTrigGrabDlg)
	m_iTrigPolarity		= -1;
	m_iStrobeEnable		= -1;
	m_iStrobeMode		= -1;
	m_iStrobePolarity	= -1;
	m_iStrobeDelay		= -1;
	m_iFrameMode		= -1;
	m_iFramePolarity	= -1;
	m_iFrameDelay		= -1;
	m_iImagesNum = 1;
	m_bContinuous = TRUE;
	m_iTrigEnable = -1;
	m_nVerifyEnd = 0;			
	m_nVerifyThreshold = 0;
	m_nVerifyStart = 0;
	m_frameResetSize = 0.0f;
	//}}AFX_DATA_INIT
	m_vParent = (CSeqsnapView*) pParent;
	m_maxTime = 0;
	m_minTime = 0;
	m_avgTime = 0;
	m_trgThread = NULL;
	m_iTrigSrc = 0;
	m_nNumMissed = 0;
	m_nNumLost = 0;
	
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
	DDX_Control(pDX, IDC_STROBE_POL_LOW, m_ctlStrobePolLow);
	DDX_Control(pDX, IDC_STROBE_POL_HI, m_ctlStrobePolHi);
	DDX_Control(pDX, IDC_STROBE_DELAY, m_ctlStrobeDelay);
	DDX_Control(pDX, IDC_FRAME_RESET_SIZE, m_ctlFrameResetSize);
	DDX_Control(pDX, IDC_FRAME_POL_HI, m_ctlFramePolHigh);
	DDX_Control(pDX, IDC_FRAME_POL_LOW, m_ctlFramePolLow);
	DDX_Control(pDX, IDC_FRAME_DISABLE, m_ctlFrameDisable);
	DDX_Control(pDX, IDC_FRAME_ENABLE, m_ctlFrameEnable);
	DDX_Control(pDX, IDC_FRAME_DELAY, m_ctlFrameDelay);
	DDX_Control(pDX, IDC_FASTSTROBE, m_ctlFastStrobe);
	DDX_Control(pDX, IDC_SLOWSTROBE, m_ctlSlowStrobe);
	DDX_Control(pDX, IDC_STROBE_DISABLE, m_ctlStrobeDisable);
	DDX_Control(pDX, IDC_STROBE_ENABLE, m_ctlStrobeEnable);
	DDX_Control(pDX, IDC_TRIGGER_ENABLE, m_TrigEnable);
	DDX_Control(pDX, IDC_TRGSTART, m_TrigStart);
	DDX_Control(pDX, IDC_STATIC1, m_winStats);
	DDX_Control(pDX, IDC_IMAGES_NUM, m_ImagesNum);
	DDX_Radio(pDX, IDC_FALLING_EDGE,		m_iTrigPolarity);
	DDX_Radio(pDX, IDC_STROBE_DISABLE,		m_iStrobeEnable);
	DDX_Radio(pDX, IDC_FASTSTROBE,			m_iStrobeMode);
	DDX_Radio(pDX, IDC_STROBE_POL_LOW,		m_iStrobePolarity);
	DDX_Radio(pDX, IDC_FRAME_DISABLE,		m_iFrameMode);
	DDX_Radio(pDX, IDC_FRAME_POL_LOW,		m_iFramePolarity);
	DDX_Text(pDX, IDC_IMAGES_NUM, m_iImagesNum);
	DDV_MinMaxInt(pDX, m_iImagesNum, 1, 2147483647);
	DDX_Check(pDX, IDC_CONTINUOUS, m_bContinuous);
	DDX_Radio(pDX, IDC_TRIGGER_ENABLE, m_iTrigEnable);
	DDX_Text(pDX, IDC_Y_END, m_nVerifyEnd);
	DDX_Text(pDX, IDC_THRESHOLD, m_nVerifyThreshold);
	DDX_Text(pDX, IDC_Y_START, m_nVerifyStart);
	DDX_Text(pDX, IDC_FRAME_RESET_SIZE, m_frameResetSize);
	DDV_MinMaxFloat(pDX, m_frameResetSize, 0.0f, 200000.0f);
	DDX_Radio(pDX, IDC_TRGSRC_SOFT, m_iTrigSrc);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTrigGrabDlg, CDialog)
	//{{AFX_MSG_MAP(CTrigGrabDlg)
	ON_MESSAGE(UM_KILLME, OnKillMe)
	ON_BN_CLICKED(IDC_TRGSTART,	OnTrgstart)
	ON_BN_CLICKED(IDC_TRGSTOP,	OnTrgstop)
	ON_BN_CLICKED(IDC_TRGTIME,	OnTrgtime)
	ON_BN_CLICKED(IDOK,			OnExit)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CONTINUOUS, OnContinuous)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrigGrabDlg message handlers

BOOL CTrigGrabDlg::OnInitDialog()
{
	char str[10];
	CEdit* pEdit = NULL;
	CSliderCtrl* pSliderCtrl = NULL;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();
	CICamera *cam=theapp->m_cam;
	CAM_ATTR attr;
	DWORD m_areaDy;
	

	CDialog::OnInitDialog();
	RefreshDialogFromCamParams();
	UpdateData(FALSE);

	pSliderCtrl = (CSliderCtrl*) GetDlgItem(IDC_STROBE_DELAY);

	ASSERT(pSliderCtrl);
    pSliderCtrl->SetRange(0, 60000, FALSE);
	pSliderCtrl->SetPos(m_iStrobeDelay - 1);

	pEdit = (CEdit*) GetDlgItem(IDC_STROBE_DELAY_E);

	ASSERT(pEdit);
	wsprintf(str, "%d", m_iStrobeDelay);
	pEdit->SetWindowText(str);


	pSliderCtrl  = (CSliderCtrl*) GetDlgItem(IDC_FRAME_DELAY);

	ASSERT(pSliderCtrl);
    pSliderCtrl->SetRange(0, 60000, FALSE);
	pSliderCtrl->SetPos(m_iFrameDelay - 1);


	pEdit  = (CEdit*) GetDlgItem(IDC_FRAME_DELAY_E);

	ASSERT(pEdit);
	wsprintf(str, "%d", m_iFrameDelay);
	pEdit->SetWindowText(str);

	m_vParent->DelImageServer();
	m_vParent->ClearView();

	m_ImagesNum.EnableWindow(FALSE);

	m_ctlStrobeDisable.EnableWindow(cam->AcqParamSupported(P_STROBE_ENABLE));
	m_ctlStrobeEnable.EnableWindow(cam->AcqParamSupported(P_STROBE_ENABLE));

	m_ctlStrobePolLow.EnableWindow(cam->AcqParamSupported(P_STROBE_POLARITY));
	m_ctlStrobePolHi.EnableWindow(cam->AcqParamSupported(P_STROBE_POLARITY));

	m_ctlFastStrobe.EnableWindow(cam->AcqParamSupported(P_STROBE_MODE));
	m_ctlSlowStrobe.EnableWindow(cam->AcqParamSupported(P_STROBE_MODE));

	m_ctlStrobeDelay.EnableWindow(cam->AcqParamSupported(P_STROBE_DELAY));
	m_ctlFrameResetSize.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_SIZE));

	m_ctlFramePolHigh.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_POLARITY));
	m_ctlFramePolLow.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_POLARITY));

	m_ctlFrameDisable.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_MODE));
	m_ctlFrameEnable.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_MODE));

	m_ctlFrameDelay.EnableWindow(cam->AcqParamSupported(P_FRAME_RESET_OFFSET));

	cam->GetAttr(&attr);
	m_areaDy = attr.dwHeight;
	
	pEdit = (CEdit*) GetDlgItem(IDC_Y_START);
	ASSERT(pEdit);
	sprintf(str, "%d", (int) ((double) m_areaDy / 3.0));
	pEdit->SetWindowText (str);

	pEdit = (CEdit*) GetDlgItem(IDC_Y_END);
	ASSERT(pEdit);
	sprintf(str, "%d", (int) ((double) m_areaDy *(2/ 3.0)));
	pEdit->SetWindowText (str);
	
	pEdit = (CEdit*) GetDlgItem(IDC_THRESHOLD);
	ASSERT(pEdit);
	sprintf(str, "%d", 20);
	pEdit->SetWindowText (str);
		
	SetTimer( c_nTimerId, 1000, NULL ); 
	ResetStatistics();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTrigGrabDlg::RefreshDialogFromCamParams()
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();	
	CICamera *cam = theApp->m_cam;

	m_iTrigEnable		= (int) cam->GetAcqParam(P_TRIGGER_ENABLE);
	m_iTrigSrc			= (int) cam->GetAcqParam(P_TRIGGER_SRC);
	if (m_iTrigSrc==IFC_EXT_AUTO_TRIG)
		m_iTrigSrc=3;
	m_iTrigPolarity		= (int) cam->GetAcqParam(P_TRIGGER_POLARITY);

	m_iStrobeEnable		= (int) cam->GetAcqParam(P_STROBE_ENABLE);
	m_iStrobeMode		= (int) cam->GetAcqParam(P_STROBE_MODE);
	m_iStrobePolarity	= (int) cam->GetAcqParam(P_STROBE_POLARITY);
	m_iStrobeDelay		= (int) cam->GetAcqParam(P_STROBE_DELAY); // us post trigger

	m_iFrameMode		= (int) cam->GetAcqParam(P_FRAME_RESET_MODE);
	m_iFramePolarity	= (int) cam->GetAcqParam(P_FRAME_RESET_POLARITY);
	m_frameResetSize	= (float) cam->GetAcqParam(P_FRAME_RESET_SIZE);	// us
	m_iFrameDelay		= (int) cam->GetAcqParam(P_FRAME_RESET_OFFSET);	 // us post trigger

}

void CTrigGrabDlg::OnTrgstart() 
{
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	CICamera *cam = theApp->m_cam;
	
	//UpdateData(TRUE);
	// Delete any pre-existing trigger thread
	if(m_trgThread) {
		delete m_trgThread;
		m_trgThread = NULL;
		cam->SetAcqParam(P_TRIGGER_ENABLE, IFC_DISABLE);
		
		//m_vParent->ClearView();
		m_TrigStart.SetWindowText ("Start"); 
		
		
	}
	else {
		UpdateData(TRUE);
		UpdateData(TRUE);
		ResetStatistics();
		m_TrigStart.SetWindowText ("Stop"); 
		
		cam->SetAcqParam(P_TRIGGER_ENABLE,			m_iTrigEnable);
		cam->SetAcqParam(P_TRIGGER_POLARITY,		m_iTrigPolarity);
		if (m_iTrigSrc==3)
			cam->SetAcqParam(P_TRIGGER_SRC,				IFC_EXT_AUTO_TRIG);
		else
			cam->SetAcqParam(P_TRIGGER_SRC,				m_iTrigSrc);
		
		cam->SetAcqParam(P_STROBE_ENABLE,			m_iStrobeEnable);
		cam->SetAcqParam(P_STROBE_MODE,				m_iStrobeMode);
		cam->SetAcqParam(P_STROBE_POLARITY,			m_iStrobePolarity);
		cam->SetAcqParam(P_STROBE_DELAY,			m_iStrobeDelay);   // lines post-trigger
		
		cam->SetAcqParam(P_FRAME_RESET_MODE,		m_iFrameMode);
		cam->SetAcqParam(P_FRAME_RESET_POLARITY,	m_iFramePolarity);
		cam->SetAcqParam(P_FRAME_RESET_SIZE,		m_frameResetSize);	// us
		cam->SetAcqParam(P_FRAME_RESET_OFFSET,		m_iFrameDelay);		// lines post-trigger
		
		m_trgThread = new CTrgThrd(this);
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

	if(	pSliderCtrl == (CSliderCtrl*) GetDlgItem(IDC_STROBE_DELAY))
	{
		pEdit = (CEdit*) GetDlgItem(IDC_STROBE_DELAY_E);
		m_iStrobeDelay = (int) nPos;
		wsprintf(str, "%d", ++m_iStrobeDelay);
	}
	else
	{
		pEdit = (CEdit*) GetDlgItem(IDC_FRAME_DELAY_E);
		m_iFrameDelay = (int) nPos;
		wsprintf(str, "%d", ++m_iFrameDelay);
	}

	ASSERT(pEdit);
	pEdit->SetWindowText(str);
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTrigGrabDlg::OnContinuous() 
{
UpdateData();

	if(m_bContinuous)
	{
		m_ImagesNum.EnableWindow(FALSE);
	}
	else
	{
		m_ImagesNum.EnableWindow(TRUE);
	}	
}

void CTrigGrabDlg::RefreshStatistics()
{

	LPTSTR pData = m_strData.GetBuffer(c_nMaxData);
	GetStatistics( pData );
	m_strData.ReleaseBuffer();

	if (m_strData == m_strLastData) return;

	m_strLastData = m_strData;

	CClientDC	cDC(&m_winStats);
	CDC         cMemDC;
	CBitmap     cBitmap;
	CBitmap    *pOldBitmap;
	CFont	   *pOldFont;
	CRect       client;

	//   Get the Client Rectangle
	m_winStats.GetClientRect(client);

	//   Create Compatible Memory Device Context
	cMemDC.CreateCompatibleDC( &cDC );

	//   Create a Bitmap for the Memory Device Context
	cBitmap.CreateCompatibleBitmap(&cDC, client.Width(), client.Height());

	// Select the Bitmap into the Memory Device Context
	pOldBitmap = cMemDC.SelectObject(&cBitmap);

	// Get the Parent Background Brush
	HBRUSH hBrush = (HBRUSH) SendMessage(WM_CTLCOLORDLG, (WPARAM)cMemDC.m_hDC, (LPARAM)m_hWnd);
	// Erase Background
	cMemDC.FillRect(&client, CBrush::FromHandle(hBrush) );
	
	// Set the mem dc font
	HFONT hFont = (HFONT) m_winStats.SendMessage(WM_GETFONT, 0, 0);
	pOldFont = cMemDC.SelectObject( CFont::FromHandle(hFont) );

	CSize sizeText = cMemDC.GetTextExtent(m_strData);
	int nMidX = client.Width() / 2;
	int nY = 0;

	pData = m_strData.GetBuffer(c_nMaxData);
	while (*pData && nY < client.Height() )
	{
		LPTSTR pStart = pData;

		// find the tab and out name
		LPTSTR pTab = pData;
		while (*pTab && *pTab != _T('\t') ) pTab++;
		if (pTab)
		{
			*pTab++ = _T('\0');
		}
		cMemDC.TextOut(0, nY, pStart );

		// find the end of the line and output data
		LPTSTR pEol = pTab;
		while (*pEol && *pEol != _T('\n') ) pEol++;
		if (pEol)
		{
			*pEol++ = _T('\0');
		}
		cMemDC.TextOut(nMidX, nY, pTab);

		// move to next line
		pData = pEol;
		nY += sizeText.cy;
	}
	m_strData.ReleaseBuffer();

	//   Transfer Formated Display to Screen
	cDC.BitBlt(0, 0, client.Width(), client.Height(), &cMemDC, 0, 0, SRCCOPY);

	//   Clean-Up Resources
	cMemDC.SelectObject(pOldBitmap);
	cMemDC.SelectObject(pOldFont);
}


void CTrigGrabDlg::OnTimer(UINT nIDEvent) 
{
	RefreshStatistics();
	
	CDialog::OnTimer(nIDEvent);
}

int CTrigGrabDlg::GetStatistics(LPTSTR pszData)
{
	LPTSTR pszWork = pszData;

	pszWork += sprintf(pszWork, _T("Triggers\t%d\n"), m_nTriggers);
	pszWork += sprintf(pszWork, _T("Average Acq Time\t%d  %s\n"), m_avgTime, "ms");
	pszWork += sprintf(pszWork, _T("MaxInterval\t%d  %s\n"), m_maxTime, "ms");
	pszWork += sprintf(pszWork, _T("MinInterval\t%d  %s\n"), m_minTime, "ms");
	pszWork += sprintf(pszWork, _T("LastInterval\t%d  %s\n"), m_dwLastInterval, "ms");
	pszWork += sprintf(pszWork, _T("Good Images\t%d\n"), m_nVerifyGood);
	pszWork += sprintf(pszWork, _T("Bad Images\t%d\n"), m_nVerifyBad);
	pszWork += sprintf(pszWork, _T("Missed Images\t%d\n"), m_nNumMissed);
	pszWork += sprintf(pszWork, _T("Lost Images\t%d\n"), m_nNumLost);

	// return filled length
	return (pszWork - pszData);
}

void CTrigGrabDlg::ResetStatistics()
{
	m_nTriggers = 0;
	m_avgTime = 0;
	m_maxTime = 0;
	m_minTime = 0;
	m_dwLastInterval = 0;
	m_nVerifyGood = 0;
	m_nVerifyBad = 0;
	m_nNumMissed = 0;
	m_nNumLost = 0;
}


LRESULT CTrigGrabDlg::OnKillMe(WPARAM wParam, LPARAM lParam)
{
	if(m_trgThread)
	{
		delete m_trgThread;
		m_trgThread = NULL;
		//m_vParent->ClearView();
		m_TrigStart.SetWindowText ("Start"); 

	}

	return 0;
}
