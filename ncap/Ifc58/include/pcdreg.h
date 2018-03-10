/******************************************************************************
 *
 * MODULE
 *    pcdreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/pcdreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 1/21/00 9:58a $
 *
 * ABSTRACT
 *    IFC PCDig Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _PCD_REG
#define _PCD_REG


typedef enum {
	PCD_OCT_BYTE_SWAP,
	PCD_OCT_WORD_SWAP
} PCD_OCT_SWAP_TYPE;


enum {                    /* PCI configuration space registers */

    PCD_VENDOR_ID_32,
    PCD_DEVICE_ID_32,
    PCD_PCICMDSTAT_32,
    PCD_PCICMD_32,
    PCD_IOEN_32,
    PCD_MEMEN_32,
    PCD_PCIBMEN_32,
    PCD_PAREN_32,
    PCD_SEREN_32,
    PCD_FBB_32,
    PCD_PCISTAT_32,
    PCD_DTPAR_32,
    PCD_STABT_32,
    PCD_RTABT_32,
    PCD_RMABT_32,
    PCD_SSERR_32,
    PCD_DPARE_32,
    PCD_REVID_32,
    PCD_MEMSZ_32,
    PCD_CLASSCODE_32,
    PCD_CALN_32,
    PCD_LAT_32,
    PCD_HDR_32,
    PCD_BIST_32,
    PCD_BADR0_32,
    PCD_BADR1_32,
    PCD_BADR2_32,
    PCD_BADR3_32,
    PCD_BADR4_32,
    PCD_BADR5_32,
    PCD_XROM_32,
    PCD_INTLN_32,
    PCD_INTPIN_32,
    PCD_MINGNT_32,
    PCD_MAXLAT_32,
    PCD_MAX_CFGREG
};

enum {
    PCD_MBOX1_32 = PCD_MAX_CFGREG,   /* PCI Interface Control Register Set  */
    PCD_MB_FXSZ_32,
    PCD_MB_ILACE_32,
    PCD_MB_HSHK_32,
    PCD_MB_FYSZ_32,
    PCD_MB_PIX_32,
    PCD_MB0X2_32,
    PCD_MB_AOIXST_32,
    PCD_MB_AOIYST_32,
    PCD_MB0X3_32,
    PCD_MB_AOIXSZ_32,
    PCD_MB_AOIYSZ_32,
    PCD_MB_FYSZHI_32,
    PCD_MB_STFLD_32,
    PCD_MB_BMSEMA_32,
    PCD_MB0X4_32,
    PCD_MB_IMGADR_32,
    PCD_MB_BMINITFLG_32,
    PCD_MB_CONT_32,
    PCD_BMDST_32,
    PCD_BMXC_32,
    PCD_INTCTL_32,
    PCD_INTEN_32,
    PCD_BINTEN_32,
    PCD_INTST_32,
    PCD_BINTST_32,
    PCD_MAINT_32,
    PCD_TAINT_32,
    PCD_ENDIAN_32,
    PCD_BMCTL_32,
    PCD_FIFOFL_32,
    PCD_FIFO4P_32,
    PCD_FIFOEM_32,
    PCD_BMDONE_32,
    PCD_BMREQ_32,
    PCD_NVAD_32,
    PCD_RST_32,
    PCD_FIFOCLR_32,
    PCD_NVCTL_32,
    PCD_MAXREGS1
};

enum {
    PCD_BMCON_32 = PCD_MAXREGS1,
    PCD_BMENB_32,
    PCD_BMSTEP_32,
    PCD_BMLUT_32,
    PCD_OCTACC_32,
    PCD_DMAACC_32,
	PCD_SGINIT_32,
    PCD_AQSTART_32,
    PCD_AQADR_32,
    PCD_INTADR_32,
    PCD_ZOOM_32,
    PCD_HZOOM_32,
    PCD_OCTSWAP_32,
    PCD_PAD_32,
    PCD_CLIP_32,
    PCD_DIB_32,
	PCD_SEGSIZE_32,
	PCD_OCTSTART_32,
	PCD_SWCOUNT_32,
    PCD_INTCON1_32,
	PCD_ADRIEN_32,
	PCD_BMIEN_32,
	PCD_SWCTIEN_32,
    PCD_INTSTAT1_32,
	PCD_ADRINT_32,
	PCD_BMINT_32,
	PCD_SWCTINT_32,


    PCD_CTCON_32,
    PCD_LENSYNC_32,
    PCD_LENPOL_32,
    PCD_FENENB_32,
    PCD_FENPOL_32,
    PCD_MULTENB_32,
    PCD_MULTPOL_32,
    PCD_MMODE_32,
    PCD_PCLKPOL_32,

    PCD_OUTCON_32,
    PCD_DRIVEEXT_32,
    PCD_USEEXT_32,
    PCD_RETIME_32,
    PCD_RETPOL_32,
    PCD_CAM3_32,
    PCD_EXSEN_32,
    PCD_EXSPOL_32,
    PCD_EXTMD_32,
    PCD_PRIEN_32,
    PCD_PRIP_32,
	PCD_CMODECTL_32,
	PCD_CCLKDIS_32,
	PCD_CCLKVAL_32,

