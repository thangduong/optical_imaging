// CNCapProfile.h: interface for the CNCapProfile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef CNCAPPROFILE_H
#define CNCAPPROFILE_H

#include <windows.h>
#include <stdio.h>
#include "CIniFile.h"

class CNCapProfile  
{
	long m_iCount;
	char dataLocation[512];
	char imageLocation[512];
	CIniFile m_IniFile;

	int m_LptPort;
	int m_LptStartStopBit;
	int m_LptPreBit;
	int m_LptPostBit;
	int m_LptStoreBit;

	int m_FrameCapBoardNum;
	int m_CamNum;
	char m_ModuleName[512];

	char configFile[512];
	
	int m_LptShutterCtrlBit;
	int m_LptFilterWheelCtrlBit;
public:
	CNCapProfile();
	virtual ~CNCapProfile();

	virtual HRESULT __stdcall GetTcpIpCmdPort(DWORD* pPort) { if (pPort) (*pPort) = 22; return S_OK; }
	virtual HRESULT __stdcall GetTcpIpBindAddress(unsigned char** pBindAddr) { (*pBindAddr) = (unsigned char*)"0.0.0.0"; return S_OK; }
	
	virtual HRESULT __stdcall GetDataLocations(unsigned char** streamloc, unsigned char** imgloc) {
		if (streamloc)
			(*streamloc) = (unsigned char*)dataLocation;
		if (imgloc)
			(*imgloc) = (unsigned char*)imageLocation;
		return S_OK;
	}
	virtual HRESULT __stdcall SetDataLocation(const unsigned char* loc) {
		sprintf(dataLocation, "c:\\temp\\%s", loc);
		CreateDirectory(dataLocation, 0);
		return S_OK;
	}

	virtual HRESULT __stdcall GetLptInfo(int* port, int* startstop, int* prebit, int* postbit, int* storeBit = 0) {
		(*port) = m_LptPort;
		(*startstop) = m_LptStartStopBit;
		(*prebit) = m_LptPreBit;
		(*postbit) = m_LptPostBit;
		if (storeBit)
			(*storeBit) = m_LptStoreBit;
		return S_OK;
	}

	virtual HRESULT __stdcall GetModuleName(unsigned char** pModName) {
		(*pModName) = 0;
		if (m_ModuleName && (strlen(m_ModuleName) > 0))
			(*pModName) = (unsigned char*)m_ModuleName;
		return S_OK;
	}

	virtual HRESULT __stdcall GetConfigFile(unsigned char** pConfigFile) {
		(*pConfigFile) = (unsigned char*)configFile;
		return S_OK;
	}

	virtual HRESULT __stdcall GetBoardNum(int* pBoardNum) {
		(*pBoardNum) = m_FrameCapBoardNum;
		return S_OK;
	}

	virtual HRESULT __stdcall GetCamNum(int* pCamNum) {
		(*pCamNum) = m_CamNum;
		return S_OK;
	}

	virtual HRESULT __stdcall GetShutterCtrlBit(int* pBit) {
		(*pBit) = m_LptShutterCtrlBit;
		return S_OK;
	}

	virtual HRESULT __stdcall GetFilterWheelCtrlBit(int* pBit) {
		(*pBit) = m_LptFilterWheelCtrlBit;		
		return S_OK;
	}

	virtual HRESULT __stdcall Load();
	virtual HRESULT __stdcall Save();


	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif