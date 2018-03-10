/******************************************************************************
 *
 * MODULE   
 *		PCDCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pcdcam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:40a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCDig class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCDCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_PCDCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>

#define PCD_NUM_LUT_ENTRIES 0x10000

typedef enum {
	PCD_DIFFERENTIAL_TRIG,
	PCD_TTL_TRIG,
	PCD_OPTO_COUPLED_TRIG
} PCD_TRIG_SRC_TYPE; 

typedef enum {
	PCD_TMODE_DISABLE=0,
	PCD_TMODE_HWTRIG0_ASSERT=2,
	PCD_TMODE_HWTRIG0_DEASSERT=3,
	PCD_TMODE_HWTRIG1_ASSERT=4,
	PCD_TMODE_HWTRIG1_DEASSERT=5,
	PCD_TMODE_SWTRIG0=6,
	PCD_TMODE_SWTRIG1=7,

} PCD_TRIG_MODE_TYPE;

typedef enum {
	PCD_MULTI_INPUT_FIELD,
	PCD_MULTI_INPUT_VALID_DATA
} PCD_MULTI_INPUT_TYPE;

typedef enum {
	PCD_EXSYNC_FREE_RUNNING,
	PCD_EXSYNC_TRIG1, 
	PCD_EXSYNC_TRIG2,
	PCD_EXSYNC_SOFT_TRIG, 
	PCD_EXSYNC_SOFT_TRIG2, 
	PCD_EXSYNC_VB_TRIG
} PCD_EXSYNC_MODE_TYPE;


typedef enum {
	PCD_1CHAN_L2R,				// |A,A,A,..........A,A|
	PCD_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	PCD_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	PCD_2CHAN_SEP_TAP_R2L,		// 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|            <=A|            <=B|
	PCD_4CHAN_SEP_TAP_L2R,		// 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |D=>    |
	PCD_4CHAN_SEP_TAP_R2L,		// 4 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|    <=A|    <=B|    <=C|    <=D|
	PCD_4CHAN_2SEG_INTERLEAVED,// 4 Taps,2 Segments, each interleaved		|A,B,A,B,...,A,B|C,D,C,D,...,C,D|
	PCD_4CHAN_INTERLEAVE_CONVERGE,//4 Taps,2 Segments converge, interleaved	|A,B,A,B,=>     |     <= C,D,C,D|
	PCD_2CHAN_SEP_TAP_CONVERGE,	// |A =>   |    <= B|
	PCD_SEP_QUAD_TAP_CONVERGE,  // 4TAPS - 4 QUADRANTS
	PCD_2TAP_INTERLINE_A_EVEN,			// Tap A even lines Tap B odd lines
	PCD_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines
	PCD_3CHAN_SEP_TAP_L2R,		// 3 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |
	PCD_USER_DEFINED_GEO,		// a user-defined geometry

	PCD_NUM_GEOMETRY_KINDS,

	PCD_INVALID_GEOMETRY=-1

} PCD_IMAGE_GEOMETRY_TYPE;

typedef enum {
	PCD_DISABLE_TRIG_DIVIDE=0,
	PCD_DIVIDE_TRIG_0=2,
	PCD_DIVIDE_TRIG_1=3
} PCD_DIVIDE_CTL_TYPE;

typedef enum {
	PCD_EXSYNC_START_CYCLE_END,
	PCD_EXSYNC_START_CYCLE_BEGIN,
	PCD_EXSYNC_START_MIDPOINT
} PCD_EXSYNC_START_LOC_TYPE;

typedef enum {
	PCD_PRI_START_CYCLE_BEGIN,
	PCD_PRI_START_MIDPOINT,
	PCD_PRI_START_CYCLE_END
} PCD_PRI_START_LOC_TYPE;

typedef enum {
	PCD_PRI_END_AT_LEN_BEGIN,
	PCD_PRI_END_AT_LEN_END,
	PCD_PRI_END_IS_START_DEPEND,
} PCD_PRI_END_LOC_TYPE;


#include <PCDig.h>

#define PCD_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x1000*PCD_PCI_DEVICE_ID)



typedef enum {
	PCD_MULTI_ENABLE=PCD_PECULIAR_PARAM_BASE,			// IFC_ENABLE_TYPE
	PCD_MULTI_POLARITY, 		// IFC_POLARITY_TYPE

	PCD_MULTI_INPUT_MODE,		// IFC_MULTI_INPUT_TYPE

	PCD_PCLK_POLARITY, 		// IFC_EDGE_TYPE

	PCD_MULTI_OUTPUT_ENABLE,	// IFC_ENABLE_TYPE
	PCD_USE_EXT_MULTI,		// IFC_ENABLE_TYPE
	PCD_RETIME_ENABLE,		// IFC_ENABLE_TYPE

	PCD_RETIME_POLARITY, 		// IFC_EDGE_TYPE

	PCD_CAM3_ENABLE,			// IFC_ENABLE_TYPE

	PCD_EXSYNC_ENABLE,		// IFC_ENABLE_TYPE

	PCD_EXSYNC_POLARITY,		// IFC_POLARITY_TYPE

	PCD_EXSYNC_MODE,			// IFC_EXSYNC_MODE

	PCD_PRI_ENABLE,			// IFC_ENABLE_TYPE
	PCD_PRI_POLARITY,			// IFC_POLARITY_TYPE
	
	PCD_CAM_MODE_CTL,			// range 0..15
	PCD_EXT_SYNC_TIME,		// units are microseconds range 140ns - 572us
	PCD_EXT_SYNC_PERIOD_TIME,	// units are microseconds range 210ns - 18.75s
	PCD_CCLK_FREQ_SEL,		//	range ???
	PCD_IMAGE_GEOMETRY,		// PCD_IMAGE_GEOMETRY_TYPE
	PCD_NUM_CAMERAS,		// range 1..3
	PCD_TRIG_GLITCH_DETECTOR, // IFC_ENABLE_TYPE
	PCD_CCLK_STATIC_ENABLE,		// IFC_ENABLE_TYPE
	PCD_CCLK_STATIC_STATE,		// IFC_LEVEL_TYPE
	PCD_EXO_FILENAME,		// String holding the filename
	PCD_TRIG_DIVIDE_FACTOR,	// Factor to scale trigger by
	PCD_TRIG_DIVIDE_CONTROL, // Which trigger if any divider is applied to
	PCD_USER_DEF_GEO_NAME,	// Name of user-defined geometry DLL
	PCD_EXSYNC_START_LOCATION, // PCD_EXSYNC_START_LOC_TYPE
	PCD_EXSYNC_MIDPOINT_DELAY, // units are microseconds range 140ns - 18.75s
	PCD_PRI_START_LOCATION,	// PCD_PRI_START_LOC_TYPE
	PCD_PRI_MIDPOINT_DELAY,   // units are microseconds range 140ns - 18.75s
	PCD_PRI_END_LOCATION,	// PCD_PRI_END_LOC_TYPE
	PCD_TRIG_START_EVENT,	// PCD_TRIG_MODE_TYPE
	PCD_TRIG_STOP_EVENT,	// PCD_TRIG_MODE_TYPE
	PCD_SPATIAL_CORR_LINES,  // Number of lines between color sensor elements
	PCD_SPATIAL_LEAD_COLOR, // Leading color when spatial correction used
	PCD_HI_SPEED_ACQ_ENABLE,  // IFC_ENABLE_TYPE , to enable very high frame rate acquire




	PCD_PARAM_END_MARKER
} PCD_PARAMS_TYPE;


typedef enum {
	PCD_PGRP_EXSYNC_OUTPUT=IFC_PGRP_MOD_PECULIAR1,
	PCD_PGRP_PRI_OUTPUT

} PCD_PGRPS_TYPE;

#define PCD_PGRP_EXSYNC_OUTPUT_MASK	PGRP_ID_TO_MASK(PCD_PGRP_EXSYNC_OUTPUT)
#define PCD_PGRP_PRI_OUTPUT_MASK	PGRP_ID_TO_MASK(PCD_PGRP_PRI_OUTPUT)


#define PCD_NUM_PARAMS (GEN_PARAM_END_MARKER+PCD_PARAM_END_MARKER-PCD_PECULIAR_PARAM_BASE)


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCDCam : public CICamera  
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
	CPCDCam(CPCDig *pcd,DWORD port);
	virtual ~CPCDCam();
	CPCDig *m_pcd;
};
#endif

#endif // !defined(AFX_PCDCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