    PCD_FEXSCLK_32,
    PCD_EXSCLK_32,
	PCD_EXSEL_32,
	PCD_PRISEL_32,
	PCD_EMIDPNT_32,
	PCD_PRIHOLD_32,

    PCD_EXSTIME_32,

    PCD_ACQCON_32,
    PCD_STMODE_32,
    PCD_ETMODE_32,
    PCD_ACQMD_32,
    PCD_FLDSEL_32,
    PCD_FCNT_32,
    PCD_NEWACQ_32,
    PCD_GSTAT_32,
    PCD_FSTRT_32,

	PCD_FIFOINIT_32,

    PCD_HOFF_32,
    PCD_HACT_32,
    PCD_VOFF_32,
    PCD_VACT_32,

    PCD_CCLKCON_32,
    PCD_SYNDATA_32,
    PCD_SYNCLKA_32,
    PCD_SYNCLKB_32,
    PCD_SYNMUXA_32,
    PCD_SYNMUXB_32,
	PCD_LVACT_32,

    PCD_LUTCON0_32,
    PCD_LUT0PSIZE_32,
    PCD_LACCESS_32,
    PCD_LUT0PG_32,

    PCD_LUTCON1_32,
    PCD_LUT1PSIZE_32,
    PCD_LUT1PG_32,

    PCD_TRIGCON_32,
    PCD_TRIG0POL_32,
    PCD_TRIG0SRC_32,
	PCD_TRIG0GD_32,
    PCD_TRIG1POL_32,
    PCD_TRIG1SRC_32,
	PCD_TRIG1GD_32,

    PCD_TRIGSTAT_32,
    PCD_TRIG0DIFF_32,
    PCD_TRIG0TTL_32,							
    PCD_TRIG0OPTO_32,
    PCD_TRIG0CYC_32,
    PCD_TRIG1DIFF_32,
    PCD_TRIG1TTL_32,
    PCD_TRIG1OPTO_32,
    PCD_TRIG1CYC_32,
    PCD_CAMLEN_32,
    PCD_CAMFEN_32,
    PCD_CAMMULTI_32,

    PCD_SWTRIG0_32,
    PCD_SWTRIG1_32,

    PCD_INTCON0_32,
    PCD_VBIEN_32,
    PCD_HBIEN_32,
    PCD_TRIG0IEN_32,
    PCD_TRIG1IEN_32,
    PCD_SOAQIEN_32,
    PCD_EOAQIEN_32,
    PCD_PIOIEN_32,

    PCD_INTSTAT0_32,
    PCD_VBINT_32,
    PCD_HBINT_32,
    PCD_TRIG0INT_32,
    PCD_TRIG1INT_32,
    PCD_SOAQINT_32,
    PCD_EOAQINT_32,
    PCD_PIOINT_32,

	PCD_TRIGDIV_32,
	PCD_TRIGCNT_32,
	PCD_TRGDIV_32,
	PCD_DIVCON_32,

	PCD_PVACT_32,
	PCD_PMIDPNT_32,

    PCD_DECIM_32,
    PCD_HDEC_32,
    PCD_VDEC_32,

    PCD_SFORM_32,

    PCD_PORTCON_32,
    PCD_OUTSTB_32,
    PCD_INREGENB_32,
    PCD_INSTBPOL_32,
    PCD_INREGCLR_32,
    PCD_IPINTPOL_32,
    PCD_IPINTSTAT_32,
    PCD_IPSTRBSTA_32,

    PCD_OUTPORT_32,
    PCD_INPORT_32,
	PCD_AGCSTS_32,
	PCD_AINT_32,

	PCD_U1RX_32,
	PCD_U1IE_32,
	PCD_U1IIFC_32,
	PCD_U1LC_32,
	PCD_U1MC_32,
	PCD_U1DTR_32,
	PCD_U1RTS_32,
	PCD_U1LS_32,
	PCD_U1MS_32,
	PCD_U1CTS_32,
	PCD_U1SC_32,
	
	PCD_U2RX_32,
	PCD_U2IE_32,
	PCD_U2IIFC_32,
	PCD_U2LC_32,
	PCD_U2MC_32,
	PCD_U2DTR_32,
	PCD_U2RTS_32,
	PCD_U2LS_32,
	PCD_U2MS_32,
	PCD_U2CTS_32,
	PCD_U2SC_32,

	PCD_FPGACON_32,
	PCD_FPGAPRG_32,
	PCD_FPGARDY_32,
	PCD_FPGDONE_32,
	PCD_BRDID_32,
	PCD_FPGADAT_32,
	PCD_SCATDST0_32,
	PCD_SCATLEN0_32,

    PCD_MAXREGS2       /* keep it last */
};


#endif