/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/16/03 2:21p $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging, Inc.  All rights reserved.
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	m_parent = (CSeqsnapView *)pParent;
	m_parent->CreateImageServer();
}


void CCamSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCamSel, CDialog)
	//{{AFX_MSG_MAP(CCamSel)
	ON_LBN_SELCHANGE(IDC_LIST_CAMNAME, OnSelchangeListCamname)
	ON_WM_CLOSE()
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


