/******************************************************************************
 *
 * MODULE   
 *		IntrEx.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/examples/PCVision/IntrEx/IntrEx.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/24/99 9:36a $
 *
 * ABSTRACT  
 *		IFC Interrupt Example
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
// IntrEx.h : main header file for the INTREX application
//

#if !defined(AFX_INTREX_H__D59E9153_0072_11D2_A128_00A0246D9D39__INCLUDED_)
#define AFX_INTREX_H__D59E9153_0072_11D2_A128_00A0246D9D39__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "IfcIntr.h"

// max number of PCVision we can handle in the system
#define MAX_BOARD_COUNT 8
/////////////////////////////////////////////////////////////////////////////
// CIntrExApp:
// See IntrEx.cpp for the implementation of this class
//

class CIntrExApp : public CWinApp
{
public:
	CIntrExApp();

	// ITI hardware related routines 
	BOOL InitalizeIFC();
	void RemoveIFC();
	BOOL InitializeIfcIntr();

	// array of ponters to the PCVidion board modules
	CICapMod		*m_pBrdMod;
	// pointer to the active module
	CICapMod		*m_pActiveMod;		
	CICamera *m_cam;

	// camera frame size for each channel
	DWORD		m_nCurdx;
	DWORD		m_nCurdy;
	//  active board sequence number
	int			m_iActiveBoard;
	// image source depth (for IC-ASYNC always 8bit)
	int			m_iSrcBitDepth;
	CIfcInterrupt *m_pIntrObj[THREAD_LAST];
	unsigned long m_ulCounter[THREAD_LAST];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntrExApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIntrExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTREX_H__D59E9153_0072_11D2_A128_00A0246D9D39__INCLUDED_)