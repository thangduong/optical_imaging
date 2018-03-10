// CNStimCtrlCmd.cpp: implementation of the CNStimCtrlCmd class.
//
// REVISION HISTORY
//	
//	10/21/2005	Thang		Added this rev history
//							Added code to handle the gamma command
//								gamma <filename>
//							Changes the gamma ramp (LUT)
//							This only works if video card has cap
//////////////////////////////////////////////////////////////////////

#include "CNStimListCmd.h"
#include "INStimPatch.h"
#include "INStimEngine.h"
#include "CDirect3DSurface.h"
#include "CDirect3DDevice.h"
#include "CList.h"
#include "CNStimSequence.h"
#include <memory.h>
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNStimCtrlCmd::CNStimCtrlCmd() : m_iCount(1)
{

}

CNStimCtrlCmd::~CNStimCtrlCmd()
{

}

ULONG __stdcall CNStimCtrlCmd::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNStimCtrlCmd::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;
	if (iid == IID_INStimCmd)
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

ULONG __stdcall CNStimCtrlCmd::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNStimCtrlCmd::IsCmd(unsigned char* pCmd)
{
	if ((memcmp(pCmd, "list", 4) == 0) ||
		(memcmp(pCmd, "exit", 4) == 0) ||
		(memcmp(pCmd, "clear", 5) == 0) ||
		(memcmp(pCmd, "stimulate ", 10) == 0) ||
		(memcmp(pCmd, "simulate ", 9) == 0) ||
		(memcmp(pCmd, "stop", 4) == 0) ||
		(memcmp(pCmd, "sequence ", 9) == 0) ||
		(memcmp(pCmd, "fsequence ", 10) == 0) ||
		(memcmp(pCmd, "preview ", 8) == 0) ||
		(memcmp(pCmd, "gamma ", 6) == 0) ||
		(memcmp(pCmd, "snap ", 5) == 0)/* ||
		(memcmp(pCmd, "viewport ", 9) == 0)*/)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT __stdcall CNStimCtrlCmd::Help(unsigned char* Desc, INStimApp* pApp, IPort* pPort) {
	return S_OK;
}


HRESULT __stdcall CNStimCtrlCmd::Exec(unsigned char* pCmd, INStimApp* pApp, IPort* pPort)
{
	char* temp = new char[strlen((char*)pCmd)+1];
	strcpy(temp, (char*)pCmd);
	INStimEngine* pEngine;
	pApp->GetGraphicsEngine(&pEngine);
	
	char* cmd = strtok(temp, " \r\n");
	if (strcmpi(cmd, "exit") == 0)
	{
		pEngine->Stop();
	}
	else if (strcmpi(cmd, "gamma") == 0) 
	{
		char* filename = strtok(0, " \r\n");
		FILE* fp = fopen(filename, "rb");
		D3DGAMMARAMP ramp;
		fread(ramp.red, 256, 2, fp);
		fread(ramp.green, 256, 2, fp);
		fread(ramp.blue, 256, 2, fp);
		fclose(fp);
		INStimEngine* pGEng;
		IDirect3DDevice9* pDevice;
		pApp->GetGraphicsEngine(&pGEng);
		pGEng->GetDirect3DDevice(&pDevice);

		pDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION, &ramp);
	}
	else if (strcmpi(cmd, "stimulate") == 0)
	{
		char* nfs = strtok(0, " \r\n");
		DWORD numFrames;
		if (nfs != 0)
		{
			numFrames = atoi(nfs);
			pEngine->Stimulate(numFrames, (unsigned char*)strtok(0, " \t\r\n"));
		}			
	}
	else if (strcmpi(cmd, "simulate") == 0)
	{
		char* nfs = strtok(0, " \r\n");
		DWORD numFrames;
		if (nfs != 0)
		{
			numFrames = atoi(nfs);
			pEngine->Simulate(numFrames, (unsigned char*)strtok(0, " \t\r\n"));
		}			
	}
	else if (strcmpi(cmd, "preview") == 0)
	{
		char* patch = strtok(0, " \r\n\t");
		char* prev = strtok(0, " \t\r\n");
		if (patch) {
			INStimAtom* pAtom = 0;
			pEngine->FindAtom((unsigned char*)patch, &pAtom);
			if (pAtom && ((prev == 0) || (atoi(prev)))) {
				pAtom->SetPreview(1);
			}
			else if (pAtom)
				pAtom->SetPreview(0);
		}
	}
	else if (strcmpi(cmd, "stop") == 0)
	{
		pEngine->Stop();
	}
	else if (strcmpi(cmd, "sequence") == 0)
	{
		int frame = atoi(strtok(0, " "));
		int type = atoi(strtok(0, " "));
		char* pn = (strtok(0, " \r\n"));
		CList<NStimSequenceItemParam, NStimSequenceItemParam> ParamList;
		bool done = false;
		while (!done) {
			char* propName = strtok(0, " ");

			if ((propName == 0) || (propName[0] == '}'))
			{
				done = true;
			}
			else
			{

				char* propValue = strtok(0, "; ");
				
				if (propValue)
				{
					NStimSequenceItemParam p;
					p.ParamName = propName;
					p.ParamValue = propValue;
					ParamList.AddTail(p);
	/*				char* junk = 0;
					do {
						junk = strtok(0, "; ");
					} while (junk && (strcmpi(junk, ";") != 0)); */
				}
			}
		}
		pEngine->AddSequenceMarker(frame, type, (unsigned char*)pn, (DWORD)&ParamList, 0);
	}
	else if (strcmpi(cmd, "ssequence") == 0)
	{
		int frame = atoi(strtok(0, " "));
		int order = atoi(strtok(0, " "));
		int type = atoi(strtok(0, " "));
		char* pn = (strtok(0, " \r\n"));
		CList<NStimSequenceItemParam, NStimSequenceItemParam> ParamList;
		bool done = false;
		while (!done) {
			char* propName = strtok(0, " ");

			if ((propName == 0) || (propName[0] == '}'))
			{
				done = true;
			}
			else
			{

				char* propValue = strtok(0, "; ");
				
				if (propValue)
				{
					NStimSequenceItemParam p;
					p.ParamName = propName;
					p.ParamValue = propValue;
					ParamList.AddTail(p);
	/*				char* junk = 0;
					do {
						junk = strtok(0, "; ");
					} while (junk && (strcmpi(junk, ";") != 0)); */
				}
			}
		}
		pEngine->AddSequenceMarker(frame, type, (unsigned char*)pn, (DWORD)&ParamList, order);
	}
	else if (strcmpi(cmd, "fsequence") == 0)
	{
		char* pn = (strtok(0, " \t\r\n"));
		int frame;
		char* framestr;
		bool done = false;
		int state = 0;
		while (!done) {
			framestr = (strtok(0, " \t\r\n"));
			if (framestr) {
				frame = atoi(framestr);
				pEngine->AddSequenceMarker(frame, state, (unsigned char*)pn, 0, 0);
				state = (state + 1) % 2;
			}
			else
				done = true;
		}
	}
	else if (strcmpi(cmd, "clear") == 0)
	{
		char* loc = strtok(0, " \r\n");
		if (loc) {
			if (strcmpi(loc, "sequence") == 0) {
				pEngine->ClearSequence();
			}
			else if (strcmpi(loc, "atom") == 0) {
				pEngine->ClearAtom();
			}
		}
		else {
			pEngine->ClearSequence();
			pEngine->ClearAtom();
		}
	}
	else if (strcmpi(cmd, "snap") == 0)
	{
		char* filename = strtok(0, " \r\n");
		IDirect3DDevice9* pDevice;
		pEngine->GetDirect3DDevice(&pDevice);
		DWORD state;
		pEngine->GetState(&state);
		pEngine->SetState(GE_PAUSE);
		pEngine->Snap((unsigned char*)filename);
		pEngine->SetState(state);
	}
	else if (strcmpi(cmd, "list") == 0)
	{
		char* listItem = strtok(0, " \t\r\n");

		INStimEngine* pEngine;
		pApp->GetGraphicsEngine(&pEngine);


		if (listItem == 0) {
			int patchCount;
			char temp[512];
			pEngine->GetAtomCount(&patchCount);

			sprintf(temp, "There are %d patches\r\n", patchCount);
			pPort->Send((unsigned char*)temp, strlen(temp));

			INStimAtom* pAtom;
			char* name;
			char* type;
			for (int i = 0; i< patchCount; i++)
			{
				pEngine->GetAtom(i, &pAtom);
				pAtom->GetName((unsigned char**)&name);
				pAtom->GetType((unsigned char**)&type);
				sprintf(temp, "        atom %d of type %s name %s\r\n", i, type, name);
				pPort->Send((unsigned char*)temp, strlen(temp));
			}
		}
		else if (strcmpi(listItem, "sequence") == 0) {
		}
		else if (strcmpi(listItem, "atom") == 0) {
		}
		else {
			INStimAtom* pAtom = 0;
			pEngine->FindAtom((unsigned char*)listItem, &pAtom);
			if (pAtom) {
				pAtom->List(pPort);
			}
		}
	}
	pEngine->Release();
	delete [] temp;

	return S_OK;
}
