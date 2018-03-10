/******************************************************************************
 *
 * MODULE
 *    TrgThrd.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/ImgProc/TrgThrd.h $
 *    $Revision: 1.1 $
 *    $Modtime: 10/25/99 1:32p $
 *
 * ABSTRACT
 *    IFC Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_TRGTHRD_H__C2055DCB_88B3_11D3_A228_005004051D9B__INCLUDED_)
#define AFX_TRGTHRD_H__C2055DCB_88B3_11D3_A228_005004051D9B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTrgThrd;
#include "ImgProcView.h"

class CTrgThrd  
{
public:
	CTrgThrd(CImgProcView *parent, int ID);
	virtual ~CTrgThrd();

	friend DWORD WINAPI TriggerThread(LPVOID owner);

	int m_ID;
	CImgProcView *m_parent;
	BOOLEAN m_shutdown;
	HANDLE m_hthread;
};

#endif // !defined(AFX_TRGTHRD_H__C2055DCB_88B3_11D3_A228_005004051D9B__INCLUDED_)
