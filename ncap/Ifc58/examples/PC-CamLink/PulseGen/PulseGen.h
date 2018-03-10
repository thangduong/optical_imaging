/******************************************************************************
 *
 * MODULE
 *    PulseGen.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/PulseGen/PulseGen.h $
 *    $Revision: 1.1 $
 *    $Modtime: 2/21/03 11:30a $
 *
 * ABSTRACT
 *    PC-CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PULSEGEN_H__A2670645_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_)
#define AFX_PULSEGEN_H__A2670645_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <ifc.h>

/////////////////////////////////////////////////////////////////////////////
// CPulseGenApp:
// See PulseGen.cpp for the implementation of this class
//

class CPulseGenApp : public CWinApp
{
public:
	CPulseGenApp();
	~CPulseGenApp();

	BOOL IFCInit(void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPulseGenApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	CICapMod	*m_pMod;	// IFC board module handle
	CICamera *m_cam;

	CAM_ATTR m_camAttrib;
	BOOL		m_anyTrigThread;
// Implementation

	//{{AFX_MSG(CPulseGenApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PULSEGEN_H__A2670645_2E6D_11D3_B0AF_00105A0F576C__INCLUDED_)
