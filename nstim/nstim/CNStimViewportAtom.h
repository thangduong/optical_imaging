// CNStimViewportAtom.h: interface for the CNStimViewportAtom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMVIEWPORTATOM_H__C5510959_B966_4AC6_9B1A_F14B8D88BF50__INCLUDED_)
#define AFX_CNSTIMVIEWPORTATOM_H__C5510959_B966_4AC6_9B1A_F14B8D88BF50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <d3dx9.h>
#include "CNStimAtom.h"

class CNStimViewportAtom : public CNStimAtom  
{
    DWORD*       X;
    DWORD*       Y;
    DWORD*       Width;
    DWORD*       Height;
    float*       MinZ;
    float*       MaxZ;
public:
	CNStimViewportAtom();
	virtual ~CNStimViewportAtom();

	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) {
		D3DVIEWPORT9 vp;
		vp.X = (*X);
		vp.Y = (*Y);
		vp.Width = (*Width);
		vp.Height = (*Height);
		vp.MinZ = (*MinZ);
		vp.MaxZ = (*MaxZ);
		pEngine->ApplyViewport(&vp);

		int cx = vp.X + (vp.Width/2);
		int cy = vp.Y + (vp.Height/2);
		pEngine->SetViewportCenter(cx,cy);
		return S_OK;
	}

	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { 
		return S_OK;
	}

	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { 
		return S_OK; 
	}
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)"viewport"; return S_OK; }

};

#endif // !defined(AFX_CNSTIMVIEWPORTATOM_H__C5510959_B966_4AC6_9B1A_F14B8D88BF50__INCLUDED_)
