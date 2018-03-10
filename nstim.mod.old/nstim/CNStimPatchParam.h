// CNStimPatchParam.h: interface for the CNStimPatchParam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMPATCHPARAM_H__6BBB0F7E_4EB8_4B2F_B056_712201D2E359__INCLUDED_)
#define AFX_CNSTIMPATCHPARAM_H__6BBB0F7E_4EB8_4B2F_B056_712201D2E359__INCLUDED_

#include <string.h>
#include "INStimParam.h"

class CNStimPatchParam : public INStimParam  
{
	long m_iCount;
	char* m_pName;
public:
	CNStimPatchParam();
	virtual ~CNStimPatchParam();

	virtual HRESULT __stdcall GetParamType(unsigned char** ppType) { return E_FAIL; }
	virtual HRESULT __stdcall GetParamInt(int* pInt) { return E_FAIL; }
	virtual HRESULT __stdcall GetParamDouble(double* pDouble) { return E_FAIL; }
	virtual HRESULT __stdcall GetParamName(unsigned char** ppName) {
		if (ppName)
			(*ppName) = (unsigned char*)m_pName;
		return S_OK;
	}

	virtual HRESULT __stdcall SetParamInt(int pInt) { return E_FAIL; }
	virtual HRESULT __stdcall SetParamDouble(double pDouble) { return E_FAIL; }
	virtual HRESULT __stdcall SetParamName(unsigned char* pName) {
		delete m_pName;
		m_pName = new char[strlen((char*)pName)+1];
		strcpy(m_pName, (char*)pName);
		return S_OK;
	}
	virtual HRESULT __stdcall GetParamFloat(float* pFloat) { return E_FAIL; }
	virtual HRESULT __stdcall SetParamFloat(float value) { return E_FAIL; }
	virtual HRESULT __stdcall GetSize(DWORD* pSize) { return E_FAIL; }
	virtual HRESULT __stdcall GetByte(int index, unsigned char* pData) { return E_FAIL; }
	virtual HRESULT __stdcall GetRawData(unsigned char** ppRawdata) { return E_FAIL; }
	virtual HRESULT __stdcall GetParamString(unsigned char* buff, int buffSize) { return E_FAIL; }

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif // !defined(AFX_CNSTIMPATCHPARAM_H__6BBB0F7E_4EB8_4B2F_B056_712201D2E359__INCLUDED_)
