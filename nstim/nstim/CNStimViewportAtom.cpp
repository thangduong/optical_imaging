// CNStimViewportAtom.cpp: implementation of the CNStimViewportAtom class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimIntPatchParam.h"
#include "CNStimFloatPatchParam.h"
#include "CNStimViewportAtom.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimViewportAtom::CNStimViewportAtom()
{
	CNStimIntPatchParam* pIntParam;
	CNStimFloatPatchParam* pFloatParam;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"x");
	X = (DWORD*)pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"y");
	Y = (DWORD*)pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Width");
	Width = (DWORD*)pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Height");
	Height = (DWORD*)pIntParam->GetParamDataPtr();

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"MinZ");
	MinZ = pFloatParam->GetParamDataPtr();

	pFloatParam = new CNStimFloatPatchParam; m_ParamList.AddTail(pFloatParam);
	pFloatParam->SetParamName((unsigned char*)"MaxZ");
	MaxZ = pFloatParam->GetParamDataPtr();

	(*X) = (*Y) = (*Width) = (*Height) = 0;
	(*MinZ) = 0;
	(*MaxZ) = 1;
}

CNStimViewportAtom::~CNStimViewportAtom()
{

}
