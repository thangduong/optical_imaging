/******************************************************************************
 *
 * MODULE
 *    amvreg.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/amvreg.h $
 *    $Revision: 1.1 $
 *    $Modtime: 6/15/00 6:48p $
 *
 * ABSTRACT
 *    IFC AM-V register definitions.
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 ******************************************************************************/

#ifndef _AMVREG_DEF
#define _AMVREG_DEF


/**************************************************************************
**
** AM-VS Register Symbol Definitions.
*/

typedef enum {

    AMV_MODID,
	AMV_REV,
	AMV_BRDID,

    AMV_LUTADR,
    AMV_LUTDATA,
    AMV_ADCDATA,

    AMV_HTOTAL,
    AMV_HESYNC,
    AMV_HEEQ,
    AMV_SEREND,
    AMV_VTOTAL,
    AMV_VSENDR,
    AMV_VSEND,
	AMV_EDONP,
    AMV_HSYNPOL,
    AMV_VSYNPOL,
    AMV_VGSTRT,
    AMV_VGEND,

    AMV_HOFF,
    AMV_HACTIVE,
    AMV_VOFF,
    AMV_VACTIVE,

    AMV_SDELAY,
    AMV_STRBDLY,
    AMV_LENPOL,
    AMV_FENPOL,

    AMV_FRSTDLY,
    AMV_FROFF,
	AMV_FRVSYNC,
    AMV_FRSTMD,
    AMV_FRSTPOL,
    AMV_FRSTSZ,

    AMV_CON1,
    AMV_SYNCSEL,
    AMV_CHSYNCEN,
    AMV_VSYNCEN,
    AMV_CLKSRC,
    AMV_LPFSEL,
    AMV_VSCAN,
    AMV_ISCALE,
    AMV_VCLKPOL,
    AMV_SMODE,
    AMV_CAMSEL,
	AMV_FLDSHFT,

    AMV_CON2,
    AMV_PLLCS,
	AMV_EINPOL,
	AMV_EIN0IEN,
	AMV_EIN1IEN,
	AMV_EIN0,
	AMV_EIN1,
	AMV_EOUT0,
	AMV_EOUT1,
	AMV_SOTINT,
	AMV_EOTINT,
	AMV_EIN0INT,
	AMV_EIN1INT,


    AMV_TRIGCON,
    AMV_TRIGEN,
    AMV_TRIGMD,
    AMV_TRGCYC,
	AMV_SOTIEN,
	AMV_EOTIEN,
    AMV_TRGSRC,
    AMV_TRGPOL,
    AMV_STRBMD,
    AMV_STRBEN,
    AMV_STRBPOL,
    AMV_SKPFLDMD,

    AMV_SWTRIG,

    AMV_PCLAMP,
    AMV_CCNT,
    AMV_PCLMPOL,
    AMV_CLMPSRC,
    AMV_CLMP,

    AMV_PLLPRG,
    AMV_PLLSDATA,

	/* ADCON internal registers */
    AMV_ADCCON,
    AMV_NREF,
	AMV_PREF,

	/* PLL internal registers     */
	AMV_PLLA0,                            
	AMV_PLLA1,  
	AMV_PLLA2,  
	AMV_PLLA3,  
	AMV_PLLA4,  
	AMV_PLLA5,
	AMV_PLLA6,
	AMV_PLLFDIV,   
	AMV_PLLLO,
	AMV_PLLHI,
	AMV_PLLRDIV,
	AMV_PLLREFPOL,
	AMV_PLLVCO,
	AMV_PLLPFD,
	AMV_PLLPDEN,
	AMV_PLLINTFLT,
	AMV_PLLINTVCO,
	AMV_PLLCLKSEL,
	AMV_PLLFBKSEL,
	AMV_PLLFBKPOL,
	AMV_PLLADD,
	AMV_PLLSWLW,
	AMV_PLLPDA,
	AMV_PLLPDB,
	AMV_PLLLDLG,
	AMV_PLLFINEEN, 
	AMV_PLLLCOUNT,
	AMV_PLLOMUX1,
	AMV_PLLOMUX2,
	AMV_PLLOMUX3,
	AMV_PLLOMUX4,
	AMV_PLLDACRST,
	AMV_PLLAUXEN,
	AMV_PLLAUXCLK,
	AMV_PLLEXTREF,


    AMV_MAXREGS

} AMV_REG_TYPE;


