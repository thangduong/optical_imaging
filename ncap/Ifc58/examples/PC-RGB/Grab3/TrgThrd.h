/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PcRgb/Grab3/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 9/07/99 1:29p $
 *
 * ABSTRACT
 *    IFC Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_TRGTHRD_H__9AFEEA59_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
#define AFX_TRGTHRD_H__9AFEEA59_6520_11D3_B0E1_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "Grab3View.h"

class CTrgThrd  
{
public:
	CTrgThrd(CGrab3View *parent);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CGrab3View *m_parent;
	BOOLEAN m_shutdown;
	HANDLE hthread;
};

#endif // !defined(AFX_TRGTHRD_H__9AFEEA59_6520_11D3_B0E1_00105A0F576C__INCLUDED_)
