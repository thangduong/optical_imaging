// CNStimAtomGammaElt.h: interface for the CNStimAtomGammaElt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMATOMGAMMAELT_H__0D8BAA51_E391_4867_8BD1_A74C89A11AC4__INCLUDED_)
#define AFX_CNSTIMATOMGAMMAELT_H__0D8BAA51_E391_4867_8BD1_A74C89A11AC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimAtom.h"

class CNStimAtomGammaElt : public CNStimAtom  
{
	int* index;
	int* red;
	int* green;
	int* blue;
public:
	CNStimAtomGammaElt();
	virtual ~CNStimAtomGammaElt();
	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) {
		pEngine->SetGammaRampElement((*index), (*red), (*green), (*blue));
		return S_OK;
	}
	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { 
		return S_OK; 
	}
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { 
		return S_OK;
	}
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { 
		if (ppType) (*ppType) = (unsigned char*)"gammaelt"; return S_OK; 
	}


};

#endif // !defined(AFX_CNSTIMATOMGAMMAELT_H__0D8BAA51_E391_4867_8BD1_A74C89A11AC4__INCLUDED_)
