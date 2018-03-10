// CNCapApp.cpp: implementation of the CNCapApp class.
//
//////////////////////////////////////////////////////////////////////

#include "CNCapApp.h"
#include "WinIo.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNCapApp::CNCapApp()
{
	m_pCmdEngine = new CNCapCmdEngine;
	m_pProfile = new CNCapProfile;
	m_pEngine = new CNCapEngine;
//	m_pProfile->Save();
}

CNCapApp::~CNCapApp()
{
	m_pCmdEngine->Release();
	m_pEngine->Release();
	m_pProfile->Release();
}

bool CNCapApp::Init() {
	bool bResult = false;
	if (m_pProfile->Load() == S_OK) {
		m_pProfile->Save();
		if (m_pCmdEngine->Init(m_pProfile, m_pEngine)) {
			if (m_pEngine->Init(m_pProfile)) {
				printf("CNCapApp::Init: *INFO* initialized\r\n");
				bResult = true;
			}
		}
	}
	else {
		printf("CNCapApp::Init: *ERROR* can't load profile\r\n");
	}

	return bResult;
}
