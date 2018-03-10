/******************************************************************************
 *
 * MODULE   
 *		IfcIntr.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/IntrEx/ifcintr.h $
 *    $Revision: 1.1 $
 *    $Modtime: 8/23/00 5:16p $
 *
 * ABSTRACT
 *    PCVisionplus Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
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
#include <pcplus.h>
#include "IntrDlg.h"


// In the order in which interrupt constants are define in pcplus.h
enum{	THREAD_SOT = PCP_INTR_SOT, // PCVisionplus Start of Trigger Interrupt
		THREAD_EOT, 
		THREAD_INPORT, 
		THREAD_SW_TIMER,
		THREAD_VB,
		THREAD_EVEN_VB,
		THREAD_ODD_VB,
		THREAD_ACQ_ADRS,
		THREAD_BMDONE,
		THREAD_AM_CASCADE,
		THREAD_EOFRM,
		THREAD_LAST};


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
	IFC_INTREVENT GetEvent();

public:
BOOL m_IsResumed;


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
