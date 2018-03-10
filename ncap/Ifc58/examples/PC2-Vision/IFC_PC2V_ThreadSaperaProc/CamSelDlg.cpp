//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           CamSelDlg.cpp
//
//  BIRTH DATE:     December 2002
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
//  DESCRIPTION:
//                  Dialog Box to select camera and port.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "resource.h"                       // main GUI symbols
#include "CamSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//            Constructor
//------------------------------------------
CCamSelDlg::CCamSelDlg(CWnd* pParent, CICamera *pCam)
	: CDialog(CCamSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pszCurCamera  = NULL;
    m_dwCurPort     = 0;
    m_pCam          = pCam;

}


//------------------------------------------
//            Destructor
//------------------------------------------
CCamSelDlg::~CCamSelDlg()
{
}



//------------------------------------------
//              DoDataExchange
//------------------------------------------
void CCamSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSelDlg)
	DDX_Control(pDX, IDC_PORT0, m_RadioPort0);
	DDX_Control(pDX, IDC_PORT1, m_RadioPort1);
	DDX_Control(pDX, IDC_PORT2, m_RadioPort2);
	DDX_Control(pDX, IDC_PORT3, m_RadioPort3);
	DDX_Control(pDX, IDC_PORT4, m_RadioPort4);
	DDX_Control(pDX, IDC_PORT5, m_RadioPort5);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSelDlg, CDialog)
	//{{AFX_MSG_MAP(CCamSelDlg)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_BN_CLICKED(IDC_PORT0, OnPort0)
	ON_BN_CLICKED(IDC_PORT1, OnPort1)
	ON_BN_CLICKED(IDC_PORT2, OnPort2)
	ON_BN_CLICKED(IDC_PORT3, OnPort3)
	ON_BN_CLICKED(IDC_PORT4, OnPort4)
	ON_BN_CLICKED(IDC_PORT5, OnPort5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




//------------------------------------------
//              OnSelchangeListCamname
//------------------------------------------
void CCamSelDlg::OnSelchangeListCamname() 
{
    CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

    // Read the selected camera name
    m_pszCurCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

}

//------------------------------------------
//              OnPort0
//------------------------------------------
void CCamSelDlg::OnPort0() 
{
    m_dwCurPort = 0;
    m_RadioPort0.SetCheck(BST_CHECKED);
}

//------------------------------------------
//              OnPort1
//------------------------------------------
void CCamSelDlg::OnPort1() 
{
    m_dwCurPort = 1;
    m_RadioPort1.SetCheck(BST_CHECKED);
}

//------------------------------------------
//              OnPort2
//------------------------------------------
void CCamSelDlg::OnPort2() 
{
    m_dwCurPort = 2;
    m_RadioPort2.SetCheck(BST_CHECKED);
}

//------------------------------------------
//              OnPort3
//------------------------------------------
void CCamSelDlg::OnPort3() 
{
    m_dwCurPort = 3;
    m_RadioPort3.SetCheck(BST_CHECKED);
}

//------------------------------------------
//              OnPort4
//------------------------------------------
void CCamSelDlg::OnPort4() 
{
    m_dwCurPort = 4;
    m_RadioPort4.SetCheck(BST_CHECKED);
}

//------------------------------------------
//              OnPort5
//------------------------------------------
void CCamSelDlg::OnPort5() 
{
    m_dwCurPort = 5;
    m_RadioPort5.SetCheck(BST_CHECKED);
}



//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CCamSelDlg::OnInitDialog() 
{
CDialog::OnInitDialog();
int i;
CListBox *lb_camname = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
char *camname;

    if (m_pCam == NULL)
        return FALSE;

    // Populate list box with the supported Camera names

    for (camname = m_pCam->GetFirstCamType(); camname; camname = m_pCam->GetNextCamType())
    {
        i = lb_camname->AddString(camname);
        lb_camname->SetItemDataPtr(i, camname);
    }

    // Set the currently selected camera on the active port
    CAM_ATTR camAttr;

    m_pCam->GetAttr(&camAttr);
    int cam_index = lb_camname->FindStringExact(-1,camAttr.camName);
    if (cam_index != LB_ERR)
    {
        lb_camname->SetCurSel(cam_index);
        m_pszCurCamera = (char*)lb_camname->GetItemDataPtr(lb_camname->GetCurSel());
    }

    // Set the port 0 Radio Button as currently selected

    m_dwCurPort = 0;
    m_RadioPort0.SetCheck(BST_CHECKED);


    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}
