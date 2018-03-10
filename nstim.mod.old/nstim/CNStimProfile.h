////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CNStimProfile.h
//
//
//	REVISION HISTORY
//
//	10/8/2005	Thang		Added this header
//							Added code to store to and load from INI file
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSTIMPROFILE_H__DCC73FE6_586F_40B0_9EA0_DB13D543541E__INCLUDED_)
#define AFX_CNSTIMPROFILE_H__DCC73FE6_586F_40B0_9EA0_DB13D543541E__INCLUDED_

#include <unknwn.h>
#include "INStimProfile.h"
#include "CIniFile.h"

class CNStimProfile : public INStimProfile
{
	long m_iCount;
	CIniFile m_Profile;

	int m_LptSyncPortNum;
	int m_LptSyncPreframeBit;
	int m_LptSyncPostFrameBit;
	int m_LptSyncStimOnStrobeBit;
	int m_LptSyncFrameDropBit;

	int m_ThreadPriority;

	int m_Fullscreen;
	int m_TcpIpPort;

	int m_FullscreenResX;
	int m_FullscreenResY;
	int m_FullscreenFramerate;
	int m_WindowedResX;
	int m_WindowedResY;
public:
	CNStimProfile();
	virtual ~CNStimProfile();

	virtual HRESULT __stdcall SetDefault() {
		m_LptSyncPortNum = 0;
		m_LptSyncPreframeBit = 0;
		m_LptSyncPostFrameBit = 1;
		m_LptSyncStimOnStrobeBit = 2;
		m_LptSyncFrameDropBit = 3;
		
		m_ThreadPriority = THREAD_PRIORITY_NORMAL;
		
		m_Fullscreen = 0;
		m_TcpIpPort = 21;
		
		m_FullscreenResX = 1920;
		m_FullscreenResY = 1080;
		m_FullscreenFramerate = 75;
		m_WindowedResX = 640;
		m_WindowedResY = 480;

		return S_OK;
	}

	virtual HRESULT __stdcall Load() {
		m_LptSyncPortNum = m_Profile.ReadInt("SYNCHRONIZATION","LPT Port Number");
		m_LptSyncPreframeBit = m_Profile.ReadInt("SYNCHRONIZATION","Preframe Bit");
		m_LptSyncPostFrameBit = m_Profile.ReadInt("SYNCHRONIZATION","Postframe Bit");
		m_LptSyncStimOnStrobeBit = m_Profile.ReadInt("SYNCHRONIZATION","StimOn Strobe Bit");
		m_LptSyncFrameDropBit = m_Profile.ReadInt("SYNCHRONIZATION","Frame drop Bit");
		
		char* temp = m_Profile.ReadString("THREADING", "Thread Priority");
		if (strcmpi(temp, "THREAD_PRIORITY_NORMAL") == 0) {
			m_ThreadPriority = THREAD_PRIORITY_NORMAL;
		}
		else if (strcmpi(temp, "THREAD_PRIORITY_TIME_CRITICAL") == 0) {
			m_ThreadPriority = THREAD_PRIORITY_TIME_CRITICAL;
		}
			
		m_TcpIpPort = m_Profile.ReadInt("CONNECTION","TcpIp Port");;

		m_Fullscreen = m_Profile.ReadInt("SCREEN","Fullscreen");
		
		m_FullscreenResX = m_Profile.ReadInt("SCREEN","Fullscreen Resolution X");;
		m_FullscreenResY = m_Profile.ReadInt("SCREEN","Fullscreen Resolution Y");;
		m_FullscreenFramerate = m_Profile.ReadInt("SCREEN","Fullscreen Framerate");;
		m_WindowedResX = m_Profile.ReadInt("SCREEN","Windowed Resolution X");;
		m_WindowedResY = m_Profile.ReadInt("SCREEN","Windowed Resolution Y");;
		
		return S_OK;
	}

