// CNCapEngine.cpp: implementation of the CNCapEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "CNCapEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

unsigned long IOBaseAddr[] = 
{
0x0408,
0x040A,
0x040C,
0x040E
};


CNCapEngine::CNCapEngine() : m_iCount(1)
{
	m_iImgWidth = 256;
	m_iImgHeight = 256;

	m_pCurImg = new unsigned short[m_iImgWidth*m_iImgHeight];

	m_iSnapId = 0;


	m_Streamer.SetCCDInfo("Dalsa CA-D1-256T", (16<<24)+(16<<16)+(0), 10*1024*1024);
	m_Streamer.SetStreamInfo(256,256,12,16,1,1,256*256*2,108);
	m_Streamer.SetPixelType(PIXELTYPE_WORD);


	m_hStreaming = CreateEvent(0, TRUE, FALSE, 0);
	m_hStreamStopped = CreateEvent(0, FALSE, FALSE, 0);

	m_hImgBuff = 0;
	m_pImgBuff = 0;
	m_hGrabId = 0;
	m_bInTimer = false;
	m_ulNumFramesToSkip = 0;

	m_SumLength = 16;

	strcpy(m_pSnapPrefix, "snap");

	m_iFilterState = 0;
	numFramesPerWavelength = 25;
}
	

HRESULT __stdcall CNCapEngine::SetDataDir(const unsigned char* dataDir) { 
	m_pProfile->SetDataLocation((unsigned char*)dataDir);
	return S_OK;
}


CNCapEngine::~CNCapEngine() {
	CloseHandle(m_hStreaming);
	CloseHandle(m_hStreamStopped);

	if (m_hGrabId != 0) {
		m_pCamera->Freeze(m_hGrabId);
		delete m_pCapMod;
	}

	if (m_hImgBuff != 0) {
		GlobalFree(m_hImgBuff);
	}
}

