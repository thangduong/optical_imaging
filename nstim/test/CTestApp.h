// CTestApp.h: interface for the CTestApp class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CTESTAPP_H
#define CTESTAPP_H

#include "CWinApp.h"
#include "CDirect3D.h"
#include "CTestWnd.h"
#include "CDirect3DDevice.h"
#include "CTcpIpServer.h"

class CTestApp : public CWinApp  
{
	CTestWnd dw;
	CDirect3D d;
	CTcpIpServer server;
public:
	CTestApp();
	virtual ~CTestApp();

	// inheritable functions
	virtual bool Init();
	virtual void MessagePump();
	virtual int Cleanup();

};

#endif
