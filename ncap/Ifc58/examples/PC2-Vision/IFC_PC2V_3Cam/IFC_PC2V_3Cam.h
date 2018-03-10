//------------------------------------------------------------------------------
//
//  APPLICATION:    IFC Demo for the PC2-Vision Frame Grabber
//
//  FILE:           IFC_PC2V_3Cam.h
//
//  BIRTH DATE:     January 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//                  -IFC (V.5.6.1)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------

#if !defined(AFX_IFC_PC2V_3CAM_H__FAD11340_C3CD_4F9D_AAC9_3D2DBE2A90E8__INCLUDED_)
#define AFX_IFC_PC2V_3CAM_H__FAD11340_C3CD_4F9D_AAC9_3D2DBE2A90E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIFC_PC2V_3CamApp:
// See IFC_PC2V_3Cam.cpp for the implementation of this class
//

class CIFC_PC2V_3CamApp : public CWinApp
{
public:
	CIFC_PC2V_3CamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFC_PC2V_3CamApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIFC_PC2V_3CamApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFC_PC2V_3CAM_H__FAD11340_C3CD_4F9D_AAC9_3D2DBE2A90E8__INCLUDED_)
