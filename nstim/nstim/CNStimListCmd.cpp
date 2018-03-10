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

struct HelpStruct {
	char* cmd;
	char* help;
};
HelpStruct helpInfo[14];

CNStimCtrlCmd::CNStimCtrlCmd() : m_iCount(1)
{
	helpInfo[0].cmd  =			"list";
	helpInfo[0].help =			"list [sequence|atom]\r\n"\
								"          Lists the atoms and sequences in memory\r\n";
	helpInfo[1].cmd  =			"exit";
	helpInfo[1].help =			"exit\r\n"\
								"          Exit NSTIM\r\n";
	helpInfo[2].cmd  =			"clear";
	helpInfo[2].help =			"clear [sequence|atom]\r\n"\
								"          Clear NSTIM\r\n";
	helpInfo[3].cmd = 0;

/*
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
		(memcmp(pCmd, "framerate", 9) == 0) ||
		(memcmp(pCmd, "genframerate", 12) == 0) ||
		(memcmp(pCmd, "dispmode", 8) == 0) ||
		(memcmp(pCmd, "snap ", 5) == 0)
*/
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
		(memcmp(pCmd, "resetatoms", 10) == 0) ||
		(memcmp(pCmd, "stimulate ", 10) == 0) ||
		(memcmp(pCmd, "stimulating", 11) == 0) ||
		(memcmp(pCmd, "simulate ", 9) == 0) ||
		(memcmp(pCmd, "stop", 4) == 0) ||
		(memcmp(pCmd, "sequence ", 9) == 0) ||
		(memcmp(pCmd, "fsequence ", 10) == 0) ||
		(memcmp(pCmd, "preview ", 8) == 0) ||
		(memcmp(pCmd, "loadgamma ", 10) == 0) ||
		(memcmp(pCmd, "dumpgamma", 9) == 0) ||
		(memcmp(pCmd, "setgamma ", 9) == 0) ||
		(memcmp(pCmd, "getgamma ", 9) == 0) ||
		(memcmp(pCmd, "framerate", 9) == 0) ||
		(memcmp(pCmd, "genframerate", 12) == 0) ||
		(memcmp(pCmd, "dispmode", 8) == 0) ||
		(memcmp(pCmd, "ping", 4) == 0) ||
		(memcmp(pCmd, "setparam ", 9) == 0) ||
		(memcmp(pCmd, "getparam ", 9) == 0) ||
		(memcmp(pCmd, "bgcolor", 7) == 0) ||
		(memcmp(pCmd, "snap ", 5) == 0) ||
		(memcmp(pCmd, "reset", 5) == 0) ||			// same as setstate to GE_PREVIEW and clear
		(memcmp(pCmd, "setstate ", 9) == 0)/* ||
		(memcmp(pCmd, "viewport ", 9) == 0)*/)
	{
		return S_OK;
	}
	else
		return S_FALSE;
}

