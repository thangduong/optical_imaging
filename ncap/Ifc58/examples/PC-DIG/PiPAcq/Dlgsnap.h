/******************************************************************************
 *
 * MODULE
 *    Dlgsnap.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PiPAcq/Dlgsnap.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/28/00 4:21p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_DLGSNAP_H__17D20AE6_3064_11D1_AE31_00A0C959E757__INCLUDED_)
#define AFX_DLGSNAP_H__17D20AE6_3064_11D1_AE31_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dlgsnap.h : header file
//

class CDlgsnap;
#include "LargeAcqView.h"
#include <ifc.h>

/////////////////////////////////////////////////////////////////////////////
// CDlgsnap dialog

class CDlgsnap : public CDialog
{
// Construction
public:
	CDlgsnap(CWnd* pParent = NULL);   // standard constructor

	virtual ~CDlgsnap();
// Dialog Data
	//{{AFX_DATA(CDlgsnap)
	enum { IDD = IDD_DLGSNAP };
	UINT	m_TimeOutTime;
	int		m_PipTrigger;
	int		m_ExsyncMode;
	UINT	m_numFrames;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgsnap)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	void SeqSnapAndSave(BOOL saveTif);

protected:

	int m_intrScaler; // image server interrupt scaling value (set to unity,i.e., display every frame)
	DWORD m_areaDx;	// DX of the image area being processed
	DWORD m_areaDy;  // DY of the image area being processed
	DWORD m_bytesPerPixel;
	CLargeAcqView *m_vparent;
	CSliderCtrl *m_slider;
	BYTE *m_SeqSnapBuf;

	// Generated message map functions
	//{{AFX_MSG(CDlgsnap)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSnap();
	afx_msg void OnPlay();
	afx_msg void OnGrab();
	afx_msg void OnSnapSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSNAP_H__17D20AE6_3064_11D1_AE31_00A0C959E757__INCLUDED_)