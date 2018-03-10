/******************************************************************************
 *
 * MODULE
 *    Switcher.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/Switcher/Switcher.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/19/03 11:12a $
 *
 * ABSTRACT
 *    main header file for the SWITCHER application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_SWITCHER_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_SWITCHER_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>
#include <PCVision2.h>



#define FRAMES_IN_HOSTBUFF 6

/////////////////////////////////////////////////////////////////////////////
// CSwitcherApp:
// See Switcher.cpp for the implementation of this class
//

class CSwitcherApp : public CWinApp
{
public:
	CSwitcherApp();
	~CSwitcherApp();

	BOOL IFCInit(void);
	void StartSwitchingGrab();



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSwitcherApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CPCVision2	*m_pMod;	// IFC board module handle
	CICamera *m_cam;
	DWORD m_childCount;

	CAM_ATTR m_camAttrib;

	DWORD   m_nbCamera;
	DWORD   m_camIdx[P2V_MAX_NUM_CAMERAS];
	DWORD   m_currentAcqChannel;

	BYTE	*m_pHostBuffFrame[P2V_MAX_NUM_CAMERAS];
	HIFCGRAB m_grabID[P2V_MAX_NUM_CAMERAS];
	BOOL	m_singleRing;


// Implementation

	//{{AFX_MSG(CSwitcherApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SWITCHER_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
