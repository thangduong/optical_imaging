/******************************************************************************
 *
 * MODULE
 *    3Cam1Grab.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/3Cam1Grab/3Cam1Grab.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/21/03 6:08p $
 *
 * ABSTRACT
 *    main header file for the 3CAM1GRAB application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_3CAM1GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_)
#define AFX_3CAM1GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>
#include "TrgThrd.h"

#define NUM_CAMERAS 3
#define FRAMES_IN_HOSTBUFF 4


/////////////////////////////////////////////////////////////////////////////
// C3Cam1GrabApp:
// See 3Cam1Grab.cpp for the implementation of this class
//

class C3Cam1GrabApp : public CWinApp
{
public:
	C3Cam1GrabApp();
	~C3Cam1GrabApp();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3Cam1GrabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CICapMod	*m_pMod;	// IFC board module handle
	CICamera *m_cam;

	CAM_ATTR m_camAttrib;

	CImgConn *m_imgConn[NUM_CAMERAS];

	BYTE *m_imgBuf;	// Memory space which is the destination of the grab operation
	CTrgThrd *m_trgThread;
	DWORD m_childCount;

	HANDLE m_connMutex;
// Implementation

	//{{AFX_MSG(C3Cam1GrabApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3CAM1GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_)
