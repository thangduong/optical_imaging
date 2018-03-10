// CNCapEngine.h: interface for the CNCapEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCAPENGINE_H__4BB092B6_5141_4D87_B320_7E8E6F7034AA__INCLUDED_)
#define AFX_CNCAPENGINE_H__4BB092B6_5141_4D87_B320_7E8E6F7034AA__INCLUDED_

#include <ifcapi.h>
#include "CNCapProfile.h"
#include "CImgPreviewWnd.h"
#include "CLinePlot.h"
#include "CHistPlot.h"
#include "CTemporalPlot.h"
#include "CCamStreamFile.h"
#include "WinIo.h"


#define	FRAMES_IN_HOSTBUFF	108

#define	WM_NCE_UI_EVENT	WM_USER+1
#define	WM_NCE_EVENT	WM_USER+2

#define	NCE_UI_SNAP		0
#define	NCE_UI_SNAP_CUSTOM	1


#define	NCE_STREAM	0
#define	NCE_STREAMONLPT	1

class CNCapEngine  
{
	long m_iCount;
	CAM_ATTR m_CamAttr;
	CNCapProfile* m_pProfile;

	char* m_pModuleName;
	char* m_pConfigFile;
	int m_iBoardNum;
	int m_iCamNum;

	CICapMod* m_pCapMod;
	CICamera* m_pCamera;


	// default to 256x256
	int m_iImgWidth;
	int m_iImgHeight;
	unsigned long m_ImgBuffSize;
	unsigned char* m_pImgBuff;
	HGLOBAL m_hImgBuff;
	HIFCGRAB m_hGrabId;

	bool m_bDone;

	bool m_bInTimer;

	unsigned short* m_pCurImg;


	CImgPreviewWnd m_PrevWnd;
	CLinePlot m_HorizontalPlot;
	CHistPlot m_HistPlot;
	CTemporalPlot m_TempPlot;
	

//	char m_pSnapBaseDir[512];
	char m_pSnapPrefix[512];
	int m_iSnapId;


	CCamStreamFile m_Streamer;
	HANDLE m_hStreaming;
	HANDLE m_hStreamStopped;
	bool m_bStopStreaming;
	unsigned long m_ulNumFramesToSkip;


	char m_pStreamFile[512];
	int m_iNumFramesToStream;
	int m_iLptBitToTriggerStream;

	void StreamOnLPT(const char* filename, int bitNum);
	void Stream(const char* filename, long numFrames);
	void Snap(const char* customFilename = 0);

	// FOOT PEDAL CODE
	HANDLE m_hFootPedalFile;
	DWORD m_dwRunThreadId;
public:
	DWORD FootPedalThreadProc();

private:
	bool m_bFootPedalThreadShouldExit;
	// END FOOTPEDAL CODE

	void Rearrange();



	/// lpt synchronization stuff

	DWORD m_wPortIoBase;
	bool m_bPreMark;
	bool m_bPostMark;
	bool m_bStoreMark;
	int m_iPort;
	int m_iStartStop;
	int m_iPreBit;
	int m_iPostBit;
	int m_iStoreBit;
	
	unsigned long m_SumLength;

	// stream markers
	void SetLptStreamStart();
	void SetLptStreamStop();
	void SetLptStreamStore();

	void SetLptPreCap();
	void SetLptPostCap();
	bool InitLpt();

public:
	CNCapEngine();
	virtual ~CNCapEngine();

	bool Init(CNCapProfile* pProfile);

	virtual HRESULT __stdcall Run();
	virtual HRESULT __stdcall StartStream(const unsigned char* filename, long numFrames);
	virtual HRESULT __stdcall StopStream();
	virtual HRESULT __stdcall SetNumFramesToSkip(unsigned long nfts) {
		m_ulNumFramesToSkip = nfts;
		return S_OK;
	}
	virtual HRESULT __stdcall SetDataDir(const unsigned char* dataDir);
	virtual HRESULT __stdcall SetSnapId(unsigned long snapId);
	virtual HRESULT __stdcall SetSnapPrefix(const unsigned char* prefix);
	virtual HRESULT __stdcall SetSumLength(unsigned long sumLength);

	virtual HRESULT __stdcall StartStreamOnLPT(const unsigned char* filename, int bitNum);
	virtual ULONG __stdcall AddRef(void);
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void **ppvObject);
	virtual ULONG __stdcall Release(void);

};

#endif // !defined(AFX_CNCAPENGINE_H__4BB092B6_5141_4D87_B320_7E8E6F7034AA__INCLUDED_)
