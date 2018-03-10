// CNStimIntPatchParam.h: interface for the CNStimIntPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMINTPATCHPARAM_H__220EE0A0_0E9A_457A_B720_3633E7224A80__INCLUDED_)
#define AFX_CNSTIMINTPATCHPARAM_H__220EE0A0_0E9A_457A_B720_3633E7224A80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatchParam.h"
#include "CNStimProfile.h"
#include <math.h>

class CNStimIntPatchParam : public CNStimPatchParam  
{
	int m_iParam;
	char m_unit[16];
public:
	CNStimIntPatchParam();
	virtual ~CNStimIntPatchParam();

	virtual HRESULT __stdcall GetParamType(unsigned char** pType);
	virtual HRESULT __stdcall GetParamInt(int* pInt);
	virtual HRESULT __stdcall SetParamInt(int pInt);

	virtual HRESULT __stdcall SetParamString(unsigned char* pStr) {
		if (pStr)
		{
			char* unit = (char*)pStr;
			while ((*unit) && ((*unit)!='_'))
				unit++;
			if (*unit)
			{
				unit++;
				CNStimProfile* pProfile = CNStimProfile::GetStimProfile();
				float fParam = (float)(atof((char*)pStr));
				if (pProfile) {
					fParam = pProfile->ConvertUnit((double)fParam, unit, m_unit);
					if ((fParam - (float)floor((double)fParam)) >= .5)
						m_iParam = (int)fParam + 1;
					else
						m_iParam = (int)fParam;
				}
			}
			else
				m_iParam = atoi((char*)pStr);
		}
		else
			m_iParam = 0;
		return S_OK;
	}
	int* GetParamDataPtr() { return &m_iParam; }
	void SetUnit(const char* unit) {
		strcpy(m_unit, unit);
	}
};

#endif // !defined(AFX_CNSTIMINTPATCHPARAM_H__220EE0A0_0E9A_457A_B720_3633E7224A80__INCLUDED_)
