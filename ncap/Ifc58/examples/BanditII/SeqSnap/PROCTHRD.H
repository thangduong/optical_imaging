/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/BanditII/SeqSnap/PROCTHRD.H $
 *    $Revision: 1.1 $
 *    $Modtime: 7/02/01 2:54p $
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
