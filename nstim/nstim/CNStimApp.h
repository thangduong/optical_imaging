// CNStimApp.h: interface for the CNStimApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMAPP_H__7AD3EAB7_5210_477B_A37C_858FE6465505__INCLUDED_)
#define AFX_CNSTIMAPP_H__7AD3EAB7_5210_477B_A37C_858FE6465505__INCLUDED_

#include "CWinApp.h"
#include "CNStimEngine.h"
#include "CNStimProfile.h"
#include "CNStimCmdEngine.h"
#include "INStimAtomFactory.h"
#include "INStimApp.h"

class CNStimApp : public CWinApp, public INStimApp
{
	long m_iCount;
	CNStimProfile* m_pProfile;
	CNStimEngine* m_pEngine;
	CNStimCmdEngine* m_pCmdEngine;
	CList<INStimAtomFactory*,INStimAtomFactory*> m_AtomFactoryList;
public:
	CNStimApp();
	virtual ~CNStimApp();
	virtual bool Init();
	virtual void MessagePump();

	virtual HRESULT __stdcall GetGraphicsEngine(INStimEngine** ppGraphicsEngine);
	virtual HRESULT __stdcall GetCommandEngine(INStimCmdEngine** ppCmdEngine);
	virtual HRESULT __stdcall GetProfile(INStimProfile** ppProfile);
	virtual HRESULT __stdcall CreateAtom(unsigned char* pAtomType, INStimAtom** ppAtom);

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif // !defined(AFX_CNSTIMAPP_H__7AD3EAB7_5210_477B_A37C_858FE6465505__INCLUDED_)
