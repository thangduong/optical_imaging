/******************************************************************************
 *
 * MODULE   
 *		PCLCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pclcam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/31/03 4:51p $
 *
 * ABSTRACT  
 *		IFC interface of the CPCLine class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCLCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_PCLCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>

#define PCL_NUM_LUT_ENTRIES 0x10000

#define PCL_RLE_TAG_LUT0 INPUT_LUT3
#define PCL_RLE_TAG_LUT1 INPUT_LUT4


typedef enum {
	PCL_DIFFERENTIAL_TRIG,
	PCL_TTL_TRIG,
	PCL_OPTO_COUPLED_TRIG
} PCL_TRIG_SRC_TYPE; 

typedef enum {
	PCL_TMODE_DISABLE=0,
	PCL_TMODE_HWTRIG0_ASSERT=2,
	PCL_TMODE_HWTRIG0_DEASSERT=3,
	PCL_TMODE_HWTRIG1_ASSERT=4,
	PCL_TMODE_HWTRIG1_DEASSERT=5,
	PCL_TMODE_SWTRIG0=6,
	PCL_TMODE_SWTRIG1=7,

} PCL_TRIG_MODE_TYPE;

typedef enum {
	PCL_MULTI_INPUT_FIELD,
	PCL_MULTI_INPUT_VALID_DATA
} PCL_MULTI_INPUT_TYPE;

typedef enum {
	PCL_EXSYNC_FREE_RUNNING,
	PCL_EXSYNC_TRIG1, 
	PCL_EXSYNC_TRIG2,
	PCL_EXSYNC_SOFT_TRIG, 
	PCL_EXSYNC_SOFT_TRIG2, 
	PCL_EXSYNC_VB_TRIG
} PCL_EXSYNC_MODE_TYPE;


typedef enum {
	PCL_1CHAN_L2R,				// |A,A,A,..........A,A|
	PCL_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	PCL_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	PCL_2CHAN_SEP_TAP_R2L,		// 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|            <=A|            <=B|
	PCL_4CHAN_SEP_TAP_L2R,		// 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |D=>    |
	PCL_4CHAN_SEP_TAP_R2L,		// 4 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|    <=A|    <=B|    <=C|    <=D|
	PCL_4CHAN_2SEG_INTERLEAVED,// 4 Taps,2 Segments, each interleaved		|A,B,A,B,...,A,B|C,D,C,D,...,C,D|
	PCL_4CHAN_INTERLEAVE_CONVERGE,//4 Taps,2 Segments converge, interleaved	|A,B,A,B,=>     |     <= C,D,C,D|
	PCL_2CHAN_SEP_TAP_CONVERGE,	// |A =>   |    <= B|
	PCL_SEP_QUAD_TAP_CONVERGE,  // 4TAPS - 4 QUADRANTS
	PCL_2TAP_INTERLINE_A_EVEN,			// Tap A even lines Tap B odd lines
	PCL_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines
	PCL_3CHAN_SEP_TAP_L2R,		// 3 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |
	PCL_USER_DEFINED_GEO,		// a user-defined geometry

	PCL_NUM_GEOMETRY_KINDS,

	PCL_INVALID_GEOMETRY=-1

} PCL_IMAGE_GEOMETRY_TYPE;

typedef enum {
	PCL_DISABLE_TRIG_DIVIDE=0,
	PCL_DIVIDE_TRIG_0=2,
	PCL_DIVIDE_TRIG_1=3
} PCL_DIVIDE_CTL_TYPE;


typedef enum {
	PCL_PRI_END_AT_LEN_BEGIN,
	PCL_PRI_END_AT_LEN_END,
	PCL_PRI_END_IS_START_DEPEND  // No extension of PRI beyond the active setting
} PCL_PRI_END_LOC_TYPE;

typedef enum {
	PCL_CAM_BYTE_0,
	PCL_CAM_BYTE_1,
	PCL_CAM_BYTE_2,
	PCL_CAM_BYTE_3
} PCL_LUT_BYTE_INPUT;


typedef enum {
	PCL_CHAN_A=1,
	PCL_CHAN_B=2,
	PCL_CHAN_C=4,
	PCL_CHAN_D=8

} PCL_CHAN_ENUM;


typedef struct {
	DWORD chan;
	DWORD index;

} PCL_TAP_INDEX_DESC;


typedef struct {
	float maxGain;
	DWORD maxOffset;

} PCL_FFC_ATTR;

typedef PCL_FFC_ATTR *LPPCL_FFC_ATTR;


class IFC_EXT_API CPCLCam;

#include <PCLine.h>

#define PCL_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x1000*PCL_PCI_DEVICE_ID)



typedef enum {
	PCL_MULTI_ENABLE=PCL_PECULIAR_PARAM_BASE,			// IFC_ENABLE_TYPE
	PCL_MULTI_POLARITY, 		// IFC_POLARITY_TYPE

	PCL_MULTI_INPUT_MODE,		// IFC_MULTI_INPUT_TYPE

	PCL_PCLK_POLARITY, 		// IFC_EDGE_TYPE

	PCL_MULTI_OUTPUT_ENABLE,	// IFC_ENABLE_TYPE
	PCL_USE_EXT_MULTI,		// IFC_ENABLE_TYPE
	PCL_RETIME_ENABLE,		// IFC_ENABLE_TYPE

	PCL_RETIME_POLARITY, 		// IFC_EDGE_TYPE

	PCL_CAM3_ENABLE,			// IFC_ENABLE_TYPE

	PCL_EXSYNC_ENABLE,		// IFC_ENABLE_TYPE

	PCL_EXSYNC_POLARITY,		// IFC_POLARITY_TYPE

	PCL_EXSYNC_MODE,			// IFC_EXSYNC_MODE

	PCL_PRI_ENABLE,			// IFC_ENABLE_TYPE
	PCL_PRI_POLARITY,			// IFC_POLARITY_TYPE
	
	PCL_CAM_MODE_CTL,			// range 0..15
	PCL_EXT_SYNC_PERIOD_TIME,	// units are microseconds range 140ns - 18.75s
	PCL_EXT_SYNC_OFFSET_TIME, // units are microseconds range 0 - 18.75s , 0.07us granularity
	PCL_EXT_SYNC_ACTIVE_TIME, // units are microseconds range 0.07us - 18.75s , 0.07us granularity
	PCL_CCLK_FREQ_SEL,		//	 units MHZ range 320khz - 100mhz
	PCL_IMAGE_GEOMETRY,		// PCL_IMAGE_GEOMETRY_TYPE
	PCL_NUM_CAMERAS,		// range 1..3
	PCL_TRIG_GLITCH_DETECTOR, // IFC_ENABLE_TYPE
	PCL_CCLK_STATIC_ENABLE,		// IFC_ENABLE_TYPE
	PCL_CCLK_STATIC_STATE,		// IFC_LEVEL_TYPE
	PCL_EXO_FILENAME,		// String holding the filename
	PCL_TRIG_DIVIDE_FACTOR,	// Factor to scale trigger by
	PCL_TRIG_DIVIDE_CONTROL, // Which trigger if any divider is applied to
	PCL_USER_DEF_GEO_NAME,	// Name of user-defined geometry DLL
	PCL_PRI_OFFSET_TIME,	// units are microseconds range 0 - 18.75s , 0.07us granularity
	PCL_PRI_ACTIVE_TIME,   // units are microseconds range 0.07us - 18.75s , 0.07us granularity
	PCL_PRI_END_LOCATION,	// PCL_PRI_END_LOC_TYPE
	PCL_LUT0_LOW_INPUT,		// 0-3 PCL_LUT_BYTE_INPUT
	PCL_LUT0_HIGH_INPUT,	// 0-3 PCL_LUT_BYTE_INPUT
	PCL_LUT1_LOW_INPUT,		// 0-3 PCL_LUT_BYTE_INPUT
	PCL_LUT1_HIGH_INPUT,	// 0-3 PCL_LUT_BYTE_INPUT
	PCL_SPATIAL_CORR_LINES,  // Number of lines between color sensor elements
	PCL_SPATIAL_LEAD_COLOR, // Leading color when spatial correction used
	PCL_TRIG_START_EVENT,	// PCL_TRIG_MODE_TYPE
	PCL_TRIG_STOP_EVENT,	// PCL_TRIG_MODE_TYPE


	PCL_PARAM_END_MARKER
} PCL_PARAMS_TYPE;

#define PCL_FFC_SETTING_DLG_ID PCL_PECULIAR_PARAM_BASE+0x200


typedef enum {
	PCL_PGRP_EXSYNC_OUTPUT=IFC_PGRP_MOD_PECULIAR1,
	PCL_PGRP_PRI_OUTPUT,
	PCL_PGRP_LUT_INPUT

} PCL_PGRPS_TYPE;

#define PCL_PGRP_EXSYNC_OUTPUT_MASK	PGRP_ID_TO_MASK(PCL_PGRP_EXSYNC_OUTPUT)
#define PCL_PGRP_PRI_OUTPUT_MASK	PGRP_ID_TO_MASK(PCL_PGRP_PRI_OUTPUT)
#define PCL_PGRP_LUT_INPUT_MASK		PGRP_ID_TO_MASK(PCL_PGRP_LUT_INPUT)


#define PCL_NUM_PARAMS (GEN_PARAM_END_MARKER+PCL_PARAM_END_MARKER-PCL_PECULIAR_PARAM_BASE)


#define PCL_SAMPLE_SZ_IMAGE_HEIGHT 0x80000000	// Use the image height for the number of lines in a sample
#define PCL_PIXEL_MAX_VAL 0x80000000		// The max value a pixel can assume for the current pixel size
#define PCL_ALL_OFFSET_VALUES 0x80000000
#define PCL_ALL_GAIN_VALUES 0x80000000
#define PCL_MIN_SAMPLE_VALUE 0xffffffff


#ifdef __cplusplus
class IFC_EXT_API CPCLCam : public CICamera  
{
public:
	BOOL FlatFieldSettingsDlg();
	LPPCL_FFC_ATTR GetFlatFieldAttr(LPPCL_FFC_ATTR ffcAttr);

	BOOL SetFlatFieldOffset(DWORD mapToValue=PCL_MIN_SAMPLE_VALUE, DWORD firstSampleY=0, DWORD sampleNumLines=PCL_SAMPLE_SZ_IMAGE_HEIGHT);
	BOOL SetFlatFieldGain(DWORD mapToValue=PCL_PIXEL_MAX_VAL,DWORD firstSampleY=0, DWORD sampleNumLines=PCL_SAMPLE_SZ_IMAGE_HEIGHT);

	BOOL WriteFlatFieldOffsets(DWORD *offsets,DWORD startIndex,DWORD numOffsets);
	BOOL WriteFlatFieldOffsets(DWORD offset=0,DWORD startIndex=0,DWORD numOffsets=PCL_ALL_OFFSET_VALUES);
	BOOL ReadFlatFieldOffsets(DWORD *offsets,DWORD startIndex,DWORD numOffsets);
	BOOL WriteFlatFieldGains(float *gains,DWORD startIndex,DWORD numGains);
	BOOL WriteFlatFieldGains(float gain=1.0,DWORD startIndex=0,DWORD numGains=PCL_ALL_GAIN_VALUES);
	BOOL ReadFlatFieldGains(float *gains,DWORD startIndex,DWORD numGains);

	BOOL SaveFlatField( LPTSTR FileName );
	BOOL ReadFlatField( LPTSTR FileName, BOOL EnableFFC=TRUE );


	BOOL GetPixelTapDesc(DWORD x, DWORD dwBitsPerPixel, PCL_IMAGE_GEOMETRY_TYPE geometry, DWORD camWidth, PCL_TAP_INDEX_DESC *desc);

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

	BOOL ColorSpatialCorrection(BYTE *framePtr, DWORD linesBetweenSensors, BOOL leadingColorRed, DWORD width=0, DWORD height=0);
	CPCLCam(CPCLine *pcl,DWORD port);
	virtual ~CPCLCam();
	CPCLine *m_pcl;
};
#endif

#endif // !defined(AFX_PCLCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
