// CNStimLptCmd.cpp: implementation of the CNStimLptCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimLptCmd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimLptCmd::CNStimLptCmd() : m_iCount(1)
{

}

CNStimLptCmd::~CNStimLptCmd()
{

}

ULONG __stdcall CNStimLptCmd::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimLptCmd::QueryInterface(REFIID iid, void **ppvObject)
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

ULONG __stdcall CNStimLptCmd::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNStimLptCmd::IsCmd(unsigned char* pCmd)
{
	if (memcmp(pCmd, "lpt ", 4) == 0)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT __stdcall CNStimLptCmd::Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort)
{
	// parse the command
	// we expect the following format:
	//	Lpt grating mask { centerx 0; centery 0; width 100; height 100 }
	//  Lpt <type> <name> { variable value; variable value; ... }
	char* temp = new char[strlen((char*)pCmd) + 1];
	strcpy(temp, (char*)pCmd);

	strtok(temp, " ");

	char* LptName = strtok(0," ");
	char* leftBrace = strtok(0, " ");

	INStimAtom* pLpt;
	if (LptName && leftBrace && (leftBrace[0] == '{'))
	{
		pApp->CreateAtom((unsigned char*)"lpt", &pLpt);
		pLpt->SetName((unsigned char*)LptName);
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

			char* propValue = strtok(0, "; ");
			
			if (propValue)
			{
				INStimParam* pParam = 0;
				pLpt->FindParam((unsigned char*)propName, &pParam);
				if (pParam)
					pParam->SetParamString((unsigned char*)propValue);

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
	pLpt->Init(pEngine);
	pEngine->AddAtom(pLpt);
	pLpt->Release();
	pEngine->SetState(state);

	pEngine->Release();

	delete [] temp;
	return S_OK;
}
