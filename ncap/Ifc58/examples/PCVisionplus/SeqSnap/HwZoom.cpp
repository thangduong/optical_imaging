/******************************************************************************
 *
 * MODULE
 *    HwZoom.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/HwZoom.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 7/17/00 2:55p $
 *
 * ABSTRACT
 *    PCVisionplus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_xzoom = 1.0;
	m_yzoom = 1.0;
}


void CHwZoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHwZoom)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHwZoom, CDialog)
	//{{AFX_MSG_MAP(CHwZoom)
	ON_BN_CLICKED(IDC_XZ_NO, OnXzNo)
	ON_BN_CLICKED(IDC_XZ_FACTOR_2, OnXzFactor2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHwZoom message handlers

void CHwZoom::OnXzNo()
{
	m_xzoom = 1.0;
}

void CHwZoom::OnXzFactor2()
{
	m_xzoom = 0.50;
}


BOOL CHwZoom::OnInitDialog() 
{
	CDialog::OnInitDialog();

    CButton *xsoftbut = (CButton*) GetDlgItem(IDC_XZ_NO);
	xsoftbut->SetCheck(TRUE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
