// CNStimAtomFactory.cpp: implementation of the CNStimAtomFactory class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimBuiltInAtomFactory.h"
#include "CNStimGratingPatch.h"
#include "CNStimBinaryNoisePatch.h"
#include "CNStimTestGratingPatch.h"
#include "CNStimLptAtom.h"
#include "CNStimViewportAtom.h"
#include "CNStimColorRectPatch.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimBuiltInAtomFactory::CNStimBuiltInAtomFactory() : m_iCount(1)
{

}

CNStimBuiltInAtomFactory::~CNStimBuiltInAtomFactory()
{

}

ULONG __stdcall CNStimBuiltInAtomFactory::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimBuiltInAtomFactory::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimAtomFactory)
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

ULONG __stdcall CNStimBuiltInAtomFactory::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNStimBuiltInAtomFactory::IsValidAtomType(unsigned char* AtomType)
{
	HRESULT hResult = S_FALSE;
	if (strcmpi((const char*)AtomType, "grating") == 0)
	{
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "binarynoise") == 0)
	{
		hResult = S_OK;
	}
	return hResult;
}

HRESULT __stdcall CNStimBuiltInAtomFactory::CreateAtom(unsigned char* AtomType, INStimAtom** ppAtom)
{
	HRESULT hResult = E_FAIL;
	if (strcmpi((const char*)AtomType, "grating") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimGratingPatch;
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "binarynoise") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimBinaryNoisePatch;
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "tgrating") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimTestGratingPatch;
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "lpt") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimLptAtom;
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "viewport") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimViewportAtom;
		hResult = S_OK;
	}
	else if (strcmpi((const char*)AtomType, "colorrect") == 0)
	{
		if (ppAtom)
			(*ppAtom) = new CNStimColorRectPatch;
		hResult = S_OK;
	}
	return hResult;
}
