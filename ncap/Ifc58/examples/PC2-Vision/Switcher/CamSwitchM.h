/******************************************************************************
 *
 * MODULE
 *    CamSwitchM.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/CamSwitchM.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/19/03 11:11a $
 *
 * ABSTRACT
 *    PC2-Vision Example Program
 *
 * TECHNICAL NOTES
 * CamSwitchM.h : header file for the CCamSwitchM class
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/
#if !defined(AFX_CAMSWITCHM_H__DD8AF2F8_DD66_4736_8C5E_C181CACBBD80__INCLUDED_)
#define AFX_CAMSWITCHM_H__DD8AF2F8_DD66_4736_8C5E_C181CACBBD80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CamSwitchM.h : header file
//

#include "Switcher.h"


/////////////////////////////////////////////////////////////////////////////
// CCamSwitchM dialog

class CCamSwitchM : public CDialog
{
// Construction
public:
	CCamSwitchM(UINT32 maxNbCamera = 0xff, CWnd* pParent = NULL);   // standard constructor
	UINT32 GetCameraIndex( UINT32 SeqIndex); 
	UINT32 GetNbCamera( void); 

// Dialog Data
	//{{AFX_DATA(CCamSwitchM)
	enum { IDD = IDD_CAMERA_SWITCH };
	int m_NbCamera;
	BOOL	m_singleRing;
	//}}AFX_DATA

	CEdit	m_CamIdx[6];
	UINT32 m_CamIdxValue[6];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCamSwitchM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
   UINT32 m_MaxNbCamera;
   BOOL m_insideValidateCameraChange;

   void ValidateCameraChange( UINT32 SeqIndex);
   void EnableCamSelectControls( void);

	// Generated message map functions
	//{{AFX_MSG(CCamSwitchM)
	virtual BOOL OnInitDialog();
	afx_msg void OnChange1stcamera();
	afx_msg void OnChange2ndcamera();
	afx_msg void OnChange3rdcamera();
	afx_msg void OnChange4thcamera();
	afx_msg void OnChange5thcamera();
	afx_msg void OnChange6thcamera();
	afx_msg void OnChangeNbCamera();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CAMSWITCHM_H__DD8AF2F8_DD66_4736_8C5E_C181CACBBD80__INCLUDED_)
