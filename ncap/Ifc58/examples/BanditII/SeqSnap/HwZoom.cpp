/******************************************************************************
 *
 * MODULE
 *    HwZoom.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/HwZoom.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 7/25/01 1:53p $
 *
 * ABSTRACT
 *    BanditII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"
#include "seqsnap.h"
#include "HwZoom.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHwZoom dialog


CHwZoom::CHwZoom(CWnd* pParent /*=NULL*/)
	: CDialog(CHwZoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHwZoom)
	m_xZoom = 1.0f;
	m_yZoom = 1.0f;
	//}}AFX_DATA_INIT
	CSeqsnapApp *theApp = (CSeqsnapApp*) AfxGetApp();
	theApp->m_cam->GetZoomCaps(&m_ZoomCap);

}


void CHwZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHwZoom)
	DDX_Text(pDX, IDC_XZOOM, m_xZoom);
	DDV_MinMaxFloat(pDX, m_xZoom, 0.2f, 1.2f);
	DDX_Text(pDX, IDC_YZOOM, m_yZoom);
	DDV_MinMaxFloat(pDX, m_yZoom, 0.2f, 1.2f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHwZoom, CDialog)
	//{{AFX_MSG_MAP(CHwZoom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHwZoom message handlers



BOOL CHwZoom::OnInitDialog() 
{
	CDialog::OnInitDialog();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
