/******************************************************************************
 *
 * MODULE   
 *		ParntMod.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ParntMod.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:28a $
 *
 * ABSTRACT  
 *		IFC interface of the CParntMod class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PARNTMOD_H__962D5A83_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_PARNTMOD_H__962D5A83_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
typedef CParentMod * PCParentMod;

#include <Module.h>
#include <CfgFile.h>
#include <IfcOs.h>
#include <IfcBus.h>
#include <ChildMod.h>

#define MAX_NUM_CHILDMODS 3

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CParentMod : public CModule  
{
public:
	void Cleanup();
	virtual BOOL ChildRegPostFix(CChildMod *child);
	virtual BOOL GetChildResource(DWORD dmodSlot,BUSRESOURCE *resource);
	virtual BOOL DetectDmod(WORD dmodSlot,IFC_BOARD_KIND *dmodKind,DWORD *dmodSubkind);
	virtual BOOL RegTableSetup();
	virtual BOOL BaseAddrInit();
	virtual BOOL BaseAddrUnInit();
	virtual void ModDataInit();
	virtual BOOL SetConfig(char * cfgFile);
	virtual BOOL Create(char *modname,DWORD seqnum);
	virtual BOOL Create(DWORD seqnum, char *cfgFile){return 0;};
	virtual PCIFCBus CreateChildBus(CChildMod *child); 
	void WriteDwordBuf(DWORD addressSpace,DWORD offset,DWORD *buf,DWORD dwordCount,DWORD inc=1);
	void WriteWordBuf(DWORD addressSpace,DWORD offset,WORD *buf,DWORD wordCount,DWORD inc=1);
	void ReadDwordBuf(DWORD addressSpace,DWORD offset,DWORD *buf,DWORD dwordCount,DWORD inc=1);
	void ReadWordBuf(DWORD addressSpace,DWORD offset,WORD *buf,DWORD wordCount,DWORD inc=1);
	CParentMod();
	virtual ~CParentMod();
	CCfgFile *m_cfgFile;
	CModFactory *m_modFactory;
	DWORD m_NumBaseAddr;
	BUSRESOURCE m_BusResources[MAX_BUS_RESOURCES];
	pCChildMod m_dMod[MAX_NUM_CHILDMODS];
protected:
	IFC_DECLARE_DYNCREATE(CParentMod)
};
#endif

#endif // !defined(AFX_PARNTMOD_H__962D5A83_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
