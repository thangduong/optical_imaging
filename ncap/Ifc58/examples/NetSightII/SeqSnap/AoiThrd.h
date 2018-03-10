/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/NetSightII/seqsnap/AoiThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 11/10/03 11:44a $
 *
 * ABSTRACT
 *    NetSight II Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2003 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_AOITHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_AOITHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAioThrd;
#include "seqsnapV.h"


class CAioThrd  
{
public:
	CAioThrd(CSeqsnapView *parent);
	virtual ~CAioThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CSeqsnapView *m_parent;
	BOOLEAN m_shutdown;
	BOOLEAN m_bNewFrame;
	HANDLE m_hthread;
	CImgConn *m_imgConn;
};

#endif // !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
