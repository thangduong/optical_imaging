/******************************************************************************
 *
 * MODULE   
 *		PCPCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCPCam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:42a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCPGB class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCPCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCPCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>



typedef enum {
	PCP_LOW_IS_ODD,
	PCP_LOW_IS_EVEN
} PCP_PWG_FLD_POL_TYPE;

typedef enum {
	PCP_FLD_SRC_SYNC_STRIPPER,
	PCP_FLD_SRC_BASED_ON_H_AND_V_SYNC
} PCP_FLD_SRC_TYPE;

typedef enum {
	PCP_LPF_6_5_MHZ,
	PCP_LPF_12_5_MHZ
} PCP_LPF_TYPE;

typedef enum {
	PCP_EXTERNAL_LOOP_FILTER,
	PCP_INTERNAL_LOOP_FILTER
} PCP_INTFLT_TYPE;	

//typedef enum {
//	PCP_GREEN_VIDEO_CHANNEL,
//	PCP_COMPOSITE_CHANNEL_0,
//	PCP_COMPOSITE_CHANNEL_1
//} PCP_SYNC_STRIPPER_SRC_TYPE;

typedef enum {
	PCP_SYNC_STRIPPER_BACK_PORCH,
	PCP_PROGRAMMABLE
} PCP_CLAMP_SRC_TYPE;

typedef enum {
	PCP_VSCAN_CLKSEL_NORMAL,
	PCP_VSCAN_CLKSEL_FRESET
} PCP_VSCAN_CLOCKSEL;


#define PCP_NUM_LUT_ENTRIES 0x10000

typedef enum {
	PCP_SOFT_TRIG,
	PCP_EXT_TRIG0,
	PCP_EXT_TRIG1,
	PCP_EXT_TRIG2,
	PCP_OPTO_COUPLED_TRIG0,
	PCP_OPTO_COUPLED_TRIG1,
	PCP_RS422_DIFF_TRIG0,
	PCP_RS422_DIFF_TRIG1
} PCP_TRIG_SRC_TYPE; 

typedef enum {
	PCP_CREF_HSYNC_FROM_STRIPPER,
	PCP_CREF_TIMING_MODE_DEPENDANT	

} PCP_PRGM_CLAMP_REF_POINT_TYPE;


#include <Pcplus.h>

#define PCP_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x1000 * PCP_PCI_DEVICE_ID)

typedef enum {

	PCP_FIELD_SRC = PCP_PECULIAR_PARAM_BASE,			// IFC_ENABLE_TYPE

	PCP_SKIP_FIELD_MODE,
	PCP_FRAME_RESET_ON_VSYNC_OUTPUT,
	PCP_TRIG_CYCLE_LATCH_TRIG,
	PCP_A_TO_D_PREF,
	PCP_A_TO_D_NREF,
	PCP_LOW_PASS_FILTER,
	PCP_PWG_FIELD_POLARITY,
	PCP_FIELD_SHIFT,
	PCP_PTG_VSYNC_OUT_EN,

	PCP_CLAMP_SOURCE,
	PCP_BACK_PORCH_CLAMP_START,
	PCP_BACK_PORCH_CLAMP_END,
	PCP_NO_CLAMP_REGION,
	PCP_PRGM_CLAMP_REF_POINT,


	PCP_EDONPISHA_MODE,
	PCP_PTG2PWG_HSYNC_FLIP,
	PCP_OVERSAMPLE_MODE,
	PCP_VSCAN_CLKSEL,
	PCP_LOOP_FILTER,

	PCP_PARAM_END_MARKER
} PCP_PARAMS_TYPE;


typedef enum {
	PCP_PGRP_REF_VOLTAGE=IFC_PGRP_MOD_PECULIAR1,
	PCP_PGRP_CLAMP_SETTINGS

} PCP_PARAM_GROUP_TYPE;

#define PCP_PGRP_REF_VOLTAGE_MASK		PGRP_ID_TO_MASK(PCP_PGRP_REF_VOLTAGE)
#define PCP_PGRP_CLAMP_SETTINGS_MASK	PGRP_ID_TO_MASK(PCP_PGRP_CLAMP_SETTINGS)


#define PCP_NUM_PARAMS (GEN_PARAM_END_MARKER+PCP_PARAM_END_MARKER-PCP_PECULIAR_PARAM_BASE)

#if defined __cplusplus && !defined NOIFCLINK

class CPCVisionPlus;

class IFC_EXT_API CPCPCam : public CICamera  
{
public:

	virtual int Freeze(HIFCGRAB grabID=NULL);
	virtual void UpdateParams();
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

	CPCPCam(CPCVisionPlus *pcp,DWORD port);
	virtual ~CPCPCam();
	DWORD GetInterlaceFactor();
	CPCVisionPlus *m_pcp;

protected:

	WORD wPllRegsShadow;
};

#endif

#endif // !defined(AFX_PCPCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