bool CNCapEngine::Init(CNCapProfile* pProfile) {
	bool bResult = false;

	m_pProfile = pProfile;
	m_pProfile->AddRef();
	pProfile->GetModuleName((unsigned char**)&m_pModuleName);
	pProfile->GetConfigFile((unsigned char**)&m_pConfigFile);
	pProfile->GetBoardNum(&m_iBoardNum);
	pProfile->GetCamNum(&m_iCamNum);
	pProfile->GetFilterWheelCtrlBit(&m_iFilterWheelTriggerBit);

	if (InitLpt()) {
		m_pCapMod = IfxCreateCaptureModule(m_pModuleName, m_iBoardNum, m_pConfigFile);
		if (m_pCapMod) {
			m_pCamera = m_pCapMod->GetCam(m_iCamNum);
			if (m_pCamera) {
				m_pCamera->GetAttr(&m_CamAttr);
				m_iImgWidth = m_CamAttr.dwWidth;
				m_iImgHeight = m_CamAttr.dwHeight;

				m_ImgBuffSize = m_CamAttr.dwWidth*m_CamAttr.dwHeight*m_CamAttr.dwBytesPerPixel*FRAMES_IN_HOSTBUFF;
				printf("width = %d height = %d bytesPerPixel = %d\r\n",
					m_CamAttr.dwWidth, m_CamAttr.dwHeight, 
					m_CamAttr.dwBytesPerPixel);

				printf("allocating hostbuf for 5 sec of %d bytes (%dk) assuming 108fps\r\n", m_ImgBuffSize, m_ImgBuffSize/1024);
				m_hImgBuff = GlobalAlloc(GMEM_FIXED, m_ImgBuffSize);
				if (m_hImgBuff) {
					m_pImgBuff = (unsigned char*)GlobalLock(m_hImgBuff);


					// all good, start grabbing
					m_hGrabId = m_pCamera->Grab(0,m_pImgBuff, FRAMES_IN_HOSTBUFF);

					bResult = true;
				}
				else
				{
					printf("can't allocate memory\r\n");
					delete m_pCapMod;
					m_pCapMod = 0;
					m_pCamera = 0;
				}
			}
			else {
				delete m_pCapMod;
				m_pCapMod = 0;
			}
		}

		if (bResult) {
			m_PrevWnd.Create("Preview", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			m_HorizontalPlot.Create("Mid Line", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			m_HistPlot.Create("Histogram", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			m_TempPlot.Create("TemporalTrace", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			m_LUTPreviewWnd.Create("LUTPreview", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			m_HcPreview.Create("High Contrast", WS_EX_TOOLWINDOW, WS_VISIBLE, 0, 0, m_iImgWidth, m_iImgHeight);
			Rearrange();
		}
		else {
			printf("Can't initialize camera\r\n");
		}
	}
	StopFilter();// hold high or filter wheel will go berzerk

	return bResult;
}


void CNCapEngine::Rearrange() {
	RECT r, dr;
	m_PrevWnd.GetWindowRect(&r);
	m_HorizontalPlot.GetWindowRect(&dr);

	dr.top += r.bottom;
	dr.bottom += r.bottom;
	dr.right -= dr.left;
	dr.left = 0;

	m_HorizontalPlot.MoveWindow(dr.left, dr.top, dr.right - dr.left, dr.bottom - dr.top);

	m_HistPlot.GetWindowRect(&dr);
	dr.left += r.right;
	dr.right += r.right;
	dr.bottom -= dr.top;
	dr.top = 0;

	m_HistPlot.MoveWindow(dr.left, dr.top, dr.right - dr.left, dr.bottom - dr.top);
	
	m_TempPlot.GetWindowRect(&dr);
	dr.left += r.right;
	dr.right += r.right;
	dr.top += r.bottom;
	dr.bottom += r.bottom;

	m_TempPlot.MoveWindow(dr.left, dr.top, dr.right - dr.left, dr.bottom - dr.top);

	m_LUTPreviewWnd.GetWindowRect(&dr);
	int w = (r.right-r.left);
	dr.right = w*2 + dr.right - dr.left;
	dr.left = w*2;
	dr.bottom = dr.bottom - dr.top;
	dr.top += 0;

	m_LUTPreviewWnd.MoveWindow(dr.left, dr.top, dr.right - dr.left, dr.bottom - dr.top);

	m_HcPreview.GetWindowRect(&dr);
	w = (r.right-r.left);
	dr.right = w*2 + dr.right - dr.left;
	dr.left = w*2;
	dr.top = dr.bottom;
	dr.bottom = 2*dr.bottom;

	m_HcPreview.MoveWindow(dr.left, dr.top, dr.right - dr.left, dr.bottom - dr.top);
}

void CNCapEngine::Snap(const char* customFilename) {
	char filename[512];

	char* pSnapBaseDir;
	m_pProfile->GetDataLocations(0, (unsigned char**)&pSnapBaseDir);
	if (customFilename == 0)
		sprintf(filename, "%s\\%s%04d.img", pSnapBaseDir, m_pSnapPrefix, m_iSnapId++);
	else
	{
		int len;
		if (((len = strlen(customFilename)) < 4) | (
			strcmpi(customFilename+(len-4), ".img") != 0))
			sprintf(filename, "%s\\%s.img", pSnapBaseDir, customFilename);
		else
			sprintf(filename, "%s\\%s", pSnapBaseDir, customFilename);
	}

	FILE* fp = fopen(filename, "wb");

	if (fp) {
		fwrite(&m_iImgWidth, sizeof(m_iImgWidth), 1, fp);
		fwrite(&m_iImgHeight, sizeof(m_iImgHeight), 1, fp);
		unsigned long bpp = 12;
		fwrite(&bpp, sizeof(bpp), 1, fp);
		fwrite(m_pCurImg, m_iImgWidth*m_iImgHeight, 2, fp);
		fclose(fp);

		char title[512];
		sprintf(title, "Preview [%s]", filename);
		m_PrevWnd.SetWindowText(title);
	}

}

HRESULT __stdcall CNCapEngine::StartStream(const unsigned char* filename, long numFrames) {

	char actualFilename[512];
	char* pStreamBaseDir;
	m_pProfile->GetDataLocations((unsigned char**)&pStreamBaseDir, 0);
	sprintf(actualFilename, "%s\\%s.csf", pStreamBaseDir, filename, m_iSnapId++);

	strcpy(m_pStreamFile, (char*)actualFilename);
	m_iNumFramesToStream = numFrames;

	PostMessage(m_PrevWnd.GetHwnd(), WM_NCE_EVENT, NCE_STREAM, 0);
	WaitForSingleObject(m_hStreaming, INFINITE);
	printf("stream started\r\n");
	return S_OK;
}

HRESULT __stdcall CNCapEngine::StartStreamOnLPT(const unsigned char* filename, int bit) {

	char actualFilename[512];
	char* pStreamBaseDir;
	m_pProfile->GetDataLocations((unsigned char**)&pStreamBaseDir, 0);
	sprintf(actualFilename, "%s\\%s", pStreamBaseDir, filename, m_iSnapId++);

	strcpy(m_pStreamFile, (char*)actualFilename);
	m_iLptBitToTriggerStream = bit;
	PostMessage(m_PrevWnd.GetHwnd(), WM_NCE_EVENT, NCE_STREAMONLPT, 0);
	WaitForSingleObject(m_hStreaming, INFINITE);
	printf("stream started\r\n");

	return S_OK;
}

HRESULT __stdcall CNCapEngine::StartMSStreamOnLPT(const unsigned char* filename, int bit) {

	char actualFilename[512];
	char* pStreamBaseDir;
	m_pProfile->GetDataLocations((unsigned char**)&pStreamBaseDir, 0);
	sprintf(actualFilename, "%s\\%s", pStreamBaseDir, filename, m_iSnapId++);

	strcpy(m_pStreamFile, (char*)actualFilename);
	m_iLptBitToTriggerStream = bit;
	PostMessage(m_PrevWnd.GetHwnd(), WM_NCE_EVENT, NCE_MSSTREAMONLPT, 0);
	WaitForSingleObject(m_hStreaming, INFINITE);
	printf("multi-spectral stream started\r\n");

	return S_OK;
}

HRESULT __stdcall CNCapEngine::StopStream() {
	if (WaitForSingleObject(m_hStreaming, 0) == WAIT_OBJECT_0) {
		m_bStopStreaming = true;
		WaitForSingleObject(m_hStreamStopped, INFINITE);
	}
	return S_OK;
}

void CNCapEngine::Stream(const char* filename, long numFrames) {

	m_bStopStreaming = false;
	SetEvent(m_hStreaming);

	int iSeqNum = -1;
	int iLastSeqNum = -1;
	unsigned char* pHostBuffFrame;
	int iNumFrames = 0;
	m_Streamer.OpenFile(filename, false, false);
	printf("pre stream loop\r\n");

	unsigned long ulFramesSkipped = 0;

	SetLptStreamStart();

	while (!m_bStopStreaming) {

		if (ulFramesSkipped == m_ulNumFramesToSkip) {
			ulFramesSkipped = 0;
			SetLptPreCap();
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {


				SetLptPostCap();

//				printf("snapstream\r\n");
//				printf("stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				m_Streamer.WriteTimestamp();
				m_Streamer.WriteData(pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
				m_Streamer.WriteTimestamp();

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
				iNumFrames++;
				if (iNumFrames < numFrames) {
					break;
				}
			}
			else 
				break;
		}
		else {
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

//				printf("SKIPPING stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
				iNumFrames++;
				ulFramesSkipped++;
				if (iNumFrames < numFrames) {
					break;
				}
			}
			else 
				break;
		}
	}

	SetLptStreamStop();

	printf("post stream loop\r\n");
	m_Streamer.CloseFile();
	ResetEvent(m_hStreaming);
	SetEvent(m_hStreamStopped);
}

void CNCapEngine::StreamOnLPT(const char* filename, int bitNum) {

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	m_bStopStreaming = false;
	SetEvent(m_hStreaming);

	int iSeqNum = -1;
	int iLastSeqNum = -1;
	unsigned char* pHostBuffFrame;
	int iNumFrames = 0;
	char local_filename[512];
	printf("pre stream loop\r\n");
	bool streaming = false;
	int stimNum = 0;
	int numsum = 0;
	unsigned short tempData[256*256];
	unsigned long ulFramesSkipped = 0;
	memset(tempData,0, sizeof(tempData));

	SetLptStreamStart();

	while (!m_bStopStreaming) {

		if (ulFramesSkipped == m_ulNumFramesToSkip) {
			ulFramesSkipped = 0;
			unsigned long value = 0;
			GetPortVal(m_wPortIoBase+1, &value, 1);
			int shouldGrab = value & (1<<m_iLptBitToTriggerStream);

			if (shouldGrab)
				SetLptPreCap();
	//		printf("grabbing\r\n");
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

	//		printf("grabbed\r\n");

				if (shouldGrab)
					SetLptPostCap();

	//			printf("snapstream\r\n");
	//			printf("stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				iNumFrames++;
				unsigned long value = 0;
	//			if (GetPortVal(m_wPortIoBase+1, &value, 1)) {
					//printf("%08x pv  \r\n", value);
				if (shouldGrab) {
					if (!streaming)
					{
						sprintf(local_filename, "%s.%04d.csf", filename, stimNum++);
						m_Streamer.OpenFile(local_filename, false, false);
						streaming = true;
						SetLptStreamStore();
					}
					for (int x = 0;x < 256*256; x++) {
					 	tempData[x] += ((unsigned short*)pHostBuffFrame)[x] >> 4;
					}
					if (numsum == (m_SumLength-1)) {
						SetLptStreamStore();
		//				printf("cap!\r\n");
						m_Streamer.WriteTimestamp();
						m_Streamer.WriteData(tempData, m_iImgWidth*m_iImgHeight*2);//pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
						m_Streamer.WriteTimestamp();
						numsum = 0;
						memset(tempData,0, sizeof(tempData));
					}
					else {
						numsum = numsum + 1;
//						for (int x = 0;x < 256*256; x++) {
//						 	tempData[x] += ((unsigned short*)pHostBuffFrame)[x] >> 4;
//						}
					}
				}
				else {
					if (streaming)
					{
						if (numsum > 0) {
							SetLptStreamStore();
							m_Streamer.WriteTimestamp();
							m_Streamer.WriteData(tempData, m_iImgWidth*m_iImgHeight*2);//pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
							m_Streamer.WriteTimestamp();
							numsum = 0;
							memset(tempData,0, sizeof(tempData));
						}
						streaming = false;
						m_Streamer.CloseFile();
					}
				}
	//			}

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
			}
			else 
				break;
		}
		else {
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

//				printf("SKIPPING stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
				ulFramesSkipped++;
			}
			else 
				break;
		}
	}

	SetLptStreamStop();

	printf("post stream loop\r\n");
	if (streaming)
		m_Streamer.CloseFile();
	ResetEvent(m_hStreaming);
	SetEvent(m_hStreamStopped);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
}

void CNCapEngine::MSStreamOnLPT(const char* filename, int bitNum) {

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	m_bStopStreaming = false;
	SetEvent(m_hStreaming);

	int iSeqNum = -1;
	int iLastSeqNum = -1;
	unsigned char* pHostBuffFrame;
	int iNumFrames = 0;
	char local_filename[512];
	printf("pre stream loop\r\n");
	bool streaming = false;
	int stimNum = 0;
	int numsum = 0;
	unsigned short tempData[256*256];
	unsigned long ulFramesSkipped = 0;
	memset(tempData,0, sizeof(tempData));

	SetLptStreamStart();
	int switchFrameMod = 0;
	FILE* filterPosFile = 0;

	while (!m_bStopStreaming) {

		if (ulFramesSkipped == m_ulNumFramesToSkip) {
			ulFramesSkipped = 0;
			unsigned long value = 0;
			GetPortVal(m_wPortIoBase+1, &value, 1);
			int shouldGrab = value & (1<<m_iLptBitToTriggerStream);

			if (shouldGrab)
				SetLptPreCap();
	//		printf("grabbing\r\n");
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

	//		printf("grabbed\r\n");

				if (shouldGrab) {
					if (switchFrameMod==numFramesPerWavelength) {
						switchFrameMod = 0;
						///switch filter!
						GoFilter();
					}
					else
						StopFilter();
					switchFrameMod++;
					SetLptPostCap();
				}

	//			printf("snapstream\r\n");
	//			printf("stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				iNumFrames++;
				unsigned long value = 0;
	//			if (GetPortVal(m_wPortIoBase+1, &value, 1)) {
					//printf("%08x pv  \r\n", value);
				if (shouldGrab) {
					if (!streaming)
					{
						sprintf(local_filename, "%s.%04d.csf", filename, stimNum);
						m_Streamer.OpenFile(local_filename, false, false);
						sprintf(local_filename, "%s.%04d.fpf", filename, stimNum);
						filterPosFile = fopen(local_filename, "wb");
						stimNum++;
						streaming = true;
						SetLptStreamStore();
					}
					for (int x = 0;x < 256*256; x++) {
					 	tempData[x] += ((unsigned short*)pHostBuffFrame)[x] >> 4;
					}
					if (numsum == (m_SumLength-1)) {
						SetLptStreamStore();
		//				printf("cap!\r\n");
						m_Streamer.WriteTimestamp();
						m_Streamer.WriteData(tempData, m_iImgWidth*m_iImgHeight*2);//pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
						m_Streamer.WriteTimestamp();
						numsum = 0;
						memset(tempData,0, sizeof(tempData));

						if (filterPosFile)
							fprintf(filterPosFile, "%d\r\n", m_iFilterState);
					}
					else {
						numsum = numsum + 1;
//						for (int x = 0;x < 256*256; x++) {
//						 	tempData[x] += ((unsigned short*)pHostBuffFrame)[x] >> 4;
//						}
					}
				}
				else {
					if (streaming)
					{
						if (numsum > 0) {
							SetLptStreamStore();
							m_Streamer.WriteTimestamp();
							m_Streamer.WriteData(tempData, m_iImgWidth*m_iImgHeight*2);//pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
							m_Streamer.WriteTimestamp();
							numsum = 0;
							memset(tempData,0, sizeof(tempData));
							if (filterPosFile)
								fprintf(filterPosFile, "%d\r\n", m_iFilterState);
						}
						streaming = false;
						m_Streamer.CloseFile();
						fclose(filterPosFile); filterPosFile = 0;
					}
				}
	//			}

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
			}
			else 
				break;
		}
		else {
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

//				printf("SKIPPING stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
				ulFramesSkipped++;
			}
			else 
				break;
		}
	}
	StopFilter();

	SetLptStreamStop();

	printf("post stream loop\r\n");
	if (streaming) {
		m_Streamer.CloseFile();
		if (filterPosFile) {
			fclose(filterPosFile);
			filterPosFile = 0;
		}
	}
	ResetEvent(m_hStreaming);
	SetEvent(m_hStreamStopped);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_NORMAL);
}
/*
void CNCapEngine::StreamOnLPT(const char* filename, int bitNum) {

	m_bStopStreaming = false;
	SetEvent(m_hStreaming);

	int iSeqNum = -1;
	int iLastSeqNum = -1;
	unsigned char* pHostBuffFrame;
	int iNumFrames = 0;
	char local_filename[512];
	printf("pre stream loop\r\n");
	bool streaming = false;
	int stimNum = 0;

	unsigned long ulFramesSkipped = 0;

	SetLptStreamStart();

	while (!m_bStopStreaming) {

		if (ulFramesSkipped == m_ulNumFramesToSkip) {
			ulFramesSkipped = 0;
			unsigned long value = 0;
			GetPortVal(m_wPortIoBase+1, &value, 1);
			int shouldGrab = value & (1<<m_iLptBitToTriggerStream);

			if (shouldGrab)
				SetLptPreCap();
	//		printf("grabbing\r\n");
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

	//		printf("grabbed\r\n");

				if (shouldGrab)
					SetLptPostCap();

	//			printf("snapstream\r\n");
	//			printf("stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				iNumFrames++;
				unsigned long value = 0;
	//			if (GetPortVal(m_wPortIoBase+1, &value, 1)) {
					//printf("%08x pv  \r\n", value);
				if (shouldGrab) {
					if (!streaming)
					{
						sprintf(local_filename, "%s.%04d.csf", filename, stimNum++);
						m_Streamer.OpenFile(local_filename, false, false);
						streaming = true;
					}
	//				printf("cap!\r\n");
					m_Streamer.WriteTimestamp();
					m_Streamer.WriteData(pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
					m_Streamer.WriteTimestamp();
				}
				else {
					if (streaming)
					{
						streaming = false;
						m_Streamer.CloseFile();
					}
				}
	//			}

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
			}
			else 
				break;
		}
		else {
			if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
				IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

//				printf("SKIPPING stream sequence number %d\r\n", iSeqNum);
				int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
				if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
					printf("frame dropped\r\n");
					// Frame drop
				}

				iLastSeqNum = iSeqNum;

				m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
				ulFramesSkipped++;
			}
			else 
				break;
		}
	}

	SetLptStreamStop();

	printf("post stream loop\r\n");
	if (streaming)
		m_Streamer.CloseFile();
	ResetEvent(m_hStreaming);
	SetEvent(m_hStreamStopped);
}
/*
// old working code!
void CNCapEngine::StreamOnLPT(const char* filename, int bitNum) {

	m_bStopStreaming = false;
	SetEvent(m_hStreaming);

	int iSeqNum = -1;
	int iLastSeqNum = -1;
	unsigned char* pHostBuffFrame;
	int iNumFrames = 0;
	m_Streamer.OpenFile(filename, false, false);
	printf("pre stream loop\r\n");

	unsigned long ulFramesSkipped = 0;

	SetLptStreamStart();

	while (!m_bStopStreaming) {

		SetLptPreCap();
//		printf("grabbing\r\n");
		if ((iSeqNum=m_pCamera->GrabWaitFrameEx(m_hGrabId,&pHostBuffFrame,
			IFC_WAIT_NEWER_FRAME,500,TRUE))>=0) {

//		printf("grabbed\r\n");

			SetLptPostCap();

			printf("snapstream\r\n");
			printf("stream sequence number %d\r\n", iSeqNum);
			int iExpectedSeqNum = (iLastSeqNum+1)%FRAMES_IN_HOSTBUFF;
			if ((iLastSeqNum > 0)&&(iExpectedSeqNum != iSeqNum)) {
				printf("frame dropped\r\n");
				// Frame drop
			}

			iLastSeqNum = iSeqNum;

			iNumFrames++;
			unsigned long value = 0;
			if (GetPortVal(m_wPortIoBase+1, &value, 1)) {
				printf("%08x pv  \r\n", value);
				if (value & (1<<m_iLptBitToTriggerStream)) {
					printf("cap!\r\n");
					m_Streamer.WriteTimestamp();
					m_Streamer.WriteData(pHostBuffFrame, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
					m_Streamer.WriteTimestamp();
				}
			}

			m_pCamera->GrabRelease(m_hGrabId,iSeqNum);
		}
		else 
			break;
	}

	SetLptStreamStop();

	printf("post stream loop\r\n");
	m_Streamer.CloseFile();
	ResetEvent(m_hStreaming);
	SetEvent(m_hStreamStopped);
}
*/


	/// FOOTPEDAL CODE
