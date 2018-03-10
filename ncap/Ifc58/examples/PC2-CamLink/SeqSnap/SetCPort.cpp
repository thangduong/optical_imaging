// SetCPort.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "SetCPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetCPort dialog


CSetCPort::CSetCPort(CWnd* pParent /*=NULL*/)
	: CDialog(CSetCPort::IDD, pParent)
{
	char portName[100];
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	theapp->m_cam->GetUartPortName(portName);
	//{{AFX_DATA_INIT(CSetCPort)
	m_commNum = 3;
	m_comPortName = portName;
	//}}AFX_DATA_INIT
}


void CSetCPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetCPort)
	DDX_Text(pDX, IDC_COMM_NUM, m_commNum);
	DDV_MinMaxUInt(pDX, m_commNum, 3, 15);
	DDX_Text(pDX, IDC_COM_NAME, m_comPortName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetCPort, CDialog)
	//{{AFX_MSG_MAP(CSetCPort)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetCPort message handlers