HRESULT __stdcall CNStimCtrlCmd::Help(unsigned char* Desc, INStimApp* pApp, IPort* pPort) {
	char* temp = new char[strlen((char*)Desc)+1];
	strcpy(temp, (char*)Desc);
	char* cmd = strtok(temp, " \r\n");
	cmd = strtok(0, " \r\n");

	if (cmd == 0) {
		for (int i = 0; helpInfo[i].cmd != 0; i++) {
			pPort->Send((unsigned char*)helpInfo[i].help, strlen(helpInfo[i].help));
		}
	}
	else {

	}
	unsigned char zero = 0;
	pPort->Send(&zero, 1);


	delete [] temp;
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
	else if (strcmpi(cmd, "ping") == 0)  {
		pPort->Send((unsigned char*)"pong", 5);
	}
	else if (strcmpi(cmd, "bgcolor") == 0)  {
		char* bkColor = strtok(0, " \r\n");
		if (bkColor)
			pEngine->SetBkColor(atoi(bkColor));
		else
			pEngine->SetBkColor(0x808080);
	}
	else if (strcmpi(cmd, "genframerate") == 0)  {
		DWORD state;
		char* nframes = strtok(temp, " \r\n");
		pEngine->GetState(&state);
		pEngine->SetState(GE_PAUSE);
		if (nframes)
			pEngine->CalibFramerate(atoi(nframes));
		else
			pEngine->CalibFramerate(0);
		pEngine->SetState(state);
	}
	else if (strcmpi(cmd, "resetatoms") == 0)  {
		DWORD state;
		pEngine->GetState(&state);
		pEngine->SetState(GE_PAUSE);
		// send reset to all atoms
		int count;
		pEngine->GetAtomCount(&count);
		for (int i = 0; i < count; i++) {
			INStimAtom* pAtom = 0;
			pEngine->GetAtom(i, &pAtom);
			if (pAtom)
				pAtom->Reset(pEngine);
		}
		pEngine->SetState(state);
	}
	else if (strcmpi(cmd, "stimulating") == 0)  {
		DWORD state;
		pEngine->GetState(&state);
		char result[512];
		sprintf(result, "%d", (GE_STIMULATING==state) ? 1 :0);
		pPort->Send((unsigned char*)result, strlen(result)+1);
	}
	else if (strcmpi(cmd, "framerate") == 0)  {
		double framerate;
		pEngine->GetFrameRate(&framerate);
		char data[512];
		sprintf(data, "%0.8f", framerate);
		pPort->Send((unsigned char*)data, strlen(data)+1);
	}
	else if (strcmpi(cmd, "dispmode") == 0)  {
		D3DDISPLAYMODE* mode = 0;
		pEngine->GetDisplayMode(&mode);
		if (mode) {
			char data[512];
			sprintf(data, "%d, %d, %d, %d", mode->Width, mode->Height, mode->RefreshRate, 
				mode->Format);
			pPort->Send((unsigned char*)data, strlen(data)+1);
		}
	}
	else if (strcmpi(cmd, "loadgamma") == 0) 
	{
		char* filename = strtok(0, " \r\n");
		FILE* fp = fopen(filename, "rb");
		D3DGAMMARAMP ramp;
		fread(ramp.red, 256, 2, fp);
		fread(ramp.green, 256, 2, fp);
		fread(ramp.blue, 256, 2, fp);
		fclose(fp);
		pEngine->SetGammaRamp(&ramp);
	}
	else if (strcmpi(cmd, "setgamma") == 0) 
	{
		char* index = strtok(0, " \r\n");
		char* r = strtok(0, " \r\n");
		char* g = strtok(0, " \r\n");
		char* b = strtok(0, " \r\n");
		pEngine->SetGammaRampElement(atoi(index), atoi(r), atoi(g), atoi(b));
	}
	else if (strcmpi(cmd, "getgamma") == 0) 
	{
		unsigned short r, g, b;
		char* index = strtok(0, " \r\n");
		pEngine->GetGammaRampElement(atoi(index), &r, &g, &b);
		char temp[512];
		sprintf(temp,"%d,%d,%d", r,g,b);
		pPort->Send((unsigned char*)temp, strlen(temp)+1);
	}
	else if (strcmpi(cmd, "setparam") == 0) 
	{
		char* pAtomName = strtok(0, " \r\n");
		char* pParamName = strtok(0, " \r\n");
		char* pParamValue = strtok(0, " \r\n");
		INStimAtom* pAtom = 0;
		pEngine->FindAtom((unsigned char*)pAtomName, &pAtom);
		if (pAtom) {
			DWORD state;
			pEngine->GetState(&state);
			pEngine->SetState(GE_PAUSE);
			pAtom->SetParam((unsigned char*)pParamName, (unsigned char*)pParamValue);
			pEngine->SetState(state);
		}
	}
	else if (strcmpi(cmd, "getparam") == 0) 
	{
		pPort->Send((unsigned char*)"not supported", 14);
	}
	else if (strcmpi(cmd, "dumpgamma") == 0) 
	{
		D3DGAMMARAMP ramp;
		pEngine->GetGammaRamp(&ramp);
		char temp[512];
		for (int i = 0; i < 256; i++) {
			sprintf(temp,"%d,%d,%d\r\n", ramp.red[i],ramp.green[i],ramp.blue[i]);
			pPort->Send((unsigned char*)temp, strlen(temp));
		}
		temp[0] = 0;
		pPort->Send((unsigned char*)temp, 1);
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
	else if (strcmpi(cmd, "reset") == 0)
	{
		pEngine->SetState(GE_PREVIEW);
		pEngine->ClearSequence();
		pEngine->ClearAtom();
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
		if (type == 2) {
			pEngine->AddSequenceMarker(frame, 0, (unsigned char*)pn, (DWORD)&ParamList, 0);
			pEngine->AddSequenceMarker(frame+1, 1, (unsigned char*)pn, (DWORD)&ParamList, 0);
		}
		else
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
	else if (strcmpi(cmd, "setstate") == 0)
	{
		char* state = strtok(0, " \r\n");
		if (state) {
			pEngine->SetState(atoi(state));
		}
		else {
			// ERROR: invalid param, do nothing!
		}
	}
	else if (strcmpi(cmd, "snap") == 0)
	{
		char* filename = strtok(0, " \r\n");
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