DWORD __stdcall FootPedalThread(void* user) {
	CNCapEngine* pEngine = (CNCapEngine*)user;
	return pEngine->FootPedalThreadProc();

}
DWORD CNCapEngine::FootPedalThreadProc() {
	m_hFootPedalFile = CreateFile("COM1:", GENERIC_READ | GENERIC_WRITE, 0,
		0,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0);
	DCB d;
	GetCommState(m_hFootPedalFile, &d);
	d.fOutxCtsFlow = 0;
	d.fOutxDsrFlow = 0;
	d.fDtrControl = DTR_CONTROL_DISABLE;
	SetCommMask( m_hFootPedalFile, EV_CTS |EV_DSR|EV_RLSD|EV_BREAK );
	DWORD lastTickCount = GetTickCount();
	DWORD mask;
	printf("foot pedal thread loop starting\r\n");
	int parity = 0;;
	while (!m_bFootPedalThreadShouldExit)
	{
		lastTickCount = GetTickCount();
		int e = WaitCommEvent(m_hFootPedalFile, &mask, 0);
		DWORD dif = (GetTickCount() - lastTickCount);
		// debouncing!
		if (dif > 50) {
			parity = (parity + 1) % 2;
			if (parity == 0) {
				if (mask == 16) {
					PostThreadMessage(m_dwRunThreadId, WM_NCE_UI_EVENT, NCE_UI_SNAP, 0);
				}
				else {
					PostThreadMessage(m_dwRunThreadId, WM_NCE_UI_EVENT, NCE_UI_SNAP_CUSTOM, 0);
				}
			}
		}
	}
	CloseHandle(m_hFootPedalFile);
	printf("foot pedal thread done\r\n");
	FILE* f = fopen("c:\\test.txt", "wb");
	fprintf(f, "abcdefg\r\n"); fclose(f);
	return 0;
}
	// END FOOTPEDAL CODE


