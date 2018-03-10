// Config.cpp : implementation file
//

#include "stdafx.h"
#include "seqsnap.h"
#include "Config.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CConfigOcx dialog


CConfigOcx::CConfigOcx(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigOcx::IDD, pParent)
{
	m_pParent = (CSeqsnapView*)pParent;
	//{{AFX_DATA_INIT(CConfigOcx)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigOcx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigOcx)
	DDX_Control(pDX, IDC_ITICONFIGCTRL1, m_ITIConfigCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigOcx, CDialog)
	//{{AFX_MSG_MAP(CConfigOcx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigOcx message handlers

BOOL CConfigOcx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CSeqsnapApp* theapp = (CSeqsnapApp*) AfxGetApp();

	m_ITIConfigCtrl.SetMod((long)theapp->m_iCap,true,false,false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CConfigOcx, CDialog)
    //{{AFX_EVENTSINK_MAP(CConfigOcx)
	ON_EVENT(CConfigOcx, IDC_ITICONFIGCTRL1, 1 /* SetParam */, OnSetParamIticonfigctrl1, VTS_I2 VTS_R8 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CConfigOcx::OnSetParamIticonfigctrl1(short paramID, double value, long index) 
{
	// TODO: Add your control notification handler code here
	CSeqsnapApp* theapp = (CSeqsnapApp*) AfxGetApp();
	if (m_pParent->m_ImgConn ) {
		delete m_pParent->m_ImgConn;
		m_pParent->m_ImgConn = NULL;
		theapp->m_cam->Freeze();
	}
	theapp->m_cam->SetAcqParam(paramID,value,index);
	theapp->m_cam->Grab();
	m_pParent->m_ImgConn = new CImgConn(theapp->m_cam, m_pParent->m_hWnd ,IFC_LIVE_IMAGE ,ICAP_INTR_VB);
	
}
