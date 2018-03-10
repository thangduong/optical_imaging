// xform.cpp : implementation file
//

#include "stdafx.h"
#include "configurator.h"
#include "xform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransform dialog


CTransform::CTransform(CWnd* pParent /*=NULL*/,IVideoSrc *cam)
	: CDialog(CTransform::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransform)
	m_Transform = 0;
	//}}AFX_DATA_INIT
	m_cam = cam;
}


void CTransform::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransform)
	DDX_Control(pDX, IDC_ROT180_TRANSFORM, m_ctlRot180);
	DDX_Control(pDX, IDC_MIRROR_TRANSFORM, m_ctlMirror);
	DDX_Control(pDX, IDC_FLIP_TRANSFORM, m_ctlFlip);
	DDX_Radio(pDX, IDC_TRANSFORM, m_Transform);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransform, CDialog)
	//{{AFX_MSG_MAP(CTransform)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransform message handlers

BOOL CTransform::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!m_cam->TransformSupported(VS_FLIP_TRANSFORM))
		m_ctlFlip.EnableWindow(FALSE);

	if (!m_cam->TransformSupported(VS_MIRROR_TRANSFORM))
		m_ctlMirror.EnableWindow(FALSE);

	if (!m_cam->TransformSupported(VS_ROT180_TRANSFORM))
		m_ctlRot180.EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
