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

	m_iOrigin	= 0;
	m_iRelHOffset	= (int) theapp->m_cam->RelativeHOffsetGet();
	m_iRelVOffset	= (int) theapp->m_cam->RelativeVOffsetGet();
	m_iAbsHOffset	= (int) theapp->m_cam->GetAcqParam(P_HORZ_OFF);
	m_iAbsVOffset	= (int) theapp->m_cam->GetAcqParam(P_VERT_OFF);
	m_uWidth	= (UINT) theapp->m_cam->GetAcqParam(P_WIDTH_PIXELS);
	m_uHeight	= (UINT) theapp->m_cam->GetAcqParam(P_HEIGHT_PIXELS);

	m_iHOffset = m_iRelHOffset;
	m_iVOffset = m_iRelVOffset;
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
	DDV_MinMaxInt(pDX, m_iHOffset, -16384, 16384);
	DDX_Text(pDX, IDC_WGEN_Y, m_iVOffset);
	DDV_MinMaxInt(pDX, m_iVOffset, -16384, 16384);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgwin, CDialog)
	//{{AFX_MSG_MAP(CDlgwin)
	ON_BN_CLICKED(IDC_RELATIVE, OnRelative)
	ON_BN_CLICKED(IDC_ABSOLUTE, OnAbsolute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgwin message handlers

void CDlgwin::OnRelative()
{
	CButton* pButton = (CButton*) GetDlgItem(IDC_ABSOLUTE);
	ASSERT(pButton);
	pButton->SetCheck(0);

	pButton = (CButton*) GetDlgItem(IDC_RELATIVE);
	ASSERT(pButton);
	pButton->SetCheck(1);


	m_iOrigin = 0;
	m_iHOffset = m_iRelHOffset;
	m_iVOffset = m_iRelVOffset;

	char str[80];
	wsprintf(str, "%d", m_iHOffset);
	CEdit* pOffEdit = (CEdit*) CDialog::GetDlgItem(IDC_WGEN_X);
	ASSERT(pOffEdit);
	pOffEdit->SetWindowText(str);

	wsprintf(str, "%d", m_iVOffset);
	pOffEdit = (CEdit*) CDialog::GetDlgItem(IDC_WGEN_Y);
	ASSERT(pOffEdit);
	pOffEdit->SetWindowText(str);
}

void CDlgwin::OnAbsolute()
{
	CButton* pButton = (CButton*) GetDlgItem(IDC_RELATIVE);
	ASSERT(pButton);
	pButton->SetCheck(0);

	pButton = (CButton*) GetDlgItem(IDC_ABSOLUTE);
	ASSERT(pButton);
	pButton->SetCheck(1);

	m_iOrigin = 1;
	m_iHOffset = m_iAbsHOffset;
	m_iVOffset = m_iAbsVOffset;

	char str[80];
	wsprintf(str, "%d", m_iHOffset);
	CEdit* pOffEdit = (CEdit*) CDialog::GetDlgItem(IDC_WGEN_X);
	ASSERT(pOffEdit);
	pOffEdit->SetWindowText(str);

	wsprintf(str, "%d", m_iVOffset);
	pOffEdit = (CEdit*) CDialog::GetDlgItem(IDC_WGEN_Y);
	ASSERT(pOffEdit);
	pOffEdit->SetWindowText(str);
}

BOOL CDlgwin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CButton* pButton = (CButton*) GetDlgItem(IDC_RELATIVE);
	ASSERT(pButton);
	pButton->SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
