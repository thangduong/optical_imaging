/******************************************************************************
 *
 * MODULE   
 *		Pv2Cam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pv2cam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 6/09/04 10:52a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCVision2 class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2002 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_P2VCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_P2VCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __cplusplus
class CP2VCam;
#endif

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>


typedef enum {
	P2V_VIDEO_STD_NTSC	=1,
	P2V_VIDEO_STD_PAL,
	P2V_VIDEO_STD_SECAM,
	P2V_VIDEO_STD_NONE
} P2V_VIDEO_STANDARD_TYPE;

typedef enum {
	P2V_FIELD_PROCESS_ALL	=1,
	P2V_FIELD_PROCESS_ODD_ONLY,
	P2V_FIELD_PROCESS_EVEN_ONLY

} P2V_FIELD_PROCESS_TYPE;


typedef enum {
	P2V_LOW_IS_ODD,
	P2V_LOW_IS_EVEN
} P2V_PWG_FLD_POL_TYPE;

typedef enum {
	P2V_FLD_SRC_SYNC_STRIPPER,
	P2V_FLD_SRC_GENERATED_BASED_ON_H_AND_V_SYNC
} P2V_FLD_SRC_TYPE;



typedef enum {
	P2V_SYNC_COMPOSITE_VIDEO=1,
	P2V_SYNC_COMPOSITE_SYNC=2,
	P2V_SYNC_SEPARATE_SYNC=3,
	P2V_SYNC_INTERNAL_SYNC=4,
	P2V_SYNC_RED=5,
	P2V_SYNC_GREEN,
	P2V_SYNC_BLUE

} P2V_SYNC_SRC_TYPE;

typedef enum {
	P2V_SYNC_STRIPPER_BACK_PORCH,
	P2V_PROGRAMMABLE
} P2V_CLAMP_SRC_TYPE;

#define P2V_NUM_LUT_ENTRIES 0x100
#define P2V_NUM_LUT_CHANNELS 3


typedef enum {
	P2V_CREF_HSYNC_FROM_STRIPPER,
	P2V_CREF_TIMING_MODE_DEPENDANT	

} P2V_PRGM_CLAMP_REF_POINT_TYPE;


typedef enum {
	P2V_PIXEL_CLOCK_INTERNAL,
	P2V_PIXEL_CLOCK_EXTERNAL

} P2V_PIXEL_CLOCK_TYPE;

typedef enum {
	P2V_UART_PORT_AUTO,
	P2V_UART_PORT_CON1,	
	P2V_UART_PORT_CON2
} P2V_UART_PORT_TYPE;

typedef enum {
	P2V_FALLING_EDGE,
	P2V_RISING_EDGE,
	P2V_ACTIVE_LOW,
	P2V_ACTIVE_HIGH


} P2V_TRIG_POL_TYPE;

typedef enum {
	P2V_SINGLE_TAP,
	P2V_2TAP_ILACE_TOGGLE,
	P2V_2TAP_ILACE_FIXED
} P2V_MULTITAP_MODE_TYPE;

typedef enum {
	P2V_PLANAR_DISABLED,
	P2V_PLANAR_HORZ,
	P2V_PLANAR_VERT
} P2V_PLANAR_MODE_TYPE;

#define P2V_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x3000 )


#include <PCVision2.h>




typedef enum {

	P2V_CLAMP_START = P2V_PECULIAR_PARAM_BASE,
	P2V_CLAMP_END,
	P2V_FIELD_PROCESS,
	P2V_MASTER_HSYNC,
	P2V_VS_PULSE_ENABLE,
	P2V_VS_PULSE_OFFSET,
	P2V_VS_PULSE_DURATION,
	P2V_LOW_PASS_FILTER,
	P2V_SYNC_SOURCE,
	P2V_ADD_VSYNC_TO_FRAME_RESET,
	P2V_ADD_FRAME_RESET_TO_VSYNC,
	P2V_SELECT_UART_PORT,
	P2V_MULTITAP_MODE,
	P2V_HORZ_FRONT_PORCH,
	P2V_HORZ_BACK_PORCH,
	P2V_VSYNC_WAIT_COUNT,
	P2V_VSYNC_ALIGN_ON_HS,
	P2V_FRAME_RESET_ALIGN_ON_HS,
	P2V_STROBE_ALIGN_ON_HS,
	P2V_VSYNC_OUT_ENABLE,
	P2V_SYNC_OUT_ALL_CONN,
	P2V_PLL_GAIN,
	P2V_PLANAR_MODE,
	P2V_PRECLAMP_ENABLE,
	P2V_VIDEO_INPUT_CHANNEL,

	P2V_PARAM_END_MARKER
} P2V_PARAMS_TYPE;


typedef enum {
	P2V_IN_CHAN_STD_FOR_PORT,
	P2V_IN_CHAN_1,
	P2V_IN_CHAN_2,
	P2V_IN_CHAN_3

} P2V_VIDEO_INPUT_CHANNEL_TYPE;

typedef enum {
	P2V_VSYNC_DISABLE,
	P2V_VSYNC_LINE_WIDTH,
	P2V_VSYNC_TIME_WIDTH,
} P2V_VSYNC_MODE_TYPE;

typedef enum {
	 P2V_LPF_6_5_MHZ,
	 P2V_LPF_12_MHZ,
	 P2V_LPF_BYPASS,
} P2V_LPF_TYPE;


typedef enum {
	P2V_PGRP_CLAMP_SETTINGS=IFC_PGRP_MOD_PECULIAR1,
	P2V_PGRP_HSYNC_SETTINGS=IFC_PGRP_MOD_PECULIAR2,
	P2V_PGRP_VSYNC_SETTINGS=IFC_PGRP_MOD_PECULIAR3,
	P2V_PGRP_PIX_CLK_SETTINGS=IFC_PGRP_MOD_PECULIAR4,
	P2V_PGRP_VS_PULSE_SETTINGS=IFC_PGRP_MOD_PECULIAR5,
	P2V_PGRP_WEN_SETTINGS=IFC_PGRP_MOD_PECULIAR6,

} P2V_PARAM_GROUP_TYPE;




#define P2V_PGRP_CLAMP_SETTINGS_MASK	PGRP_ID_TO_MASK(P2V_PGRP_CLAMP_SETTINGS)
#define P2V_PGRP_HSYNC_SETTINGS_MASK	PGRP_ID_TO_MASK(P2V_PGRP_HSYNC_SETTINGS)
#define P2V_PGRP_VSYNC_SETTINGS_MASK	PGRP_ID_TO_MASK(P2V_PGRP_VSYNC_SETTINGS)
#define P2V_PGRP_PIX_CLK_SETTINGS_MASK	PGRP_ID_TO_MASK(P2V_PGRP_PIX_CLK_SETTINGS)
#define P2V_PGRP_VS_PULSE_SETTINGS_MASK	PGRP_ID_TO_MASK(P2V_PGRP_VS_PULSE_SETTINGS)
#define P2V_PGRP_WEN_SETTINGS_MASK		PGRP_ID_TO_MASK(P2V_PGRP_WEN_SETTINGS)

#define P2V_NUM_PARAMS (GEN_PARAM_END_MARKER+P2V_PARAM_END_MARKER-P2V_PECULIAR_PARAM_BASE)


#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CP2VCam : public CICamera  
{
public:

	virtual int Freeze(HIFCGRAB grabID=NULL);
	virtual void UpdateParams();
	virtual void SetAcqParam(ACQ_PARAMS_TYPE paramID, double value,DWORD index=0);
	virtual ACQ_PARAMS_TYPE GetFirstParam(DWORD paramGroupMask=IFC_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE);
	virtual ACQ_PARAMS_TYPE GetNextParam(ACQ_PARAMS_TYPE paramID,DWORD paramGroupMask=IFC_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE);
	virtual BOOL SetLutFunction(LUTID_TYPE lutID,IFCLUTFUNC func,DWORD *constants,LUT_PORTION_TYPE lutPortion=LUT_INTELLI_WIDTH);
	virtual void ReadLutBuf(LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void WriteLutBuf(LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD);
	virtual void GetLUTCaps(LPLUTCAP caps);
	virtual void SetLutPathPage(LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum) {return;};
	virtual void SetWindowGen(short x, short y, short dx, short dy);
	virtual BOOL SetCameraType(pSTRING camName,BOOL updateHW=TRUE);
	virtual void GetAttr(LPCAM_ATTR lpAttr, BOOL zoomCorrected=TRUE);
	virtual ACQ_PARAMS_TYPE GetParamIndex(ACQ_PARAMS_TYPE RawID);
	virtual void AddApplicabilityFuncs(void);
	virtual ACQ_PARAMS_TYPE GetParamAlias(ACQ_PARAMS_TYPE paramID);
	virtual pSTRING GetStdCameraType(IFC_STD_CAM_TYPE stdCamType);
	virtual BOOL GetUartPortName(char *Name, DWORD uartIndex=0);


	virtual BYTE *GetDisplayAddr(DWORD options=0);
	ACQ_PARAMS_TYPE GetParamIdFromIndex(DWORD paramIndex);

	CP2VCam(CPCVision2 *pv2,DWORD port);
	virtual ~CP2VCam();
	DWORD GetInterlaceFactor();
	CPCVision2 *m_pv2;

	BYTE m_LutCache[P2V_NUM_LUT_CHANNELS][P2V_NUM_LUT_ENTRIES];
	HIFCGRAB m_planarGrabAoi;

	PCORHW_MASTER_MODE m_masterModeCache;
	PCORHW_VIDEO_FORMAT m_videoFormatCache;
	UINT32 m_PixelFormatCache;
	int m_pixelClockSrcCache;
	UINT32 m_clampStartCache;
	UINT32 m_clampStopCache;
	UINT32  m_xminCache;	  			// Number of pixels to crop at the beginning of each line
	UINT32	m_xlenCache;	  			// Number of pixels to acquire per line
	UINT32	m_yminCache;	  			// Number of lines to crop at the beginning of each field
	UINT32	m_ylenCache;	  			// Number of lines to acquire per field
	UINT32	m_scaleXCache;			// Number of pixels output per line after cropping
	UINT32	m_scaleYCache;			// Number of lines output per field after cropping
	UINT32	m_fieldOrderCache;
	UINT32	m_fieldProcessCache;
	int	m_clampEnableCache;
	UINT32 m_wenPolarityCache;
	UINT32 m_wenVerticalOffsetCache;
	int m_wenEnableCache;
	DWORD m_contrastCache;
	int m_brightCache;




protected:



};

#endif

#endif // !defined(AFX_P2VCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
