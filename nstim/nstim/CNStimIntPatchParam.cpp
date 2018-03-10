// CNStimIntPatchParam.cpp: implementation of the CNStimIntPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimIntPatchParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimIntPatchParam::CNStimIntPatchParam()
{
	m_iParam = 0;
	m_unit[0] = 0;
}

CNStimIntPatchParam::~CNStimIntPatchParam()
{

}

HRESULT __stdcall CNStimIntPatchParam::GetParamType(unsigned char** ppType)
{
	if (ppType)
		(*ppType) = (unsigned char*)"int";
	return S_OK;
}

HRESULT __stdcall CNStimIntPatchParam::GetParamInt(int* pInt)
{
	if (pInt)
		(*pInt) = m_iParam;
	return S_OK;
}

HRESULT __stdcall CNStimIntPatchParam::SetParamInt(int pInt)
{
	m_iParam = pInt;
	return S_OK;
}
