/******************************************************************************
 *
 * MODULE
 *    OutPort.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/OutPort.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 3/22/00 3:06p $
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
#include "OutPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutPort dialog


COutPort::COutPort(CWnd* pParent /*=NULL*/)
	: CDialog(COutPort::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutPort)
	m_genstrobe = FALSE;
	m_outport_val = 0;
	//}}AFX_DATA_INIT
}


void COutPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutPort)
	DDX_Check(pDX, IDC_GENSTROBE, m_genstrobe);
	DDX_Text(pDX, IDC_OUTPORT_VAL, m_outport_val);
	DDV_MinMaxUInt(pDX, m_outport_val, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutPort, CDialog)
	//{{AFX_MSG_MAP(COutPort)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutPort message handlers