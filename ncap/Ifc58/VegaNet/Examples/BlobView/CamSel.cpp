/******************************************************************************
 *
 * MODULE
 *    camsel.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/VegaNet/Examples/BlobView/CamSel.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 1/09/02 5:01p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999-2002 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "BlobView.h"

#include "BlobViewDoc.h"
#include "BlobViewView.h"

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
	m_parent = (CBlobViewView *)pParent;
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
	CListBox *lb = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);

	if (!m_parent->m_pICap)
		return;
	// Read the selected camera name
	char curCamera[200];
	int iSel = lb->GetCurSel();
	lb->GetText(iSel, curCamera);

	// Assign the selected camera to the current port
	m_parent->m_pICap->SetCameraType(curCamera);
}


BOOL CCamSel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	CListBox *lb_camname = (CListBox*)GetDlgItem(IDC_LIST_CAMNAME);
	HRESULT status;
	char camname[200];
	
	if (!m_parent->m_pICap)
		return FALSE;
	
	/* Populate list box with the supported Camera names */
	
	status = m_parent->m_pICap->GetFirstCamType(camname);
	while(status==S_OK) {
		i=lb_camname->AddString(camname);
		lb_camname->SetItemDataPtr(i,camname);
		status = m_parent->m_pICap->GetNextCamType(camname);
	}

	// Set the currently selected camera on the active port
	VS_CAM_ATTR camAttr;
	m_parent->m_pICap->GetAttr(&camAttr,TRUE);
	int cam_index = lb_camname->FindStringExact(-1,camAttr.camName);
	if (cam_index != LB_ERR)
		lb_camname->SetCurSel(cam_index);	
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

CCamSel::~CCamSel()
{
}


