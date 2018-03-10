/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/VegaNet/Examples/Overlay/PROCTHRD.H $
 *     $Revision: 1.1 $
 *     $Modtime: 3/25/99 11:24a $
 *
 * ABSTRACT
 *     This module is part of the PCDig Image Processing Example
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/

#if !defined(AFX_PROCTHRD_H__A54330F2_2F62_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_PROCTHRD_H__A54330F2_2F62_11D1_AE31_00A0C959E757__INCLUDED_

class PROCTHRD;

#include "OverlayV.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// procthrd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PROCTHRD window

class PROCTHRD 
{
// Construction
public:
	PROCTHRD(COverlayView *thread_view);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PROCTHRD)
	//}}AFX_VIRTUAL

// Implementation
public:

	friend DWORD WINAPI ProcessThread(LPVOID owner);
	virtual ~PROCTHRD();

	// Generated message map functions
protected:
	//{{AFX_MSG(PROCTHRD)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
private:
	BOOLEAN shutdown;
	HANDLE hthread;
	COverlayView *m_thread_view;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCTHRD_H__A54330F2_2F62_11D1_AE31_00A0C959E757__INCLUDED_)
