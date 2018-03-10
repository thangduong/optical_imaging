// CNStimLptCmd.h: interface for the CNStimLptCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMLPTCMD_H__EE6FAA8E_F704_4EB8_80D7_208EC6D0EA69__INCLUDED_)
#define AFX_CNSTIMLPTCMD_H__EE6FAA8E_F704_4EB8_80D7_208EC6D0EA69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "INStimCmd.h"

class CNStimLptCmd : public INStimCmd  
{
	long m_iCount;
public:
	CNStimLptCmd();
	virtual ~CNStimLptCmd();

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

	virtual HRESULT __stdcall IsCmd(unsigned char* pCmd);
	virtual HRESULT __stdcall Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort);

	virtual HRESULT __stdcall Help(unsigned char* Desc, INStimApp* pApp, IPort* pPort) {
		return S_OK;
	}
};

#endif // !defined(AFX_CNSTIMLPTCMD_H__EE6FAA8E_F704_4EB8_80D7_208EC6D0EA69__INCLUDED_)
