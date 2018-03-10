/******************************************************************************
 *
 * MODULE
 *    PCPreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/pcpreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 7/06/00 1:12p $
 *
 * ABSTRACT
 *    IFC PCPGB Register names
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _PCP_REG
#define _PCP_REG


typedef enum {
	PCP_OCT_BYTE_SWAP,
	PCP_OCT_WORD_SWAP
} PCP_OCT_SWAP_TYPE;


enum {                    /* PCI configuration space registers */

    PCP_VENDOR_ID_32,
    PCP_DEVICE_ID_32,

    PCP_PCICMDSTAT_32,
    PCP_PCICMD_32,
    PCP_IOEN_32,
    PCP_MEMEN_32,
    PCP_BMEN_32,
    PCP_PAREN_32,
    PCP_SEREN_32,
    PCP_FBB_32,
    PCP_PCISTAT_32,
    PCP_DTPAR_32,
    PCP_STABT_32,
    PCP_RTABT_32,
    PCP_RMABT_32,
    PCP_SSERR_32,
    PCP_DPARE_32,

    PCP_REVID_32,
    PCP_MEMSZ_32,
    PCP_CLASSCODE_32,

    PCP_CALN_32,
    PCP_LAT_32,
    PCP_HDR_32,
    PCP_BIST_32,

    PCP_BADR0_32,
    PCP_BADR1_32,
    PCP_BADR2_32,
    PCP_BADR3_32,
    PCP_BADR4_32,
    PCP_BADR5_32,

    PCP_XROM_32,

    PCP_INTLN_32,
    PCP_INTPIN_32,
    PCP_MINGNT_32,
    PCP_MAXLAT_32,

    PCP_MAX_CFGREG
};

enum {
    PCP_MBOX1_32 = PCP_MAX_CFGREG,   /* PCI Interface Control Register Set  */
    PCP_MB_FXSZ_32,
    PCP_MB_ILACE_32,
    PCP_MB_HSHK_32,
    PCP_MB_FYSZ_32,
    PCP_MB_PIX_32,

    PCP_MB0X2_32,
    PCP_MB_AOIXST_32,
    PCP_MB_AOIYST_32,

    PCP_MB0X3_32,
    PCP_MB_AOIXSZ_32,
    PCP_MB_AOIYSZ_32,
    PCP_MB_FYSZHI_32,
    PCP_MB_STFLD_32,
    PCP_MB_BMSEMA_32,

    PCP_MB0X4_32,
    PCP_MB_IMGADR_32,
    PCP_MB_BMINITFLG_32,
    PCP_MB_CONT_32,

    PCP_BMDST_32,

    PCP_BMXC_32,

    PCP_INTCTL_32,
    PCP_INTEN_32,
    PCP_BINTEN_32,
    PCP_INTST_32,
    PCP_BINTST_32,
    PCP_MAINT_32,
    PCP_TAINT_32,
    PCP_ENDIAN_32,

    PCP_BMCTL_32,
    PCP_FIFOFL_32,
    PCP_FIFO4P_32,
    PCP_FIFOEM_32,
    PCP_BMDONE_32,
    PCP_BMREQ_32,
    PCP_NVAD_32,
    PCP_RST_32,
    PCP_FIFOCLR_32,
    PCP_NVCTL_32,

    PCP_MAXREGS1
};

enum {
    PCP_BRDSTAT_32 = PCP_MAXREGS1,
    PCP_BLDSTAT_32,
    PCP_FPGDONE_32,
    PCP_FPGARDY_32,
	PCP_PIOLSTAT_32,
	PCP_CMPRESENT_32,
    PCP_REV_32,

    PCP_ORCAPRGM_32,
    PCP_ORCAPRGMBYTE_32,

    PCP_ORCARST_32,

    PCP_MAXREGS2       /* keep it last */
};

enum {
    PCP_PTGH1_32 = PCP_MAXREGS2,
	PCP_HTOTAL_32,
	PCP_HESYNC_32,
	PCP_HSYNCPOL_32,
	PCP_XTALHPOL_32,

	PCP_PTGH2_32,