HRESULT __stdcall CNCapEngine::Run() {
	// FOOT PEDAL CODE
	DWORD footPedalThreadId;
	m_bFootPedalThreadShouldExit = false;
	m_dwRunThreadId = GetCurrentThreadId();
	CreateThread(0,0,FootPedalThread, this, 0, &footPedalThreadId);
	// END FOOT PEDAL CODE

	m_bDone = false;

	MSG msg;
	
	SetTimer(m_PrevWnd.GetHwnd(), 0, 5, 0);
	while (!m_bDone) {


		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {

			if (msg.message == WM_TIMER) {
				if (!m_bInTimer) {
					m_bInTimer = true;
					int LastFrame = m_pCamera->GrabFrameSeqNum(m_hGrabId);
					LastFrame = LastFrame % FRAMES_IN_HOSTBUFF;
//					printf("LastFrame = %d\r\n", LastFrame);
					if (LastFrame > 0) {
						short* temp = (short*)(m_pImgBuff + (m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel*LastFrame));
						memcpy(m_pCurImg, temp, m_iImgWidth*m_iImgHeight*m_CamAttr.dwBytesPerPixel);
						if (m_pCurImg) {

							unsigned short minv = 65535;
							unsigned short maxv = 0;
							int i;

							// NOTE: this code is here because of syncing issues.. when the new cable is ready
							// this code probably won't be necessary!
							for (i = 0; i < m_iImgWidth * m_iImgHeight; i++) {
								m_pCurImg[i] = (1<<5)*((m_pCurImg[i])&0xfff0) >> 9;// & 0x000);
							}
//							printf("max = %d min = %d\r\n", maxv, minv);
							/*
							for (i = 0; i < m_iImgWidth * m_iImgHeight; i++) {
								m_pCurImg[i] = (4096*(m_pCurImg[i] - minv)) / (maxv - minv);
							}
							*/
							m_PrevWnd.Show((short*)m_pCurImg);
							m_LUTPreviewWnd.Show((short*)m_pCurImg);
							m_HorizontalPlot.Show((short*)m_pCurImg);
							m_HistPlot.Show((short*)m_pCurImg);
							m_TempPlot.Show((short*)m_pCurImg);
							m_HcPreview.Show((short*)m_pCurImg);
						}
					}
					m_bInTimer = false;
				}
				else {
					printf("***************************************SKIPPED***********\r\n");
				}

			} 
			else if (msg.message == WM_NCE_EVENT) {
				switch(msg.wParam) {
				case NCE_STREAM:
					Stream(m_pStreamFile, m_iNumFramesToStream);
 					break;
				case NCE_STREAMONLPT:
					StreamOnLPT(m_pStreamFile, m_iLptBitToTriggerStream);
					break;
				case NCE_MSSTREAMONLPT:
					MSStreamOnLPT(m_pStreamFile, m_iLptBitToTriggerStream);
					break;
				}
			}
			else if (msg.message == WM_NCE_UI_EVENT) {
				switch(msg.wParam) {
				case NCE_UI_SNAP:
					Snap();
					break;
				case NCE_UI_SNAP_CUSTOM: {
					char customName[512];
					printf("Enter custom name:");
					scanf("%s", customName);
					Snap(customName);
										 }
					break;
				}
			}
			else if (msg.message == WM_QUIT) {
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// FOOT PEDAL CODE
	m_bFootPedalThreadShouldExit = true;
	SetCommBreak(m_hFootPedalFile);
	Sleep(1000*30);
	// END FOOT PEDAL CODE
	return S_OK;
}


void CNCapEngine::SetLptStreamStart() {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);

	dw |= (1<<m_iStartStop);
	SetPortVal(m_wPortIoBase, dw, 1);
}

void CNCapEngine::SetLptStreamStore() {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);

	if (m_bStoreMark)
		dw |= (1<<m_iStoreBit);
	else
		dw &= ~(1<<m_iStoreBit);
	SetPortVal(m_wPortIoBase, dw, 1);

	m_bStoreMark = !m_bStoreMark;
}

void CNCapEngine::SetLptStreamStop() {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);

	dw &= ~(1<<m_iStartStop);
	SetPortVal(m_wPortIoBase, dw, 1);
}

