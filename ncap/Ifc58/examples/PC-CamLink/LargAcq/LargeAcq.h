/******************************************************************************
 *
 * MODULE
 *    LargeAcq.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/LargeAcq/LargeAcq.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/18/01 9:06a $
 *
 * ABSTRACT
 *    main header file for the LARGEACQ application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_LARGEACQ_H__EF37B465_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
#define AFX_LARGEACQ_H__EF37B465_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>


/////////////////////////////////////////////////////////////////////////////
// CLargeAcqApp:
// See LargeAcq.cpp for the implementation of this class
//

class CLargeAcqApp : public CWinApp
{
public:
	CLargeAcqApp();
	~CLargeAcqApp();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLargeAcqApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CICapMod	*m_pMod;	// IFC board module handle
	CICamera *m_cam;

	CAM_ATTR m_camAttrib;
	BOOL		m_anyTrigThread;


// Implementation

	//{{AFX_MSG(CLargeAcqApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LARGEACQ_H__EF37B465_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
