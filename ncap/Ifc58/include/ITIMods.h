/*********************************************************************
 *
 * MODULE
 *    ITIMods.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/ITIMods.h $
 *     $Revision: 1.1 $
 *     $Modtime: 11/21/03 9:29a $
 *
 * ABSTRACT
 *    IFC interface of the CITIModules class.
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-2000, Imaging Technology, Inc., All rights reserved.
 ***********************************************************************/

#if !defined(AFX_ITIMODS_H__21615572_C7E9_11D1_AE89_00A0C959E757__INCLUDED_)
#define AFX_ITIMODS_H__21615572_C7E9_11D1_AE89_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Iobject.h>
#include <Module.h>

#define MAX_NUM_CHILD_MODS 3
#define MAX_NUM_PARENT_MODULES 16


typedef struct  {
	char			name[MAX_MODNAME_LEN];
	DWORD			revision;
} ITI_CHILD_MOD;

typedef struct _ITI_PARENT_MOD ITI_PARENT_MOD;
typedef ITI_PARENT_MOD *LPITI_PARENT_MOD;
struct _ITI_PARENT_MOD {
	char			name[MAX_MODNAME_LEN];
	char			fullName[MAX_MODNAME_LEN];
	DWORD			seqNum;
	DWORD			revision;
	BOOL			PhysModPresent;
	ITI_CHILD_MOD   child[MAX_NUM_CHILD_MODS];
	ITI_PARENT_MOD	*next;
};

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CITIMods : public CIobject
{
public:
	LPITI_PARENT_MOD GetNext();
	LPITI_PARENT_MOD GetFirst();
	CITIMods();
	CITIMods(char *cfgFile);

	virtual ~CITIMods();
private:
	LPITI_PARENT_MOD m_first;
	LPITI_PARENT_MOD m_next;
};
#endif

#endif // !defined(AFX_ITIMODS_H__21615572_C7E9_11D1_AE89_00A0C959E757__INCLUDED_)
