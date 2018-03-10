/*********************************************************************
 *
 * MODULE
 *    llfunc.h
 *
 * REVISION INFORMATION
 *     $Logfile: /ifc/include/llfunc.h $
 *     $Revision: 1.1 $
 *     $Modtime: 2/25/99 10:37a $
 *
 * ABSTRACT
 *    IFC 150/40 AT-PCI IO functions.
 *
 * TECHNICAL NOTES
 *     These routines serve as the lower level bus access read/write
 *     handlers for the Host-to-150/40 PCI data transfer operations.
 *
 *
 * Copyright (c) 1998, Imaging Technology, Inc., All rights reserved.
 ***********************************************************************/

#ifndef _INC_LLFUNCS_
#define _INC_LLFUNCS_

#include <Module.h>

DWORD pcicfg_rmsdword(pCModule mod, short index);
void  pcicfg_wmsdword(pCModule mod, short index, DWORD value);

BYTE  pci_mem_rbyte(pCModule mod, short indx);
void  pci_mem_wbyte(pCModule mod, short indx, BYTE val);
BYTE  pci_mem_rmsbyte(pCModule mod, short indx);
void  pci_mem_wmsbyte(pCModule mod, short indx, BYTE val);

WORD  pci_mem_rword(pCModule mod, short indx);
void  pci_mem_wword(pCModule mod, short indx, WORD val);
WORD  pci_mem_rmsword(pCModule mod, short indx);
void  pci_mem_wmsword(pCModule mod, short indx, WORD val);

DWORD pci_mem_rdword(pCModule mod, short indx);
void  pci_mem_wdword(pCModule mod, short indx, DWORD val);
DWORD pci_mem_rmsdword(pCModule mod, short indx);
void  pci_mem_wmsdword(pCModule mod, short indx, DWORD val);

void pci_rbbuf(DWORD adr,DWORD count,WORD inc,pBYTE buf);
void pci_wbbuf(DWORD adr,DWORD count,WORD inc,pBYTE buf);
void pci_cbbuf(DWORD adr,DWORD count,WORD inc,BYTE val);

void pci_rwbuf(DWORD adr,DWORD count,WORD inc,pWORD buf);
void pci_wwbuf(DWORD adr,DWORD count,WORD inc,pWORD buf);
void pci_cwbuf(DWORD adr,DWORD count,WORD inc,WORD val);

void pci_rdwbuf(DWORD adr,DWORD count,WORD inc, pDWORD buf);
void pci_wdwbuf(DWORD adr,DWORD count,WORD inc,pDWORD buf);
void pci_cdwbuf(DWORD adr,DWORD count,WORD inc,DWORD val);

pWORD  pci_adr(pCModule mod, short index);


#endif
