/******************************************************************************
 *
 * MODULE   
 *		ChildMod.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ChildMod.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:28a $
 *
 * ABSTRACT  
 *		IFC interface of the CChildMod class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CHILDMOD_H__18E849E3_9655_11D1_AE73_00A0C959E757__INCLUDED_)
#define AFX_CHILDMOD_H__18E849E3_9655_11D1_AE73_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>

typedef CChildMod *pCChildMod;
#include <Module.h>
#include <ParntMod.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CChildMod : public CModule  
{
public:
	virtual BOOL Create(CParentMod *parent,DWORD slotNum);
	virtual BOOL RegTableSetup();
	virtual BOOL BaseAddrInit();
	virtual void ModDataInit();
	CChildMod();
	virtual ~CChildMod();
	BUSRESOURCE m_BusResource;

protected:
	IFC_DECLARE_DYNCREATE(CChildMod)
};
#endif

#endif // !defined(AFX_CHILDMOD_H__18E849E3_9655_11D1_AE73_00A0C959E757__INCLUDED_)
