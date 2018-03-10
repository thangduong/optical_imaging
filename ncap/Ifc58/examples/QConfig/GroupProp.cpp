// GroupProp.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "GroupProp.h"
#include "ConfigureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGroupProp dialog


CGroupProp::CGroupProp(CWnd* pParent /*=NULL*/)
	: CDialog(CGroupProp::IDD, pParent)
{
	IFC_PARAM_GROUP_PROPS groupProps;
	char mask[80];
	CConfigureDlg *parent=(CConfigureDlg*)pParent;
	parent->m_pCamera->GetGroupProperties(parent->m_rClickGroup,&groupProps);
	sprintf(mask,"0x%x", groupProps.groupMask);
	//{{AFX_DATA_INIT(CGroupProp)
	m_GroupEnum = groupProps.groupName;
	m_GroupMask = mask;
	m_GroupName = groupProps.presentationName;
	//}}AFX_DATA_INIT
}


void CGroupProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGroupProp)
	DDX_Text(pDX, IDC_EDIT_GENUM, m_GroupEnum);
	DDX_Text(pDX, IDC_EDIT_GMASK, m_GroupMask);
	DDX_Text(pDX, IDC_EDIT_GNAME, m_GroupName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGroupProp, CDialog)
	//{{AFX_MSG_MAP(CGroupProp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGroupProp message handlers
