/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/PCVisionplus/SeqSnap/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/28/00 2:36p $
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

#if !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
#define AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "TrigGrabDlg.h"

#include <Vixni.h>

class CVixnEOF : public CVixn  
{
public:

	int			m_iModId;
	int			m_iSoftTrig;
	CVixnEle	m_intrCount;
	CVixnEle	m_deltaTime;
	CVixnEle	m_modId;
	CVixnEle	m_SoftTrig;

	virtual BOOL VixnMain();

	CVixnEOF(PCParentMod pMod);
	virtual ~CVixnEOF();
};

class CTrgThrd  
{
public:
	// CTrgThrd(CTrgSheet *parent);
	CTrgThrd(CTrigGrabDlg *parent);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	CTrigGrabDlg *m_parent;
	BOOLEAN m_shutdown;
	BOOLEAN m_bDisplay;
	BOOLEAN m_bNewFrame;
	HANDLE m_hthread;
	HANDLE m_hDisplayThread;
	CImgConn *m_imgConn;
};

#endif // !defined(AFX_TRGTHRD_H__709E2C12_34DB_11D1_AE32_00A0C959E757__INCLUDED_)
