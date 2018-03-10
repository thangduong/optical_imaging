/******************************************************************************
 *
 * MODULE   
 *		IFCBus.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IFCBus.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:26a $
 *
 * ABSTRACT  
 *		IFC interface of the CIFCBus class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IFCBUS_H__E554E633_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
#define AFX_IFCBUS_H__E554E633_93FD_11D1_AE72_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Iobject.h>
#include <ifcstd.h>

#include <ifcclass.h>
typedef CIFCBus *PCIFCBus;

#define MAX_BUS_RESOURCES 10

#define PCI_BASE_ADDRESS0	0x10
#define PCI_BASE_ADDRESS1	0x14
#define PCI_BASE_ADDRESS2	0x18
#define PCI_BASE_ADDRESS3	0x1c
#define PCI_BASE_ADDRESS4	0x20
#define PCI_BASE_ADDRESS5	0x24

typedef enum {
	IFC_MEM_SPACE,
	IFC_IO_SPACE,
} IFC_SPACE;

typedef enum {
	IFC_RBYTE,
	IFC_WBYTE,
	IFC_RMSBYTE,
	IFC_WMSBYTE,

	IFC_RWORD,
	IFC_WWORD,
	IFC_RMSWORD,
	IFC_WMSWORD,

	IFC_RDWORD,
	IFC_WDWORD,
	IFC_RMSDWORD,
	IFC_WMSDWORD,

	IFC_RBBUF,
	IFC_WBBUF,
	IFC_CBBUF,

	IFC_RWBUF,
	IFC_WWBUF,
	IFC_CWBUF,

	IFC_RDWBUF,
	IFC_WDWBUF,
	IFC_CDWBUF,

	IFC_REGADR,

	IFC_NUM_IFCUNCS
} LLFUNCS_TYPE;

typedef struct {
	DWORD		PhysicalAddr;
	DWORD		LogicalAddr;
	DWORD		Length;
	IFC_SPACE	Space;
} BUSRESOURCE;	


typedef void (*PFV)();

typedef void (*RWBUFH) (DWORD adr,DWORD count,WORD inc,pWORD buf);
typedef void (*WWBUFH) (DWORD adr,DWORD count,WORD inc,pWORD buf);
typedef void (*CWBUFH) (DWORD adr,DWORD count,WORD inc,WORD val);
typedef void (*RDWBUFH) (DWORD adr,DWORD count,WORD inc,pDWORD buf);
typedef void (*WDWBUFH) (DWORD adr,DWORD count,WORD inc,pDWORD buf);
typedef void (*CDWBUFH) (DWORD adr,DWORD count,WORD inc,DWORD val);


#include <IFCOS.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CIFCBus : public CIobject  
{
public:
	PFV GetLLFuncPtr(LLFUNCS_TYPE funcID);
	BOOL ReadConfigByte(OSHANDLE h_driver, WORD reg_offset, BYTE *p_byte);
	BOOL ReadConfigWord(OSHANDLE h_driver, WORD reg_offset, WORD *p_word);
	BOOL ReadConfigDWord(OSHANDLE h_driver, WORD reg_offset, DWORD *p_dword);
	BOOL WriteConfigDWord(OSHANDLE h_driver, WORD reg_offset, DWORD val);
	BOOL WaitBusMutex(DWORD milliseconds=1000);
	void ReleaseBusMutex(void);

	CIFCBus(DWORD busNum=0);
	virtual ~CIFCBus();

private:
	DWORD m_busNumber;
	OSHANDLE	m_BusMutex;	// Bus access mutex
	CIFCOS *m_os;

};
#endif

#endif // !defined(AFX_IFCBUS_H__E554E633_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
