/******************************************************************************
 *
 * MODULE   
 *		TrgGrab.cpp
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/examples/LineScan/IntrEx/TrgGrab.cpp $
 *		$Revision: 1.1 $
 *		$Modtime: 3/22/00 3:06p $
 *
 * ABSTRACT  
 *		IFC Interrupt Example
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
// TrgGrab.cpp : implementation file
//

#include "stdafx.h"
#include "IntrEx.h"
#include "TrgGrab.h"
#include "TrigPro.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab property page

IMPLEMENT_DYNCREATE(CTrgGrab, CPropertyPage)


CTrgGrab::CTrgGrab(CTrgSheet *parent)
: CPropertyPage(CTrgGrab::IDD)
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	//{{AFX_DATA_INIT(CTrgGrab)
	//}}AFX_DATA_INIT
	if (theApp->m_startEvent == PCL_TMODE_DISABLE)
		m_TrigStartEvent = 0;
	else
		m_TrigStartEvent = (DWORD)theApp->m_startEvent - 1;

	if (theApp->m_stopEvent == PCL_TMODE_DISABLE)
		m_TrigEndEvent = 0;
	else
		m_TrigEndEvent = (DWORD)(theApp->m_stopEvent) - 1;
	m_parent = parent;


}

CTrgGrab::CTrgGrab()
: CPropertyPage(CTrgGrab::IDD)
{
}

CTrgGrab::~CTrgGrab()
{
}

void CTrgGrab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrgGrab)
	DDX_Radio(pDX, IDC_TRIG_START_DISABLE, m_TrigStartEvent);
	DDX_Radio(pDX, IDC_TRIG_END_DISABLE, m_TrigEndEvent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrgGrab, CPropertyPage )
	//{{AFX_MSG_MAP(CTrgGrab)
	ON_BN_CLICKED(IDC_APPLY, OnApplyTrig)
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrgGrab message handlers


BOOL CTrgGrab::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTrgGrab::OnApplyTrig() 
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	UpdateData(TRUE);
	if (m_TrigStartEvent != 0)
		theApp->m_startEvent = (PCL_TRIG_MODE_TYPE)(m_TrigStartEvent+1);
	else 
		theApp->m_startEvent = PCL_TMODE_DISABLE;

	if (m_TrigEndEvent != 0)
		theApp->m_stopEvent = (PCL_TRIG_MODE_TYPE)(m_TrigEndEvent+1);
	else 
		theApp->m_stopEvent = PCL_TMODE_DISABLE;

	((CPCLine*)(theApp->m_pActiveMod))->SetAcqTriggerEvents(theApp->m_startEvent ,theApp->m_stopEvent);
	
}

void CTrgGrab::OnCancel() 
{
	CIntrExApp *theApp=(CIntrExApp*)AfxGetApp();	
	CICamera *cam=theApp->m_cam;

	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	
}
