/******************************************************************************
 *
 * MODULE
 *    pcrreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/pcrreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 3/22/01 4:29p $
 *
 * ABSTRACT
 *    IFC PCRGB Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _PCR_REG
#define _PCR_REG


typedef enum {
	PCR_OCT_BYTE_SWAP,
	PCR_OCT_WORD_SWAP
} PCR_OCT_SWAP_TYPE;


enum {                    /* PCI configuration space registers */

    PCR_VENDOR_ID_32,
    PCR_DEVICE_ID_32,

    PCR_PCICMDSTAT_32,
    PCR_PCICMD_32,
    PCR_IOEN_32,
    PCR_MEMEN_32,
    PCR_BMEN_32,
    PCR_PAREN_32,
    PCR_SEREN_32,
    PCR_FBB_32,
    PCR_PCISTAT_32,
    PCR_DTPAR_32,
    PCR_STABT_32,
    PCR_RTABT_32,
    PCR_RMABT_32,
    PCR_SSERR_32,
    PCR_DPARE_32,

    PCR_REVID_32,
    PCR_MEMSZ_32,
    PCR_CLASSCODE_32,

    PCR_CALN_32,
    PCR_LAT_32,
    PCR_HDR_32,
    PCR_BIST_32,

    PCR_BADR0_32,
    PCR_BADR1_32,
    PCR_BADR2_32,
    PCR_BADR3_32,
    PCR_BADR4_32,
    PCR_BADR5_32,

    PCR_XROM_32,

    PCR_INTLN_32,
    PCR_INTPIN_32,
    PCR_MINGNT_32,
    PCR_MAXLAT_32,

    PCR_MAX_CFGREG
};

enum {
    PCR_MBOX1_32 = PCR_MAX_CFGREG,   /* PCI Interface Control Register Set  */
    PCR_MB_FXSZ_32,
    PCR_MB_ILACE_32,
    PCR_MB_HSHK_32,
    PCR_MB_FYSZ_32,
    PCR_MB_PIX_32,

    PCR_MB0X2_32,
    PCR_MB_AOIXST_32,
    PCR_MB_AOIYST_32,

    PCR_MB0X3_32,
    PCR_MB_AOIXSZ_32,
    PCR_MB_AOIYSZ_32,
    PCR_MB_FYSZHI_32,
    PCR_MB_STFLD_32,
    PCR_MB_BMSEMA_32,

    PCR_MB0X4_32,
    PCR_MB_IMGADR_32,
    PCR_MB_BMINITFLG_32,
    PCR_MB_CONT_32,

    PCR_BMDST_32,

    PCR_BMXC_32,

    PCR_INTCTL_32,
    PCR_INTEN_32,
    PCR_BINTEN_32,
    PCR_INTST_32,
    PCR_BINTST_32,
    PCR_MAINT_32,
    PCR_TAINT_32,
    PCR_ENDIAN_32,

    PCR_BMCTL_32,
    PCR_FIFOFL_32,
    PCR_FIFO4P_32,
    PCR_FIFOEM_32,
    PCR_BMDONE_32,
    PCR_BMREQ_32,
    PCR_NVAD_32,
    PCR_RST_32,
    PCR_FIFOCLR_32,
    PCR_NVCTL_32,

    PCR_MAXREGS1
};

enum {
    PCR_BRDSTAT_32 = PCR_MAXREGS1,
    PCR_BLDSTAT_32,
    PCR_FPGDONE_32,
    PCR_FPGARDY_32,
    PCR_REV_32,

    PCR_ORCAPRGM_32,
    PCR_ORCAPRGMBYTE_32,

    PCR_ORCARST_32,

    PCR_MAXREGS2       /* keep it last */
};

enum {
    PCR_PTGH1_32 = PCR_MAXREGS2,
	PCR_HTOTAL_32,
	PCR_HESYNC_32,
	PCR_HSYNCPOL_32,
	PCR_XTALHPOL_32,

	PCR_PTGH2_32,
	PCR_PSCANSTRT_32,
	PCR_PSCANEND_32,
	PCR_PSCANPOL_32,
	PCR_PSCANENABLE_32,
	PCR_PSCANMD_32,