	virtual HRESULT __stdcall Save() {
		m_Profile.WriteInt("SYNCHRONIZATION","LPT Port Number", m_LptSyncPortNum);
		m_Profile.WriteInt("SYNCHRONIZATION","Preframe Bit", m_LptSyncPreframeBit);
		m_Profile.WriteInt("SYNCHRONIZATION","Postframe Bit", m_LptSyncPostFrameBit);
		m_Profile.WriteInt("SYNCHRONIZATION","StimOn Strobe Bit", m_LptSyncStimOnStrobeBit);
		m_Profile.WriteInt("SYNCHRONIZATION","Frame drop Bit", m_LptSyncFrameDropBit);

		switch(m_ThreadPriority) {
		case THREAD_PRIORITY_NORMAL:
			m_Profile.WriteString("THREADING","Thread Priority", "THREAD_PRIORITY_NORMAL");
			break;
		case THREAD_PRIORITY_TIME_CRITICAL:
			m_Profile.WriteString("THREADING","Thread Priority", "THREAD_PRIORITY_TIME_CRITICAL");
			break;
		}

		m_Profile.WriteInt("CONNECTION","TcpIp Port", m_TcpIpPort);

		m_Profile.WriteInt("SCREEN","Fullscreen", m_Fullscreen);
		
		m_Profile.WriteInt("SCREEN","Fullscreen Resolution X", m_FullscreenResX);
		m_Profile.WriteInt("SCREEN","Fullscreen Resolution Y", m_FullscreenResY);
		m_Profile.WriteInt("SCREEN","Fullscreen Framerate", m_FullscreenFramerate);
		m_Profile.WriteInt("SCREEN","Windowed Resolution X", m_WindowedResX);
		m_Profile.WriteInt("SCREEN","Windowed Resolution Y", m_WindowedResY);
		
		return S_OK;
	}

	// returns true if the application should run in full screen
	//		running in windowed mode generally means debugging mode.
	//	S_OK = true; S_FALSE = false
	virtual HRESULT __stdcall IsFullscreen() { return (m_Fullscreen) ? S_OK : S_FALSE; }
	virtual HRESULT __stdcall GetTcpIpCmdPort(DWORD* pPort) { if (pPort) (*pPort) = m_TcpIpPort; return S_OK; }
	virtual HRESULT __stdcall GetTcpIpBindAddress(unsigned char** pBindAddr) { return E_FAIL; }
	virtual HRESULT __stdcall MapXCoordinate(const unsigned char* pData, int* pXCoord) { return E_FAIL; }
	virtual HRESULT __stdcall MapYCoordinate(const unsigned char* pData, int* pYCoord) { return E_FAIL; }
	virtual HRESULT __stdcall ShouldHideCursor() { return S_FALSE; }

	virtual HRESULT __stdcall GetGraphicsEngineThreadPriority(int* pPriority) {
		(*pPriority) = m_ThreadPriority;
//		(*pPriority) = THREAD_PRIORITY_NORMAL;
		return S_OK;
	}

	virtual HRESULT __stdcall GetLptSyncPortInfo(int* pPortNum, int* pPreFrame, int* pPostFrame,
		int* pStimOnStrobeBit, int* pFrameDropBit) { 
		
		(*pPortNum) = m_LptSyncPortNum; 
		(*pPreFrame) = m_LptSyncPreframeBit; 
		(*pPostFrame) = m_LptSyncPostFrameBit; 
		(*pStimOnStrobeBit) = m_LptSyncStimOnStrobeBit;
		(*pFrameDropBit) = m_LptSyncFrameDropBit;

/*		(*pPortNum) = 0; 
		(*pPreFrame) = 0; 
		(*pPostFrame) = 1; 
		(*pStimOnStrobeBit) = 2;
		(*pFrameDropBit) = 3;
		*/
		return S_OK; 
	}
	virtual HRESULT __stdcall GetWindowedResolution(int* pWidth, int* pHeight) { 
		if (pWidth)
			(*pWidth) = m_WindowedResX;
//			(*pWidth) = 640;
		if  (pHeight)
			(*pHeight) = m_WindowedResY;
//			(*pHeight) = 480;
		return S_OK;
	}
	virtual HRESULT __stdcall GetFullscreenResolution(int* pWidth, int* pHeight, int* pFramerate) { 
/*		(*pWidth) = 1920;
		(*pHeight) = 1080;
		(*pFramerate) = 75;
		*/
		(*pWidth) = m_FullscreenResX;
		(*pHeight) = m_FullscreenResY;
		(*pFramerate) = m_FullscreenFramerate;
		return S_OK;
	}

	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);
};

#endif // !defined(AFX_CNSTIMPROFILE_H__DCC73FE6_586F_40B0_9EA0_DB13D543541E__INCLUDED_)
