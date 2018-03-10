/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/LargeAcq/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/21/99 2:14p $
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

#if !defined(AFX_TRGTHRD_H__EF37B467_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
#define AFX_TRGTHRD_H__EF37B467_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "LargeAcqView.h"

class CTrgThrd  
{
public:
	BOOL SetAoiPos(DWORD x, DWORD y);
	CTrgThrd(CLargeAcqView *parent);
	DWORD TriggerLoop(void);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CLargeAcqView *m_parent;
	BOOLEAN m_shutdown;
	HANDLE hthread;
	DWORD m_ScrollOffset;
};

#endif // !defined(AFX_TRGTHRD_H__EF37B467_2FCA_11D3_B0B0_00105A0F576C__INCLUDED_)
