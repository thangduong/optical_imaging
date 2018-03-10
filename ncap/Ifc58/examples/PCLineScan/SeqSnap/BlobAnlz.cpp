// BlobAnlz.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "BlobAnlz.h"
#include "ProcThrd.h"
#include "seqsnapv.h"

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
	m_MaxBlobArea = 20;
	m_minBlobArea = 8;
	m_NumBlobs = 0;
	//}}AFX_DATA_INIT
	m_parent = (CSeqsnapView*)pParent;
}


void BlobAnlz::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BlobAnlz)
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


	m_nTimer = SetTimer(1, 500, 0);

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void BlobAnlz::OnTimer(UINT nIDEvent) 
{
	CSeqsnapApp *theapp=(CSeqsnapApp*)AfxGetApp();	
	CProcessThread *rleThread=m_parent->m_rleThread;
	UpdateData(TRUE);
	m_AvgBlobArea = rleThread->m_avgBlobArea;
	m_NumBlobs = rleThread->m_numDetectedBlobs;


	

	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}

void BlobAnlz::OnDestroy() 
{
	CDialog::OnDestroy();

	KillTimer(m_nTimer);   
	
}

void BlobAnlz::OnSetBlobParams() 
{
	CProcessThread *rleThread=m_parent->m_rleThread;
	UpdateData(TRUE);
	rleThread->m_minBlobArea = m_minBlobArea;
	rleThread->m_maxBlobArea  = m_MaxBlobArea;
	
	
}
