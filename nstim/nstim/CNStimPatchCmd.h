// CNStimPatchCmd.h: interface for the CNStimPatchCmd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMPATCHCMD_H__16D91066_ADB8_4D24_8B49_45B81B45A598__INCLUDED_)
#define AFX_CNSTIMPATCHCMD_H__16D91066_ADB8_4D24_8B49_45B81B45A598__INCLUDED_

#include <d3dx9.h>
#include "INStimCmd.h"

class CNStimPatchCmd : public INStimCmd  
{
	long m_iCount;
public:
	CNStimPatchCmd();
	virtual ~CNStimPatchCmd();

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

	virtual HRESULT __stdcall IsCmd(unsigned char* pCmd);
	virtual HRESULT __stdcall Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort);
	virtual HRESULT __stdcall Help(unsigned char* Desc, INStimApp* pApp, IPort* pPort) { return S_OK; }

};

#endif // !defined(AFX_CNSTIMPATCHCMD_H__16D91066_ADB8_4D24_8B49_45B81B45A598__INCLUDED_)
