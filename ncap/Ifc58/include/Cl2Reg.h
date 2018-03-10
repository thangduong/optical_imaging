/******************************************************************************
 *
 * MODULE
 *    CL2reg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/Cl2Reg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/23/04 6:13p $
 *
 * ABSTRACT
 *    IFC PCPC2Link Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2003-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _CL2_REG
#define _CL2_REG


#define CL2_GC_REG_BASE 0x1000000


enum {                    /* PCI configuration space registers */

    CL2_VENDOR_ID_32,
	CL2_DEVICE_ID_32,
	CL2_PCICMDSTAT_32,
	CL2_PCICMD_32,
	CL2_IOEN_32,
	CL2_MEMEN_32,
	CL2_BMEN_32,
	CL2_PAREN_32,
	CL2_SEREN_32,
	CL2_FBB_32,
	CL2_PCISTAT_32,
	CL2_DTPAR_32,
	CL2_STABT_32,
	CL2_RTABT_32,
	CL2_RMABT_32,
	CL2_SSERR_32,
	CL2_DPARE_32,
	CL2_REVID_32,
	CL2_MEMSZ_32,
	CL2_CLASSCODE_32,
	CL2_CALN_32,
	CL2_LAT_32,
	CL2_HDR_32,
	CL2_BIST_32,
	CL2_BADR0_32,
	CL2_BADR1_32,
	CL2_BADR2_32,
	CL2_BADR3_32,
	CL2_BADR4_32,
	CL2_BADR5_32,
	CL2_XROM_32,
	CL2_INTLN_32,
	CL2_INTPIN_32,
	CL2_MINGNT_32,
	CL2_MAXLAT_32,

	CL2_MAX_REG1
};





#endif

