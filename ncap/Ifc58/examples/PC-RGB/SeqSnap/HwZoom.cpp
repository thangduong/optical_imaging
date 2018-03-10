/******************************************************************************
 *
 * MODULE
 *    HwZoom.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/SEQSNAP/HwZoom.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/01/02 8:09a $
 *
 * ABSTRACT
 *    PCRGB Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
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
	ON_BN_CLICKED(IDC_XZ_FACTOR_4, OnXzFactor4)
	ON_BN_CLICKED(IDC_YZ_NO, OnYzNo)
	ON_BN_CLICKED(IDC_YZ_FACTOR_2, OnYzFactor2)
	ON_BN_CLICKED(IDC_YZ_FACTOR_4, OnYzFactor4)
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
	m_xzoom = 0.5;
}

void CHwZoom::OnXzFactor4() 
{
	m_xzoom = 0.25;
}

void CHwZoom::OnYzNo()
{
	m_yzoom = 1.0;
}

void CHwZoom::OnYzFactor2() 
{
	m_yzoom = 0.5;
}

void CHwZoom::OnYzFactor4() 
{
	m_yzoom = 0.25;
}

BOOL CHwZoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    CButton *xsoftbut = (CButton*)GetDlgItem(IDC_XZ_NO);
	xsoftbut->SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
