// CNStimIntArrayPatchParam.cpp: implementation of the CNStimIntArrayPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimIntArrayPatchParam.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimIntArrayPatchParam::CNStimIntArrayPatchParam()
{
	m_dwSize = 0;
	m_pData = 0;
}

CNStimIntArrayPatchParam::~CNStimIntArrayPatchParam()
{
	delete m_pData;
}

HRESULT __stdcall CNStimIntArrayPatchParam::GetParamType(unsigned char** pType) {
	(*pType) = (unsigned char*)"BitArray";
	return S_OK;
}


HRESULT __stdcall CNStimIntArrayPatchParam::GetSize(DWORD* pSize) {
	(*pSize) = m_dwSize*sizeof(m_pData[0]);
	return S_OK;
}

HRESULT __stdcall CNStimIntArrayPatchParam::GetByte(int index, unsigned char* pData) {
	(*pData) = (unsigned char)((unsigned char*)m_pData)[index];
	return S_OK;
}

HRESULT __stdcall CNStimIntArrayPatchParam::GetRawData(unsigned char** ppRawData) {
	(*ppRawData) = (unsigned char*)m_pData;
	return S_OK;
}

HRESULT __stdcall CNStimIntArrayPatchParam::SetParamString(unsigned char* pStr) {
	// parse the string for bits
	char* temp = new char[strlen((char*)pStr)+1];
	strcpy(temp, (char*)pStr);
	m_dwSize = 1; //strlen((char*)pStr);
	int i = 0;
	while (temp[i])
	{
		if (temp[i] == ',')
			m_dwSize++;
		i++;
	}
	delete m_pData;
	m_pData = new int[m_dwSize];

	char* pCurInt = temp;
	char* pEnd = temp;
	while (((*pEnd)  != ',') && ((*pEnd) != 0)) {
		pEnd++;
	}
	pEnd[0] = 0;

	for (i = 0; i < m_dwSize; i++) {
		m_pData[i] = atoi(pCurInt);
		pCurInt = pEnd+1;
		pEnd = pEnd+1;
		while (((*pEnd)  != ',') && ((*pEnd) != 0)) {
			pEnd++;
		}
		pEnd[0] = 0;
	}
	delete [] temp;
	return S_OK;
}
