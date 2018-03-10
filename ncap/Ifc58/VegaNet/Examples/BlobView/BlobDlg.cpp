// BlobAnlz.cpp : implementation file
//

#include "stdafx.h"
#include "BlobView.h"
#include "BlobDlg.h"
#include "BlobViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BlobAnlz dialog


BlobAnlz::BlobAnlz(CWnd* pParent /*=NULL*/)
	: CDialog(BlobAnlz::IDD, pParent)
{
	//{{AFX_DATA_INIT(BlobAnlz)
	m_AvgBlobArea = 0;
	m_MaxBlobArea = 100;
	m_minBlobArea = 16;
	m_NumBlobs = 0;
	//}}AFX_DATA_INIT
	m_parent = (CBlobViewView*)pParent;
}


void BlobAnlz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BlobAnlz)
	DDX_Control(pDX, IDC_NUM_BLOBS, m_ctlNumBlobs);
	DDX_Control(pDX, IDC_AVG_BLOB_AREA, m_ctlAvgBlobArea);
	DDX_Text(pDX, IDC_AVG_BLOB_AREA, m_AvgBlobArea);
	DDX_Text(pDX, IDC_MAX_BLOB_AREA, m_MaxBlobArea);
	DDV_MinMaxDWord(pDX, m_MaxBlobArea, 1, 1000000);
	DDX_Text(pDX, IDC_MIN_BLOB_AREA, m_minBlobArea);
	DDV_MinMaxDWord(pDX, m_minBlobArea, 1, 1000000);
	DDX_Text(pDX, IDC_NUM_BLOBS, m_NumBlobs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BlobAnlz, CDialog)
	//{{AFX_MSG_MAP(BlobAnlz)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SET_BLOB_PARAMS, OnSetBlobParams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BlobAnlz message handlers

BOOL BlobAnlz::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char docName[100];
	VSPROPS vidSrcProps;
	m_parent->m_pICap->GetProps(&vidSrcProps);
	sprintf(docName, "Blob Analysis  %s : %s", m_parent->m_vidSrcNodeName,(char*)vidSrcProps.installedName);

	SetWindowText(docName);


	m_nTimer = SetTimer(1, 500, 0);

	if (m_parent->m_blobObj) {
		m_parent->m_blobObj->SetBlobAreas(m_minBlobArea,m_MaxBlobArea);
	}	
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BlobAnlz::OnTimer(UINT nIDEvent) 
{
	char str[80];
	m_AvgBlobArea = m_parent->m_avgBlobArea;
	m_NumBlobs = m_parent->m_numDetectedBlobs;
	m_ctlAvgBlobArea.SetWindowText(itoa(m_AvgBlobArea,str,10));
	m_ctlNumBlobs.SetWindowText(itoa(m_NumBlobs,str,10));

	CDialog::OnTimer(nIDEvent);
}

void BlobAnlz::OnDestroy() 
{
	CDialog::OnDestroy();

	KillTimer(m_nTimer);   
	
}

void BlobAnlz::OnSetBlobParams() 
{
	UpdateData(TRUE);
	if (m_parent->m_blobObj) {
		m_parent->m_blobObj->SetBlobAreas(m_minBlobArea,m_MaxBlobArea);
	}	
	
}
