// CNStimIntArrayPatchParam.h: interface for the CNStimIntArrayPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMINTARRAYPATCHPARAM_H__8A658F79_63F3_4CB8_B17F_0E8AB23316B9__INCLUDED_)
#define AFX_CNSTIMINTARRAYPATCHPARAM_H__8A658F79_63F3_4CB8_B17F_0E8AB23316B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CNStimPatchParam.h"

class CNStimIntArrayPatchParam : public CNStimPatchParam  
{
	DWORD m_dwSize;
	int* m_pData;
public:
	CNStimIntArrayPatchParam();
	virtual ~CNStimIntArrayPatchParam();

	virtual HRESULT __stdcall GetParamType(unsigned char** pType);
	virtual HRESULT __stdcall GetSize(DWORD* pSize);
	virtual HRESULT __stdcall GetByte(int index, unsigned char* pData);
	virtual HRESULT __stdcall GetRawData(unsigned char** ppRawData);
	virtual HRESULT __stdcall SetParamString(unsigned char* pStr);
	int** GetParamDataPtr() { return &m_pData; }
	int* GetParamSizePtr() { return (int*)&m_dwSize; }

};

#endif // !defined(AFX_CNSTIMINTARRAYPATCHPARAM_H__8A658F79_63F3_4CB8_B17F_0E8AB23316B9__INCLUDED_)
