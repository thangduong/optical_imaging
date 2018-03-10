// CNStimColorRectPatch.cpp: implementation of the CNStimColorRectPatch class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimColorRectPatch.h"
#include "CDirect3DDevice.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimColorRectPatch::CNStimColorRectPatch()
{
	CNStimIntPatchParam* pIntParam;
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Width");
	m_pWidth = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Height");
	m_pHeight = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Color");
	m_pColor = pIntParam->GetParamDataPtr();
}

CNStimColorRectPatch::~CNStimColorRectPatch()
{

}

HRESULT __stdcall CNStimColorRectPatch::AdvanceFrame(int numFrames)
{
	return S_OK;
}

HRESULT __stdcall CNStimColorRectPatch::Draw(INStimEngine* pEngine)
{
	IDirect3DDevice9* pDevice = 0;
	pEngine->GetDirect3DDevice(&pDevice);
	CDirect3DDevice Device = pDevice;
	if (pDevice)
	{
		D3DRECT r;
		r.x1 = (*m_pCenterX)-(*m_pWidth)/2;
		r.y1 = (*m_pCenterY)-(*m_pHeight)/2;
		r.x2 = (*m_pCenterX)+(*m_pWidth)/2;
		r.y2 = (*m_pCenterY)+(*m_pHeight)/2;
		pDevice->Clear(1,&r,D3DCLEAR_TARGET, (*m_pColor), 0,0);
	}
	return S_OK;
}

HRESULT __stdcall CNStimColorRectPatch::Init(INStimEngine* pEngine)
{
	return S_OK;
}

