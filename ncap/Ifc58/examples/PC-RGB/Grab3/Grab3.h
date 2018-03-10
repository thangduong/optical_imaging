/******************************************************************************
 *
 * MODULE
 *    Grab3.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/Grab3/Grab3.h $
 *    $Revision: 1.1 $
 *    $Modtime: 9/14/99 11:22a $
 *
 * ABSTRACT
 *    main header file for the GRAB3 application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_GRAB3_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_GRAB3_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>


/////////////////////////////////////////////////////////////////////////////
// CGrab3App:
// See Grab3.cpp for the implementation of this class
//

class CGrab3App : public CWinApp
{
public:
	CGrab3App();
	~CGrab3App();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrab3App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CICapMod	*m_pMod;	// IFC board module handle
	CICamera *m_cam;
	DWORD m_childCount;

	CAM_ATTR m_camAttrib;


// Implementation

	//{{AFX_MSG(CGrab3App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAB3_H__9AFEEA57_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