void CNCapEngine::SetLptPreCap() {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);

	if (m_bPreMark)
		dw |= (1<<m_iPreBit);
	else
		dw &= ~(1<<m_iPreBit);
	SetPortVal(m_wPortIoBase, dw, 1);

	m_bPreMark = !m_bPreMark;
}

void CNCapEngine::SetLptPostCap() {
	bool ;
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);

	if (m_bPostMark)
		dw |= (1<<m_iPostBit);
	else
		dw &= ~(1<<m_iPostBit);
	SetPortVal(m_wPortIoBase, dw, 1);

	m_bPostMark = !m_bPostMark;
}

bool CNCapEngine::InitLpt() {

	bool bResult = false;

	m_bPreMark = 0;
	m_bPostMark = 0;
	m_bStoreMark = 0;

	m_pProfile->GetLptInfo(&m_iPort, &m_iStartStop, &m_iPreBit, &m_iPostBit, &m_iStoreBit); 
	if (InitializeWinIo()) {
		// LPT1
		GetPhysLong((unsigned char*)IOBaseAddr[m_iPort], &m_wPortIoBase);
		SetPortVal(m_wPortIoBase, 0, 1);
		bResult = true;

	}
	else {
		if (InitializeWinIo()) {
			// LPT1
			GetPhysLong((unsigned char*)IOBaseAddr[m_iPort], &m_wPortIoBase);
			SetPortVal(m_wPortIoBase, 0, 1);
			bResult = true;

		}
		else {
			printf("can't initialize winio!\r\n");
		}
	}



	return bResult;
}



