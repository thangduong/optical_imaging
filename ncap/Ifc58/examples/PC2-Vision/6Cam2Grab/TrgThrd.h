/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-Vision/6Cam2Grab/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/06/03 9:52a $
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
#include "6Cam2GrabView.h"

class CTrgThrd  
{
public:
	CTrgThrd(DWORD groupID);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	BOOLEAN m_shutdown;
	HANDLE hthread;
	DWORD m_groupID;
};

#endif // !defined(AFX_TRGTHRD_H__52E83F45_CD2A_45F9_AB08_E35075F68924__INCLUDED_)
