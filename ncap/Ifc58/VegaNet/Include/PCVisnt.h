/******************************************************************************
 *
 * MODULE   
 *		PCVisnt.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/PCVisnt.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/06/01 11:47a $
 *
 * ABSTRACT  
 *		IFC interface of the CAmV class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCVISN_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_PCVISN_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#define VPCV_NUM_LUT_ENTRIES 256
#define NUM_VPCV_CAM_MODULES 4

#define VPCV_PIXEL_SIZE 8		// In Bits

#define VPCV_NREF_MIN 0.0		// NREF Minimum Value in Volts
#define VPCV_NREF_MAX 1.2		// NREF Maximum Value in Volts
#define VPCV_NREF_STP (VPCV_NREF_MAX/256.0)	// NREF Step in Volts
#define VPCV_NREF_RBV 0			// NREF Register Base Value

#define VPCV_PREF_MIN 0.0		// PREF Minimum Value in Volts
#define VPCV_PREF_MAX 2.0		// PREF Maximum Value in Volts
#define VPCV_PREF_STP (VPCV_PREF_MAX/256.0)	// PREF Step in Volts
#define VPCV_PREF_RBV 0			// PREF Register Base Value



typedef enum VPCV_FLD_SRC_TYPE {
	VPCV_VIDEO_STRIPPED_FLD,
	VPCV_LEN_AND_FEN_DETECTED_FLD
} VPCV_FLD_SRC_TYPE;


#define VPCV_PECULIAR_PARAM_BASE MOD_PECULIAR_PARAM_BASE

typedef enum VPCV_PARAMS_TYPE {
	VPCV_FIELD_SRC = VSP_MOD_UNIQUE_BASE,	// IFC_ENABLE_TYPE
	VPCV_SKIP_FIELD_MODE,
	VPCV_FRAME_RESET_ON_VSYNC_OUTPUT,
	VPCV_LOW_PASS_FILTER_EN,
	VPCV_FIELD_SHIFT,
	VPCV_PTG_VSYNC_OUT_EN,
	VPCV_CLAMP_SOURCE,
	VPCV_NREF_CONTROL,
	VPCV_PREF_CONTROL,
	VPCV_EDONPISHA_MODE,
	VPCV_INPORT_POLARITY,
	VPCV_INPORT,
	VPCV_OUTPORT,
	VPCV_YCRCB_MONO_ACQ,

	VPCV_PARAM_END_MARKER

} VPCV_PARAMS_TYPE;

typedef enum VPCV_PARAM_GROUP_TYPE {
	VPCV_PGRP_CLAMP_SETTINGS=VS_PGRP_MOD_PECULIAR1
} VPCV_PARAM_GROUP_TYPE;

#define VPCV_PGRP_CLAMP_SETTINGS_MASK	PGRP_ID_TO_MASK(VPCV_PGRP_CLAMP_SETTINGS)


#define VPCV_NUM_PARAMS (GEN_PARAM_END_MARKER+VPCV_PARAM_END_MARKER-VPCV_PECULIAR_PARAM_BASE)


#endif // !defined(AFX_PCVISN_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
