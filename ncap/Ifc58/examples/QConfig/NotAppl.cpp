// NotAppl.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "NotAppl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNotAppl dialog


CNotAppl::CNotAppl(CWnd* pParent /*=NULL*/,CString item, char *reason)
	: CDialog(CNotAppl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNotAppl)
	m_ReasonNotApplicable = reason;
	m_ItemName = item;
	//}}AFX_DATA_INIT
}


void CNotAppl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNotAppl)
	DDX_Text(pDX, IDC_NOT_APPL_REASON, m_ReasonNotApplicable);
	DDX_Text(pDX, IDC_NA_ITEM_NAME, m_ItemName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNotAppl, CDialog)
	//{{AFX_MSG_MAP(CNotAppl)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNotAppl message handlers
