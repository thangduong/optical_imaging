// CNStimGratingPatch.h: interface for the CNStimGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMGRATINGPATCH_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_)
#define AFX_CNSTIMGRATINGPATCH_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatch.h"
#include "CDirect3DTexture.h"
#include "CDirect3DVertexBuffer.h"
#include "INStimEngine.h"

class CNStimGratingPatch : public CNStimPatch  
{
	static char* m_pPatchType;
	static float* sineTable;
	static float* cosineTable;
	static bool lutInitialized;
	IDirect3DDevice9* m_pDevice;
	INStimEngine* m_pEngine;
#define LUT_RESOLUTION				10			// 2 points per degreee
//#define	FP_PRECISION				10			// fixed point math precision (2^10 is about 3 sig fig)
	int m_iCurrentFrame;
	int m_iNumFrames;


	// patch internal storage
	CDirect3DTexture m_GratingBuff;
	CDirect3DTexture m_BackBuff;
	CDirect3DVertexBuffer m_VertexBuffer;

	int m_iBackBuffWidth;
	int m_iBackBuffHeight;

	int m_iGratingBuffWidth;
	int m_iGratingBuffHeight;

	int m_iShapeWidth;
	int m_iShapeHeight;
	
	// patch parameters
	int* m_pWidth;
	int* m_pHeight;
	float* m_pSfPixPerCycle;
	float* m_pSpatialPhase;
	float* m_pTfCycPerSec;
	int* m_pAlpha;
	int* m_pBiDir;
	int biDirCtr;
	float* m_pBlitAngle2;
	float* m_pBlitAngle3;
	int* m_pShape;
	float* m_pContrast;				// contrast in pix value (p-p)/2
	float* m_pLuminance;				// luminance in pix value
	int* m_pType;		// 0 = drifting grating, 1 = counterphase, 2 = counterphase flicker
	double m_FramesPerSec;			// framerate of the monitor (taken on init or reset)
	double m_CurPhase;				// current phase of the grating
									// this is calculated from the tf and frame num
									// m_CurPhase is a number between 0 and 2*pi
//	int* m_pBlitOrder;				// blit grating on first or mask on first
	int m_iIncDir;



	/// precomputed values for faster transformation
	float left0, top0, right0, bottom0;		// back buffer to front buffer
	float left2, top2, right2, bottom2;		// grating to back buffer

	float xTrans;
	float yTrans;
	float ct0;
	float st0;
	float ct2;
	float st2;



public:
	CNStimGratingPatch();
	virtual ~CNStimGratingPatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames);
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine);
	virtual HRESULT __stdcall Init(INStimEngine* pEngine);
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine);
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)m_pPatchType; return S_OK; }
	virtual HRESULT __stdcall SetParam(unsigned char* pParamName, unsigned char* pParamValue);

};

#endif // !defined(AFX_CNSTIMGRATINGPATCH_H__86B3A0AB_C85B_4A56_A3AE_3AD8BDA9B97F__INCLUDED_)
