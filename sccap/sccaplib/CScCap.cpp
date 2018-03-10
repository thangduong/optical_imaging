// CScCap.cpp: implementation of the CScCap class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "CScCap.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScCap::CScCap() : m_cRefCnt(1)
{
	m_Connection.RegisterCallback(this);
	m_outFile = 0;
	m_pCapReceiver = 0;
}

CScCap::~CScCap()
{
	m_Connection.UnregisterCallback(this);
}

bool CScCap::Connect(const char* server) {
	return m_Connection.Open((const unsigned char*)server) == S_OK ? true : false;
}

bool CScCap::Disconnect() {
	return m_Connection.Close() == S_OK ? true : false;
}

bool CScCap::SendCmd(const char* cmd) {
	char* junk = new char[strlen(cmd)+5];
	sprintf(junk, "%s\r\n", cmd);
	bool result = m_Connection.Send((const unsigned char*)junk, strlen(junk)) == S_OK ? true: false;
	delete junk;
	return result;
}

HRESULT __stdcall CScCap::OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2) {
	printf("OnPortEvent %d\r\n", event);
	if (event == PE_DATA_ARRIVED) {
		printf("got %d bytes\r\n", param2);
		char* temp = (char*)param1;
		if (strlen(temp) > 1) {
			if (temp[0] == 'D') {
				// DP
				if (temp[1] == 'P') {
					int chan;
					unsigned long time;
					sscanf(temp+2, "%d %d", &chan, &time);
					printf("dp at %d %d\r\n", chan, time);

					if (m_outFile) {
						int tag = TAG_DP;
						int size = 8;
						fwrite(&tag, 1, sizeof(tag), m_outFile);
						fwrite(&size, 1, sizeof(size), m_outFile);
						fwrite(&chan, 1, sizeof(chan), m_outFile);
						fwrite(&time, 1, sizeof(time), m_outFile);
						fflush(m_outFile);
					}
					OnDp(chan, time);
				}
			}
			else if (temp[0] == 'S') {
				// spike
				int chan, id, junk;
				unsigned long time;
				sscanf(temp+1, "%d %d %d %d", &chan, &id, &junk, &time);
				printf("spike at time %d: %d, %d", time, chan, id);
				if (m_outFile) {
					int tag = TAG_SPIKE;
					int size = 16;
					fwrite(&tag, 1, sizeof(tag), m_outFile);
					fwrite(&size, 1, sizeof(size), m_outFile);
					fwrite(&chan, 1, sizeof(chan), m_outFile);
					fwrite(&id, 1, sizeof(id), m_outFile);
					fwrite(&junk, 1, sizeof(junk), m_outFile);
					fwrite(&time, 1, sizeof(time), m_outFile);
					fflush(m_outFile);
				}
				OnSpike(chan, id, junk, time);
			}
		}
	}
	return S_OK;
}

void CScCap::OnSpike(int chan, int id, int junk, unsigned long time) {
	if (m_pCapReceiver)
		m_pCapReceiver->OnSpike(chan, id, junk, time);
}

void CScCap::OnDp(int chan, unsigned long time) {
	if (m_pCapReceiver)
		m_pCapReceiver->OnDp(chan, time);
}

bool CScCap::StartCap(const char* filename) {
	if (m_outFile != 0) {
		fclose(m_outFile);
	}
	m_outFile = fopen(filename, "wb");
	return (m_outFile != 0) ? true : false;
}

bool CScCap::StopCap() {
	if (m_outFile != 0) {
		fclose(m_outFile);
		m_outFile = 0;
	}
	return (m_outFile == 0) ? true : false;
}

void CScCap::SetCapReceiver(IScCapReceiver* pReceiver) {
	m_pCapReceiver = pReceiver;
}

IScCapReceiver* CScCap::GetCapReceiver() {
	return m_pCapReceiver;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//	IUnknown Implementation
////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT __stdcall CScCap::QueryInterface(REFIID iid, LPVOID* pObj)
{
	(*pObj) = NULL;
	if (iid == IID_IUnknown)
	{
		(*pObj) = static_cast<IUnknown*>(this);
	}
	else if (iid == IID_IPortCallback)
	{
		(*pObj) = static_cast<IPortCallback*>(this);
	}
	if (*pObj)
	{
		((IUnknown*)(*pObj))->AddRef();
		return S_OK;
	}
	else 
		return E_NOINTERFACE;
}


ULONG __stdcall CScCap::AddRef()
{
	return InterlockedIncrement((long*)&m_cRefCnt);
}


ULONG __stdcall CScCap::Release()
{
	if (InterlockedDecrement((long*)&m_cRefCnt) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_cRefCnt;
}

