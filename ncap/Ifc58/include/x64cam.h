/******************************************************************************
 *
 * MODULE   
 *		X64Cam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/x64cam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/20/03 9:30a $
 *
 * ABSTRACT  
 *		IFC interface of the Cx64 class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_X64_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_X64_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CX64Cam;

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>



typedef enum {
	X64_FIELDS_PROCESS_ALL	=1,
	X64_FIELDS_PROCESS_ODD_ONLY,
	X64_FIELDS_PROCESS_EVEN_ONLY

} X64_FIELD_PROCESS_TYPE;


typedef enum {
	X64_LOW_IS_ODD,
	X64_LOW_IS_EVEN
} X64_PWG_FLD_POL_TYPE;




#define X64_NUM_LUT_ENTRIES 0x1000
#define X64_NUM_LUT_CHANNELS 3



typedef enum {
	X64_PIXEL_CLOCK_INTERNAL,
	X64_PIXEL_CLOCK_EXTERNAL

} X64_PIXEL_CLOCK_TYPE;


typedef enum {
	X64_SOFT_FRAME_TRIG,
	X64_OPTO_FRAME_TRIG1,
	X64_OPTO_FRAME_TRIG2,
	X64_LVDS_FRAME_TRIG1,
	X64_LVDS_FRAME_TRIG2,
	X64_FREQ_FRAME_TRIG,


} X64_FRAME_TRIG_SRC_TYPE; 

typedef enum {
	X64_TIMER_LINE_TRIG,
	X64_SHAFT_LINE_TRIG,
} X64_LINE_TRIG_SRC_TYPE; 



#define X64_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x6000 )


typedef enum {
	X64_DVAL_INPUT_FIELD,
	X64_DVAL_INPUT_VALID_DATA
} X64_DVAL_INPUT_TYPE;



typedef enum {
	X64_1CHAN_L2R,				// |A,A,A,..........A,A|
	X64_2CHAN_INTERLEAVED,		// |A,B,A,B,A,B,...,A,B|
	X64_2CHAN_SEP_TAP_L2R,		// 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>            |B=>            |
	X64_2CHAN_SEP_TAP_R2L,		// 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|            <=A|            <=B|
	X64_4CHAN_SEP_TAP_L2R,		// 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |D=>    |
	X64_4CHAN_SEP_TAP_R2L,		// 4 CHANNELS SEPERATE TAPS RIGHT TO LEFT	|    <=A|    <=B|    <=C|    <=D|
	X64_4CHAN_2SEG_INTERLEAVED,// 4 Taps,2 Segments, each interleaved		|A,B,A,B,...,A,B|C,D,C,D,...,C,D|
	X64_2CHAN_SEP_TAP_CONVERGE,	// |A =>   |    <= B|
	X64_3CHAN_SEP_TAP_L2R,		// 3 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=>    |B=>    |C=>    |

	X64_8CHAN_INTERLEAVED,		// |A,B,C,D,E,F,G,H,...,A,B,C,D,E,F,G,H,|
	X64_8CHAN_SEP_TAP_L2R,		// 8 CHANNELS SEPERATE TAPS LEFT TO RIGHT	|A=> |B=> |C=> |D=> |E=> |F=> |G=> |H=> |

	X64_2TAP_INTERLINE_A_EVEN,			// Tap A even lines Tap B odd lines
	X64_2TAP_INTERLINE_B_EVEN,			// Tap B even lines Tap A odd lines

	X64_USER_DEFINED_GEO,		// a user-defined geometry

	X64_NUM_GEOMETRY_KINDS,



	X64_INVALID_GEOMETRY=-1

} X64_IMAGE_GEOMETRY_TYPE;


typedef enum {
	X64_CCTL_FIXED_LOW,
	X64_CCTL_FIXED_HIGH,
	X64_CCTL_EXSYNC,
	X64_CCTL_PRI,

	X64_CCTL_NUM_VALS
} X64_CAM_CTL_SELECT_TYPE;



typedef enum {
	X64_CHAN_A=1,
	X64_CHAN_B=2,
	X64_CHAN_C=4,
	X64_CHAN_D=8

} X64_CHAN_ENUM;



#include <x64.h>




typedef enum {
	X64_CHANNEL_ORDER_NORMAL=1,
	X64_CHANNEL_ORDER_REVERSE
} X64_CHANNEL_ORDER_TYPE;

typedef enum {
	X64_TAP_OUTPUT_ALTERNATE=1,			// odd even, every 2 taps
	X64_TAP_OUTPUT_SEGMENTED,			// one segment per tap
	X64_TAP_OUTPUT_PARALLEL				// one byte per tap, one segment per line
} X64_TAP_OUTPUT_TYPE;

// Direction
#define X64_DIRECTION_LR		 	0x00000001
#define X64_DIRECTION_RL		 	0x00000002
#define X64_DIRECTION_UD		 	0x00000004
#define X64_DIRECTION_DU		 	0x00000008
#define X64_DIRECTION_FROM_TOP		0x00000010
#define X64_DIRECTION_FROM_MID		0x00000020
#define X64_DIRECTION_FROM_BOT		0x00000040


typedef enum {

	X64_FIELD_PROCESS = X64_PECULIAR_PARAM_BASE,
	X64_DVAL_ENABLE,	 		// IFC_ENABLE_TYPE
	X64_DVAL_INPUT_MODE,	// X64_DVAL_INPUT_TYPE

	X64_EXSYNC_ENABLE,		// IFC_ENABLE_TYPE
	X64_EXSYNC_POLARITY,		// IFC_POLARITY_TYPE
	
	X64_EXT_SYNC_OFFSET_TIME, // units are microseconds 
	X64_EXT_SYNC_ACTIVE_TIME, // units are microseconds 

	X64_PRI_ENABLE,			// IFC_ENABLE_TYPE
	X64_PRI_POLARITY,			// IFC_POLARITY_TYPE
	X64_PRI_OFFSET_TIME,	// units are microseconds 
	X64_PRI_ACTIVE_TIME,   // units are microseconds 

	X64_IMAGE_GEOMETRY,		// X64_IMAGE_GEOMETRY_TYPE


	X64_CAM_CTL1_SIGNAL,	// which timing output signal is applied to Camera Control 1
	X64_CAM_CTL2_SIGNAL,	// which timing output signal is applied to Camera Control 2
	X64_CAM_CTL3_SIGNAL,	// which timing output signal is applied to Camera Control 3
	X64_CAM_CTL4_SIGNAL,	// which timing output signal is applied to Camera Control 4

	X64_FRAME_TRIG_SRC,		// Select frame trigger source, also dictates EXSYNC mode
	X64_FRAME_TRIG_FREQ,

	X64_LINE_TRIG_ENABLE,
	X64_LINE_TRIG_SRC,
	X64_LINE_TRIG_DROP_COUNT,
	X64_LINE_TRIG_NUM_PHASE,
	X64_LINE_TRIG_DEBOUNCE,
	X64_LINE_TRIG_CYCLE_TIME,

	X64_NUM_TAPS,
	X64_NUM_CHANNELS,
	X64_CHANNEL_ORDER,   // X64_CHANNEL_ORDER_TYPE
	X64_TAP_OUTPUT,		// X64_TAP_OUTPUT_TYPE
	X64_TAP_DIRECTION,




	X64_PARAM_END_MARKER
} X64_PARAMS_TYPE;



typedef enum {
	X64_PGRP_EXSYNC_OUTPUT=IFC_PGRP_MOD_PECULIAR1,
	X64_PGRP_PRI_OUTPUT,
	X64_PGRP_LUT_INPUT,
	X64_PGRP_CAM_CTL_ASSIGNMENT,
	X64_PGRP_FRAME_TRIGGER,
	X64_PGRP_LINE_TRIGGER,
	X64_PGRP_PIXEL,
	X64_PGRP_CUSTOM_GEO,
	

} X64_PARAM_GROUP_TYPE;



#define X64_PGRP_EXSYNC_OUTPUT_MASK			PGRP_ID_TO_MASK(X64_PGRP_EXSYNC_OUTPUT)
#define X64_PGRP_PRI_OUTPUT_MASK			PGRP_ID_TO_MASK(X64_PGRP_PRI_OUTPUT)
#define X64_PGRP_LUT_INPUT_MASK				PGRP_ID_TO_MASK(X64_PGRP_LUT_INPUT)
#define X64_PGRP_CAM_CTL_ASSIGNMENT_MASK	PGRP_ID_TO_MASK(X64_PGRP_CAM_CTL_ASSIGNMENT)
#define X64_PGRP_FRAME_TRIGGER_MASK			PGRP_ID_TO_MASK(X64_PGRP_FRAME_TRIGGER)
#define X64_PGRP_LINE_TRIGGER_MASK			PGRP_ID_TO_MASK(X64_PGRP_LINE_TRIGGER)
#define X64_PGRP_PIXEL_MASK					PGRP_ID_TO_MASK(X64_PGRP_PIXEL)
#define X64_PGRP_CUSTOM_GEO_MASK			PGRP_ID_TO_MASK(X64_PGRP_CUSTOM_GEO)



#define X64_NUM_PARAMS (GEN_PARAM_END_MARKER+X64_PARAM_END_MARKER-X64_PECULIAR_PARAM_BASE)


class IFC_EXT_API CX64Cam : public CICamera  
{
public:

	virtual int Freeze(HIFCGRAB grabID=NULL);
	virtual void UpdateParams();
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

	Cx64Frame *HostSchemaFrame( LPCAM_ATTR lpAttr);
	BOOL UpdateDefRingBuf(void);
	IFC_EDDS *GetTrashBuffer(DWORD trashBufSize);


	virtual BYTE *GetDisplayAddr(DWORD options=0);
	ACQ_PARAMS_TYPE GetParamIdFromIndex(DWORD paramIndex);

	CX64Cam(Cx64 *X64,DWORD port);
	virtual ~CX64Cam();
	DWORD GetInterlaceFactor();
	BOOL CamInit();
	Cx64 *m_X64;

	WORD m_LutCache[X64_NUM_LUT_CHANNELS][X64_NUM_LUT_ENTRIES];

	PX64_ACQ_HANDLE m_AcqHandle;
	UINT32 m_curPixelSize;	
	PCORHW_ACQ_WINDOW m_AcqWindow;
	UINT32 m_PixelFormat;
	CIFrame *m_gottenCamFrame;


	Cx64Frame		*m_SchemaFrameids[NUM_SCHEMA_FRAME_IDS];
	DWORD			m_framesInSchema;

	short			m_fcount;		/* Acquisition frame count */

	BYTE *m_defaultRingBuf;
	DWORD m_defaultRingNumFrames;
	DWORD m_defaultRingBufSize;
	BYTE *m_defaultRingBufOrig;
	HIFCGRAB m_defGrabId;

	BOOL m_eventsRouted;
	OS_sem_t		m_AcqMutex;
	DWORD m_lastScan;
	BOOL m_paramsInit;


	IFC_EDDS *m_TrashScatter;
	BYTE *m_TrashBuf;
	DWORD m_TrashBufSize;

protected:




};

#endif // !defined(AFX_X64_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
