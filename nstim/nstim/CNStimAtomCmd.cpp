// CNStimAtomCmd.cpp: implementation of the CNStimAtomCmd class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimAtomCmd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimAtomCmd::CNStimAtomCmd() : m_iCount(1)
{

}

CNStimAtomCmd::~CNStimAtomCmd()
{

}

ULONG __stdcall CNStimAtomCmd::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimAtomCmd::QueryInterface(REFIID iid, void **ppvObject)
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

ULONG __stdcall CNStimAtomCmd::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNStimAtomCmd::IsCmd(unsigned char* pCmd)
{
	if (memcmp(pCmd, "atom ", 4) == 0)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT __stdcall CNStimAtomCmd::Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort)
{
	// parse the command
	// we expect the following format:
	//	Atom grating mask { centerx 0; centery 0; width 100; height 100 }
	//  Atom <type> <name> { variable value; variable value; ... }
	char* temp = new char[strlen((char*)pCmd) + 1];
	strcpy(temp, (char*)pCmd);
	char* atom = strtok(temp, " ");

	char* AtomType = strtok(0, " ");

	char* AtomName = strtok(0," ");
	char* leftBrace = strtok(0, " ");

	INStimAtom* pAtom = 0;
	if (AtomName && leftBrace && (leftBrace[0] == '{'))
	{
		pApp->CreateAtom((unsigned char*)AtomType, &pAtom);
		if (pAtom)	
			pAtom->SetName((unsigned char*)AtomName);
	}

	if (pAtom) {
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
					pAtom->SetParam((unsigned char*)propName, (unsigned char*)propValue);
					/*
					pAtom->FindParam((unsigned char*)propName, &pParam);
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
		pAtom->Init(pEngine);
		pEngine->AddAtom(pAtom);
		pAtom->Release();
		pEngine->SetState(state);

		pEngine->Release();
	}
	else {
		pPort->Send((unsigned char*)"no such atom type exist!", strlen("no such atom type exist!")+1);
	}

	delete [] temp;
	return S_OK;
}
