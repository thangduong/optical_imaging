/******************************************************************************
 *
 * MODULE
 *    TrigPro.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/IntrEx/TrigPro.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 7/30/99 9:10a $
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
#include "IntrEx.h"
#include "TrigPro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CTrigPro, CPropertyPage)

static int TrigCaptions[2] = {IDS_STR_TRIG0,IDS_STR_TRIG1}; 

CTrigPro::CTrigPro(CTrgSheet* pParent , int TrigIndex) 
: CPropertyPage(CTrigPro::IDD,TrigCaptions[TrigIndex])
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theApp->m_cam;
	m_TrigIndex = TrigIndex;
	//{{AFX_DATA_INIT(CTrigPro)
	m_GlitchDetectEnable = (int)cam->GetAcqParam(PCD_TRIG_GLITCH_DETECTOR,TrigIndex);
	m_TrigPolarity = (int)cam->GetAcqParam(P_TRIGGER_POLARITY,TrigIndex);
	m_TriggerSource = (int)cam->GetAcqParam(P_TRIGGER_SRC,TrigIndex);
	//}}AFX_DATA_INIT
}

CTrigPro::CTrigPro()
: CPropertyPage(CTrigPro::IDD)
{
}



void CTrigPro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrigPro)
	DDX_Radio(pDX, IDC_GD_DISABLE, m_GlitchDetectEnable);
	DDX_Radio(pDX, IDC_POLFALL, m_TrigPolarity);
	DDX_Radio(pDX, IDC_TrigDifferential, m_TriggerSource);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrigPro, CDialog)
	//{{AFX_MSG_MAP(CTrigPro)
	ON_BN_CLICKED(ID_APPLY, OnTApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrigPro message handlers



BOOL CTrigPro::OnInitDialog() 
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	CPropertyPage::OnInitDialog();
	
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CTrigPro::OnTApply() 
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theApp->m_cam;
	UpdateData(TRUE);
	cam->SetAcqParam(PCD_TRIG_GLITCH_DETECTOR,m_GlitchDetectEnable,m_TrigIndex);
	cam->SetAcqParam(P_TRIGGER_POLARITY,m_TrigPolarity,m_TrigIndex);
	cam->SetAcqParam(P_TRIGGER_SRC,m_TriggerSource,m_TrigIndex);
	
}

void CTrigPro::OnCancel() 
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theApp->m_cam;
	m_GlitchDetectEnable = (int)cam->GetAcqParam(PCD_TRIG_GLITCH_DETECTOR,m_TrigIndex);
	m_TrigPolarity = (int)cam->GetAcqParam(P_TRIGGER_POLARITY,m_TrigIndex);
	m_TriggerSource = (int)cam->GetAcqParam(P_TRIGGER_SRC,m_TrigIndex);
	UpdateData(FALSE);
}
