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
//                  Dialog Box to select a camera type.
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
CCamSelDlg::CCamSelDlg(CWnd* pParent, CICamera *pCam, DWORD dwPortIndex)
	: CDialog(CCamSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCamSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_pszCurCamera  = NULL;
    m_dwCurPort     = dwPortIndex;
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
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSelDlg, CDialog)
	//{{AFX_MSG_MAP(CCamSelDlg)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
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
//              OnInitDialog
//------------------------------------------
BOOL CCamSelDlg::OnInitDialog() 
{
CDialog::OnInitDialog();
int i;
CListBox *lb_camname = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
char *camname;
CString strToShow;


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

    // Change the Window title

    strToShow.Format(_T("Select Camera Type for Port # %d"), m_dwCurPort);
    SetWindowText(strToShow);

    return TRUE;    // return TRUE unless you set the focus to a control
                    // EXCEPTION: OCX Property Pages should return FALSE
}