#define AMV_SKIP -1

/**************************************************************************
**
** AM-V Register Bit Field Definitions.
*/

/* PTG Parameters */





/* AMV_FRSTSZ */
typedef enum {
	AMV_USE_FR_OFF_PER,
	AMV_FR_ONE_LINE,
	AMV_FRSTSZ_SKIP=AMV_SKIP
} AMV_FRSTSZ_TYPE;


/*--------------------------- CON1 Register -----------------------------*/

/* AMV_SYNCSEL */
typedef enum {
	AMV_PTG_HSYNC_OUT,     
	AMV_PTG_CSYNC_OUT     
} AMV_SYNCSEL_TYPE;




/* AMV_CLKSRC */
typedef enum {
	AMV_PLLCLK,             
	AMV_XTALCLK
} AMV_CLKSRC_TYPE;
	



/* AMV_ISCALE */
typedef enum {
	AMV_SCALE_1,
	AMV_SCALE_1_5          
} AMV_ISCALE_TYPE;

/* AMVV_VCLKPOL */
typedef enum {
	AMV_VCLKPOL_NORMAL,
	AMV_VCLKPOL_INVERTED          
} AMV_VCLKPOL_TYPE;

/* AMV_SMODE */
typedef enum {
	AMV_NI_LACED,
	AMV_I_LACED            
} AMV_SMODE_TYPE;


typedef enum {
	AMV_VSCAN_DISABLE,            
	AMV_VSCAN_ENABLE
} AMV_VSCAN_TYPE;


/* AMV_CAMSEL -- Camera port selections */
typedef enum {
	AMV_PORT0,              
	AMV_PORT1,              
	AMV_PORT2,
	AMV_PORT3
} AMV_CAMSEL_TYPE;

/* AMV_FLDSHFT */
typedef enum {
	AMV_CROP_HALFLINE,
	AMV_FLDSHFT_NORM
} AMV_FLDSHFT_TYPE;

/* AMV_PLLCS */
typedef enum {
	AMV_PLL_PROG_MODE,
	AMV_PLL_NORM_MODE      
} AMV_PLLCS_TYPE;

/*-------------------------- TRGCON Register ----------------------------*/


/* AMV_TRGCYC */
typedef enum {
	AMV_TRGCYC_IDLE,
	AMV_TRGCYC_ACTIVE
} AMV_TRGCYC_TYPE;





/* AMV_STRBMD */
typedef enum {
	AMV_FAST_STROBE,
	AMV_SLOW_STROBE,
	AMV_STRBMD_SKIP=AMV_SKIP
} AMV_STRBMD_TYPE;




/*-------------------------- PCLAMP Register -----------------------------*/


/* AMV_CLMPSRC */
typedef enum {
	AMV_AUTOCLAMP,
	AMV_PROGCLAMP          
} AMV_CLMPSRC_TYPE;


typedef enum {
	AMV_EXT_OUT_0,
	AMV_EXT_OUT_1,
	AMV_NUM_EXT_OUT
} AMV_EXTOUT_TYPE;

typedef enum {
	AMV_EXT_IN_0,
	AMV_EXT_IN_1,
	AMV_NUM_EXT_IN
} AMV_EXTIN_TYPE;


/* AMV_EINPOL */
typedef enum {
	AMV_EIN_ACT_HI, /* interrupt on rising edge */
	AMV_EIN_ACT_LOW /* interrupt on falling edge */
} AMV_EINPOL_TYPE;


#endif