ULONG __stdcall CNCapEngine::AddRef(void) {
	return InterlockedIncrement(&m_iCount);
}

HRESULT __stdcall CNCapEngine::QueryInterface(REFIID iid, void **ppvObject) {
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

ULONG __stdcall CNCapEngine::Release(void) {
	if (InterlockedDecrement(&m_iCount) == 0)
	{
		delete this;
		return 0;
	}
	else
		return m_iCount;
}

HRESULT __stdcall CNCapEngine::SetSnapId(unsigned long snapId) {
	m_iSnapId = snapId;
	return S_OK;
}

HRESULT __stdcall CNCapEngine::SetSnapPrefix(const unsigned char* prefix) {
	strcpy(m_pSnapPrefix, (char*)prefix);
	return S_OK;
}
HRESULT __stdcall CNCapEngine::SetSumLength(unsigned long sumLength) {
	m_SumLength = sumLength;
	return S_OK;
}

HRESULT __stdcall CNCapEngine::SetShutterState(int state) {
	int bitNum = 0;
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);
	m_pProfile->GetShutterCtrlBit(&bitNum);
	if (state)
		dw |= (1<<bitNum);
	else
		dw &= ~(1<<bitNum);
	SetPortVal(m_wPortIoBase, dw, 1);

	return S_OK;
}

HRESULT __stdcall CNCapEngine::GetShutterState(int* state) {
	int bitNum = 0;
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);
	m_pProfile->GetShutterCtrlBit(&bitNum);
	GetPortVal(m_wPortIoBase, &dw, 1);
	(*state) = (dw&(1<<bitNum))>>bitNum;

	return S_OK;
}

HRESULT __stdcall CNCapEngine::GoFilter(bool updatePos) {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);
	dw &= ~(1<<m_iFilterWheelTriggerBit);
	SetPortVal(m_wPortIoBase, dw, 1);
	if (updatePos) {
		m_iFilterState++;
		m_iFilterState = m_iFilterState % 4;
	}
	return S_OK;

}

HRESULT __stdcall CNCapEngine::StopFilter() {
	DWORD dw;
	GetPortVal(m_wPortIoBase, &dw, 1);
	dw |= (1<<m_iFilterWheelTriggerBit);
	SetPortVal(m_wPortIoBase, dw, 1);
	return S_OK;

}


HRESULT __stdcall CNCapEngine::SetFilterState(int fs) {
	while (m_iFilterState != fs) {
		GoFilter();
		Sleep(100);
		StopFilter();
		Sleep(500);
	}
	return S_OK;
}
