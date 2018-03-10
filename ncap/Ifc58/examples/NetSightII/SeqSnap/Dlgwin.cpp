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
	CSeqsnapApp *theapp = (CSeqsnapApp*) AfxGetApp();

	//{{AFX_DATA_INIT(CDlgwin)
	//}}AFX_DATA_INIT

	m_iHOffset	= (int) theapp->m_cam->GetAcqParam(P_HORZ_OFF);
	m_iVOffset	= (int) theapp->m_cam->GetAcqParam(P_VERT_OFF);
	m_uWidth	= (UINT) theapp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
	m_uHeight	= (UINT) theapp->m_cam->GetAcqParam(P_HEIGHT_PIXELS);

}


void CDlgwin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgwin)
	DDX_Text(pDX, IDC_WGEN_DX, m_uWidth);
	DDV_MinMaxUInt(pDX, m_uWidth, 64, 16384);
	DDX_Text(pDX, IDC_WGEN_DY, m_uHeight);
	DDV_MinMaxUInt(pDX, m_uHeight, 2, 16384);
	DDX_Text(pDX, IDC_WGEN_X, m_iHOffset);
	DDV_MinMaxInt(pDX, m_iHOffset, 0, 16384);
	DDX_Text(pDX, IDC_WGEN_Y, m_iVOffset);
	DDV_MinMaxInt(pDX, m_iVOffset, 0, 16384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgwin, CDialog)
	//{{AFX_MSG_MAP(CDlgwin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgwin message handlers



BOOL CDlgwin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
