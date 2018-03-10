// CNStimBitArrayPatchParam.cpp: implementation of the CNStimBitArrayPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#include <string.h>
#include "CNStimBitArrayPatchParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimBitArrayPatchParam::CNStimBitArrayPatchParam()
{
	m_dwSize = 0;
	m_pData = 0;
}

CNStimBitArrayPatchParam::~CNStimBitArrayPatchParam()
{
	delete m_pData;
}

HRESULT __stdcall CNStimBitArrayPatchParam::GetParamType(unsigned char** pType) {
	(*pType) = (unsigned char*)"BitArray";
	return S_OK;
}


HRESULT __stdcall CNStimBitArrayPatchParam::GetSize(DWORD* pSize) {
	(*pSize) = m_dwSize;
	return S_OK;
}

HRESULT __stdcall CNStimBitArrayPatchParam::GetByte(int index, unsigned char* pData) {
	(*pData) = (unsigned char)m_pData[index];
	return S_OK;
}

HRESULT __stdcall CNStimBitArrayPatchParam::GetRawData(unsigned char** ppRawData) {
	(*ppRawData) = (unsigned char*)m_pData;
	return S_OK;
}

HRESULT __stdcall CNStimBitArrayPatchParam::SetParamString(unsigned char* pStr) {
	// parse the string for bits

	m_dwSize = strlen((char*)pStr);
	delete m_pData;
	m_pData = new char[m_dwSize];
	for (int i = 0; i < m_dwSize; i++) {
		if (pStr[i] == '0') {
			m_pData[i] = 0;
		}
		else if (pStr[i] == '1') {
			m_pData[i] = 255;
		}
		else {
			m_pData[i] = 128;
		}
	}
	return S_OK;
}
