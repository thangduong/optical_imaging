/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 1/16/02 8:54a $
 *
 * ABSTRACT
 *    PCVisionPlus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
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
	//{{AFX_DATA_INIT(CCamSel)
	m_PortNum = 0;
	//}}AFX_DATA_INIT
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	m_parent = (CSeqsnapView *)pParent;
	m_parent->CreateImageServer();
}


void CCamSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSel)
	DDX_Radio(pDX, IDC_PORT0, m_PortNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSel, CDialog)
	//{{AFX_MSG_MAP(CCamSel)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PORT0, OnPort0)
	ON_BN_CLICKED(IDC_PORT1, OnPort1)
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
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CCamSel::~CCamSel()
{
}



void CCamSel::OnPort0()
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

	// Read the selected camera name
	char *curCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

	m_parent->DelImageServer(); // Delete Image server, since the image attributes are changing

	theapp->m_cam = theapp->m_iCap->GetCam(0);
	// Assign the selected camera to the current port
	theapp->m_cam->SetCameraType(curCamera);


	m_parent->ClearView();
	// Create a new image server to display the selected camera
	m_parent->CreateImageServer();
	
}

void CCamSel::OnPort1() 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

	// Read the selected camera name
	char *curCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

	m_parent->DelImageServer(); // Delete Image server, since the image attributes are changing

	theapp->m_cam = theapp->m_iCap->GetCam(1);
	// Assign the selected camera to the current port
	theapp->m_cam->SetCameraType(curCamera);


	m_parent->ClearView();
	// Create a new image server to display the selected camera
	m_parent->CreateImageServer();
	
}
