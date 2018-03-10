/******************************************************************************
 *
 * MODULE   
 *		Module.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Module.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/29/04 4:48p $
 *
 * ABSTRACT  
 *		IFC interface of the CModule class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_MODULE_H__CCAF3343_709F_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_MODULE_H__CCAF3343_709F_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>

typedef CModule *pCModule;

/* board types */
typedef enum {
	IFC_CAP_MBOARD,		// Image Capture motherboard, e.g., IC-PCI,PCVision
	IFC_MNG_MBOARD,		// Image Manager motherboard, e.g., IM-PCI
	IFC_CMC_MBOARD,		// Computational module motherboard, e.g., CMC-PCI
	IFC_AM_DBOARD,
	IFC_CM_DBOARD,
	IFC_DM_DBOARD,

	IFC_NUM_BOARD_KINDS
} IFC_BOARD_KIND;

typedef enum {
    IFC_BRD_NULL,
    IFC_BRD_PA,
    IFC_BRD_IMS,
    IFC_BRD_IMA,
    IFC_BRD_IML,
    IFC_BRD_ICVL,
    IFC_BRD_ICP,
    IFC_BRD_IMP,
    IFC_BRD_CMP,
    IFC_BRD_IMV,
    IFC_BRD_ICA,
    IFC_BRD_PCD,
	IFC_NUM_BRD_TYPES
 } IFC_BRD_ID_TYPE;


typedef enum {
    IFC_HW_ART_REV,
    IFC_HW_ECO,
    IFC_HW_SERIAL_NUM,
    IFC_HW_DISP_KIND,
    IFC_BRD_KIND,   /* value of type IFC_BRD_ID_TYPE */
    IFC_MAX_HW_PARAM
} IFC_HW_PARAMS;


#include <IFCError.h>
#include <iobject.h>
#include <IfcOs.h>
#include <register.h>
#include <config.h>
#include <IntrCbak.h>
#include "Intrupt.h"


#define IFC_MAX_MOD_CB_OBJS 40

#define MAX_MODNAME_LEN 16
#define MAX_MODULE_INTERRUPTS 24

// Module Create flags
#define MOPT_SINGLE_PROC_USE 0x0001

#define BOARD_MUTEX_WAITTIME 10000
#define IFC_WAIT_FOREVER 0xffffffff

#define IFC_MAX_MODULE_SEQNUM 8

typedef enum {
	IFC_CFG_CURRENT_CAMERA,
	IFC_CFG_ALL_CAMERAS
} IFC_CFG_CAMERA_SPECIFIER;

// Process Config file flags
#define IFC_PCFG_ANY_SEQNUM 0x00000001
#define IFC_PCFG_CAM_MODEL  0x00000002


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CModule : public CIobject 
{
public:
	void DeleteIntrCallback(PCIntrCallback callBackObj);
	PCIntrCallback CreateIntrCallback(IFC_INTREVENT iEvent, pIntrCallBackFunc func, LPVOID pParam);
	virtual DWORD Revision();
	char * ModName();
	void Cleanup();
	BOOL GetTimeout();
	void SetTimeout(DWORD numMillisecs);
	LPTSTR UniqueName(char *buf,char *format, ...);
	void SetInspectMode();
	void SetVirtualMode();
	BOOL IsVirtualModule();

	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual BOOL ProcessCamerasInConfigFile(const char *szCfgFileName = NULL){return 0;};
	virtual BOOL ReadUserConfigFile(const char *szCfgFileName){return 0;};
	virtual BOOL WriteConfigFile(const char *szCfgFileName, BOOL bCamFlag = IFC_CFG_CURRENT_CAMERA, BOOL CreateCamDefs=TRUE){return 0;};
	virtual BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName){return 0;};
	virtual void DisplayReg(BOOL verbose=FALSE,REGID reg=IFC_ALL_REGISTERS);

	virtual BOOL ModInit();
	virtual pSTRING RegName(REGID reg);
	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);
	virtual DWORD RegTableNumEntries(); // provided by leaf class returns num entries of static reg table
	virtual BOOL RegTableSetup();
	virtual pIFC_MODREG RegTableAddr(); // provided by leaf class returns address of static reg table
	virtual BOOL BaseAddrInit();
	virtual BOOL BaseAddrUnInit() { return TRUE;};
	virtual void ModDataInit(); // provided by leaf class, initializes module peculiar data
	virtual BOOL Create(char *modname,DWORD seqnum,pCModule parent=NULL,DWORD modFlags=0);
	void PutLastError(DWORD error,const char *errstr,...);
	DWORD GetLastError(void);
	void PutLastError(DWORD error);
	virtual BOOL LoadFpga(char *szFpgaFileName);
	virtual BOOL FPGAByteWrite(BYTE val);
	static FILE *EnvFopen(pSTRING name, pSTRING mode);
	static BOOL EnvFileName(pSTRING name, pSTRING fullPathName);

	virtual BOOL IfxGetBoardParam(IFC_HW_PARAMS eParamId,DWORD *param);
	virtual BOOL InspectModePostProcess(DWORD dwFlags=0) { return TRUE; };
	virtual BOOL InterruptEnable(IFC_INTREVENT iEvent, BOOL enable) { return TRUE; };
	virtual BOOL AddInterruptObject( CInterrupt *intrObject);
	virtual BOOL DeleteInterruptObject( CInterrupt *intrObject);
	virtual BOOL SetInterruptEvents(IFC_INTREVENT iEvent);

	BOOL FpgaFileExist(char *szFpgaFileName);

	CModule();
	virtual ~CModule();
	CIFCOS		*m_os;
	CIFCBus		*m_bus;
	CIFCError	*m_error;
	OSHANDLE	m_hdriver;
	pCModule	m_parent;
	CRegister	*m_regs;
	char		m_modName[MAX_MODNAME_LEN];
	DWORD		m_seqNum;
	CConfig		*m_cfg;
	BOOL		m_InspectOnly;

	// m_moduleMutex is used if module type is such that only one-object of 
	// CModule type can exist for it at a time 
	OS_sem_t	m_moduleMutex;
	BOOL		m_gotModuleMutex;

	OSHANDLE		m_BoardMutex;	// Board access mutex, used for all board-peculiar atomizing

	DWORD		m_revision;
	char		m_VirtualDaughterModNames[30];


protected:
	IFC_DECLARE_DYNCREATE(CModule)

	BOOL		m_IsVirtual;

	virtual DWORD ReadPPROM(DWORD dwIndex,DWORD accessKey) { return 0;};
	virtual void WritePPROM(DWORD dwIndex,DWORD dwVal,DWORD accessKey){};

	OSHANDLE SetRegAccessMutex(OSHANDLE mutex);

	CINTERRUPT_LIST_ITEM *m_intrObjectRoot;

private:
	DWORD		m_timeoutTime;
	OSHANDLE	m_regAccessMutex;
	PCIntrCallback m_intrCallbackObjs[IFC_MAX_MOD_CB_OBJS];
};
#endif


#if defined( __cplusplus )
extern "C" {
#endif


LPVOID IFCCALL IfxCModuleRuntimeClass();


#ifdef __cplusplus
}
#endif





#endif // !defined(AFX_MODULE_H__CCAF3343_709F_11D1_A574_00A0C959E757__INCLUDED_)
