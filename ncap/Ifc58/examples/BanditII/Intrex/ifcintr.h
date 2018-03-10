/******************************************************************************
 *
 * MODULE   
 *		IfcIntr.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/Intrex/ifcintr.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/02/01 2:46p $
 *
 * ABSTRACT
 *    BanditII Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2001 Coreco Imaging, Inc.  All rights reserved.
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
#include <Bandit2.h>

// In the order in which interrupt constants are define in Bandit2.h
enum {	
		THREAD_VB = BDT_INTR_VB,
		THREAD_EOFRM,
		THREAD_SOT , 
		THREAD_BMDONE,
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
