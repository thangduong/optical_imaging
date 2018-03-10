// CscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "CscDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCscDlg dialog


CCscDlg::CCscDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCscDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCscDlg)
	m_iRadioButtonCsc = 0;
	//}}AFX_DATA_INIT
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	m_parent = (CSeqsnapView *) pParent;
	m_parent->CreateImageServer();
}


void CCscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCscDlg)
	DDX_Radio(pDX, IDC_RADIO_RGB_TO_RGB, m_iRadioButtonCsc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCscDlg, CDialog)
	//{{AFX_MSG_MAP(CCscDlg)
	ON_BN_CLICKED(IDC_RADIO_RGB_TO_YUV, OnRadioRgbToYuv)
	ON_BN_CLICKED(IDC_RADIO_RGB_TO_YIQ, OnRadioRgbToYiq)
	ON_BN_CLICKED(IDC_RADIO_RGB_TO_YCRCB_4_4_4, OnRadioRgbToYcrcb444)
	ON_BN_CLICKED(IDC_RADIO_RGB_TO_HSI, OnRadioRgbToHsi)
	ON_BN_CLICKED(IDC_RADIO_RGB_TO_RGB, OnRadioRgbToRgb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCscDlg message handlers

// This maps the camera CSC parameter to the associated radio button.
DWORD CCscDlg::m_dwCscButtonVals[NUM_CSC_OPTIONS] = {
	0, // IFC_CSC_USE_CUSTOM_MATRIX 
	0, // IFC_CSC_RGB_TO_RGB
	1, // IFC_CSC_RGB_TO_YUV
	2, // IFC_CSC_RGB_TO_YIQ
	3, // IFC_CSC_RGB_TO_YCRCB_4_4_4
	0, // IFC_CSC_RGB_TO_YCRCB_4_2_2
	0, // IFC_CSC_RGB_TO_YCRCB_4_2_2
	4, // IFC_CSC_HSI
};

BOOL CCscDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();
	m_pCam = theapp->m_cam;
	m_dwCscSel = (IFC_COLOR) ((DWORD) m_pCam->GetAcqParam(P_COLOR_SPACE_CONV));
	m_iRadioButtonCsc = m_dwCscButtonVals[m_dwCscSel];
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCscDlg::OnRadioRgbToYuv() 
{
	m_dwCscSel = IFC_CSC_RGB_TO_YUV;
	NewImageServer();
}

void CCscDlg::OnRadioRgbToYiq() 
{
	m_dwCscSel = IFC_CSC_RGB_TO_YIQ;
	NewImageServer();
}

void CCscDlg::OnRadioRgbToYcrcb444() 
{
	m_dwCscSel = IFC_CSC_RGB_TO_YCRCB444;
	NewImageServer();
}


void CCscDlg::OnRadioRgbToHsi() 
{
	m_dwCscSel = IFC_CSC_RGB_TO_HSI;
	NewImageServer();
}

void CCscDlg::OnRadioRgbToRgb() 
{
	m_dwCscSel = IFC_CSC_RGB_TO_RGB;
	NewImageServer();
}

void CCscDlg::NewImageServer()
{
	m_parent->DelImageServer();
/*
	IFC_COLOR oldColor= (IFC_COLOR)(DWORD)m_pCam->GetAcqParam(P_PIXEL_COLOR);
	if (oldColor != IFC_RGB) { 
		DWORD width=(DWORD)m_pCam->GetAcqParam(P_WIDTH_PIXELS);
		if (oldColor==IFC_RGB_PLANAR)
			width /= 3;
		else if (oldColor==IFC_aRGB_PLANAR)
			width /= 4;
		m_pCam->SetAcqParam(P_PIXEL_COLOR, (double) IFC_RGB);
		m_pCam->SetAcqParam(P_WIDTH_PIXELS, (double) width);
	}
*/
	m_pCam->SetAcqParam(P_COLOR_SPACE_CONV, (double) m_dwCscSel);
	m_parent->ClearView();
	m_parent->CreateImageServer();
}

