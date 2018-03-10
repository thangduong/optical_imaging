/******************************************************************************
 *
 * MODULE
 *    bdtreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/bdtreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 4/13/01 11:00a $
 *
 * ABSTRACT
 *    IFC BDTGB Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _BDT_REG
#define _BDT_REG


typedef enum {
	BDT_OCT_BYTE_SWAP,
	BDT_OCT_WORD_SWAP
} BDT_OCT_SWAP_TYPE;


enum {                    /* PCI configuration space registers */

    BDT_VENDOR_ID_32,
    BDT_DEVICE_ID_32,




	BDT_MAX_REG1
};





#endif

