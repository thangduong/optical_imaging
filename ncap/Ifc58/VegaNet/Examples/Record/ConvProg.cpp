// ConvProg.cpp : implementation file
//

#include "stdafx.h"
#include "record.h"
#include "ConvProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvProg dialog


CConvProg::CConvProg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvProg)
	m_convText = _T("");
	//}}AFX_DATA_INIT

	m_cancelRequested = FALSE;
}


void CConvProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvProg)
	DDX_Text(pDX, IDC_CONV_TXT, m_convText);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvProg, CDialog)
	//{{AFX_MSG_MAP(CConvProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvProg message handlers

void CConvProg::OnCancel() 
{
	
	CDialog::OnCancel();
	m_cancelRequested = TRUE;

}
