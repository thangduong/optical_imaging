// CNStimApp.cpp: implementation of the CNStimApp class.
//
//////////////////////////////////////////////////////////////////////

#include "CNStimApp.h"
#include "CNStimEngine.h"
#include "CNStimGratingPatch.h"
#include "CNStimColorRectPatch.h"
#include "CNStimBuiltInAtomFactory.h"
#include "debug.h"
#include <stdio.h>

CNStimApp theApp;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimApp::CNStimApp() : m_iCount(1)
{
	CDirect3DWnd::RegisterClass();
	m_pProfile = new CNStimProfile;
	m_pEngine = new CNStimEngine;
	m_pCmdEngine = new CNStimCmdEngine;
	m_AtomFactoryList.AddTail(new CNStimBuiltInAtomFactory);

	m_pProfile->Load();
	char logPath[512];
	m_pProfile->GetLogPath((unsigned char*)logPath);
	debug.SetLogPath(logPath);
}

CNStimApp::~CNStimApp()
{
	m_pCmdEngine->Release();
	m_pEngine->Release();
	m_pProfile->Release();
	POSITION pos = m_AtomFactoryList.GetHeadPosition();
	while (pos)
		m_AtomFactoryList.GetNext(pos)->Release();
}

bool CNStimApp::Init() {

	m_pCmdEngine->Init(this);

	bool bResult = m_pEngine->Init(m_pProfile);

	/*
	p = new CNStimColorRectAtom;
	p->SetCenterX(100); p->SetCenterY(100);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();

	p = new CNStimColorRectAtom;
	p->SetCenterX(200); p->SetCenterY(200);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();

	p = new CNStimColorRectAtom;
	p->SetCenterX(200); p->SetCenterY(200);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();

	p = new CNStimColorRectAtom;
	p->SetCenterX(300); p->SetCenterY(300);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();

	p = new CNStimColorRectAtom;
	p->SetCenterX(500); p->SetCenterY(500);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();

  */
//	INStimAtom* p;
	/*
	p = new CNStimGratingAtom;
	p->SetCenterX(50); p->SetCenterY(50);
	p->SetWidth(100); p->SetHeight(100);
	p->SetAngle(10);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p);  
	p->Release();
*/
/*	for (int i = 0; i < 20; i++)
	{
		
		int xl = 100*((i%5))+50;
		int yl = 100*((i/5))+50;

		p = new CNStimGratingAtom;
		p->SetCenterX(xl); p->SetCenterY(yl);
		p->SetWidth(100); p->SetHeight(100);
		p->SetAngle(i*10);
		p->Init(m_pEngine);
		char temp[512];
		sprintf(temp, "%d", i);
		p->SetName((unsigned char*)temp);

		m_pEngine->AddAtom(p); 
		p->Release();
	}

	for (i = 0; i < 30*4; i++)
	{
		
		unsigned char temp[512];
		for (int j = 0;j < 5;j ++)
		{
			sprintf((char*)temp, "%d", rand()%20);
//			OutputDebugString(temp);
			m_pEngine->AddSequenceMarker(i*15, SM_START, temp);
			m_pEngine->AddSequenceMarker((i+1)*15, SM_STOP, temp);
		}
//		OutputDebugString("\r\n");
	}

	/*

  for (int i = 0; i < 100; i++)
	{
		
		int xl = 50*((i%27));
		int yl = 50*((i/27));

	p = new CNStimGratingAtom;
	p->SetCenterX(xl); p->SetCenterY(yl);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();
	}
	*/
/*
	p = new CNStimGratingAtom;
	p->SetCenterX(50); p->SetCenterY(50);
	p->Init(m_pEngine);

	m_pEngine->AddAtom(p); 
	p->Release();
*/
 //	p.Init(m_pEngine);
//	p.Draw(m_pEngine);
	return bResult;
}

void CNStimApp::MessagePump()
{
	m_pEngine->Run();
}

HRESULT __stdcall CNStimApp::CreateAtom(unsigned char* pAtomType, INStimAtom** ppAtom)
{
	HRESULT hResult = E_FAIL;
	POSITION pos = m_AtomFactoryList.GetHeadPosition();
	(*ppAtom) = 0;
	while (pos)
	{
		INStimAtomFactory* pFactory = m_AtomFactoryList.GetNext(pos);
		hResult = pFactory->CreateAtom(pAtomType, ppAtom);
		if (SUCCEEDED(hResult))
			break;
	}
	return hResult;
}

HRESULT __stdcall CNStimApp::GetGraphicsEngine(INStimEngine** ppGraphicsEngine)
{
	(*ppGraphicsEngine) = m_pEngine;
	m_pEngine->AddRef();
	return S_OK;
}

HRESULT __stdcall CNStimApp::GetCommandEngine(INStimCmdEngine** ppCmdEngine)
{
	(*ppCmdEngine) = m_pCmdEngine;
	m_pCmdEngine->AddRef();
	return S_OK;
}

HRESULT __stdcall CNStimApp::GetProfile(INStimProfile** ppProfile)
{
	(*ppProfile) = m_pProfile;
	m_pProfile->AddRef();
	return S_OK;
}


ULONG __stdcall CNStimApp::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimApp::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimApp)
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

ULONG __stdcall CNStimApp::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}
