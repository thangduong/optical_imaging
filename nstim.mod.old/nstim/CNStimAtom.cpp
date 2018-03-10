// CNStimAtom.cpp: implementation of the CNStimAtom class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimAtom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNStimAtom::CNStimAtom() : m_iCount(1)
{
	m_pName = 0;
}

CNStimAtom::~CNStimAtom()
{
	delete m_pName;
}

ULONG __stdcall CNStimAtom::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimAtom::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimAtom)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	else if (iid == IID_IUnknown)
	{
		if (ppvObject)
		{
			AddRef();
			(*ppvObject) = this;
			hr = S_OK;
		}
		else
			hr = E_FAIL;
	}
	return hr;
}

ULONG __stdcall CNStimAtom::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}


HRESULT __stdcall CNStimAtom::GetParamCount(int* pParamCount) {
	(*pParamCount) = m_ParamList.GetCount();
	return S_OK;
}

HRESULT __stdcall CNStimAtom::GetParam(int index, INStimParam** ppParam) {
	POSITION pos = m_ParamList.FindIndex(index);
	(*ppParam) = m_ParamList.GetAt(pos);
	return S_OK;
}
