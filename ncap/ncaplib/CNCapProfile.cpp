// CNCapProfile.cpp: implementation of the CNCapProfile class.
//
//////////////////////////////////////////////////////////////////////

#include "CNCapProfile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNCapProfile::CNCapProfile() : m_iCount(1), m_IniFile("ncap.ini")
{
	strcpy(dataLocation, "c:\\temp");
	strcpy(imageLocation, "c:\\temp\\images");
	CreateDirectory(imageLocation, 0);
	m_LptPort = 0;
	m_LptStartStopBit = 0;
	m_LptPreBit = 1;
	m_LptPostBit = 2;
	m_LptStoreBit = 3;
	m_LptFilterWheelCtrlBit = 7;
	m_LptShutterCtrlBit = 6;

	m_FrameCapBoardNum = 0;
	m_CamNum = 0;
	strcpy(m_ModuleName, "");

	strcpy(configFile, "DalsaCAD1-256T.txt");

}

CNCapProfile::~CNCapProfile()
{

}


HRESULT __stdcall CNCapProfile::Load() {
	strcpy(dataLocation, m_IniFile.ReadString("DATA", "Data Location"));
	strcpy(imageLocation, m_IniFile.ReadString("DATA", "Image Location"));

	m_LptPort = m_IniFile.ReadInt("SYNCHRONIZATION", "LPT Port");
	m_LptStartStopBit = m_IniFile.ReadInt("SYNCHRONIZATION", "LPT Startstop Bit");
	m_LptPreBit = m_IniFile.ReadInt("SYNCHRONIZATION", "LPT Pre Bit");
	m_LptPostBit = m_IniFile.ReadInt("SYNCHRONIZATION", "LPT Post Bit");
	m_LptStoreBit = m_IniFile.ReadInt("SYNCHRONIZATION", "LPT Store Bit");

	m_FrameCapBoardNum = m_IniFile.ReadInt("FRAME CAPTURE", "Board Num");
	m_CamNum = m_IniFile.ReadInt("FRAME CAPTURE", "Camera Num");
	strcpy(m_ModuleName, m_IniFile.ReadString("FRAME CAPTURE", "Module Name"));

	strcpy(configFile, m_IniFile.ReadString("FRAME CAPTURE", "Cam Spec File"));

	m_LptFilterWheelCtrlBit = m_IniFile.ReadInt("CONTROL", "LPT Filter Wheel Ctrl Bit");
	m_LptShutterCtrlBit = m_IniFile.ReadInt("CONTROL", "LPT Shutter Ctrl Bit");
	return S_OK;
}

HRESULT __stdcall CNCapProfile::Save() {
	m_IniFile.WriteString("DATA", "Data Location", dataLocation);
	m_IniFile.WriteString("DATA", "Image Location", imageLocation);
	CreateDirectory(dataLocation, 0);
	CreateDirectory(imageLocation, 0);

	m_IniFile.WriteInt("SYNCHRONIZATION", "LPT Port", m_LptPort);
	m_IniFile.WriteInt("SYNCHRONIZATION", "LPT Pre Bit", m_LptPreBit);
	m_IniFile.WriteInt("SYNCHRONIZATION", "LPT LPT Startstop Bit", m_LptStartStopBit);
	m_IniFile.WriteInt("SYNCHRONIZATION", "LPT Post Bit", m_LptPostBit);
	m_IniFile.WriteInt("SYNCHRONIZATION", "LPT Store Bit", m_LptStoreBit);

	m_IniFile.WriteInt("FRAME CAPTURE", "Board Num", m_FrameCapBoardNum);
	m_IniFile.WriteInt("FRAME CAPTURE", "Camera Num", m_CamNum);
	m_IniFile.WriteString("FRAME CAPTURE", "Module Name", m_ModuleName);

	m_IniFile.WriteString("FRAME CAPTURE", "Cam Spec File", configFile);

	m_IniFile.WriteInt("CONTROL", "LPT Filter Wheel Ctrl Bit", m_LptFilterWheelCtrlBit);
	m_IniFile.WriteInt("CONTROL", "LPT Shutter Ctrl Bit", m_LptShutterCtrlBit);
	return S_OK;
}

ULONG __stdcall CNCapProfile::AddRef(void)
{
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNCapProfile::QueryInterface(REFIID iid, void **ppvObject)
{
	HRESULT hr = E_NOINTERFACE;

	if (iid == IID_IUnknown)
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

ULONG __stdcall CNCapProfile::Release(void)
{
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}
