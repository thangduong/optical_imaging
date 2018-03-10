/******************************************************************************
 *
 * MODULE   
 *		PCDigt.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/pcdigt.h $
 *		$Revision: 1.1 $
 *		$Modtime: 8/14/02 1:47p $
 *
 * ABSTRACT  
 *		Video source types of the CPCDig class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCDIGT_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_PCDIGT_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#define VPCD_NUM_LUT_ENTRIES 0x10000

typedef enum VPCD_TRIG_SRC_TYPE {
	VPCD_DIFFERENTIAL_TRIG,
	VPCD_TTL_TRIG,
	VPCD_OPTO_COUPLED_TRIG
} VPCD_TRIG_SRC_TYPE; 

typedef enum VPCD_TRIG_MODE_TYPE {
	VPCD_TMODE_DISABLE=0,
	VPCD_TMODE_HWTRIG0_ASSERT=2,
	VPCD_TMODE_HWTRIG0_DEASSERT=3,
	VPCD_TMODE_HWTRIG1_ASSERT=4,
	VPCD_TMODE_HWTRIG1_DEASSERT=5,
	VPCD_TMODE_SWTRIG0=6,
	VPCD_TMODE_SWTRIG1=7,

} VPCD_TRIG_MODE_TYPE;

typedef enum VPCD_MULTI_INPUT_TYPE {
	VPCD_MULTI_INPUT_FIELD,
	VPCD_MULTI_INPUT_VALID_DATA
} VPCD_MULTI_INPUT_TYPE;

typedef enum VPCD_EXSYNC_MODE_TYPE {
	VPCD_EXSYNC_FREE_RUNNING,
	VPCD_EXSYNC_TRIG1, 
	VPCD_EXSYNC_TRIG2,
	VPCD_EXSYNC_SOFT_TRIG, 
	VPCD_EXSYNC_SOFT_TRIG2, 
	VPCD_EXSYNC_VB_TRIG
} VPCD_EXSYNC_MODE_TYPE;


typedef enum VPCD_IMAGE_GEOMETRY_TYPE {
	VPCD_1CHAN_L2R,				// |A,A,A,..........A,A|
	VPCD_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	VPCD_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	VPCD_2CHAN_SEP_TAP_R2L,		// 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|            <=A|            <=B|
	VPCD_4CHAN_SEP_TAP_L2R,		// 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |D=>    |
	VPCD_4CHAN_SEP_TAP_R2L,		// 4 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|    <=A|    <=B|    <=C|    <=D|
	VPCD_4CHAN_2SEG_INTERLEAVED,// 4 Taps,2 Segments, each interleaved		|A,B,A,B,...,A,B|C,D,C,D,...,C,D|
	VPCD_4CHAN_INTERLEAVE_CONVERGE,//4 Taps,2 Segments converge, interleaved	|A,B,A,B,=>     |     <= C,D,C,D|
	VPCD_2CHAN_SEP_TAP_CONVERGE,	// |A =>   |    <= B|
	VPCD_SEP_QUAD_TAP_CONVERGE,  // 4TAPS - 4 QUADRANTS
	VPCD_2TAP_INTERLINE_A_EVEN,			// Tap A even lines Tap B odd lines
	VPCD_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines
	VPCD_3CHAN_SEP_TAP_L2R,		// 3 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |
	VPCD_USER_DEFINED_GEO,		// a user-defined geometry

	VPCD_NUM_GEOMETRY_KINDS,

	VPCD_INVALID_GEOMETRY=-1

} VPCD_IMAGE_GEOMETRY_TYPE;

typedef enum VPCD_DIVIDE_CTL_TYPE {
	VPCD_DISABLE_TRIG_DIVIDE=0,
	VPCD_DIVIDE_TRIG_0=2,
	VPCD_DIVIDE_TRIG_1=3
} VPCD_DIVIDE_CTL_TYPE;

typedef enum VPCD_EXSYNC_START_LOC_TYPE {
	VPCD_EXSYNC_START_CYCLE_END,
	VPCD_EXSYNC_START_CYCLE_BEGIN,
	VPCD_EXSYNC_START_MIDPOINT
} VPCD_EXSYNC_START_LOC_TYPE;

typedef enum VPCD_PRI_START_LOC_TYPE {
	VPCD_PRI_START_CYCLE_BEGIN,
	VPCD_PRI_START_MIDPOINT,
	VPCD_PRI_START_CYCLE_END
} VPCD_PRI_START_LOC_TYPE;

typedef enum VPCD_PRI_END_LOC_TYPE {
	VPCD_PRI_END_AT_LEN_BEGIN,
	VPCD_PRI_END_AT_LEN_END,
	VPCD_PRI_END_IS_START_DEPEND,
} VPCD_PRI_END_LOC_TYPE;





typedef enum VPCD_PARAMS_TYPE {
	VPCD_MULTI_ENABLE = VSP_MOD_UNIQUE_BASE,			// VS_ENABLE_TYPE
	VPCD_MULTI_POLARITY, 		// VS_POLARITY_TYPE

	VPCD_MULTI_INPUT_MODE,		// VS_MULTI_INPUT_TYPE

	VPCD_PCLK_POLARITY, 		// VS_EDGE_TYPE

	VPCD_MULTI_OUTPUT_ENABLE,	// VS_ENABLE_TYPE
	VPCD_USE_EXT_MULTI,		// VS_ENABLE_TYPE
	VPCD_RETIME_ENABLE,		// VS_ENABLE_TYPE

	VPCD_RETIME_POLARITY, 		// VS_EDGE_TYPE

	VPCD_CAM3_ENABLE,			// VS_ENABLE_TYPE

	VPCD_EXSYNC_ENABLE,		// VS_ENABLE_TYPE

	VPCD_EXSYNC_POLARITY,		// VS_POLARITY_TYPE

	VPCD_EXSYNC_MODE,			// VS_EXSYNC_MODE

	VPCD_PRI_ENABLE,			// VS_ENABLE_TYPE
	VPCD_PRI_POLARITY,			// VS_POLARITY_TYPE
	
	VPCD_CAM_MODE_CTL,			// range 0..15
	VPCD_EXT_SYNC_TIME,		// units are microseconds range 140ns - 572us
	VPCD_EXT_SYNC_PERIOD_TIME,	// units are microseconds range 210ns - 18.75s
	VPCD_CCLK_FREQ_SEL,		//	range ???
	VPCD_IMAGE_GEOMETRY,		// VPCD_IMAGE_GEOMETRY_TYPE
	VPCD_NUM_CAMERAS,		// range 1..3
	VPCD_TRIG_GLITCH_DETECTOR, // VS_ENABLE_TYPE
	VPCD_CCLK_STATIC_ENABLE,		// VS_ENABLE_TYPE
	VPCD_CCLK_STATIC_STATE,		// VS_LEVEL_TYPE
	VPCD_EXO_FILENAME,		// String holding the filename
	VPCD_TRIG_DIVIDE_FACTOR,	// Factor to scale trigger by
	VPCD_TRIG_DIVIDE_CONTROL, // Which trigger if any divider is applied to
	VPCD_USER_DEF_GEO_NAME,	// Name of user-defined geometry DLL
	VPCD_EXSYNC_START_LOCATION, // VPCD_EXSYNC_START_LOC_TYPE
	VPCD_EXSYNC_MIDPOINT_DELAY, // units are microseconds range 140ns - 18.75s
	VPCD_PRI_START_LOCATION,	// VPCD_PRI_START_LOC_TYPE
	VPCD_PRI_MIDPOINT_DELAY,   // units are microseconds range 140ns - 18.75s
	VPCD_PRI_END_LOCATION,	// VPCD_PRI_END_LOC_TYPE
	VPCD_TRIG_START_EVENT,	// VPCD_TRIG_MODE_TYPE
	VPCD_TRIG_STOP_EVENT,	// VPCD_TRIG_MODE_TYPE
	VPCD_SPATIAL_CORR_LINES,  // Number of lines between color sensor elements
	VPCD_SPATIAL_LEAD_COLOR, // Leading color when spatial correction used
	VPCD_HI_SPEED_ACQ_ENABLE,  // IFC_ENABLE_TYPE , to enable very high frame rate acquire




	VPCD_PARAM_END_MARKER
} VPCD_PARAMS_TYPE;


typedef enum VPCD_PGRPS_TYPE {
	VPCD_PGRP_EXSYNC_OUTPUT=VS_PGRP_MOD_PECULIAR_BASE,
	VPCD_PGRP_PRI_OUTPUT

} VPCD_PGRPS_TYPE;

#define VPCD_PGRP_EXSYNC_OUTPUT_MASK	PGRP_ID_TO_MASK(VPCD_PGRP_EXSYNC_OUTPUT)
#define VPCD_PGRP_PRI_OUTPUT_MASK	PGRP_ID_TO_MASK(VPCD_PGRP_PRI_OUTPUT)


#define VPCD_NUM_PARAMS (GEN_PARAM_END_MARKER+VPCD_PARAM_END_MARKER-VPCD_PECULIAR_PARAM_BASE)



#endif // !defined(AFX_PCDCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)