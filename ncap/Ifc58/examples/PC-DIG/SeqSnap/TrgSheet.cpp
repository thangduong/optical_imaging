/******************************************************************************
 *
 * MODULE
 *    TrgSheet.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/SEQSNAP/TrgSheet.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/06/99 6:35p $
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
#include "seqsnap.h"
#include "TrgSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrgSheet

IMPLEMENT_DYNAMIC(CTrgSheet, CPropertySheet)

CTrgSheet::CTrgSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_vparent = (CSeqsnapView*)pParentWnd;
	m_trigProp = new CTrgGrab(this);
	AddPage(m_trigProp);
	for (int i=0; i < 2; i++) {
		m_trigAttr[i] = new CTrigPro(this,i);
		AddPage(m_trigAttr[i]);
	}
}


CTrgSheet::CTrgSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_vparent = (CSeqsnapView*)pParentWnd;
	m_trigProp = new CTrgGrab(this);
	AddPage(m_trigProp);
	for (int i=0; i < 2; i++) {
		m_trigAttr[i] = new CTrigPro(this,i);
		AddPage(m_trigAttr[i]);
	}
}

CTrgSheet::~CTrgSheet()
{
}



BEGIN_MESSAGE_MAP(CTrgSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CTrgSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrgSheet message handlers

BOOL CTrgSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
   // this hides the Apply button
   CWnd* pApplyButton = GetDlgItem (ID_APPLY_NOW);
   ASSERT (pApplyButton);
   pApplyButton->ShowWindow (SW_HIDE);
	
	return bResult;
}


BOOL CTrgSheet::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	RemovePage(m_trigProp);
	delete m_trigProp;
	for (int i=0; i < 2; i++) {
		RemovePage(m_trigAttr[i]);
		delete m_trigAttr[i];
	}
	
	return CPropertySheet::DestroyWindow();
}
