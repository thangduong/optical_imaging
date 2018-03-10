// CNStimBinaryNoisePatch.h: interface for the CNStimBinaryNoisePatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMBINARYNOISEPATCH_H__EA6CA42A_941C_45CB_AF04_D9D10721C37C__INCLUDED_)
#define AFX_CNSTIMBINARYNOISEPATCH_H__EA6CA42A_941C_45CB_AF04_D9D10721C37C__INCLUDED_

#include "CDirect3DSurface.h"
#include "CDirect3DTexture.h"
#include "CDirect3DVertexBuffer.h"
#include "CNStimPatch.h"

class CNStimBitArrayPatchParam;

class CNStimBinaryNoisePatch : public CNStimPatch  
{
	CDirect3DTexture m_LumTex[255];
//	CDirect3DSurface surf = Device.CreateSurface(100,100,D3DFMT_A8R8G8B8,D3DPOOL_SYSTEMMEM);
//	CDirect3DTexture m_Texture;
	CDirect3DVertexBuffer m_VertexBuffer;
		// locations of the grids
		
	int* m_pNGridX;
	int* m_pNGridY;
	int* m_pGridWidth;
	int* m_pGridHeight;
	D3DRECT* m_pGridLoc;
	CNStimBitArrayPatchParam* m_pData;

	int m_StimMark;
public:
	CNStimBinaryNoisePatch();
	virtual ~CNStimBinaryNoisePatch();

	virtual HRESULT __stdcall AdvanceFrame(int numFrames);
	virtual HRESULT __stdcall Draw(INStimEngine* pEngine);
	virtual HRESULT __stdcall Init(INStimEngine* pEngine);
};

#endif // !defined(AFX_CNSTIMBINARYNOISEPATCH_H__EA6CA42A_941C_45CB_AF04_D9D10721C37C__INCLUDED_)
