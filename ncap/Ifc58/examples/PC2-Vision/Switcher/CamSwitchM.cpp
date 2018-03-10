/******************************************************************************
 *
 * MODULE
 *    CamSwitchM.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/CamSwitchM.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 5/19/03 1:31p $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 * CamSwitchM.cpp : implementation of the CCamSwitchM class
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/


#include "stdafx.h"
#include "CamSwitchM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCamSwitchM dialog


CCamSwitchM::CCamSwitchM( UINT32 maxNbCamera /* = 0xff0*/, CWnd* pParent /*=NULL*/)
	: CDialog(CCamSwitchM::IDD, pParent)
{
   m_MaxNbCamera = maxNbCamera;
   m_insideValidateCameraChange=FALSE;
	//{{AFX_DATA_INIT(CCamSwitchM)
	m_singleRing = FALSE;
	m_NbCamera = 2;
	//}}AFX_DATA_INIT
}


void CCamSwitchM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCamSwitchM)
	DDX_Text(pDX, IDC_NB_CAMERA, m_NbCamera);
	DDX_Check(pDX, IDC_SINGLE_RING, m_singleRing);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_CAMSWITCH_1STCAMERA, m_CamIdx[0]);
	DDX_Control(pDX, IDC_CAMSWITCH_2NDCAMERA, m_CamIdx[1]);
	DDX_Control(pDX, IDC_CAMSWITCH_3RDCAMERA, m_CamIdx[2]);
	DDX_Control(pDX, IDC_CAMSWITCH_4THCAMERA, m_CamIdx[3]);
	DDX_Control(pDX, IDC_CAMSWITCH_5THCAMERA, m_CamIdx[4]);
	DDX_Control(pDX, IDC_CAMSWITCH_6THCAMERA, m_CamIdx[5]);
}


BEGIN_MESSAGE_MAP(CCamSwitchM, CDialog)
	//{{AFX_MSG_MAP(CCamSwitchM)
	ON_EN_CHANGE(IDC_CAMSWITCH_1STCAMERA, OnChange1stcamera)
	ON_EN_CHANGE(IDC_CAMSWITCH_2NDCAMERA, OnChange2ndcamera)
	ON_EN_CHANGE(IDC_CAMSWITCH_3RDCAMERA, OnChange3rdcamera)
	ON_EN_CHANGE(IDC_CAMSWITCH_4THCAMERA, OnChange4thcamera)
	ON_EN_CHANGE(IDC_CAMSWITCH_5THCAMERA, OnChange5thcamera)
	ON_EN_CHANGE(IDC_CAMSWITCH_6THCAMERA, OnChange6thcamera)
	ON_EN_CHANGE(IDC_NB_CAMERA, OnChangeNbCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCamSwitchM message handlers

BOOL CCamSwitchM::OnInitDialog() 
{
   char msg[128];
	CDialog::OnInitDialog();
	
   UpdateData( TRUE);

   for( UINT32 i = 1; (i <= 6) && ( i <= m_MaxNbCamera); i++)
   {
      sprintf( msg, "%d", i);
      m_CamIdxValue[i - 1] = i;
      m_CamIdx[i - 1].SetWindowText(msg);
   }

   EnableCamSelectControls();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCamSwitchM::OnChange1stcamera() 
{
   ValidateCameraChange( 0);
}

void CCamSwitchM::OnChange2ndcamera() 
{
   ValidateCameraChange( 1);
}

void CCamSwitchM::OnChange3rdcamera() 
{
   ValidateCameraChange( 2);
}

void CCamSwitchM::OnChange4thcamera() 
{
   ValidateCameraChange( 3);
}

void CCamSwitchM::OnChange5thcamera() 
{
   ValidateCameraChange( 4);
}

void CCamSwitchM::OnChange6thcamera() 
{
   ValidateCameraChange( 5);
}

void CCamSwitchM::OnChangeNbCamera() 
{
   UINT32 oldNbCamera = m_NbCamera;

	UpdateData( TRUE);

   if(  (m_NbCamera < 0) || (m_NbCamera > (int)m_MaxNbCamera) )
   {
      m_NbCamera = oldNbCamera;
   }
   else
   {
      EnableCamSelectControls();
   }
	UpdateData( FALSE);	
}

void CCamSwitchM::EnableCamSelectControls( void) 
{
      //enable/disable the camera selection.
      for( int i = 0; i < 6; i++)
      {
         if( i < m_NbCamera)
         {
            m_CamIdx[i].EnableWindow( TRUE);
         }
         else
         {
            m_CamIdx[i].EnableWindow( FALSE);
         }
      }
}


void CCamSwitchM::ValidateCameraChange( UINT32 SeqIndex) 
{
	char oldMsg[128];
	char msg[128];
	UINT32 camIdx;
	if (	m_insideValidateCameraChange)
		return;
	m_insideValidateCameraChange=TRUE;
	
	m_CamIdx[SeqIndex].GetWindowText( oldMsg, 128);
	
	UpdateData( TRUE);
	
	m_CamIdx[SeqIndex].GetWindowText( msg, 128);
	
	camIdx = atoi( msg);
	
	if( (camIdx > 6) || (camIdx < 1))
	{
		m_CamIdx[SeqIndex].SetWindowText( oldMsg);
	}
	else
	{
		m_CamIdxValue[SeqIndex ] = camIdx;
	}
	
	m_insideValidateCameraChange=FALSE;
	UpdateData( FALSE);
}

UINT32 CCamSwitchM::GetCameraIndex( UINT32 SeqIndex) 
{
   return( m_CamIdxValue[ SeqIndex]);
}

UINT32 CCamSwitchM::GetNbCamera( void) 
{
   return( m_NbCamera);
}
