// Dlgwin.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "Dlgwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgwin dialog


CDlgwin::CDlgwin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgwin::IDD, pParent)
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	//{{AFX_DATA_INIT(CDlgwin)
	//}}AFX_DATA_INIT
	m_x = (int)theapp->m_cam->GetAcqParam(P_HORZ_OFF);
	m_dx = (int)theapp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
	m_y = (int)theapp->m_cam->GetAcqParam(P_VERT_OFF);
	m_dy = (int)theapp->m_cam->GetAcqParam(P_HEIGHT_PIXELS);	
}


void CDlgwin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgwin)
	DDX_Text(pDX, IDC_WGEN_DX, m_dx);
	DDV_MinMaxUInt(pDX, m_dx, 64, 16384);
	DDX_Text(pDX, IDC_WGEN_DY, m_dy);
	DDV_MinMaxUInt(pDX, m_dy, 2, 32768);
	DDX_Text(pDX, IDC_WGEN_X, m_x);
	DDV_MinMaxInt(pDX, m_x, 0, 16384);
	DDX_Text(pDX, IDC_WGEN_Y, m_y);
	DDV_MinMaxUInt(pDX, m_y, 0, 16384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgwin, CDialog)
	//{{AFX_MSG_MAP(CDlgwin)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgwin message handlers
