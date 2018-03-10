// MaxSize.cpp : implementation file
//

#include "stdafx.h"
#include "Record.h"
#include "MaxSize.h"
#include "RecordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MaxSize dialog


MaxSize::MaxSize(CWnd* pParent /*=NULL*/)
	: CDialog(MaxSize::IDD, pParent)
{

	CMyRecordView *view = (CMyRecordView*)pParent;
	//{{AFX_DATA_INIT(MaxSize)
	m_maxFileSize = view->m_maxFileSize;
	m_stop = 0;
	m_compMethod = view->m_frameEncode;
	m_Sound = view->m_Sound;
	m_quality = view->m_quality;
	//}}AFX_DATA_INIT
}


void MaxSize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MaxSize)
	DDX_Control(pDX, IDC_QUALITY, m_ctlQuality);
	DDX_Text(pDX, IDC_MAX_FILE_SIZE, m_maxFileSize);
	DDV_MinMaxDWord(pDX, m_maxFileSize, 0, 1000000);
	DDX_Radio(pDX, IDC_STOP, m_stop);
	DDX_Radio(pDX, IDC_FILE_COMP, m_compMethod);
	DDX_Check(pDX, IDC_SOUND, m_Sound);
	DDX_Slider(pDX, IDC_QUALITY, m_quality);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MaxSize, CDialog)
	//{{AFX_MSG_MAP(MaxSize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MaxSize message handlers

BOOL MaxSize::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	m_ctlQuality.SetRangeMin(1);
	m_ctlQuality.SetRangeMax(100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
