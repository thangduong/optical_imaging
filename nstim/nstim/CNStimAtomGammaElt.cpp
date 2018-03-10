// CNStimAtomGammaElt.cpp: implementation of the CNStimAtomGammaElt class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimAtomGammaElt.h"
#include "CNStimIntPatchParam.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimAtomGammaElt::CNStimAtomGammaElt()
{
	CNStimIntPatchParam* pIntParam;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"index");
	index = pIntParam->GetParamDataPtr();
	
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"red");
	red = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"green");
	green = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"blue");
	blue = pIntParam->GetParamDataPtr();

	(*index) = (*red) = (*green) = (*blue) = 0;
}

CNStimAtomGammaElt::~CNStimAtomGammaElt()
{

}
