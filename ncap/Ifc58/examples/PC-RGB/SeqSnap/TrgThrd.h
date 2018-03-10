/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/SEQSNAP/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 10/27/99 4:11p $
 *
 * ABSTRACT
 *    PCRGB Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "TrigGrabDlg.h"

class CTrgThrd  
{
public:
	// CTrgThrd(CTrgSheet *parent);
	CTrgThrd(CTrigGrabDlg *parent);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CTrigGrabDlg *m_parent;
	BOOLEAN m_shutdown;
	HANDLE m_hthread;
};

#endif // !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
