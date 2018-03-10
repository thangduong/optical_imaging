// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "ColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorDlg dialog


CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorDlg)
	m_iRadioButtonColorMode = -1;
	//}}AFX_DATA_INIT
	m_pCam = NULL;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	m_parent = (CSeqsnapView *) pParent;
	m_parent->CreateImageServer();
}


void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorDlg)
	DDX_Control(pDX, IDC_RADIO_RED, m_radioButtonRed);
	DDX_Radio(pDX, IDC_RADIO_RED, m_iRadioButtonColorMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	//{{AFX_MSG_MAP(CColorDlg)
	ON_BN_CLICKED(IDC_RADIO_RED, OnRadioRed)
	ON_BN_CLICKED(IDC_RADIO_GREEN, OnRadioGreen)
	ON_BN_CLICKED(IDC_RADIO_BLUE, OnRadioBlue)
	ON_BN_CLICKED(IDC_RADIO_aRGB_PLANAR, OnRADIOaRGBPLANAR)
	ON_BN_CLICKED(IDC_RADIO_RGB, OnRadioRgb)
	ON_BN_CLICKED(IDC_RADIO_RGB_24, OnRadioRgb24)
	ON_BN_CLICKED(IDC_RADIO_RGB_PLANAR, OnRadioRgbPlanar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorDlg message handlers


DWORD CColorDlg::m_dwColorButtonIds[NUM_COLOR_OPTIONS] = {
	IDC_RADIO_RED,
	IDC_RADIO_GREEN,
	IDC_RADIO_BLUE,
	IDC_RADIO_RGB,
	IDC_RADIO_RGB_24,
	IDC_RADIO_RGB_PLANAR,
	IDC_RADIO_aRGB_PLANAR
};

DWORD CColorDlg::m_dwBitmapIds[NUM_COLOR_OPTIONS] = {
	IDB_RED_BUTTON,
	IDB_GREEN_BUTTON,
	IDB_BLUE_BUTTON,
	IDB_RGB_BUTTON,
	IDB_RGB_24_BUTTON,
	IDB_RGB_PLANAR_BUTTON,
	IDB_aRGB_PLANAR_BUTTON
};

// This maps the camera color parameter to the associated radio button.
DWORD CColorDlg::m_dwColorButtonVals[IFC_NUM_COLOR_MODES] = {
	0, // IFC_MONO (not supported, map to red)
	0, // IFC_RED
	1, // IFC_GREEN
	2, // IFC_BLUE
	3, // IFC_RGB
	4, // IFC_RGB_PACK24
	0, // IFC_MONO_WORD_LO (not supported, map to red)
	0, // IFC_MONO_WORD_HI (not supported, map to red)
	5, // IFC_RGB_PLANAR
	6, // IFC_aRGB_PLANAR
	0, // IFC_YCRCB (not supported, map to RGB)
	0, // IFC_YCRCBMONO (not supported, map to RGB)
};

BOOL CColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();
	m_pCam = theapp->m_cam;
	m_color = (IFC_COLOR) ((DWORD) m_pCam->GetAcqParam(P_PIXEL_COLOR));
	m_iRadioButtonColorMode = m_dwColorButtonVals[m_color];

	CButton* pRadioButton;
    if ((BYTE) GetVersion() >=4) {
		for (WORD i = 0; i < NUM_COLOR_OPTIONS; i++) {
			if (m_Bitmaps[i].LoadBitmap(m_dwBitmapIds[i])) {
				pRadioButton = (CButton*) GetDlgItem(m_dwColorButtonIds[i]);
				pRadioButton->ModifyStyle(0, BS_BITMAP);
				pRadioButton->SetBitmap(m_Bitmaps[i]);
			}
        }
    }

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColorDlg::OnRadioRed() 
{
	m_color = IFC_RED;
	NewImageServer();
}

void CColorDlg::OnRadioGreen() 
{
	m_color = IFC_GREEN;
	NewImageServer();
}

void CColorDlg::OnRadioBlue() 
{
	m_color = IFC_BLUE;
	NewImageServer();
}

void CColorDlg::OnRadioRgb() 
{
	m_color = IFC_RGB;
	NewImageServer();
}

void CColorDlg::OnRadioRgb24() 
{
	m_color = IFC_RGB_PACK24;
	NewImageServer();
}

void CColorDlg::OnRadioRgbPlanar() 
{
	m_color = IFC_RGB_PLANAR;
	NewImageServer();
}

void CColorDlg::OnRADIOaRGBPLANAR() 
{
	m_color = IFC_aRGB_PLANAR;
	NewImageServer();
}

void CColorDlg::NewImageServer()
{
	m_parent->DelImageServer();
	m_pCam->SetAcqParam(P_PIXEL_COLOR, (double) m_color);
	m_parent->ClearView();
	m_parent->CreateImageServer();
}
