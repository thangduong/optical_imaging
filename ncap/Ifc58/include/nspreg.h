/******************************************************************************
 *
 * MODULE
 *    nspreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/nspreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/17/04 8:23a $
 *
 * ABSTRACT
 *    IFC CNetSightII Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2002-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _NSP_REG
#define _NSP_REG


#define NSP_FE_REG_BASE			0x0000
#define NSP_THS8083_REG_BASE	0x0100
#define NSP_DE_REG_BASE			0x1000

#define NSP_CFG_REG_BASE 0x10000000




enum {                    /* PCI configuration space registers */

    NSP_VENDOR_ID_32=NSP_CFG_REG_BASE,
	NSP_DEVICE_ID_32,
	NSP_PCICMDSTAT_32,
	NSP_PCICMD_32,
	NSP_IOEN_32,
	NSP_MEMEN_32,
	NSP_BMEN_32,
	NSP_PAREN_32,
	NSP_SEREN_32,
	NSP_FBB_32,
	NSP_PCISTAT_32,
	NSP_DTPAR_32,
	NSP_STABT_32,
	NSP_RTABT_32,
	NSP_RMABT_32,
	NSP_SSERR_32,
	NSP_DPARE_32,
	NSP_REVID_32,
	NSP_MEMSZ_32,
	NSP_CLASSCODE_32,
	NSP_CALN_32,
	NSP_LAT_32,
	NSP_HDR_32,
	NSP_BIST_32,
	NSP_BADR0_32,
	NSP_BADR1_32,
	NSP_BADR2_32,
	NSP_BADR3_32,
	NSP_BADR4_32,
	NSP_BADR5_32,
	NSP_XROM_32,
	NSP_INTLN_32,
	NSP_INTPIN_32,
	NSP_MINGNT_32,
	NSP_MAXLAT_32,


	NSP_MAX_REG1
};



typedef enum {

	NSP_FE_REG_STROBE_TRIGGER_CFG      =0x0e,
	NSP_FE_REG_AUTOSWITCH_CTRL_CFG1    =0x14,
	NSP_FE_GENERAL_PURPOSE_OUTPORT     =0x5b,
	NSP_FE_GENERAL_PURPOSE_OUTPORT_CFG =0x5c,
	NSP_FE_GENERAL_PURPOSE_INPORT      =0x5d,
	NSP_FE_GENERAL_PURPOSE_INPORT_CFG  =0x5e,
	NSP_FE_REG_MISC_CFG                =0x69,
	NSP_FE_REG_VS_BLOCK                =0x75,
	NSP_FE_REG_FRAME_RESET_CONTROL	   =0x78,
	NSP_FE_REG_FR_BLOCK                =0x94,
	NSP_FE_REG_HS_BLOCK                =0x97

} NSP_FE_REG_TYPE;

typedef enum {
	NSP_THS8083_PHASE_SEL 	=NSP_THS8083_REG_BASE + 0x09,
	NSP_THS8083_PLL_GAIN	=NSP_THS8083_REG_BASE + 0x0A,
	NSP_THS8083_CLP_CTRL	=NSP_THS8083_REG_BASE + 0x20
} NSP_THS8083_REG_TYPE;


typedef enum {
	NSP_DE_REG_REG1=NSP_DE_REG_BASE

} NSP_DE_REG_TYPE;


#endif

