// CNStimOIGratingPatch.h: interface for the CNStimOIGratingPatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMOIGRATINGPATCH_H__618C78FE_E049_4CA7_B8E7_2EE59978596A__INCLUDED_)
#define AFX_CNSTIMOIGRATINGPATCH_H__618C78FE_E049_4CA7_B8E7_2EE59978596A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatch.h"
#include "CNStimIntArrayPatchParam.h"
#include "CDirect3DSurface.h"
#include "CDirect3DTexture.h"
#include "CDirect3DVertexBuffer.h"
// Our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;
    FLOAT rhw;
    FLOAT tu, tv;   // The texture coordinates
};
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_TEX1)

class CNStimOIGratingPatch : public CNStimPatch  
{
	static const char* m_pPatchType;
	static float* sineTable;
	static float* cosineTable;
	static bool lutInitialized;
#define LUT_RESOLUTION				10			// 2 points per degreee
	double framerate;
	IDirect3DDevice9* m_pDevice;
	INStimEngine* m_pEngine;
	CDirect3DTexture m_GratingBuff;
	CDirect3DTexture m_BackBuff;
	CDirect3DVertexBuffer m_VertexBuffer;
	int m_iGratingBuffWidth;
	int m_iGratingBuffHeight;
	int* m_pNumCond;		// # of conditions
	struct CondDesc {
		float* m_pSfPixPerCycle;
		float* m_pSpatialPhase;
		float* m_pTfCycPerSec;
		int* m_pAlpha;
		int* m_pBiDir;
		float* m_pOrientation;
		float* m_pContrast;				// contrast in pix value (p-p)/2
		float* m_pLuminance;			// luminance in pix value
		int* m_pXDisplacement;
		int* m_pYDisplacement;
		int m_iIncDir;
		double m_CurPhase;
		int* m_pCenterX;
		int* m_pCenterY;
/*		int m_iCurrentFrame;
		int m_iNumFrames;
*/
		int m_iGratingBuffWidth;
		int m_iGratingBuffHeight;

		CDirect3DSurface surf;
		double m_dOrSine;
		double m_dOrCosine;
	}* m_pCondDesc;
	int* m_pWidth;
	int* m_pHeight;
	int* m_pShape;
	int* m_pStimSeqLen;					// length of stimulation sequence
	int** m_pStimSequence;				// the actual stimulation sequence
	int m_iStimSeqMarker;				// current position in the stim seq
	int m_iNumFramesInCurCond;			// # of frames executed in current condition
	int* m_pFramesPerCond;
	int m_iBackBuffWidth;
	int m_iBackBuffHeight;
	float left0, top0, right0, bottom0;		// back buffer to front buffer
	float bkleft0, bktop0, bkright0, bkbottom0;		// back buffer to front buffer
	bool m_bCondSwitched;
	double m_FramesPerSec;			// framerate of the monitor (taken on init or reset)
	CNStimIntArrayPatchParam* m_pStimSeqArray;

	void InitCond(INStimEngine* pEngine, CondDesc* pCond);
	void DrawCond(INStimEngine* pEngine, CondDesc* pCond, bool switchCond);
	void ResetCond(CondDesc* pCond);
	void AdvanceCondFrame(CondDesc* pCond);
public:
	CNStimOIGratingPatch();
	virtual ~CNStimOIGratingPatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames);
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine);
	virtual HRESULT __stdcall Init(INStimEngine* pEngine);
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine);
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)m_pPatchType; return S_OK; }
	virtual HRESULT __stdcall SetParam(unsigned char* pParamName, unsigned char* pParamValue);

};

#endif // !defined(AFX_CNSTIMOIGRATINGPATCH_H__618C78FE_E049_4CA7_B8E7_2EE59978596A__INCLUDED_)
