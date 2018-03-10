/******************************************************************************
 *
 * MODULE
 *    LutThrsh.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/LutThrsh.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 6/07/00 2:54p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "seqsnap.h"
#include "LutThrsh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLutThrsh dialog


CLutThrsh::CLutThrsh(CWnd* pParent /*=NULL*/,DWORD pixMaxVal)
	: CDialog(CLutThrsh::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLutThrsh)
	m_lutThresh = 0;
	m_LutThreshMax = pixMaxVal;
	//}}AFX_DATA_INIT
	m_pixMaxVal = pixMaxVal;
}


void CLutThrsh::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLutThrsh)
	DDX_Text(pDX, IDC_LUTTHRESH, m_lutThresh);
	DDV_MinMaxUInt(pDX, m_lutThresh, 0, m_pixMaxVal);
	DDX_Text(pDX, IDC_LUT_THRESH_MAX, m_LutThreshMax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLutThrsh, CDialog)
	//{{AFX_MSG_MAP(CLutThrsh)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLutThrsh message handlers
