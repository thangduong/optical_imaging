/******************************************************************************
 *
 * MODULE
 *    TrigPro.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/SEQSNAP/TrigPro.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/24/99 4:03p $
 *
 * ABSTRACT
 *    PCDig Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_TRIGPRO_H__2A0410D7_3420_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRIGPRO_H__2A0410D7_3420_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TrigPro.h : header file
//

class CTrigPro;

#include <ifc.h>
#include <pcdig.h>
#include "trgsheet.h"

/////////////////////////////////////////////////////////////////////////////
// CTrigPro dialog

class CTrigPro : public CPropertyPage
{
	DECLARE_DYNCREATE(CTrigPro)

// Construction
public:
	CTrigPro(CTrgSheet* pParent, int TrigIndex=0);
	CTrigPro();

// Dialog Data
	//{{AFX_DATA(CTrigPro)
	enum { IDD = IDD_PROPTRG };
	int		m_GlitchDetectEnable;
	int		m_TrigPolarity;
	int		m_TriggerSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTrigPro)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	CTrgSheet *m_parent;

	int m_TrigIndex;
protected:
	// Generated message map functions
	//{{AFX_MSG(CTrigPro)
	virtual BOOL OnInitDialog();
	afx_msg void OnTApply();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIGPRO_H__2A0410D7_3420_11D1_AE32_00A0C959E757__INCLUDED_)
