// UserName.cpp : implementation file
//

#include "stdafx.h"
#include "UserName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUserName dialog


CUserName::CUserName(CWnd* pParent /*=NULL*/,LPTSTR nodeName)
	: CDialog(CUserName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUserName)
	m_Domain = _T("");
	m_password = _T("");
	m_UserName = _T("");
	m_NodeName = _T("");
	//}}AFX_DATA_INIT
	if (nodeName)
		m_NodeName = nodeName;

}


void CUserName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUserName)
	DDX_Text(pDX, IDC_DOMAIN, m_Domain);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_NODE_NAME, m_NodeName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUserName, CDialog)
	//{{AFX_MSG_MAP(CUserName)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUserName message handlers
