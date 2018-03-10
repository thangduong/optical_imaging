// CNStimCmdEngine.cpp: implementation of the CNStimCmdEngine class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CNStimCmdEngine.h"
#include "CNStimGratingPatch.h"
#include "CNStimPatchCmd.h"
#include "CNStimListCmd.h"
#include "CNStimAtomCmd.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimCmdEngine::CNStimCmdEngine()
{
	m_iCmdBufferSize = 1024*10;						// 10k buffer
	m_pCmdBuffer = new char[m_iCmdBufferSize];
	m_iCmdBufferMark = 0;

	m_CmdList.AddTail(new CNStimCtrlCmd);
	m_CmdList.AddTail(new CNStimPatchCmd);
	m_CmdList.AddTail(new CNStimAtomCmd);
}

CNStimCmdEngine::~CNStimCmdEngine()
{
	delete m_pCmdBuffer;
}

bool CNStimCmdEngine::Init(INStimApp* pApp)//const CSmartPtr<INStimProfile>& Profile, const CSmartPtr<INStimEngine>& Engine)
{
	bool bResult = false;
	char* pBindAddr = "0.0.0.0";
	m_App = pApp;
	DWORD port;
	INStimProfile* pProfile;
	m_App->GetProfile(&pProfile);
	pProfile->GetTcpIpCmdPort(&port);
	pProfile->Release();
	char temp[512];
	pProfile->GetTcpIpBindAddress((unsigned char**)&pBindAddr);
	sprintf(temp, "%s:%d", pBindAddr, port);
	m_Server.RegisterCallback(this);
	m_Server.Start((const unsigned char*)temp);

	return bResult;
}

void CNStimCmdEngine::OnCommand(IPort* pPort, char* pCmd, int len)
{
	// parse the command...
	// first, make the string lowercase
	for (int i = 0; i < len; i++)
		pCmd[i] = tolower(pCmd[i]);

#ifdef _DEBUG
	OutputDebugString(pCmd);
#endif
	POSITION pos = m_CmdList.GetHeadPosition();
	while (pos)
	{
		CSmartPtr<INStimCmd> Cmd = m_CmdList.GetNext(pos);
		if (Cmd->IsCmd((unsigned char*)pCmd) == S_OK)
		{
			Cmd->Exec((unsigned char*)pCmd, m_App.GetPtr(), pPort);
			break;
		}
	}
}

HRESULT __stdcall CNStimCmdEngine::OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2)
{
	if (caller == &m_Server)
	{
		if (event == PSE_ON_CONNECT)
		{
			IPort* pPort = (IPort*)param1;
			pPort->AddRef();
			m_PortList.AddTail(pPort);
			pPort->RegisterCallback(this);
		}
	}
	else
	{
		if (event == PE_DATA_ARRIVED)
		{
			for (int i = 0; i < (int)param2; i++)
			{
				m_pCmdBuffer[m_iCmdBufferMark] = (((char*)param1)[i]);
				if (m_pCmdBuffer[m_iCmdBufferMark] == '\n')
				{
					m_pCmdBuffer[m_iCmdBufferMark] = 0;
					IPort* pPort;
					caller->QueryInterface(IID_IPort, (void**)&pPort);
					OnCommand(pPort, m_pCmdBuffer, m_iCmdBufferMark);
					pPort->Release();
					m_iCmdBufferMark = 0;
				}
				else
				{
					m_iCmdBufferMark++;
					if (m_iCmdBufferMark >= m_iCmdBufferSize)
					{	// in case of overflow
						m_iCmdBufferMark = 0;	
					}
				}
			}
		}
	}

	return S_OK;
}


ULONG __stdcall CNStimCmdEngine::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimCmdEngine::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;

	if (iid == IID_IPortServerCallback)
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
	else if (iid == IID_IPortCallback)
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

ULONG __stdcall CNStimCmdEngine::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

