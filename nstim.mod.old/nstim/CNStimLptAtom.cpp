// CNStimLptAtom.cpp: implementation of the CNStimLptAtom class.
//
//////////////////////////////////////////////////////////////////////
#include "CNStimIntPatchParam.h"
#include "CNStimLptAtom.h"
#include "CList.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimLptAtom::CNStimLptAtom()
{
	CNStimIntPatchParam* pIntParam;

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Port");
	m_pPort = pIntParam->GetParamDataPtr();
	
	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Bit");
	m_pBit = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Value");
	m_pValue = pIntParam->GetParamDataPtr();

	pIntParam = new CNStimIntPatchParam; m_ParamList.AddTail(pIntParam);
	pIntParam->SetParamName((unsigned char*)"Toggle");
	m_pToggle = pIntParam->GetParamDataPtr();

	(*m_pToggle) = (*m_pValue) = (*m_pBit) = 0;
	(*m_pPort) = 1;

}

CNStimLptAtom::~CNStimLptAtom()
{

}
