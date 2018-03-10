/******************************************************************************
 *
 * MODULE   
 *		LnkCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/lnkcam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/30/04 11:32a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCLink class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_LNKCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_LNKCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>

#define LNK_MIN_NUM_LUT_ENTRIES		0x10000
#define LNK_MIN_SCATTER_LIST_SLOTS	0x8000
#define LNK_MIN_NUM_OCT_ENTRIES		0x10000



typedef enum {
	LNK_DIFFERENTIAL_TRIG,
	LNK_TTL_TRIG,
	LNK_OPTO_COUPLED_TRIG
} LNK_TRIG_SRC_TYPE; 

typedef enum {
	LNK_TMODE_DISABLE=0,
	LNK_TMODE_HWTRIG0_ASSERT=2,
	LNK_TMODE_HWTRIG0_DEASSERT=3,
	LNK_TMODE_HWTRIG1_ASSERT=4,
	LNK_TMODE_HWTRIG1_DEASSERT=5,
	LNK_TMODE_SWTRIG0=6,
	LNK_TMODE_SWTRIG1=7,

} LNK_TRIG_MODE_TYPE;

typedef enum {
	LNK_DVAL_INPUT_FIELD,
	LNK_DVAL_INPUT_VALID_DATA
} LNK_DVAL_INPUT_TYPE;

typedef enum {
	LNK_EXSYNC_FREE_RUNNING,
	LNK_EXSYNC_TRIG1, 
	LNK_EXSYNC_TRIG2,
	LNK_EXSYNC_SOFT_TRIG, 
	LNK_EXSYNC_SOFT_TRIG2, 
	LNK_EXSYNC_VB_TRIG
} LNK_EXSYNC_MODE_TYPE;


typedef enum {
	LNK_1CHAN_L2R,				// |A,A,A,..........A,A|
	LNK_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	LNK_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	LNK_2CHAN_SEP_TAP_R2L,		// 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|            <=A|            <=B|
	LNK_4CHAN_SEP_TAP_L2R,		// 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |D=>    |
	LNK_2CHAN_SEP_TAP_CONVERGE=8,	// |A =>   |    <= B|
	LNK_2TAP_INTERLINE_A_EVEN=10,			// Tap A even lines Tap B odd lines
	LNK_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines
	LNK_3CHAN_SEP_TAP_L2R,		// 3 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |
	LNK_USER_DEFINED_GEO,		// a user-defined geometry

	LNK_NUM_GEOMETRY_KINDS,

	LNK_INVALID_GEOMETRY=-1

} LNK_IMAGE_GEOMETRY_TYPE;

typedef enum {
	LNK_DISABLE_TRIG_DIVIDE=0,
	LNK_DIVIDE_TRIG_0=2,
	LNK_DIVIDE_TRIG_1=3
} LNK_DIVIDE_CTL_TYPE;


typedef enum {
	LNK_PRI_END_IS_START_DEPEND,  // No extension of PRI beyond the active setting
	LNK_PRI_END_AT_LEN_BEGIN,
	LNK_PRI_END_AT_LEN_END
} LNK_PRI_END_LOC_TYPE;

typedef enum {
	LNK_CAM_BYTE_0,
	LNK_CAM_BYTE_1,
	LNK_CAM_BYTE_2,
	LNK_CAM_BYTE_ZERO
} LNK_LUT_BYTE_INPUT;


typedef enum {
	LNK_CCTL_FIXED_LOW,
	LNK_CCTL_FIXED_HIGH,
	LNK_CCTL_EXSYNC,
	LNK_CCTL_PRI

} LNK_CAM_CTL_SELECT_TYPE;



typedef enum {
	LNK_CHAN_A=1,
	LNK_CHAN_B=2,
	LNK_CHAN_C=4,
	LNK_CHAN_D=8

} LNK_CHAN_ENUM;




#ifdef __cplusplus
class IFC_EXT_API CLinkCam;
#endif

#include <PCLink.h>

#define LNK_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x1000*LNK_PCI_DEVICE_ID)



typedef enum {
	LNK_DVAL_ENABLE=LNK_PECULIAR_PARAM_BASE,		// IFC_ENABLE_TYPE
	LNK_DVAL_POLARITY,			// IFC_EDGE_TYPE
	LNK_DVAL_INPUT_MODE,	// LNK_DVAL_INPUT_TYPE

	LNK_SPR_ENABLE,			// IFC_ENABLE_TYPE
	LNK_SPR_POLARITY,			// IFC_POLARITY_TYPE

	LNK_EXSYNC_ENABLE,		// IFC_ENABLE_TYPE

	LNK_EXSYNC_POLARITY,		// IFC_POLARITY_TYPE

	LNK_EXSYNC_MODE,			// IFC_EXSYNC_MODE

	LNK_PRI_ENABLE,			// IFC_ENABLE_TYPE
	LNK_PRI_POLARITY,			// IFC_POLARITY_TYPE
	
	LNK_EXT_SYNC_PERIOD_TIME,	// units are microseconds range 140ns - 18.75s
	LNK_EXT_SYNC_OFFSET_TIME, // units are microseconds range 0 - 18.75s , 0.07us granularity
	LNK_EXT_SYNC_ACTIVE_TIME, // units are microseconds range 0.07us - 18.75s , 0.07us granularity
	LNK_IMAGE_GEOMETRY,		// LNK_IMAGE_GEOMETRY_TYPE
	LNK_NUM_CAMERAS,		// range 1..3
	LNK_TRIG_GLITCH_DETECTOR, // IFC_ENABLE_TYPE
	LNK_EXO_FILENAME,		// String holding the filename
	LNK_TRIG_DIVIDE_FACTOR,	// Factor to scale trigger by
	LNK_TRIG_DIVIDE_CONTROL, // Which trigger if any divider is applied to
	LNK_USER_DEF_GEO_NAME,	// Name of user-defined geometry DLL
	LNK_PRI_OFFSET_TIME,	// units are microseconds range 0 - 18.75s , 0.07us granularity
	LNK_PRI_ACTIVE_TIME,   // units are microseconds range 0.07us - 18.75s , 0.07us granularity
	LNK_PRI_END_LOCATION,	// LNK_PRI_END_LOC_TYPE
	LNK_LUT0_LOW_INPUT,		// 0-3 LNK_LUT_BYTE_INPUT
	LNK_LUT0_HIGH_INPUT,	// 0-3 LNK_LUT_BYTE_INPUT
	LNK_LUT1_LOW_INPUT,		// 0-3 LNK_LUT_BYTE_INPUT
	LNK_LUT1_HIGH_INPUT,	// 0-3 LNK_LUT_BYTE_INPUT
	LNK_CAM_CTL1_SIGNAL,	// which timing output signal is applied to Camera Control 1
	LNK_CAM_CTL2_SIGNAL,	// which timing output signal is applied to Camera Control 2
	LNK_CAM_CTL3_SIGNAL,	// which timing output signal is applied to Camera Control 3
	LNK_CAM_CTL4_SIGNAL,	// which timing output signal is applied to Camera Control 4
	LNK_SPATIAL_CORR_LINES,  // Number of lines between color sensor elements
	LNK_SPATIAL_LEAD_COLOR, // Leading color when spatial correction used
	LNK_TRIG_START_EVENT,	// LNK_TRIG_MODE_TYPE
	LNK_TRIG_STOP_EVENT,	// LNK_TRIG_MODE_TYPE
	LNK_FEN_PULSE,		// IFC_ENABLE_TYPE
	LNK_LOW_LATENCY_READ, 	// IFC_ENABLE_TYPE
	LNK_TRIG_CYCLE_LATCH_TRIG, 	// IFC_ENABLE_TYPE



	LNK_PARAM_END_MARKER
} LNK_PARAMS_TYPE;

#define LNK_FFC_SETTING_DLG_ID LNK_PECULIAR_PARAM_BASE+0x200


typedef enum {
	LNK_PGRP_EXSYNC_OUTPUT=IFC_PGRP_MOD_PECULIAR1,
	LNK_PGRP_PRI_OUTPUT,
	LNK_PGRP_LUT_INPUT,
	LNK_PGRP_CAM_CTL_ASSIGNMENT

} LNK_PGRPS_TYPE;

#define LNK_PGRP_EXSYNC_OUTPUT_MASK			PGRP_ID_TO_MASK(LNK_PGRP_EXSYNC_OUTPUT)
#define LNK_PGRP_PRI_OUTPUT_MASK			PGRP_ID_TO_MASK(LNK_PGRP_PRI_OUTPUT)
#define LNK_PGRP_LUT_INPUT_MASK				PGRP_ID_TO_MASK(LNK_PGRP_LUT_INPUT)
#define LNK_PGRP_CAM_CTL_ASSIGNMENT_MASK	PGRP_ID_TO_MASK(LNK_PGRP_CAM_CTL_ASSIGNMENT)


#define LNK_NUM_PARAMS (GEN_PARAM_END_MARKER+LNK_PARAM_END_MARKER-LNK_PECULIAR_PARAM_BASE)


#define LNK_SAMPLE_SZ_IMAGE_HEIGHT 0x80000000	// Use the image height for the number of lines in a sample
#define LNK_PIXEL_MAX_VAL 0x80000000		// The max value a pixel can assume for the current pixel size
#define LNK_ALL_OFFSET_VALUES 0x80000000
#define LNK_ALL_GAIN_VALUES 0x80000000
#define LNK_MIN_SAMPLE_VALUE 0xffffffff




#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CLinkCam : public CICamera  
{
public:


	virtual void UpdateParams();
	virtual BOOL SetLutFunction(LUTID_TYPE lutID,IFCLUTFUNC func,DWORD *constants,LUT_PORTION_TYPE lutPortion=LUT_INTELLI_WIDTH);
	virtual void ReadLutBuf(LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void WriteLutBuf(LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void GetLUTCaps(LPLUTCAP caps);
	virtual void SetLutPathPage(LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum);
	virtual void SetWindowGen(short x, short y, short dx, short dy);
	virtual BOOL SetCameraType(pSTRING camName,BOOL updateHW=TRUE);
	virtual pSTRING GetStdCameraType(IFC_STD_CAM_TYPE stdCamType);
	virtual void GetAttr(LPCAM_ATTR lpAttr, BOOL zoomCorrected=TRUE);
	virtual ACQ_PARAMS_TYPE GetParamIndex(ACQ_PARAMS_TYPE RawID);
	virtual BOOL GetUartPortName(char *Name, DWORD uartIndex=0);
	BOOL ColorSpatialCorrection(BYTE *framePtr, DWORD linesBetweenSensors, BOOL leadingColorRed, DWORD width=0, DWORD height=0);


	CLinkCam(CPCLink *pcl,DWORD port);
	virtual ~CLinkCam();
	CPCLink *m_lnk;
};
#endif

#endif // !defined(AFX_PCLCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