	PCP_PTGV1_32,
	PCP_VTOTAL_32,
	PCP_VSEND_32,
	PCP_VSYNCPOL_32,
	PCP_EDONP_32,
	PCP_VERROR_32,

	PCP_PTGV2_32,
	PCP_VGSTRT_32,
	PCP_VGEND_32,

	PCP_PWGH_32,
	PCP_HOFF_32,
	PCP_HACT_32,

	PCP_PWGV_32,
	PCP_VOFF_32,
	PCP_VACT_32,
	PCP_EXTRIGSTAT0_32,
	PCP_EXTRIGSTAT1_32,
	PCP_OPTOTRIGSTAT0_32,
	PCP_OPTOTRIGSTAT1_32,
	PCP_DIFFTRIGSTAT0_32,
	PCP_DIFFTRIGSTAT1_32,

	PCP_INCON1_32,
	PCP_TRIGEN_32,
	PCP_TRIGSEL_32,
	PCP_TRIGPOL_32,
	PCP_TRIGCYC_32,
	PCP_SKPFLDMD_32,
	PCP_WENMD_32,
	PCP_STRBMD_32,
	PCP_STRBPOL_32,
	PCP_STRBEN_32,
	PCP_STRBDLY_32,
	PCP_FRSTMD_32,
	PCP_FRSTPOL_32,
	PCP_FRSTSZ_32,
	PCP_FRSTONV_32,
	PCP_FROFF_32,
	PCP_TRIG_MD_32,

	PCP_INCON2_32,
	PCP_PLLCS_32,
	PCP_DACCS_32,
	PCP_TIMEMD_32,
	PCP_LPFSEL_32,
	PCP_VIDEOINSEL_32,
	PCP_VSCLKSEL_32,
	PCP_OVRSM_32,
	PCP_VCLK_POL_32,
	PCP_LENPOL_32,
	PCP_FENPOL_32,
	PCP_FLDPOL_32,
	PCP_FLD_SRC_32,
	PCP_FLDSHFT_32,
	PCP_VSYNCEN_32,
	PCP_SMODE_32,
	PCP_VSCANTST_32,
	PCP_MISCOUT0_32,
	PCP_MISCOUT1_32,
	PCP_MISCOUT2_32,
	PCP_MISC_IN_32,
	PCP_ILUTSADDR_32,

	PCP_AM_INTCLR_32,
	PCP_SOT_INT_STAT_32,
	PCP_EOT_INT_STAT_32,
	PCP_PIO_INT_STAT_32,
	PCP_TCNT_INT_STAT_32,
	PCP_VB_INT_STAT_32,
	PCP_VBEVEN_INT_STAT_32,
	PCP_VBODD_INT_STAT_32,

	PCP_AM_INTEN_32,
	PCP_SOT_INTEN_32,
	PCP_EOT_INTEN_32,
	PCP_PIO_INTEN_32,
	PCP_TCNT_INT_EN_32,
	PCP_VB_INT_EN_32,
	PCP_VBEVEN_INT_EN_32,
	PCP_VBODD_INT_EN_32,

	PCP_SOFTTRIG_32,

	PCP_PCLAMP_32,
	PCP_CLMPSRC_32,
	PCP_BPSTART_32,
	PCP_BPEND_32,
	PCP_NOCLAMP_32,
	PCP_CNTENSRC_32,

	PCP_PCLAMPHI_32,

	PCP_PLLPROG_32,
	PCP_PLLSDATA_32,

	PCP_DACPROG_32,
	PCP_DACSDATA_32,

	PCP_TIMER_32,
	PCP_TIMERCNT_32,

	PCP_PORTCON_32,
	PCP_OUTSTB_32,
	PCP_INREGENB_32,
	PCP_INSTBPOL_32,
	PCP_INREGCLR_32,
	PCP_IPINTPOL_32,
	PCP_INT_IN_STAT_32,
	PCP_STRB_IN_STAT_32,

	PCP_OUTPORT_REG_32,
	PCP_OUTPORT_32,
	PCP_INPORT_REG_32,
	PCP_INPORT_32,

	PCP_ALPHA_32,
	PCP_ALPHA_VAL_32,
	PCP_ACNT_MD_32,
	PCP_ACNT_DIR_32,
	PCP_DIAG_MODE_32,

