/******************************************************************************
 *
 * MODULE   
 *		BDTCam.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/bdtcmrgb.h $
 *		$Revision: 1.1 $
 *		$Modtime: 1/20/03 3:40p $
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

#if !defined(AFX_BDTCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_BDTCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBDTRgbCam;

#include <ifcstd.h>
#include <ifcclass.h>
#include <Camera.h>
#include <BDII.h>
#include <BdtCam.h>


#include <Bandit2.h>


typedef enum {

	BDR_CLAMP_START = BDT_PECULIAR_PARAM_BASE,
	BDR_CLAMP_END,
	BDR_FIELD_PROCESS,
	BDR_MASTER_HSYNC,
	BDR_VS_PULSE_ENABLE,
	BDR_VS_PULSE_OFFSET,
	BDR_VS_PULSE_DURATION,
	BDR_SYNC_SOURCE,
	BDR_HD_HIROSE_PIN,
	BDR_VD_HIROSE_PIN,
	BDR_EXP_HIROSE_PIN,
	BDR_RESET_HIROSE_PIN,
	BDR_HORZ_FRONT_PORCH,
	BDR_HORZ_BACK_PORCH,	

	BDR_PARAM_END_MARKER
} BDR_PARAMS_TYPE;


typedef enum {
	BDR_PGRP_CLAMP_SETTINGS=IFC_PGRP_MOD_PECULIAR1,
	

} BDR_PARAM_GROUP_TYPE;




#define BDR_PGRP_CLAMP_SETTINGS_MASK	PGRP_ID_TO_MASK(BDR_PGRP_CLAMP_SETTINGS)

#define BDR_RGB_NUM_PARAMS (GEN_PARAM_END_MARKER+BDR_PARAM_END_MARKER-BDR_PECULIAR_PARAM_BASE)


class IFC_EXT_API CBDTRgbCam : public CICamera  
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
	virtual LPIFC_AOI_DESC GetPlanarAoi(IFC_COLOR eColorPlane, LPIFC_AOI_DESC lpAoiDesc);
	virtual ACQ_PARAMS_TYPE GetParamIndex(ACQ_PARAMS_TYPE RawID);
	virtual void AddApplicabilityFuncs(void);
	virtual ACQ_PARAMS_TYPE GetParamAlias(ACQ_PARAMS_TYPE paramID);
	virtual pSTRING GetStdCameraType(IFC_STD_CAM_TYPE stdCamType);
	virtual BOOL GetAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf,BOOL lock);
	virtual void UnlockAcqSurfaceDesc(IFC_ACQ_SURF_DESC *acqSurf);

	virtual BOOL ProcessConfigFile(DWORD dwFlags=0);
	virtual pSTRING GetFirstCamType(void);

	void CreateSymbolTable(PIFC_PARAM_CAPS parmTable);
	void WriteCamera(CConfig *cfg, PIFC_CAMERA_DEF_TYPE pCam, BOOL CreateCamDefs=TRUE);
	BOOL WriteConfigFile(CCfgFile *cfgFile, IFC_CFG_CAMERA_SPECIFIER eCamFlag, BOOL CreateCamDefs);
	BOOL WriteConfigFile(const char *szCfgFileName, const char *szCameraName);
	void MakeBanditCamList();

	virtual BYTE *GetDisplayAddr(DWORD options=0);
	ACQ_PARAMS_TYPE GetParamIdFromIndex(DWORD paramIndex);

	CBDTRgbCam(CBanditII *bdt,DWORD port);
	virtual ~CBDTRgbCam();
	DWORD GetInterlaceFactor();
	CBanditII *m_bdt;

	PIFC_CAMERA_DEF_TYPE m_CamListRoot;

protected:

	WORD wPllRegsShadow;
	ConfigSymbol *m_SymbolTable;
	BDII_ANALOG_CONTROL_CAPS m_AnalogControlCaps;


};

#endif // !defined(AFX_BDTCMRGB_H__582D6F70_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
