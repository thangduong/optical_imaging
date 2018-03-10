// CNStimLptAtom.h: interface for the CNStimLptAtom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMLPTATOM_H__06F9FEC3_B7D1_41A8_9F82_7418B08D81D9__INCLUDED_)
#define AFX_CNSTIMLPTATOM_H__06F9FEC3_B7D1_41A8_9F82_7418B08D81D9__INCLUDED_

#include "CNStimAtom.h"
#include "CLPTPort.h"

class CNStimLptAtom : public CNStimAtom  
{
	int* m_pPort;
	int* m_pBit;
	int* m_pValue;
	int* m_pToggle;
	CLPTPort m_Port;
public:
	CNStimLptAtom();
	virtual ~CNStimLptAtom();

	virtual HRESULT __stdcall Exec(INStimEngine* pEngine) {
		if ((*m_pToggle) == 0)
			m_Port.SetBit((*m_pBit), (*m_pValue) ? true : false);
		else
			m_Port.ToggleBit((*m_pBit));
		return S_OK;
	}
	virtual HRESULT __stdcall Init(INStimEngine* pEngine) { 
		m_Port.SetPortNum((*m_pPort));
		return S_OK; 
	}
	virtual HRESULT __stdcall Reset(INStimEngine* pEngine) { 
		return S_OK;
	}
	virtual HRESULT __stdcall GetType(unsigned char** ppType) { if (ppType) (*ppType) = (unsigned char*)"lpt"; return S_OK; }

};

#endif // !defined(AFX_CNSTIMLPTATOM_H__06F9FEC3_B7D1_41A8_9F82_7418B08D81D9__INCLUDED_)
