/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PiPAcq/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 7/01/99 10:40a $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
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
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

	if (!theapp->m_cam)
		return;
	// Read the selected camera name
	char *curCamera = (char*)lb->GetItemDataPtr(lb->GetCurSel());

	// Assign the selected camera to the current port
	theapp->m_cam->SetCameraType(curCamera);
}


BOOL CCamSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CLargeAcqApp *theapp=(CLargeAcqApp*)AfxGetApp();
	
	int i;
	CListBox *lb_camname = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
	char *camname;
	
	if (!theapp->m_cam)
		return FALSE;
	
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


