/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 10/18/02 6:13p $
 *
 * ABSTRACT
 *    PCRGB Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2001 Coreco Imaging, Inc.  All rights reserved.
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
	DDX_Control(pDX, IDC_PORT_LIST, m_ctlPortList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSel, CDialog)
	//{{AFX_MSG_MAP(CCamSel)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_PORT_LIST, OnSelchangePortList)
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
	int cam_index = lb_camname->FindStringExact(-1,camAttr.camName);
	if (cam_index != LB_ERR)
		lb_camname->SetCurSel(cam_index);	
	
	CICamera *cam;
	for ( i = 0; cam=iCap->GetCam(i) ; i++) {
		char portName[100];
		char camPortName[40];
		sprintf(portName,"Port %d  %s",i, iCap->GetCamPortName(i,camPortName));
		m_ctlPortList.AddString(portName);
	}

	m_ctlPortList.SetCurSel(m_PortNum);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CCamSel::~CCamSel()
{
}





void CCamSel::OnSelchangePortList() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	PCICapMod iCap = theapp->m_iCap;
	int i;
	UpdateData(TRUE);

	m_PortNum = m_ctlPortList.GetCurSel();	

	m_parent->DelImageServer(); // Delete Image server, since the image attributes are changing

	theapp->m_cam = iCap->GetCam(m_PortNum);
	iCap->SetActiveCamera(theapp->m_cam );


	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
	char *camname;
	
	
	lb->ResetContent();
	/* Populate list box with the supported Camera names */
	for(camname = theapp->m_cam->GetFirstCamType();camname;camname = theapp->m_cam->GetNextCamType()) {
		i=lb->AddString(camname);
		lb->SetItemDataPtr(i,camname);
	}
	
	// Set the currently selected camera on the active port
	CAM_ATTR camAttr;
	theapp->m_cam->GetAttr(&camAttr);
	int cam_index = lb->FindStringExact(-1,camAttr.camName);
	if (cam_index != LB_ERR)
		lb->SetCurSel(cam_index);	


	// Read the selected camera name
	char *curCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());
	// Assign the selected camera to the current port
	theapp->m_cam->SetCameraType(curCamera);


	m_parent->ClearView();
	// Create a new image server to display the selected camera
	m_parent->CreateImageServer();
	
}
