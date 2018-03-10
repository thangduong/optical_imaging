/******************************************************************************
 *
 * MODULE
 *    pv2reg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/Pv2Reg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/02/04 1:31p $
 *
 * ABSTRACT
 *    IFC PCVision2 Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 2002-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _P2V_REG
#define _P2V_REG


#define P2V_FE_REG_BASE			0x0000
#define P2V_THS8083_REG_BASE	0x0100
#define P2V_DE_REG_BASE			0x1000

#define P2V_CFG_REG_BASE 0x10000000




enum {                    /* PCI configuration space registers */

    P2V_VENDOR_ID_32=P2V_CFG_REG_BASE,
	P2V_DEVICE_ID_32,
	P2V_PCICMDSTAT_32,
	P2V_PCICMD_32,
	P2V_IOEN_32,
	P2V_MEMEN_32,
	P2V_BMEN_32,
	P2V_PAREN_32,
	P2V_SEREN_32,
	P2V_FBB_32,
	P2V_PCISTAT_32,
	P2V_DTPAR_32,
	P2V_STABT_32,
	P2V_RTABT_32,
	P2V_RMABT_32,
	P2V_SSERR_32,
	P2V_DPARE_32,
	P2V_REVID_32,
	P2V_MEMSZ_32,
	P2V_CLASSCODE_32,
	P2V_CALN_32,
	P2V_LAT_32,
	P2V_HDR_32,
	P2V_BIST_32,
	P2V_BADR0_32,
	P2V_BADR1_32,
	P2V_BADR2_32,
	P2V_BADR3_32,
	P2V_BADR4_32,
	P2V_BADR5_32,
	P2V_XROM_32,
	P2V_INTLN_32,
	P2V_INTPIN_32,
	P2V_MINGNT_32,
	P2V_MAXLAT_32,


	P2V_MAX_REG1
};



typedef enum {

	P2V_FE_REG_STROBE_TRIGGER_CFG      =0x0e,
	P2V_FE_REG_AUTOSWITCH_CTRL_CFG1    =0x14,
	P2V_FE_REG_FRAME_TRIG_HIGH         =0x39,
	P2V_FE_GENERAL_PURPOSE_OUTPORT     =0x5b,
	P2V_FE_GENERAL_PURPOSE_OUTPORT_CFG =0x5c,
	P2V_FE_GENERAL_PURPOSE_INPORT      =0x5d,
	P2V_FE_GENERAL_PURPOSE_INPORT_CFG  =0x5e,
	P2V_FE_REG_MISC_CFG                =0x69,
	P2V_FE_REG_VS_BLOCK                =0x75,
	P2V_FE_REG_FRAME_RESET_CONTROL	   =0x78,
	P2V_FE_REG_FR_BLOCK                =0x94,
	P2V_FE_REG_HS_BLOCK                =0x97

} P2V_FE_REG_TYPE;

typedef enum {
	P2V_THS8083_PHASE_SEL 	=P2V_THS8083_REG_BASE + 0x09,
	P2V_THS8083_PLL_GAIN	=P2V_THS8083_REG_BASE + 0x0A,
	P2V_THS8083_CLP_CTRL	=P2V_THS8083_REG_BASE + 0x20
} P2V_THS8083_REG_TYPE;


typedef enum {
	P2V_DE_REG_REG1=P2V_DE_REG_BASE

} P2V_DE_REG_TYPE;


#endif