    PCP_MAXREGS3       /* keep it last */
};

enum {
	PCP_ACQREG_32 = PCP_MAXREGS3,
	PCP_ACQADR_RST_32,
	PCP_FCNT_32,
	PCP_FLDSEL_32,
	PCP_ACQMD_32,
	PCP_NEWACQ_32,
	PCP_GSTAT_32,
	PCP_FLDSTART_32,
	PCP_PREV_FLDSTART_32,
	PCP_AMVBSTAT_32,
	PCP_AMFLDSTAT_32,
	PCP_IN_MODE_32,

//	PCP_ALPHA2_32,
//	PCP_ALPHA2_VAL_32,
//	PCP_ACNT2_MD_32,
//	PCP_ACNT2_DIR_32,
//	PCP_DIAG2_MODE_32,

	PCP_BMCTLX_32,
	PCP_BM_ON_32,
	PCP_BMSHIFT_32,
	PCP_BMBYTESEL_32,
	PCP_BM_ZOOM_32,
	PCP_PAD_EN_32,
	PCP_CLIP_EN_32,
	PCP_SCAN_DIR_32,
	PCP_DMASTART_32,

	PCP_MEMINIT_32,

	PCP_ACQ_STRT_32,
	PCP_ACQ_STRT_ADDR_32,

	PCP_ACQ_LINE_INT_32,
	PCP_INTADR_32,
	PCP_LSBMASK_32,

	PCP_SGSZ_32,
	PCP_SGSZ_VAL_32,

	PCP_OCT_START_32,
	PCP_OCT_START_ADDR_32,

	PCP_INTSTAT_32,
	PCP_ACQ_LINE_INT_STAT_32,
	PCP_BM_INT_STAT_32,
	PCP_AM_INT_STAT_32,
	PCP_EOF_INT_STAT_32,

	PCP_INTENREG_32,
	PCP_ACQ_LINE_INT_EN_32,
	PCP_BM_INT_EN_32,
	PCP_AM_INT_EN_32,
	PCP_EOF_INTEN_32,

	PCP_ACQADR_32,
	PCP_ACQADR_STAT_32,

	PCP_AINT_32,
	PCP_AINT_REG_32,
	PCP_AGCSTS_32,
	PCP_AGCSTS_REG_32,
	PCP_MDSTADR_32,
	PCP_MDSTADR_REG_32,
	PCP_MXCNT_32,
	PCP_MXCNT_REG_32,

    PCP_MAXREGS4       /* keep it last */
};

enum {
	PCP_PLLA0_16 = PCP_MAXREGS4,
    PCP_PLLA1_16,  
    PCP_PLLA2_16,  
    PCP_PLLA3_16,  
    PCP_PLLA4_16,  
    PCP_PLLA5_16,  
    PCP_PLLA6_16,
	
    PCP_FDIV_16,  
    PCP_LO_16,    
    PCP_HI_16,    
    PCP_RDIV_16,  
    PCP_REFPOL_16,
    PCP_VCO_16,   
    PCP_PFD_16,   
    PCP_PDEN_16,  
    PCP_INTFLT_16,
    PCP_INTVCO_16, 
    PCP_CLKSEL_16,
	
    PCP_FBKSEL_16, 
    PCP_FBKPOL_16, 
    PCP_ADD_16,    
    PCP_SWLW_16,   
    PCP_PDA_16,    
    PCP_PDB_16,    
    PCP_LDLG_16,   
    PCP_FINEEN_16,
	
    PCP_LCOUNT_16, 
    PCP_OMUX1_16,  
    PCP_OMUX2_16,  
    PCP_OMUX3_16,  
    PCP_OMUX4_16,  
    PCP_DACRST_16, 
    PCP_AUXEN_16,  
    PCP_AUXCLK_16, 
    PCP_EXTREF_16, 

	PCP_MAX_PLLREG
};

enum {
	PCP_PREF_16 = PCP_MAX_PLLREG,
    PCP_NREF_16,
    PCP_CLMP_VOLT_16,
	PCP_STRIP_16,

	PCP_MAX_DACREG
};




#endif
