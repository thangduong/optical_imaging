/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/PROCTHRD.H $
 *    $Revision: 1.1 $
 *    $Modtime: 5/24/00 12:08p $
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
