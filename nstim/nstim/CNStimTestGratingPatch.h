// CNStimTestGratingPatch.h: interface for the CNStimTestGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMTestGratingPatch_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_)
#define AFX_CNSTIMTestGratingPatch_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatch.h"
#include "CDirect3DTexture.h"
#include "CDirect3DVertexBuffer.h"

class CNStimTestGratingPatch : public CNStimPatch  
{
	static char* m_pPatchType;
	int m_iCurrentFrame;
	int m_iNumFrames;


	// patch internal storage
	CDirect3DTexture m_ShapeMap;
	CDirect3DTexture m_BackBuff;
	CDirect3DTexture m_OneCycle;
	CDirect3DVertexBuffer m_VertexBuffer;
	int nx;
	int ny;

	int m_iBackBuffWidth;
	int m_iBackBuffHeight;

	int m_iShapeWidth;
	int m_iShapeHeight;
	
	// patch parameters
	int* m_pWidth;
	int* m_pHeight;
	int* m_pSfPixPerCycle;
	float* m_pSpatialPhase;
	float* m_pTfCycPerSec;
	int* m_pAlpha;
	int* m_pBiDir;
	float* m_pBlitAngle2;
	int* m_pShape;
	float* m_pContrast;				// contrast in pix value (p-p)/2
	float* m_pLuminance;				// luminance in pix value

	int m_iIncDir;
//	int* 
public:
	CNStimTestGratingPatch();
	virtual ~CNStimTestGratingPatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames);
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine);
	virtual HRESULT __stdcall Init(INStimEngine* pEngine);
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine);
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)m_pPatchType; return S_OK; }

};

#endif // !defined(AFX_CNSTIMTestGratingPatch_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_)
