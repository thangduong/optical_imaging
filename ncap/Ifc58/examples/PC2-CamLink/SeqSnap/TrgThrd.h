/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/21/03 10:18a $
 *
 * ABSTRACT
 *    CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "TrgGrab.h"

class CTrgThrd  
{
public:
	CTrgThrd(CTrgGrab *parent);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CTrgGrab *m_parent;
	BOOLEAN m_shutdown;
	HANDLE m_hthread;
};

#endif // !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