	PCR_PTGV1_32,
	PCR_VTOTAL_32,
	PCR_VSEND_32,
	PCR_VSYNCPOL_32,
	PCR_EDONP_32,
	PCR_VERROR_32,

	PCR_PTGV2_32,
	PCR_VGSTRT_32,
	PCR_VGEND_32,

	PCR_PWGH_32,
	PCR_HOFF_32,
	PCR_HACT_32,

	PCR_PWGV_32,
	PCR_VOFF_32,
	PCR_VACT_32,

	PCR_INCON1_32,
	PCR_TRIGEN_32,
	PCR_TRIGSEL_32,
	PCR_TRIGPOL_32,
	PCR_TRIGCYC_32,
	PCR_SKPFLDMD_32,
	PCR_WENMD_32,
	PCR_STRBMD_32,
	PCR_STRBPOL_32,
	PCR_STRBEN_32,
	PCR_STRBDLY_32,
	PCR_FRSTMD_32,
	PCR_FRSTPOL_32,
	PCR_FRSTSZ_32,
	PCR_FRSTONV_32,
	PCR_FROFF_32,
	PCR_TRIG_MD_32,

	PCR_INCON2_32,
	PCR_PLLCS_32,
	PCR_DACCS_32,
	PCR_TIMEMD_32,
	PCR_LPFSEL_32,
	PCR_VIDEOINSEL_32,
	PCR_STRP_IN_SEL_32,
	PCR_VCLK_POL_32,
	PCR_LENPOL_32,
	PCR_FENPOL_32,
	PCR_FLDPOL_32,
	PCR_FLD_SRC_32,
	PCR_FLDSHFT_32,
	PCR_VSYNCEN_32,
	PCR_SMODE_32,
	PCR_VSCANTST_32,
	PCR_MISC_OUT_32,
	PCR_MISC_STRB_OUT_32,
	PCR_CSC_CYCSTAT_32,
	PCR_MISC_IN_32,

	PCR_AM_INTCLR_32,
	PCR_SOT_INT_STAT_32,
	PCR_EOT_INT_STAT_32,
	PCR_PIO_INT_STAT_32,
	PCR_TCNT_INT_STAT_32,
	PCR_VB_INT_STAT_32,
	PCR_VBE_INT_STAT_32,
	PCR_VBO_INT_STAT_32,
	PCR_FINT_STAT_32,

	PCR_AM_INTEN_32,
	PCR_SOT_INTEN_32,
	PCR_EOT_INTEN_32,
	PCR_PIO_INTEN_32,
	PCR_TCNT_INT_EN_32,
	PCR_VB_INTEN_32,
	PCR_VBE_INTEN_32,
	PCR_VBO_INTEN_32,

	PCR_SOFTTRIG_32,

	PCR_PCLAMP_32,
	PCR_CLMPSRC_32,
	PCR_BPSTART_32,
	PCR_BPEND_32,
	PCR_NOCLAMP_32,
	PCR_CNTENSRC_32,

	PCR_PCLAMPHI_32,
	PCR_FPSTART_32,
	PCR_FPEND_32,
	PCR_FPENABLE_32,
	PCR_ILUT_HIGH_EN_32,
	PCR_ILUT_SADDR_32,

	PCR_PLLPROG_32,
	PCR_PLLSDATA_32,

	PCR_DACPROG_32,
	PCR_DACSDATA_32,

	PCR_TIMER_32,
	PCR_TIMERCNT_32,

	PCR_PORTCON_32,
	PCR_OUTSTB_32,
	PCR_INREGENB_32,
	PCR_INSTBPOL_32,
	PCR_INREGCLR_32,
	PCR_IPINTPOL_32,
	PCR_INT_IN_STAT_32,
	PCR_STRB_IN_STAT_32,
	PCR_OUTPORT_32,
	PCR_INPORT_32,

	PCR_CSC_COEF_X_32,

	PCR_CSC_COEF_Y_32,

	PCR_CSC_COEF_Z_32,

    PCR_MAXREGS3       /* keep it last */
};

