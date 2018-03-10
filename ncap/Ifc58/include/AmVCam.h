/******************************************************************************
 *
 * MODULE   
 *		AmVCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/AmVCam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/06/01 1:46p $
 *
 * ABSTRACT  
 *		IFC interface of the CAmV class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_AMVCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
#define AFX_AMVCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>
#include <AmV.h>

#define AMV_NUM_LUT_ENTRIES 256
#define NUM_AMV_CAM_MODULES 4

#define AMV_PIXEL_SIZE 8		// In Bits

#define AMV_NREF_MIN 0.0		// NREF Minimum Value in Volts
#define AMV_NREF_MAX 1.2		// NREF Maximum Value in Volts
#define AMV_NREF_STP (AMV_NREF_MAX/256.0)	// NREF Step in Volts
#define AMV_NREF_RBV 0			// NREF Register Base Value

#define AMV_PREF_MIN 0.0		// PREF Minimum Value in Volts
#define AMV_PREF_MAX 2.0		// PREF Maximum Value in Volts
#define AMV_PREF_STP (AMV_PREF_MAX/256.0)	// PREF Step in Volts
#define AMV_PREF_RBV 0			// PREF Register Base Value



typedef enum {
	AMV_VIDEO_STRIPPED_FLD,
	AMV_LEN_AND_FEN_DETECTED_FLD
} AMV_FLD_SRC_TYPE;


#define AMV_PECULIAR_PARAM_BASE MOD_PECULIAR_PARAM_BASE

typedef enum {
	AMV_FIELD_SRC = AMV_PECULIAR_PARAM_BASE,	// IFC_ENABLE_TYPE
	AMV_SKIP_FIELD_MODE,
	AMV_FRAME_RESET_ON_VSYNC_OUTPUT,
	AMV_LOW_PASS_FILTER_EN,
	AMV_FIELD_SHIFT,
	AMV_PTG_VSYNC_OUT_EN,
	AMV_CLAMP_SOURCE,
	AMV_NREF_CONTROL,
	AMV_PREF_CONTROL,
	AMV_EDONPISHA_MODE,
	AMV_INPORT_POLARITY,
	AMV_INPORT,
	AMV_OUTPORT,
	AMV_YCRCB_MONO_ACQ,

	AMV_PARAM_END_MARKER

} AMV_PARAMS_TYPE;

typedef enum {
	AMV_PGRP_CLAMP_SETTINGS=IFC_PGRP_MOD_PECULIAR1
} AMV_PARAM_GROUP_TYPE;

#define AMV_PGRP_CLAMP_SETTINGS_MASK	PGRP_ID_TO_MASK(AMV_PGRP_CLAMP_SETTINGS)

typedef enum {
	HORIZONTAL_OFFSET,
	VERTICAL_OFFSET,

	AMV_OFFSET_TYPE_END_MARKER
} AMV_OFFSET_TYPE;

#define AMV_NUM_PARAMS (GEN_PARAM_END_MARKER+AMV_PARAM_END_MARKER-AMV_PECULIAR_PARAM_BASE)

#ifdef __cplusplus

class IFC_EXT_API CAmVCam : public CICamera  
{
public:
	void UpdateRelativeOffset(double dOffset, WORD wOffsetID);
	virtual BOOL RelativeHOffsetSet(double dHoff);
	virtual double RelativeHOffsetGet();
	virtual BOOL RelativeVOffsetSet(double dVoff);
	virtual double RelativeVOffsetGet();
	virtual DWORD ReadReg(REGID reg);
	virtual void WriteReg(REGID reg, DWORD val);
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
	virtual ACQ_PARAMS_TYPE GetParamAlias(ACQ_PARAMS_TYPE paramID);
	virtual pSTRING GetStdCameraType(IFC_STD_CAM_TYPE stdCamType);

	CAmVCam(CAmV *amv,DWORD port);
	virtual ~CAmVCam();
	DWORD GetInterlaceFactor();
	BYTE m_lut[AMV_NUM_LUT_ENTRIES];

	CAmV *m_amv;
protected:
	friend class CAmV;
	void SetSupportedTransforms(DWORD transformMask);

	void SetCameraIndex(pSTRING camName);
	double m_dVOffset[AMV_MAX_CAM_DEF];
	double m_dHOffset[AMV_MAX_CAM_DEF];
	int m_iCamIndex;
public:
	BOOL m_insideUpdateParam;
};
#endif

#endif // !defined(AFX_AMVCAM_H__E99D9D73_9E36_11D1_AE74_00A0C959E757__INCLUDED_)
