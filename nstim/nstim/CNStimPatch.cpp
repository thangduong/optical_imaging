// CNStimPatch.cpp: implementation of the CNStimPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimPatch.h"
#include "CNStimFloatPatchParam.h"
#include "CNStimStringPatchParam.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimPatch::CNStimPatch() : m_iCount(1)
{
	CNStimIntPatchParam* pIntParam;
	CNStimFloatPatchParam* pFloatParam;
	CNStimStringPatchParam* pStringParam;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"CenterX");
	m_pCenterX = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"CenterY");
	m_pCenterY = pIntParam->GetParamDataPtr();
	pIntParam->SetUnit("pix");

	/*
	pIntParam = new CNStimIntPatchParam;
	pIntParam->SetParamName((unsigned char*)"Duration");
	m_pDuration = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam;
	pIntParam->SetParamName((unsigned char*)"TemporalOffset");
	m_pTemporalOffset = pIntParam->GetParamDataPtr();
	*/

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"BlitType");
	m_pBlitType = pIntParam->GetParamDataPtr();

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"BlitAngle");
	m_pBlitAngle = pFloatParam->GetParamDataPtr();
	
	(*m_pBlitAngle) = 0;
//	m_fAngle = 0;
//	m_iCenterX = m_iCenterY = 100;
//	m_iWidth = m_iHeight = 100;

	m_pName = 0;


	pStringParam = new CNStimStringPatchParam; m_ParamList.AddTail(pStringParam);
	pStringParam->SetParamName((unsigned char*)"Viewport");
	m_pViewportName = pStringParam->GetParamDataPtr();
	m_pViewport = 0;

	m_bPreview = false;
}

CNStimPatch::~CNStimPatch()
{
	delete m_pName;
}

ULONG __stdcall CNStimPatch::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimPatch::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimPatch)
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

ULONG __stdcall CNStimPatch::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}


HRESULT __stdcall CNStimPatch::GetParamCount(int* pParamCount) {
	(*pParamCount) = m_ParamList.GetCount();
	return S_OK;
}

HRESULT __stdcall CNStimPatch::GetParam(int index, INStimParam** ppParam) {
	POSITION pos = m_ParamList.FindIndex(index);
	(*ppParam) = m_ParamList.GetAt(pos);
	return S_OK;
}
