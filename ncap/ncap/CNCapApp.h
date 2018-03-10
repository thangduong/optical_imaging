// CNCapApp.h: interface for the CNCapApp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CNCAPAPP_H
#define CNCAPAPP_H

#include "CNCapCmdEngine.h"
#include "CNCapProfile.h"
#include "CNCapEngine.h"
#include "CWinApp.h"

class CNCapApp : public CWinApp
{
	CNCapCmdEngine* m_pCmdEngine;
	CNCapProfile* m_pProfile;
	CNCapEngine* m_pEngine;
public:
	CNCapApp();
	virtual ~CNCapApp();

	bool Init();
	bool Run() { return m_pEngine->Run(); }
};

#endif
