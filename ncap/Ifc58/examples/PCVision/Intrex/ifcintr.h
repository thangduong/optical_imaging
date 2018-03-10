// IfcIntr.h: interface for the CIfcInterrupt class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __IFCINTR_H__
#define __IFCINTR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifc.h>
#include <pcvision.h>

enum{

	THREAD_VB, 			// vertical blank
	THREAD_ODD_VB,
	THREAD_EVEN_VB,
	THREAD_AM,
	THREAD_TRIG,
	THREAD_ACQ_ADRS,
	THREAD_ACQ,
	THREAD_BMDONE,
	THREAD_INPORT,
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

private:
	pCModule		m_pMod;
	IFC_INTREVENT	m_iEvent;
	CInterrupt		*m_Intr;
	HANDLE			m_Win32Event;
	int				m_iTimeout;
	BOOL			m_bContinue;
	CWinThread		*m_pThread;
	BOOL			m_bTerminateDontRun;
	LPVOID			m_pFuncParam;
	void			(*m_pFunc)(LPVOID pParam);
	LPVOID			m_pTimeoutFuncParam;
	void			(*m_pTimeoutFunc)(LPVOID pParam);

};

#endif // __IFCINTR_H__
