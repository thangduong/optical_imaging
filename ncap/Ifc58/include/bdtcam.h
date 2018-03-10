/******************************************************************************
 *
 * MODULE   
 *		BDTCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/bdtcam.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/09/02 11:28a $
 *
 * ABSTRACT  
 *		IFC interface of the CBandit class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_BDTCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_BDTCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>
#include <BDII.h>


typedef enum {
	BDT_VIDEO_STD_NTSC	=BDII_VIDEO_STD_NTSC,
	BDT_VIDEO_STD_PAL	=BDII_VIDEO_STD_PAL,	
	BDT_VIDEO_STD_SECAM	=BDII_VIDEO_STD_SECAM,
	BDT_VIDEO_STD_NONE	=BDII_VIDEO_STD_NONE
} BDT_VIDEO_STANDARD_TYPE;

typedef enum {
	BDT_FIELD_PROCESS_ALL		= BDII_FIELD_PROCESS_ALL,
	BDT_FIELD_PROCESS_ODD_ONLY	= BDII_FIELD_PROCESS_ODD_ONLY,
	BDT_FIELD_PROCESS_EVEN_ONLY	= BDII_FIELD_PROCESS_EVEN_ONLY

} BDT_FIELD_PROCESS_TYPE;


typedef enum {
	BDT_LOW_IS_ODD,
	BDT_LOW_IS_EVEN
} BDT_PWG_FLD_POL_TYPE;

typedef enum {
	BDT_FLD_SRC_SYNC_STRIPPER,
	BDT_FLD_SRC_GENERATED_BASED_ON_H_AND_V_SYNC
} BDT_FLD_SRC_TYPE;

typedef enum {
	BDT_LPF_6MHZ,
	BDT_LPF_10MHZ
} BDT_LPF_TYPE;


typedef enum {
	BDT_SYNC_COMPOSITE_VIDEO=1,
	BDT_SYNC_COMPOSITE_SYNC=2,
	BDT_SYNC_SEPARATE_SYNC=3,
	BDT_SYNC_RED=5,
	BDT_SYNC_GREEN,
	BDT_SYNC_BLUE

} BDT_SYNC_SRC_TYPE;

typedef enum {
	BDT_VSYNC_DISABLE,
	BDT_VSYNC_LINE_WIDTH,
	BDT_VSYNC_TIME_WIDTH,
} BDT_VSYNC_MODE_TYPE;


typedef enum {
	BDT_SYNC_STRIPPER_BACK_PORCH,
	BDT_PROGRAMMABLE
} BDT_CLAMP_SRC_TYPE;

#define BDT_NUM_LUT_ENTRIES 0x100

typedef enum {
	BDT_SOFT_TRIG,
	BDT_EXT_TRIG0,
	BDT_EXT_TRIG1,
	BDT_EXT_TRIG2,
	BDT_OPTO_COUPLED_TRIG0,
	BDT_OPTO_COUPLED_TRIG1,
	BDT_RS422_DIFF_TRIG,
} BDT_TRIG_SRC_TYPE; 

typedef enum {
	BDT_CREF_HSYNC_FROM_STRIPPER,
	BDT_CREF_TIMING_MODE_DEPENDANT	

} BDT_PRGM_CLAMP_REF_POINT_TYPE;

typedef enum {
	BDT_SINGLE_TAP,
	BDT_2TAP_ILACE_TOGGLE


} BDT_MULTITAP_MODE_TYPE;



class CBDTCam;
#define BDT_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x3000 )

#include <Bandit2.h>


typedef enum {

	
	BDT_FIELD_PROCESS= BDT_PECULIAR_PARAM_BASE,
	

	BDT_PARAM_END_MARKER
} BDT_PARAMS_TYPE;


typedef enum {
	BDT_PGRP_FIRST_GROUP=IFC_PGRP_MOD_PECULIAR1,
	BDT_PGRP_NUM_GROUPS

} BDT_PARAM_GROUP_TYPE;



#define BDT_PGRP_FIRST_GROUP_MASK	PGRP_ID_TO_MASK(BDT_PGRP_FIRST_GROUP)

#define BDT_NUM_PARAMS (GEN_PARAM_END_MARKER+BDT_PARAM_END_MARKER-BDT_PECULIAR_PARAM_BASE)


class IFC_EXT_API CBDTCam : public CICamera  
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
	virtual BOOL GetAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf,BOOL lock);
	virtual void UnlockAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf);

	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual pSTRING GetFirstCamType(void);
	virtual BOOL SetTransform(IFC_TRANSFORM_TYPE eTransform);

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);
	BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName);
	void MakeBanditCamList();

	CBDTCam(CBanditII *bdt,DWORD port);
	virtual ~CBDTCam();
	DWORD GetInterlaceFactor();
	CBanditII *m_bdt;

	PIFC_CAMERA_DEF_TYPE m_CamListRoot;
	BDII_ANALOG_CONTROL_CAPS m_AnalogControlCaps;

protected:

	WORD wPllRegsShadow;
	ConfigSymbol *m_SymbolTable;
};

#endif // !defined(AFX_BDTCAM_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
