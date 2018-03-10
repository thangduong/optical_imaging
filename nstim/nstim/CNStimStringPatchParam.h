// CNStimStringPatchParam.h: interface for the CNStimStringPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMSTRINGPATCHPARAM_H__611F1CEA_05A7_4E09_9E67_8000FFE43E5B__INCLUDED_)
#define AFX_CNSTIMSTRINGPATCHPARAM_H__611F1CEA_05A7_4E09_9E67_8000FFE43E5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatchParam.h"

class CNStimStringPatchParam : public CNStimPatchParam  
{
	char m_Data[1024*10];			// no more than 10k in length
public:
	CNStimStringPatchParam();
	virtual ~CNStimStringPatchParam();
	virtual HRESULT __stdcall GetParamType(unsigned char** ppType) { return E_FAIL; }
	char* GetParamDataPtr() { return m_Data; }
	virtual HRESULT __stdcall SetParamString(unsigned char* pStr) {
		strcpy(m_Data, (char*)pStr);
		return S_OK;
	}
};

#endif // !defined(AFX_CNSTIMSTRINGPATCHPARAM_H__611F1CEA_05A7_4E09_9E67_8000FFE43E5B__INCLUDED_)
