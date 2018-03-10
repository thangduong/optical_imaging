/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/SEQSNAP/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/30/99 8:39a $
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

#if !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "trgsheet.h"

class CTrgThrd  
{
public:
	CTrgThrd(CTrgSheet *parent);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CTrgSheet *m_parent;
	BOOLEAN m_shutdown;
	HANDLE m_hthread;
};

#endif // !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
