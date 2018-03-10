// CNStimProfile.cpp: implementation of the CNStimProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimProfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimProfile::CNStimProfile() : m_iCount(1), m_Profile("nstim.ini")
{
	SetDefault();
}

CNStimProfile::~CNStimProfile()
{

}

ULONG __stdcall CNStimProfile::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimProfile::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimProfile)
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

ULONG __stdcall CNStimProfile::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}
