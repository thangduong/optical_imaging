/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/3Cam1Grab/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 5/21/03 5:40p $
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

#if !defined(AFX_TRGTHRD_H__52E83F45_CD2A_45F9_AB08_E35075F68924__INCLUDED_)
#define AFX_TRGTHRD_H__52E83F45_CD2A_45F9_AB08_E35075F68924__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "3Cam1GrabView.h"

class CTrgThrd  
{
public:
	CTrgThrd();
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	BOOLEAN m_shutdown;
	HANDLE hthread;
};

#endif // !defined(AFX_TRGTHRD_H__52E83F45_CD2A_45F9_AB08_E35075F68924__INCLUDED_)
