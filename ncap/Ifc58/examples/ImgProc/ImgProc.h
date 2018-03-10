/******************************************************************************
 *
 * MODULE
 *    ImgProc.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/ImgProc/ImgProc.h $
 *    $Revision: 1.1 $
 *    $Modtime: 12/23/99 8:51a $
 *
 * ABSTRACT
 *    main header file for the IMGPROC application
 *
 * TECHNICAL NOTES
 *
 *
 *
 ******************************************************************************/


#if !defined(AFX_IMGPROC_H__C2055DC8_88B3_11D3_A228_005004051D9B__INCLUDED_)
#define AFX_IMGPROC_H__C2055DC8_88B3_11D3_A228_005004051D9B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>

#define FRAMES_IN_HOSTBUFF 4

/////////////////////////////////////////////////////////////////////////////
// CImgProcApp:
// See ImgProc.cpp for the implementation of this class
//

class CImgProcApp : public CWinApp
{
public:
	void ReturnID(int ID);
	int GetID();
	CImgProcApp();
	~CImgProcApp();

	BOOL IFCInit(void);



// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImgProcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	CICapMod	*m_pMod;	// IFC board module handle
	CICamera	*m_cam;

	BOOL	m_bPoolID[MAX_THREADS];
	int		m_NumOfActiveViews;
	int		m_anyTrigThread;

	HWND	m_hThreads[MAX_THREADS];
	DWORD	m_dwWidth[MAX_THREADS];
	DWORD	m_dwHeight[MAX_THREADS];



// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	//{{AFX_MSG(CImgProcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGPROC_H__C2055DC8_88B3_11D3_A228_005004051D9B__INCLUDED_)
