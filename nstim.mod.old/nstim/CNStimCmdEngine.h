// CNStimCmdEngine.h: interface for the CNStimCmdEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMCMDENGINE_H__2348693C_EAE7_4B44_A3A2_A3B6211B3C71__INCLUDED_)
#define AFX_CNSTIMCMDENGINE_H__2348693C_EAE7_4B44_A3A2_A3B6211B3C71__INCLUDED_

#include "IPortCallback.h"
#include "IPortServerCallback.h"
#include "CTcpIpServer.h"
#include "IPort.h"
#include "CList.h"
#include "CSmartPtr.h"
#include "CNStimEngine.h"
#include "CNStimProfile.h"
#include "INStimCmdEngine.h"
#include "INStimApp.h"
#include "INStimCmd.h"

class CNStimCmdEngine : public INStimCmdEngine, public IPortServerCallback, public IPortCallback
{
	long m_iCount;
protected:
	CTcpIpServer m_Server;
	CList<IPort*, IPort*> m_PortList;
	CSmartPtr<INStimApp> m_App;
//	CSmartPtr<INStimProfile> m_Profile;
//	CSmartPtr<INStimEngine> m_GraphicsEngine;

	int m_iCmdBufferSize;
	char* m_pCmdBuffer;
	int m_iCmdBufferMark;

	CList<INStimCmd*, INStimCmd*> m_CmdList;

	void OnCommand(IPort* pPort, char* pCmd, int len);
public:
	CNStimCmdEngine();
	virtual ~CNStimCmdEngine();

	bool Init(INStimApp* pApp); //const CSmartPtr<INStimProfile>& Profile, const CSmartPtr<INStimEngine>& Engine);
	virtual HRESULT __stdcall OnPortEvent(IUnknown* caller, DWORD event, DWORD param1, DWORD param2);

	virtual HRESULT __stdcall Test() { return S_OK; }

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif // !defined(AFX_CNSTIMCMDENGINE_H__2348693C_EAE7_4B44_A3A2_A3B6211B3C71__INCLUDED_)