enum {
	PCR_ACQREG_32 = PCR_MAXREGS3,
	PCR_ACQADR_RST_32,
	PCR_FCNT_32,
	PCR_FLDSEL_32,
	PCR_HDEC_32,
	PCR_VDEC_32,
	PCR_ACQMD_32,
	PCR_NEWACQ_32,
	PCR_GSTAT_32,
	PCR_FLDSTART_32,
	PCR_PREV_FLDSTART_32,
	PCR_AMVBSTAT_32,
	PCR_AMFLDSTAT_32,
	PCR_IN_MODE_32,
	PCR_ILUT_HIGH_SEL_32,

	PCR_ALPHA_32,
	PCR_ALPHA_VAL_32,
	PCR_ACNT_MD_32,
	PCR_ACNT_DIR_32,
	PCR_DIAG_MODE_32,

	PCR_BMCTLX_32,
	PCR_BM_ON_32,
	PCR_BMSTEP_32,
	PCR_BM_ZOOM_32,
	PCR_PAD_EN_32,
	PCR_CLIP_EN_32,
	PCR_SCAN_DIR_32,

	PCR_MEMINIT_32,

	PCR_ACQ_STRT_32,
	PCR_ACQ_STRT_ADDR_32,

	PCR_ACQ_LINE_INT_32,
	PCR_INTADR_32,
	PCR_LSBMASK_32,

	PCR_SGSZ_32,
	PCR_SGSZ_VAL_32,

	PCR_OCT_START_32,
	PCR_OCT_START_ADDR_32,

	PCR_INTSTAT_32,
	PCR_ACQ_LINE_INT_STAT_32,
	PCR_BM_INT_STAT_32,
	PCR_AM_INT_STAT_32,
	PCR_EOF_INT_STAT_32,
	PCR_SPR0_INT_STAT_32,
	PCR_SPR1_INT_STAT_32,
	PCR_SPR2_INT_STAT_32,
	PCR_SPR3_INT_STAT_32,

	PCR_INTENREG_32,
	PCR_ACQ_LINE_INT_EN_32,
	PCR_BM_INT_EN_32,
	PCR_AM_INT_EN_32,
	PCR_EOF_INTEN_32,
	PCR_SPR0_INT_EN_32,
	PCR_SPR1_INT_EN_32,
	PCR_SPR2_INT_EN_32,
	PCR_SPR3_INT_EN_32,

	PCR_ACQADR_STAT_32,

	PCR_AINT_32,
	PCR_AINT_REG_32,
	PCR_AGCSTS_32,
	PCR_AGCSTS_REG_32,
	PCR_MDSTADR_32,
	PCR_MDSTADR_REG_32,
	PCR_MXCNT_32,
	PCR_MXCNT_REG_32,

    PCR_MAXREGS4       /* keep it last */
};

enum {
	PCR_PLLA0_16 = PCR_MAXREGS4,
    PCR_PLLA1_16,  
    PCR_PLLA2_16,  
    PCR_PLLA3_16,  
    PCR_PLLA4_16,  
    PCR_PLLA5_16,  
    PCR_PLLA6_16,
	
    PCR_FDIV_16,  
    PCR_LO_16,    
    PCR_HI_16,    
    PCR_RDIV_16,  
    PCR_REFPOL_16,
    PCR_VCO_16,   
    PCR_PFD_16,   
    PCR_PDEN_16,  
    PCR_INTFLT_16,
    PCR_INTVCO_16, 
    PCR_CLKSEL_16,
	
    PCR_FBKSEL_16, 
    PCR_FBKPOL_16, 
    PCR_ADD_16,    
    PCR_SWLW_16,   
    PCR_PDA_16,    
    PCR_PDB_16,    
    PCR_LDLG_16,   
    PCR_FINEEN_16,
	
    PCR_LCOUNT_16, 
    PCR_OMUX1_16,  
    PCR_OMUX2_16,  
    PCR_OMUX3_16,  
    PCR_OMUX4_16,  
    PCR_DACRST_16, 
    PCR_AUXEN_16,  
    PCR_AUXCLK_16, 
    PCR_EXTREF_16, 

	PCR_MAX_PLLREG
};

enum {
	PCR_RPREF_16 = PCR_MAX_PLLREG,
    PCR_GPREF_16,
    PCR_BPREF_16,
    PCR_RNREF_16,
    PCR_GNREF_16,
    PCR_BNREF_16,
    PCR_CLMP_VOLT_16,

	PCR_MAX_DACREG
};





#endif

