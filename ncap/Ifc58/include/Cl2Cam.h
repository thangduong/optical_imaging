/******************************************************************************
 *
 * MODULE   
 *		CL2Cam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Cl2Cam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/11/03 11:48a $
 *
 * ABSTRACT  
 *		IFC interface of the CPC2Link class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CL2_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_CL2_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLnk2Cam;

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>






#define CL2_NUM_LUT_ENTRIES 0x100
#define CL2_NUM_LUT_CHANNELS 3
#define CL2_NUM_LUTS 2



typedef enum {
	CL2_PIXEL_CLOCK_INTERNAL,
	CL2_PIXEL_CLOCK_EXTERNAL

} CL2_PIXEL_CLOCK_TYPE;



typedef enum {
	CL2_SOFT_FRAME_TRIG,
	CL2_OPTO_FRAME_TRIG1,
	CL2_OPTO_FRAME_TRIG2,
	CL2_LVDS_FRAME_TRIG1,
	CL2_LVDS_FRAME_TRIG2,
	CL2_FREQ_FRAME_TRIG,

} CL2_FRAME_TRIG_SRC_TYPE; 

typedef enum {
	CL2_SOFT_VFRAME_TRIG,
	CL2_OPTO_VFRAME_TRIG1,
	CL2_OPTO_VFRAME_STARTTRIG1_STOPTRIG2,
	CL2_LVDS_VFRAME_TRIG1,
	CL2_LVDS_VFRAME_STARTTRIG1_STOPTRIG2,

} CL2_VFRAME_TRIG_SRC_TYPE; 


typedef enum {
	CL2_TIMER_LINE_TRIG,
	CL2_SHAFT_LINE_TRIG,
} CL2_LINE_TRIG_SRC_TYPE; 


typedef enum {
	CL2_DVAL_INPUT_VALID_DATA,
	CL2_DVAL_INPUT_FIELD,
} CL2_DVAL_INPUT_TYPE;


#define CL2_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x6200 )



typedef enum {
	CL2_1CHAN_L2R,				// |A,A,A,..........A,A|
	CL2_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	CL2_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	CL2_2TAP_INTERLINE_A_EVEN,			// Tap A even lines Tap B odd lines
	CL2_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines

	CL2_NUM_GEOMETRY_KINDS,

	CL2_INVALID_GEOMETRY=-1

} CL2_IMAGE_GEOMETRY_TYPE;


typedef enum {
	CL2_CCTL_FIXED_LOW,
	CL2_CCTL_FIXED_HIGH,
	CL2_CCTL_EXSYNC,
	CL2_CCTL_PRI,

	CL2_CCTL_NUM_VALS
} CL2_CAM_CTL_SELECT_TYPE;



typedef enum {
	CL2_CHAN_A=1,
	CL2_CHAN_B=2,
	CL2_CHAN_C=4,
	CL2_CHAN_D=8

} CL2_CHAN_ENUM;



#include <PC2Link.h>




typedef enum {

	CL2_DVAL_ENABLE= CL2_PECULIAR_PARAM_BASE,	 		// IFC_ENABLE_TYPE
	CL2_DVAL_INPUT_MODE,

	CL2_EXSYNC_ENABLE,		// IFC_ENABLE_TYPE
	CL2_EXSYNC_POLARITY,		// IFC_POLARITY_TYPE
	
	CL2_EXT_SYNC_OFFSET_TIME, // units are microseconds 
	CL2_EXT_SYNC_ACTIVE_TIME, // units are microseconds 

	CL2_PRI_ENABLE,			// IFC_ENABLE_TYPE
	CL2_PRI_POLARITY,			// IFC_POLARITY_TYPE
	CL2_PRI_OFFSET_TIME,	// units are microseconds 
	CL2_PRI_ACTIVE_TIME,   // units are microseconds 

	CL2_IMAGE_GEOMETRY,		// CL2_IMAGE_GEOMETRY_TYPE


	CL2_CAM_CTL1_SIGNAL,	// which timing output signal is applied to Camera Control 1
	CL2_CAM_CTL2_SIGNAL,	// which timing output signal is applied to Camera Control 2
	CL2_CAM_CTL3_SIGNAL,	// which timing output signal is applied to Camera Control 3
	CL2_CAM_CTL4_SIGNAL,	// which timing output signal is applied to Camera Control 4

	CL2_FRAME_TRIG_SRC,		// Select frame trigger source, also dictates EXSYNC mode
	CL2_FRAME_TRIG_FREQ,

	CL2_VFRAME_TRIG_SOURCE,

	CL2_LINE_TRIG_ENABLE,
	CL2_LINE_TRIG_SRC,
	CL2_LINE_TRIG_DROP_COUNT,
	CL2_LINE_TRIG_NUM_PHASE,
	CL2_LINE_TRIG_DEBOUNCE,
	CL2_LINE_TRIG_CYCLE_TIME,

	CL2_COMBINE_EXSYNC_PRI,
	CL2_NLINES_INTR_COUNT,

	CL2_PARAM_END_MARKER
} CL2_PARAMS_TYPE;



typedef enum {
	CL2_PGRP_EXSYNC_OUTPUT=IFC_PGRP_MOD_PECULIAR1,
	CL2_PGRP_PRI_OUTPUT,
	CL2_PGRP_CAM_CTL_ASSIGNMENT,
	CL2_PGRP_FRAME_TRIGGER,
	CL2_PGRP_LINE_TRIGGER,
	CL2_PGRP_PIXEL,
	CL2_PGRP_VFRAME,
	CL2_PGRP_SHAFT_ENCODER,
	CL2_PGRP_ACTIVE_REGION,
	CL2_PGRP_STROBE_FORM,

	
} CL2_PARAM_GROUP_TYPE;



#define CL2_PGRP_EXSYNC_OUTPUT_MASK			PGRP_ID_TO_MASK(CL2_PGRP_EXSYNC_OUTPUT)
#define CL2_PGRP_PRI_OUTPUT_MASK			PGRP_ID_TO_MASK(CL2_PGRP_PRI_OUTPUT)
#define CL2_PGRP_CAM_CTL_ASSIGNMENT_MASK	PGRP_ID_TO_MASK(CL2_PGRP_CAM_CTL_ASSIGNMENT)
#define CL2_PGRP_FRAME_TRIGGER_MASK			PGRP_ID_TO_MASK(CL2_PGRP_FRAME_TRIGGER)
#define CL2_PGRP_LINE_TRIGGER_MASK			PGRP_ID_TO_MASK(CL2_PGRP_LINE_TRIGGER)
#define CL2_PGRP_PIXEL_MASK					PGRP_ID_TO_MASK(CL2_PGRP_PIXEL)
#define CL2_PGRP_VFRAME_MASK				PGRP_ID_TO_MASK(CL2_PGRP_VFRAME)
#define CL2_PGRP_SHAFT_ENCODER_MASK			PGRP_ID_TO_MASK(CL2_PGRP_SHAFT_ENCODER)
#define CL2_PGRP_ACTIVE_REGION_MASK			PGRP_ID_TO_MASK(CL2_PGRP_ACTIVE_REGION)
#define CL2_PGRP_STROBE_FORM_MASK			PGRP_ID_TO_MASK(CL2_PGRP_STROBE_FORM)



#define CL2_NUM_PARAMS (GEN_PARAM_END_MARKER+CL2_PARAM_END_MARKER-CL2_PECULIAR_PARAM_BASE)


class IFC_EXT_API CLnk2Cam : public CICamera  
{
public:

	virtual int Freeze(HIFCGRAB grabID=NULL);
	virtual void UpdateParams();
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

	CLnk2Cam(CPC2Link *CL2,DWORD port);
	virtual ~CLnk2Cam();
	DWORD GetInterlaceFactor();
	CPC2Link *m_CL2;

	BYTE m_LutCache[CL2_NUM_LUTS][CL2_NUM_LUT_CHANNELS][CL2_NUM_LUT_ENTRIES];

	CORHW_GRAB_HANDLE m_AcqHandle;


protected:


};

#endif // !defined(AFX_CL2_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
