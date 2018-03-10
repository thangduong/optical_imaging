// CNCapCmdEngine.cpp: implementation of the CNCapCmdEngine class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "CNCapCmdEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNCapCmdEngine::CNCapCmdEngine() : m_iCount(1)
{
	m_iCmdBufferSize = 1024*10;						// 10k buffer
	m_pCmdBuffer = new char[m_iCmdBufferSize];
	m_iCmdBufferMark = 0;
}

CNCapCmdEngine::~CNCapCmdEngine()
{
	delete m_pCmdBuffer;
}

bool CNCapCmdEngine::Init(CNCapProfile* pProfile, CNCapEngine* pEngine) 
{
	DWORD port;
	char temp[512];
	bool bResult = false;
	char* pBindAddr = "0.0.0.0";

	m_pProfile = pProfile;
	m_pEngine = pEngine;
	
	pProfile->GetTcpIpCmdPort(&port);
	pProfile->GetTcpIpBindAddress((unsigned char**)&pBindAddr);
	sprintf(temp, "%s:%d", pBindAddr, port);
	m_Server.RegisterCallback(this);
	bResult = (m_Server.Start((const unsigned char*)temp) == S_OK) ? true : false;

	return bResult;
}

ULONG __stdcall CNCapCmdEngine::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNCapCmdEngine::QueryInterface(REFIID iid, void **ppvObject)
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

ULONG __stdcall CNCapCmdEngine::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

void CNCapCmdEngine::OnCommand(IPort* pPort, char* pCmd, int len)
{
	if (pCmd == 0)
		return;
	// parse the command...
	// first, make the string lowercase
	for (int i = 0; i < len; i++)
		pCmd[i] = tolower(pCmd[i]);

	char* cmd = strtok(pCmd, " \r\n\t");
	if (cmd == 0)
		return;
	if (strcmpi(cmd, "stream") == 0) {
		printf("starting stream");
		char* filename = strtok(0, " \r\n\t");

		if (filename) {
			char* nframes = strtok(0, " \r\n\t");
			int numFrames;
			if (nframes)
				numFrames = atoi(nframes);
			else
				numFrames = -1;

			m_pEngine->StartStream((unsigned char*)filename, numFrames);
		}
		else
		{
			char reply[] = "syntax: stream <filename> [<numframes>]\r\n";
			pPort->Send((const unsigned char*)reply, strlen(reply));
		}
	}
	else if (strcmpi(cmd, "ping") == 0) {
		pPort->Send((unsigned char*)"pong", 5);
	}
	else if (strcmpi(cmd, "streamlpt") == 0) {
		printf("starting stream");
		char* filename = strtok(0, " \r\n\t");

		if (filename) {
			char* nframes = strtok(0, " \r\n\t");
			int bit;
			if (nframes)
				bit = atoi(nframes);
			else
				bit = 6;

			m_pEngine->StartStreamOnLPT((unsigned char*)filename, bit);
		}
		else
		{
			char reply[] = "syntax: stream <filename> [<numframes>]\r\n";
			pPort->Send((const unsigned char*)reply, strlen(reply));
		}
	}
	else if (strcmpi(cmd, "datadir") == 0) {
		m_pEngine->SetDataDir((unsigned char*)strtok(0, " \r\n\t"));
	}
	else if (strcmpi(cmd, "stopstream") == 0) {
		m_pEngine->StopStream();
		printf("stopping stream");
	}
	else if (strcmpi(cmd, "nfts") == 0) {
		char* nfts = strtok(0, " \r\n\t");
		unsigned long nftsv = atoi(nfts);
		m_pEngine->SetNumFramesToSkip(nftsv);
		printf("Num frame to skip set to %d\r\n", nftsv);
	} 
	else if (strcmpi(cmd, "snapid") == 0) {
		char* snapid = strtok(0, " \r\n\t");
		unsigned long snapidv = atoi(snapid);
		m_pEngine->SetSnapId(snapidv);
		printf("Snap id is now: %d\r\n", snapidv);
	}
	else if (strcmpi(cmd, "sumlength") == 0) {
		char* sumlength = strtok(0, " \r\n\t");
		unsigned long sumlengthv = atoi(sumlength);
		m_pEngine->SetSumLength(sumlengthv);
		printf("Sum length is now: %d\r\n", sumlengthv);
	}

	OutputDebugString(pCmd);
}

HRESULT __stdcall CNCapCmdEngine::OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2)
{
	OutputDebugString("on port event\r\n");
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
			for (int i = 0; i < param2; i++)
			{
				m_pCmdBuffer[m_iCmdBufferMark] = (((char*)param1)[i]);
				if (m_pCmdBuffer[m_iCmdBufferMark] == '\n')
				{
					while ((m_pCmdBuffer[m_iCmdBufferMark] == '\n') ||
						(m_pCmdBuffer[m_iCmdBufferMark] == '\r'))
						m_pCmdBuffer[m_iCmdBufferMark--] = 0;
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
