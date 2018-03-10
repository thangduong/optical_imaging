/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/examples/PC2-CamLink/Seqsnap/PROCTHRD.H $Revision: 1.1 $
 *     $Modtime: 6/16/03 2:21p $
 *
 * ABSTRACT
 *     This module is part of the IC-ASYNC AppWizard generated code
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999, Coreco Imaging, Inc.  All rights reserved.
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
