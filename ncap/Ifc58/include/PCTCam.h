// PCTCam.h: interface for the PCTCam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCTCAM_H__DAA30D41_A1BA_11D3_9FC9_00A0C959E73E__INCLUDED_)
#define AFX_PCTCAM_H__DAA30D41_A1BA_11D3_9FC9_00A0C959E73E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Camera.h"
#include "pctstdig.h"



#define PCT_PECULIAR_PARAM_BASE (MOD_PECULIAR_PARAM_BASE + 0x1000 * PCT_PCI_DEVICE_ID)

typedef enum {
	PCT_TIMING_SRC = PCT_PECULIAR_PARAM_BASE,			// IFC_ENABLE_TYPE
	PCT_PARAM_END_MARKER
} PCT_PARAMS_TYPE;

#define PCT_NUM_PARAMS (GEN_PARAM_END_MARKER+PCT_PARAM_END_MARKER-PCT_PECULIAR_PARAM_BASE)

class IFC_EXT_API PCTCam : public CICamera  
{
public:
	PCTCam(CPCTstDig *pct,DWORD port);
	virtual ~PCTCam();
	virtual BOOL SetCameraType(pSTRING camName,BOOL updateHW=TRUE);
	CPCTstDig *m_pct;
	virtual void UpdateParams();
	virtual BOOL SetLutFunction(LUTID_TYPE lutID,IFCLUTFUNC func,DWORD *constants,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD){return false;};
	virtual void ReadLutBuf(LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD){};
	virtual void WriteLutBuf(LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,LUT_PORTION_TYPE lutPortion=LUT_FULL_WORD){};
	virtual ACQ_PARAMS_TYPE GetParamIndex(ACQ_PARAMS_TYPE RawID);
	virtual void GetAttr(LPCAM_ATTR lpAttr, BOOL zoomCorrected=TRUE);

};




#endif // !defined(AFX_PCTCAM_H__DAA30D41_A1BA_11D3_9FC9_00A0C959E73E__INCLUDED_)
