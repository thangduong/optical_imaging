/********************************************************************
 *
 * MODULE
 *    overlay.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/overlay/OVERLAY.H $
 *    $Revision: 1.1 $
 *    $Modtime: 5/21/99 10:46a $
 *
 * ABSTRACT
 *    IFC Overlay example program file
 *
 * TECHNICAL NOTES
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ********************************************************************/

// overlay.h : main header file for the OVERLAY application
//

#if !defined(AFX_OVERLAY_H__ECEE69F4_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
#define AFX_OVERLAY_H__ECEE69F4_3E85_11D1_A000_00A0246D9D39__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

typedef enum {
	transparent, 
	dark_red, 
	dark_green, 
	dark_yellow, 
	dark_blue, 
	dark_magenta, 
	dark_cyan, 
	light_gray1,
	money_green, 
	sky_blue, 
	cream, 
	light_gray2, 
	medium_gray, 
	red, 
	green, 
	yellow, 
	blue, 
	magenta, 
	cyan, 
	white
}STATIC_COLOR;

typedef enum {
	STRETCH_TO_FIT, 
	zoom05, 
	zoom10, 
	zoom20
}ZOOM;

// define possible image sources
enum{
	CAM_IMG_SRC,
	HOSTBUFF_IMGSRC
};

// define possible overlay types
enum{
	SOFTWARE_OVERLAY,	// software involved into mixing overlay and image
	YCRCB_OVERLAY		// overlay on primary surface
};


typedef enum{
	NONE,
	RECTANGLE,
	ELLIPSE,
	TEXT,
	FREE
}DRAWING_MODE;


/////////////////////////////////////////////////////////////////////////////
// COverlayApp:
// See overlay.cpp for the implementation of this class
//

class COverlayApp : public CWinApp
{
public:
	COverlayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COverlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COverlayApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OVERLAY_H__ECEE69F4_3E85_11D1_A000_00A0246D9D39__INCLUDED_)
