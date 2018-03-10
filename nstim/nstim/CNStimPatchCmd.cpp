// CNStimPatchCmd.cpp: implementation of the CNStimPatchCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimPatchCmd.h"
#include "INStimPatch.h"
#include "INStimAtom.h"
#include <memory.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimPatchCmd::CNStimPatchCmd() : m_iCount(1)
{

}

CNStimPatchCmd::~CNStimPatchCmd()
{

}

ULONG __stdcall CNStimPatchCmd::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimPatchCmd::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimCmd)
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

ULONG __stdcall CNStimPatchCmd::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNStimPatchCmd::IsCmd(unsigned char* pCmd)
{
	if (memcmp(pCmd, "patch ", 6) == 0)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT __stdcall CNStimPatchCmd::Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort)
{
	// parse the command
	// we expect the following format:
	//	patch grating mask { centerx 0; centery 0; width 100; height 100 }
	//  patch <type> <name> { variable value; variable value; ... }
	char* temp = new char[strlen((char*)pCmd) + 1];
	strcpy(temp, (char*)pCmd);

	strtok(temp, " ");

	char* patchType = strtok(0," ");
	char* patchName = strtok(0," ");
	char* leftBrace = strtok(0, " ");

	INStimAtom* pPatch;
	if (patchType && patchName && leftBrace && (leftBrace[0] == '{'))
	{
		pApp->CreateAtom((unsigned char*)patchType, &pPatch);
		pPatch->SetName((unsigned char*)patchName);
	}

	bool done = false;
	while (!done) {
		char* propName = strtok(0, " ");

		if ((propName == 0) || (propName[0] == '}'))
		{
			done = true;
		}
		else
		{

			char* propValue = strtok(0, " ;");
			
			if (propValue)
			{
				INStimParam* pParam = 0;
				pPatch->SetParam((unsigned char*)propName, (unsigned char*)propValue);
				/*
				pPatch->FindParam((unsigned char*)propName, &pParam);
				if (pParam)
					pParam->SetParamString((unsigned char*)propValue);
				*/
/*				char* junk = 0;
				do {
					junk = strtok(0, "; ");
				} while (junk && (strcmpi(junk, ";") != 0)); */
			}
		}
	}

	INStimEngine* pEngine;
	pApp->GetGraphicsEngine(&pEngine);

	DWORD state;
	pEngine->GetState(&state);
	pEngine->SetState(GE_PAUSE);
	pPatch->Init(pEngine);
	pEngine->AddAtom(pPatch);
	pPatch->Release();
	pEngine->SetState(state);

	pEngine->Release();

	delete [] temp;
	return S_OK;
}
