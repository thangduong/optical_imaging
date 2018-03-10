// CNStimBitArrayPatchParam.h: interface for the CNStimBitArrayPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMBITARRAYPATCHPARAM_H__818EFAD5_11C7_430B_8B02_7F0F10078C0A__INCLUDED_)
#define AFX_CNSTIMBITARRAYPATCHPARAM_H__818EFAD5_11C7_430B_8B02_7F0F10078C0A__INCLUDED_

#include "CNStimPatchParam.h"

class CNStimBitArrayPatchParam : public CNStimPatchParam  
{
	DWORD m_dwSize;
	char* m_pData;
public:
	CNStimBitArrayPatchParam();
	virtual ~CNStimBitArrayPatchParam();
	
	virtual HRESULT __stdcall GetParamType(unsigned char** pType);
	virtual HRESULT __stdcall GetSize(DWORD* pSize);
	virtual HRESULT __stdcall GetByte(int index, unsigned char* pData);
	virtual HRESULT __stdcall GetRawData(unsigned char** ppRawData);
	virtual HRESULT __stdcall SetParamString(unsigned char* pStr);

};

#endif // !defined(AFX_CNSTIMBITARRAYPATCHPARAM_H__818EFAD5_11C7_430B_8B02_7F0F10078C0A__INCLUDED_)
