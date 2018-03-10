/******************************************************************************
 *
 * MODULE   
 *		IfcIntr.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVision2/IntrEx/ifcintr.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 9/16/02 9:35a $
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
// IfcIntr.cpp: implementation of the CIfcInterrupt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IntrEx.h"
#include "IfcIntr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// default interrupt timeout
static const int iDefaultTimeout = 1000; // miliseconds


// This is the procedure that all threads are running
UINT IntrThreadProc(LPVOID pParam)
{
	// get parent pointer
	CIfcInterrupt *pParent = (CIfcInterrupt *) pParam;
	BOOL bGotInterrupt;
	DWORD intrCount=0;
	DWORD toggle =0;

	// terminating never resumed thread? just exit
 	if(pParent->m_bTerminateDontRun == TRUE)
		return 0;


	// connect interrupt that this thread will service
	pParent->m_Intr = new CInterrupt(pParent->m_pMod, pParent->m_iEvent);

	if ( !pParent->m_Intr->Connected() ) {
		delete pParent->m_Intr; 
		::MessageBox(NULL,"Could not connect interrupt", "Error", MB_OK | MB_ICONSTOP);
		return 0;
	};


	// get event that will be signal when interrupt pParent->m_Intr is asserted
	pParent->m_Win32Event = pParent->m_Intr->EventHandle();

	// enter thread's main loop
	while (pParent->m_bContinue == TRUE) {

		//wait for an interrupt
		bGotInterrupt = WaitForSingleObject (pParent->m_Win32Event, iDefaultTimeout) == WAIT_OBJECT_0;


		pParent->m_Intr->Rearm();
		if (bGotInterrupt) {

			// got interrupt execute user's interrupt function
			if(pParent->m_pFunc != NULL)
				(*pParent->m_pFunc)(pParent->m_pFuncParam);

		}else{
			//  timed-out waiting for an interrupt execute user's time-out function
			if(pParent->m_pTimeoutFunc != NULL)
				(*pParent->m_pTimeoutFunc)(pParent->m_pTimeoutFuncParam);

		};
	};
	// exiting

	// disconnect interrupt
	delete (pParent->m_Intr);
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIfcInterrupt::CIfcInterrupt(CICapMod *pMod, IFC_INTREVENT iEvent, 
							 void (*pFunc)(LPVOID pParam), LPVOID pParam,
							 void (*pTimeoutFunc)(LPVOID pTimeoutParam), LPVOID pTimeoutParam)
{
	m_pMod				= pMod;				// ITI board module
	m_iEvent			= iEvent;			// interrupt to use
	m_iTimeout			= iDefaultTimeout;	// default timeout value
	m_pFuncParam		= pParam;			// pointer to interrupt function parameters
	m_pFunc				= pFunc;			// pointer to interrupt function
	m_pTimeoutFuncParam	= pTimeoutParam;	// pointer to timeout function parameters
	m_pTimeoutFunc		= pTimeoutFunc;		// pointer to timeout function
	m_bContinue			= TRUE;				// main loop termination variable
	m_bTerminateDontRun	= FALSE;			// flag to clean terminate never resumed threads

	m_pThread = AfxBeginThread(IntrThreadProc, (LPVOID)this, 0, 0, CREATE_SUSPENDED);
	m_pThread->m_bAutoDelete = FALSE;
}

CIfcInterrupt::~CIfcInterrupt()
{
	Terminate();
}

DWORD CIfcInterrupt::Resume()
{
	ASSERT(m_pThread != NULL);
	return  m_pThread->ResumeThread();
}

DWORD CIfcInterrupt::Suspend()
{
	ASSERT(m_pThread != NULL);
	return  m_pThread->SuspendThread();
}

void CIfcInterrupt::Terminate()
{
	ASSERT(m_pThread != NULL);
	// set flag to force clean exit if the thread
	// was created and then never resumed
	m_bTerminateDontRun = TRUE;
	// allow thread to exit its loop
	m_bContinue = FALSE;
	Resume();
	// wait until it exits 
	::WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	delete m_pThread;
	m_pThread = NULL;
}


