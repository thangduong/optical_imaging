/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 4/08/03 11:41a $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2002 Coreco Imaging Technology, Inc.  All rights reserved.
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
	m_camConn = 0;
	//}}AFX_DATA_INIT
}


void CCamSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSel)
	DDX_Radio(pDX, IDC_CONN1, m_camConn);
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
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();
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
	CSwitcherApp *theapp=(CSwitcherApp*)AfxGetApp();
	
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

