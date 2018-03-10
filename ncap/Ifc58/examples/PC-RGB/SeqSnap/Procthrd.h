/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/examples/PcRgb/SEQSNAP/PROCTHRD.H $Revision: 1.1 $
 *     $Modtime: 4/28/99 10:09a $
 *
 * ABSTRACT
 *     This module is part of the IC-ASYNC AppWizard generated code
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999, Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/

#ifndef __PROCTHRED_H__
#define __PROCTHRED_H__

#include <ifc.h>

/////////////////////////////////////////////////////////////////////////////
// CProcessThread
class  CSeqsnapView;
class CProcessThread
{

// Construction
public:
	CProcessThread(CSeqsnapView *thread_view);
	virtual ~CProcessThread();
	friend DWORD WINAPI ProcessThread(LPVOID pOwner);

private:
	BOOLEAN m_bShutdown;
	HANDLE  m_hThread;
	CSeqsnapView *m_pView;
};


#endif // _PROCTHRED_H_
