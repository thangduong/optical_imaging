/******************************************************************************
 *
 * MODULE   
 *		IfcIntr.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PC2-CamLink/intrex/ifcintr.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/20/04 11:00a $
 *
 * ABSTRACT
 *    PCVision2 Example Program
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
#include <PC2Link.h>

// In the order in which interrupt constants are define in PCVision2.h
enum {	
		THREAD_VB = CL2_INTR_VB,
		THREAD_HB,
		THREAD_EOFRM,
		THREAD_SOT , 
		THREAD_BMDONE,
		THREAD_FRAME_SKIPPED,
		THREAD_ERROR_PIXEL_CLOCK,
		THREAD_END_OF_NLINES,
		THREAD_INPORT,
		THREAD_ERROR_LINE_SIZE,

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
