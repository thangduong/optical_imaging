/*********************************************************************
 *
 * MODULE
 *    ModFacty.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/ModFacty.h $
 *     $Revision: 1.1 $
 *     $Modtime: 11/21/03 9:37a $
 *
 * ABSTRACT
 *    IFC interface of the CModFactory class.
 *
 * TECHNICAL NOTES
 *     These routines serve as the lower level bus access read/write
 *     handlers for the Host-to-150/40 PCI data transfer operations.
 *
 *
 * Copyright (c) 1998-2000, Imaging Technology, Inc., All rights reserved.
 ***********************************************************************/

#if !defined(AFX_MODFACTY_H__5D7D6042_9CA4_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_MODFACTY_H__5D7D6042_9CA4_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <Iobject.h>
#include <ifcclass.h>
#include <ChildMod.h>
#include <Module.h>
#include <ParntMod.h>
#include <ICapMod.h>

typedef struct _IFC_MOD_DESC IFC_MOD_DESC;
typedef IFC_MOD_DESC *PIFC_MOD_DESC;

typedef DWORD HICAPENUM; 

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CModFactory : public CIobject  
{
public:
	static void Close(void);
	static DWORD ModSubKind(PIFC_MOD_DESC desc);
	static BOOL AddModClass(CIRuntimeClass *modObject,char *modName,IFC_BOARD_KIND modKind, DWORD modSubkind,char *modFullName=NULL);
	static PIFC_MOD_DESC FindFirstClass(IFC_BOARD_KIND modKind);
	static PIFC_MOD_DESC FindNextClass(PIFC_MOD_DESC node,IFC_BOARD_KIND modKind);
	static char *GetFullName(char *shortName,char *fullName);
	virtual pCChildMod CreateChildMod(CParentMod *parent, WORD dmodSlot, IFC_BOARD_KIND dmodKind, DWORD dmodSubkind);
	virtual pCChildMod CreateChildMod(CParentMod *parent, WORD dmodSlot, char *modName);
	CModFactory();
	virtual ~CModFactory();

	static CIRuntimeClass * FindClass(IFC_BOARD_KIND modKind, DWORD modSubkind);
	static CIRuntimeClass * FindClass(char *modName);
protected:

};


PCICapMod IFCCALL IfxCreateCaptureModule(DWORD seqnum=0, char *cfgFile=NULL);
PCParentMod IFCCALL IfxCreateParentModule(IFC_BOARD_KIND modKind, DWORD modSubkind, DWORD seqnum, char *cfgFile=NULL, BOOL inspectOnly=FALSE);
extern "C" PCICapMod IFCCALL IfxCreateCaptureModule(char *modName,DWORD seqnum=0, char *cfgFile=NULL);
extern "C" PCParentMod IFCCALL IfxCreateParentModule(char *modName, DWORD seqnum, char *cfgFile=NULL, BOOL inspectOnly=FALSE);

// DaughterModNames are listed in order of their slots and seperated by commas, e.g., "AM-V,CM-PA"
extern "C" PCParentMod IFCCALL IfxCreateVirtualParentModule(char *modName, DWORD seqnum=0, char *cfgFile=NULL, char *DaughterModNames=NULL);
PCParentMod IFCCALL IfxCreateVirtualParentModule(IFC_BOARD_KIND modKind, DWORD modSubkind, DWORD seqnum, char *cfgFile=NULL, char *DaughterModNames=NULL);

extern "C" HICAPENUM IFCCALL IfxGetFirstCaptureModName(char *ModName);
extern "C" HICAPENUM IFCCALL IfxGetNextCaptureModName(HICAPENUM node,char *ModName);



#else
PCICapMod IFCCALL IfxCreateCaptureModule(char *modName,DWORD seqnum, char *cfgFile);
#endif




// Example
//	IFC_ADD_FACTORY_MODULE(CAmV,AMV_MODNAME,IFC_AM_DBOARD,AMV_BRD_ID)

#define IFC_ADD_FACTORY_MODULE(modClass,modName,modType,modSubType) \
	int _var_##modClass = CModFactory::AddModClass(IFC_RUNTIME_CLASS(modClass),(modName),(modType),(modSubType));


#define IFC_ADD_FACTORY_MODULE_EX(modClass,modName,modType,modSubType,modFullName) \
	int _var_##modClass = CModFactory::AddModClass(IFC_RUNTIME_CLASS(modClass),(modName),(modType),(modSubType),(modFullName) );


#endif // !defined(AFX_MODFACTY_H__5D7D6042_9CA4_11D1_AE74_00A0C959E757__INCLUDED_)
