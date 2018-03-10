/******************************************************************************
 *
 * MODULE
 *    VixnTime.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/pcdig/PulseGen/vixntime.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/30/99 11:24a $
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

#if !defined(AFX_MYVIXN_H__A13A8D3A_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
#define AFX_MYVIXN_H__A13A8D3A_38F8_11D2_AF52_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Vixni.h>

class CVixnTimer : public CVixn 
{
public:
	virtual BOOL VixnMain();
	CVixnTimer(PCParentMod mod,double frequency,DWORD microSecondsHigh,DWORD cycleCount);
	virtual ~CVixnTimer();

	BOOL SetInactive(void);

	CVixnEle m_microSecondsHigh;

	CVixnEle m_intrCount;
	CVixnEle m_ScheduleCount;
	CVixnEle m_deltaTime;
};

#endif // !defined(AFX_MYVIXN_H__A13A8D3A_38F8_11D2_AF52_00105A0F576C__INCLUDED_)
