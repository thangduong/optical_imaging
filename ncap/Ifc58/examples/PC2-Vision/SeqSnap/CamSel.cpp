/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/SeqSnap/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/16/03 4:28p $
 *
 * ABSTRACT
 *    PCVision2 Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2002-2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "CamSel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamSel dialog


CCamSel::CCamSel(CWnd* pParent /*=NULL*/)
	: CDialog(CCamSel::IDD, pParent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	//{{AFX_DATA_INIT(CCamSel)
	m_PortNum = theapp->m_cam->GetPortNum();
	//}}AFX_DATA_INIT
	m_parent = (CSeqsnapView *)pParent;
	m_parent->CreateImageServer();
}


void CCamSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSel)
	DDX_Control(pDX, IDC_PORT0, m_ctlPort0);
	DDX_Control(pDX, IDC_PORT1, m_ctlPort1);
	DDX_Control(pDX, IDC_PORT2, m_ctlPort2);
	DDX_Control(pDX, IDC_PORT3, m_ctlPort3);
	DDX_Control(pDX, IDC_PORT4, m_ctlPort4);
	DDX_Control(pDX, IDC_PORT5, m_ctlPort5);
	DDX_Radio(pDX, IDC_PORT0, m_PortNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSel, CDialog)
	//{{AFX_MSG_MAP(CCamSel)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PORT0, OnPort)
	ON_BN_CLICKED(IDC_PORT1, OnPort)
	ON_BN_CLICKED(IDC_PORT2, OnPort)
	ON_BN_CLICKED(IDC_PORT3, OnPort)
	ON_BN_CLICKED(IDC_PORT4, OnPort)
	ON_BN_CLICKED(IDC_PORT5, OnPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamSel message handlers

void CCamSel::OnSelchangeListCamname() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

	// Read the selected camera name
	char *curCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

	m_parent->DelImageServer(); // Delete Image server, since the image attributes are changing

	// Assign the selected camera to the current port
	theapp->m_cam->SetCameraType(curCamera);


	m_parent->ClearView();
	// Create a new image server to display the selected camera
	m_parent->CreateImageServer();
}


BOOL CCamSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CListBox *lb_camname = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
	char *camname;
	PCICapMod iCap = theapp->m_iCap;
	
	
	/* Populate list box with the supported Camera names */
	for(camname = theapp->m_cam->GetFirstCamType();camname;camname = theapp->m_cam->GetNextCamType()) {
		i=lb_camname->AddString(camname);
		lb_camname->SetItemDataPtr(i,camname);
	}
	
	// Set the currently selected camera on the active port
	CAM_ATTR camAttr;
	theapp->m_cam->GetAttr(&camAttr);
	int camIndex = lb_camname->FindStringExact(-1,camAttr.camName);
	if (camIndex != LB_ERR)
		lb_camname->SetCurSel(camIndex);	
	
	
	m_ctlPort0.EnableWindow(iCap->GetCam(0) != NULL);
	m_ctlPort1.EnableWindow(iCap->GetCam(1) != NULL);
	m_ctlPort2.EnableWindow(iCap->GetCam(2) != NULL);
	m_ctlPort3.EnableWindow(iCap->GetCam(3) != NULL);
	m_ctlPort4.EnableWindow(iCap->GetCam(4) != NULL);
	m_ctlPort5.EnableWindow(iCap->GetCam(5) != NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CCamSel::~CCamSel()
{
}



void CCamSel::OnPort()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
	UpdateData(TRUE);


	m_parent->DelImageServer(); // Delete Image server, since the image attributes are changing

	theapp->m_cam = theapp->m_iCap->GetCam(m_PortNum);

	CAM_ATTR camAttr;
	theapp->m_cam->GetAttr(&camAttr);
	int camIndex = lb->FindStringExact(-1,camAttr.camName);
	if (camIndex != LB_ERR)
		lb->SetCurSel(camIndex);	


	m_parent->ClearView();
	// Create a new image server to display the selected camera
	m_parent->CreateImageServer();
	
}

