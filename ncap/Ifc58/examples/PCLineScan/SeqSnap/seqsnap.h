/******************************************************************************
 *
 * MODULE
 *    seqsnap.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/LineScan/seqsnap/seqsnap.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/28/00 2:47p $
 *
 * ABSTRACT
 *    PCLine Example Program
 *
 * TECHNICAL NOTES
 * seqsnap.h : Defines the class behaviors for the application.
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_SEQSNAP_H__17D20AD6_3064_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_SEQSNAP_H__17D20AD6_3064_11D1_AE31_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include <ifc.h>
#include <PCLine.h>

/////////////////////////////////////////////////////////////////////////////
// CSeqsnapApp:
// See seqsnap.cpp for the implementation of this class
//

class CSeqsnapApp : public CWinApp
{
public:
	CSeqsnapApp();
	virtual ~CSeqsnapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSeqsnapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	void InitIFC(void);

	CPCLine *m_iCap;
	CPCLCam *m_cam;
	// currently active board
	int			m_iActiveBoard;

	DWORD m_srcBitspp;	// bits per pixel = 8

	//{{AFX_MSG(CSeqsnapApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEQSNAP_H__17D20AD6_3064_11D1_AE31_00A0C959E757__INCLUDED_)
