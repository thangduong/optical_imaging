/******************************************************************************
 *
 * MODULE
 *      procthrd.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/examples/LineScan/seqsnap/PROCTHRD.H $Revision: 1.1 $
 *     $Modtime: 7/05/00 11:29a $
 *
 * ABSTRACT
 *     This module is part of the IC-ASYNC AppWizard generated code
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2000, Imaging Technology, Inc.  All rights reserved.
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
	CProcessThread(CSeqsnapView *thread_view,BOOL saveTifFile=FALSE);
	DWORD ProcessThreadMember();

	virtual ~CProcessThread();
	friend DWORD WINAPI ProcessThread(LPVOID pOwner);

	DWORD m_minBlobArea;
	DWORD m_maxBlobArea;
	DWORD m_avgBlobArea;
	DWORD m_numDetectedBlobs;
	BOOL m_grabToFeatureRam;

private:
	BOOLEAN m_bShutdown;
	HANDLE  m_hThread;
	CSeqsnapView *m_pView;
	BOOL m_saveTifFile;

};


#endif // _PROCTHRED_H_
