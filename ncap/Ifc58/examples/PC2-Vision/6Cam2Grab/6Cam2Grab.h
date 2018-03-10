/******************************************************************************
 *
 * MODULE
 *    6Cam2Grab.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/6Cam2Grab/6Cam2Grab.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/06/03 10:17a $
 *
 * ABSTRACT
 *    main header file for the 6CAM2GRAB application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_6CAM2GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_)
#define AFX_6CAM2GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>
#include "TrgThrd.h"
#include <PCVision2.h>

#define NUM_CAMERAS 6
#define NUM_CAMERAS_PER_GROUP 3
#define NUM_CAMERA_GROUPS 2
#define FRAMES_IN_HOSTBUFF 4


/////////////////////////////////////////////////////////////////////////////
// C6Cam2GrabApp:
// See 6Cam2Grab.cpp for the implementation of this class
//

class C6Cam2GrabApp : public CWinApp
{
public:
	C6Cam2GrabApp();
	~C6Cam2GrabApp();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C6Cam2GrabApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CPCVision2	*m_pMod;	// IFC board module handle
	CICamera *m_cam;
	HIFCGRAB m_grabID[NUM_CAMERA_GROUPS];

	CAM_ATTR m_camAttrib;

	CImgConn *m_imgConn[NUM_CAMERAS];

	BYTE *m_imgBuf;	// Memory space which is the destination of the grab operation
	CTrgThrd *m_trgThread;
	DWORD m_childCount;

	HANDLE m_connMutex;
// Implementation

	//{{AFX_MSG(C6Cam2GrabApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_6CAM2GRAB_H__6C0A6614_8AE1_482B_B481_F71BFDC942C7__INCLUDED_)
