// NewCameraDlg.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "NewCameraDlg.h"

#include "ifc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewCameraDlg dialog


CNewCameraDlg::CNewCameraDlg(CWnd* pParent /*=NULL*/, PCICapMod pICap)
	: CDialog(CNewCameraDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewCameraDlg)
	m_strNewCameraName = _T("");
	//}}AFX_DATA_INIT

	m_pICap = pICap;
}


void CNewCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewCameraDlg)
	DDX_Control(pDX, IDOK, m_buttonIDOK);
	DDX_Text(pDX, IDC_EDIT_NEW_CAMERA_NAME, m_strNewCameraName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewCameraDlg, CDialog)
	//{{AFX_MSG_MAP(CNewCameraDlg)
	ON_EN_CHANGE(IDC_EDIT_NEW_CAMERA_NAME, OnChangeEditNewCameraName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewCameraDlg message handlers


BOOL CNewCameraDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_buttonIDOK.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewCameraDlg::OnChangeEditNewCameraName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	UpdateData();
	m_buttonIDOK.EnableWindow(!m_strNewCameraName.IsEmpty());
//	UpdateData(FALSE);
}

CString CNewCameraDlg::GetCamName(CString &strCamName)
{
	strCamName = m_strNewCameraName;
	return strCamName;
}


void CNewCameraDlg::OnOK() 
{
	UpdateData();

	if (m_pICap->FindCameraType(m_strNewCameraName.GetBuffer(128)))
	{
		::MessageBox(NULL, "Camera definition already exists. Please enter a new name.",
					 "Camera Definition Exists", MB_OK);

		return;
	}

	CDialog::OnOK();
}
