// CNStimFloatPatchParam.h: interface for the CNStimFloatPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMFLOATPATCHPARAM_H__3E4282FC_00F8_493F_BD1C_FC650F662840__INCLUDED_)
#define AFX_CNSTIMFLOATPATCHPARAM_H__3E4282FC_00F8_493F_BD1C_FC650F662840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatchParam.h"
#include "CNStimProfile.h"
#include <math.h>

class CNStimFloatPatchParam : public CNStimPatchParam  
{
	float m_fParam;
	char m_unit[16];
public:
	CNStimFloatPatchParam();
	virtual ~CNStimFloatPatchParam();

	virtual HRESULT __stdcall GetParamType(unsigned char** ppType) 
	{
		if (ppType)
			(*ppType) = (unsigned char*)"float";
		return S_OK;
	}
	virtual HRESULT __stdcall GetParamFloat(float* pFloat)
	{
		if (pFloat)
			(*pFloat) = m_fParam;
		return S_OK;
	}
	virtual HRESULT __stdcall SetParamFloat(float value)
	{
		m_fParam = value;
		return S_OK;
	}
	float* GetParamDataPtr() { return &m_fParam; }
		
	virtual HRESULT __stdcall SetParamString(unsigned char* pStr) {
		if (pStr)
		{
			char* unit = (char*)pStr;
			while ((*unit) && ((*unit)!='_'))
				unit++;
			m_fParam = (float)(atof((char*)pStr));
			if (*unit)
			{
				unit++;
				CNStimProfile* pProfile = CNStimProfile::GetStimProfile();
				if (pProfile)
					m_fParam = (float)pProfile->ConvertUnit((double)m_fParam, unit, m_unit);
			}
		}
		else
			m_fParam = 0.0f;
		return S_OK;
	}

	void SetUnit(const char* unit) {
		strcpy(m_unit, unit);
	}

};

#endif // !defined(AFX_CNSTIMFLOATPATCHPARAM_H__3E4282FC_00F8_493F_BD1C_FC650F662840__INCLUDED_)
