//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           ConnSelDlg.cpp
//
//  BIRTH DATE:     February 2003
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
//                  Dialog Box to select connector and camera type.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "ifc.h"                            // IFC related
#include "PCVision2.h"                      // IFC related

#include "resource.h"                       // main GUI symbols
#include "ConnSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




//------------------------------------------
//            Constructor
//------------------------------------------
CConnSelDlg::CConnSelDlg(CWnd* pParent, CICamera *pCam)
	: CDialog(CConnSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pszCurCamera  = NULL;
    m_dwCurConn     = 0;
    m_pCam          = pCam;

}


//------------------------------------------
//            Destructor
//------------------------------------------
CConnSelDlg::~CConnSelDlg()
{
}



//------------------------------------------
//              DoDataExchange
//------------------------------------------
void CConnSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnSelDlg)
	DDX_Control(pDX, IDC_CONNECTOR0, m_ButtonConn0);
	DDX_Control(pDX, IDC_CONNECTOR1, m_ButtonConn1);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CConnSelDlg, CDialog)
	//{{AFX_MSG_MAP(CConnSelDlg)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_BN_CLICKED(IDC_CONNECTOR0, OnConnector0)
	ON_BN_CLICKED(IDC_CONNECTOR1, OnConnector1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



//------------------------------------------
//              OnInitDialog
//------------------------------------------
BOOL CConnSelDlg::OnInitDialog() 
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

    // Set the "connector 0" Radio Button as currently selected

    m_dwCurConn = 0;
	m_ButtonConn0.SetCheck(BST_CHECKED);


    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}


//------------------------------------------
//              OnConnector0
//------------------------------------------
void CConnSelDlg::OnConnector0() 
{
	m_dwCurConn = 0;
	m_ButtonConn0.SetCheck(BST_CHECKED);
	m_ButtonConn1.SetCheck(BST_UNCHECKED);
}


//------------------------------------------
//              OnConnector1
//------------------------------------------
void CConnSelDlg::OnConnector1() 
{
	m_dwCurConn = 1;
	m_ButtonConn1.SetCheck(BST_CHECKED);
	m_ButtonConn0.SetCheck(BST_UNCHECKED);
}



//------------------------------------------
//              OnSelchangeListCamname
//------------------------------------------
void CConnSelDlg::OnSelchangeListCamname() 
{
    CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

    // Read the selected camera name
    m_pszCurCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

}




BOOL CConnSelDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DestroyWindow();
}
