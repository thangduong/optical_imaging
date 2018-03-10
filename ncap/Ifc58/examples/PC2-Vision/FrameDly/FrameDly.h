/******************************************************************************
 *
 * MODULE
 *    FrameDly.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/FrameDly/FrameDly.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/09/03 6:08p $
 *
 * ABSTRACT
 *    main header file for the FRAMEDLY application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_FRAMEDLY_H__1DAEAE4E_8B18_4E4B_86CB_3542A9EAC825__INCLUDED_)
#define AFX_FRAMEDLY_H__1DAEAE4E_8B18_4E4B_86CB_3542A9EAC825__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>
#include <PCVision2.h>


/////////////////////////////////////////////////////////////////////////////
// CFrameDlyApp:
// See FrameDly.cpp for the implementation of this class
//

class CFrameDlyApp : public CWinApp
{
public:
	CFrameDlyApp();
	~CFrameDlyApp();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameDlyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CPCVision2	*m_pMod;	// IFC board module handle
	CICamera *m_cam;

	CAM_ATTR m_camAttrib;
	BOOL		m_anyTrigThread;


// Implementation

	//{{AFX_MSG(CFrameDlyApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMEDLY_H__1DAEAE4E_8B18_4E4B_86CB_3542A9EAC825__INCLUDED_)
