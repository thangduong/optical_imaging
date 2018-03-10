/******************************************************************************
 *
 * MODULE   
 *		IfcIntr.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/intrex/ifcintr.h $
 *    $Revision: 1.1 $
 *    $Modtime: 9/16/04 4:26p $
 *
 * ABSTRACT
 *    NetSightII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001-2004 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/
// IfcIntr.h: interface for the CIfcInterrupt class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __IFCINTR_H__
#define __IFCINTR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifc.h>
#include <NSII.h>

// In the order in which interrupt constants are define in NetSightII.h
enum {	
		THREAD_VB = NSP_INTR_VB,
		THREAD_ODD_VB,
		THREAD_EVEN_VB,
		THREAD_EOFRM,
		THREAD_SOT , 
		THREAD_BMDONE,
		THREAD_START_FIELD,
		THREAD_START_ODD, 
		THREAD_START_EVEN, 
		THREAD_START_FRAME, 
		THREAD_BMDONE2,
		THREAD_BMDONE3,
		THREAD_SKIPPED_FIELD,
		THREAD_INPORT,
		THREAD_LOSS_SYNC,
		THREAD_TRIG_SKIPPED,
		THREAD_SW_TIMER,
		THREAD_AIO_FIFO_OVERFLOW,
		THREAD_AIO_DECISION_ABSENT,
		THREAD_AIO_DECISION_LATE,
		THREAD_DATAPIN0,
		THREAD_DATAPIN1,
		THREAD_DATAPIN2,
		THREAD_DATAPIN3,
		THREAD_DATAPIN4,
		THREAD_DATAPIN5,
		THREAD_DATAPIN6,
		THREAD_DATAPIN7,

		THREAD_LAST
};


class CIfcInterrupt  
{
public:
	CIfcInterrupt::CIfcInterrupt(CICapMod *pMod, IFC_INTREVENT iEvent, 
							 void (*Func)(LPVOID pParam), LPVOID pParam,
							 void (*TimeoutFunc)(LPVOID pTimeoutParam), LPVOID pTimeoutParam);
	virtual ~CIfcInterrupt();
	DWORD	Resume();
	DWORD	Suspend();
	void	Terminate();
	friend  UINT IntrThreadProc(LPVOID pParam);

private:
	CICapMod	*m_pMod;
	IFC_INTREVENT	m_iEvent;
	CInterrupt  *m_Intr;
	HANDLE		m_Win32Event;
	int			m_iTimeout;
	BOOL		m_bContinue;
	CWinThread  *m_pThread;
	BOOL		m_bTerminateDontRun;
	LPVOID		m_pFuncParam;
	void		(*m_pFunc)(LPVOID pParam);
	LPVOID		m_pTimeoutFuncParam;
	void		(*m_pTimeoutFunc)(LPVOID pParam);

};

#endif // __IFCINTR_H__
