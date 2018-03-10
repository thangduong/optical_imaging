// CCamStreamFile.cpp: implementation of the CCamStreamFile class.
//
//////////////////////////////////////////////////////////////////////

#include "CCamStreamFile.h"
#include <stdio.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamStreamFile::CCamStreamFile(DWORD dwBufferSize)
{
	// CONSTRUCTOR:
	//		0.  zero out the overlapped structure
	//		1.  create the event for the overlapped structure
	//		2.  allocate buffer
	//		3.  initialize variables
	//		4.  create write thread events
	memset(&m_Overlapped, 0, sizeof(m_Overlapped));
	//NOTE: it's important that the initial state be TRUE
	m_Overlapped.hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);	
	m_pBuffer[0] = (char*)VirtualAlloc(NULL, dwBufferSize, MEM_COMMIT, PAGE_READWRITE);
	m_pBuffer[1] = (char*)VirtualAlloc(NULL, dwBufferSize, MEM_COMMIT, PAGE_READWRITE);
	m_dwBufferSize = dwBufferSize;

	m_hFile = INVALID_HANDLE_VALUE;
	m_dwBytesTransferred = 0;
	m_Overlapped.Internal = m_Overlapped.InternalHigh =
		m_Overlapped.Offset = m_Overlapped.OffsetHigh = 0;
	m_ulCurrentBuffer = 0;
	m_ulCurrentBufferMarker = 0;	

	m_hQuitOpThread = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hOpDone = CreateEvent(NULL, FALSE, TRUE, NULL);
	m_hOpStarted = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hStartOp = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hOpThreadDone = CreateEvent(NULL, FALSE, FALSE, NULL);

	// initialize m_Header
	memset(&m_Header, 0, sizeof(m_Header));	
	if (!QueryPerformanceFrequency(&m_Header.timestamp_freq))
	{
		m_Header.timestamp_freq.QuadPart = 1000;
	}
	memcpy(&m_Header.magic, "VTQD", 4);
	m_Header.version = CUR_CSF_VERSION;
}

CCamStreamFile::~CCamStreamFile()
{
	// DESTRUCTOR:
	//		0.  if file is still open, close it
	//		1.  free up memory
	//		2.  close the overlapped handle
	if (m_hFile != INVALID_HANDLE_VALUE)
		CloseFile();
	VirtualFree(m_pBuffer[1], m_dwBufferSize, MEM_DECOMMIT);
	VirtualFree(m_pBuffer[0], m_dwBufferSize, MEM_DECOMMIT);
	CloseHandle(m_Overlapped.hEvent);
	CloseHandle(m_hQuitOpThread);
	CloseHandle(m_hStartOp);
	CloseHandle(m_hOpStarted);
	CloseHandle(m_hOpDone);
	CloseHandle(m_hOpThreadDone);
}

void CCamStreamFile::SetStreamInfo(
		unsigned long width,
		unsigned long height,
		unsigned long ebpp,
		unsigned long bpp,
		unsigned long xbin,
		unsigned long ybin,
		unsigned long frame_size,
		double expected_fps)
{
	m_Header.ebpp = ebpp;
	m_Header.bpp = bpp;
	m_Header.width = width;
	m_Header.height = height;
	m_Header.xbin = xbin;
	m_Header.ybin = ybin;
	m_Header.frame_size = frame_size;
	m_Header.expected_fps = expected_fps;
	m_Header.bytes_to_skip = 0;
}

void CCamStreamFile::GetStreamInfo(
		unsigned long& width,
		unsigned long& height,
		unsigned long& ebpp,
		unsigned long& bpp,
		unsigned long& xbin,
		unsigned long& ybin,
		unsigned long& frame_size,
		double& expected_fps)
{
	ebpp = m_Header.ebpp;
	bpp = m_Header.bpp;
	width = m_Header.width;
	height = m_Header.height;
	xbin = m_Header.xbin;
	ybin =  m_Header.ybin;
	frame_size = m_Header.frame_size;
	expected_fps = m_Header.expected_fps;
}

CamStreamFileHdr* CCamStreamFile::GetStreamHeader()
{
	return &m_Header;
}


bool CCamStreamFile::OpenFile(const char* filename, bool read, bool oldStyle)
{
	bool bResult = false;
	m_bRead = read;
	if (read)
	{
		m_hFile = CreateFile(
			filename, GENERIC_READ,
			FILE_SHARE_READ,
			NULL, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
			NULL);
		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			DWORD tid;
			CreateThread(NULL, 0, ThreadProc, (LPVOID)this, NULL, &tid);
		}

		// read in 2 buffers first
		WaitForSingleObject(m_hOpDone, INFINITE);
		SetEvent(m_hStartOp);
		WaitForSingleObject(m_hOpStarted, INFINITE);
		m_ulCurrentBuffer = 1;
		WaitForSingleObject(m_hOpDone, INFINITE);
		SetEvent(m_hStartOp);
		WaitForSingleObject(m_hOpStarted, INFINITE);
		m_ulCurrentBuffer = 0;

		if (!oldStyle)
		{
			// read in the header
			ReadData(&m_Header, sizeof(m_Header));

			// discard junk
			char junk[512];
			while (m_Header.bytes_to_skip)
			{
				if (m_Header.bytes_to_skip > 512)
				{
					ReadData(junk, 512);
					m_Header.bytes_to_skip -= 512;
				}
				else
				{
					ReadData(junk, m_Header.bytes_to_skip);
					m_Header.bytes_to_skip = 0;
				}
			}
		}
		else
		{
			CamStreamFileHdrOld oldHeader;
			ReadData(&oldHeader, sizeof(oldHeader));
			m_Header.version = CUR_CSF_VERSION;
			m_Header.magic = oldHeader.magic;
			m_Header.bpp = oldHeader.bpp;
			m_Header.ebpp = oldHeader.ebpp;
			m_Header.bytes_to_skip = 0;
			m_Header.width = oldHeader.width;
			m_Header.height = oldHeader.height;
			m_Header.xbin = oldHeader.xbin;
			m_Header.ybin = oldHeader.ybin;
			m_Header.frame_size = oldHeader.frame_size;
			m_Header.expected_fps = oldHeader.expected_fps;
			m_Header.timestamp_freq = oldHeader.timestamp_freq;
			m_Header.CCDInfo = oldHeader.CCDInfo;
		}
	}
	else
	{
		m_hFile = CreateFile(
			filename, GENERIC_WRITE,
			FILE_SHARE_READ,
			NULL, CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
			NULL);

		if (m_hFile != INVALID_HANDLE_VALUE)
		{
			DWORD tid;
			CreateThread(NULL, 0, ThreadProc, (LPVOID)this, NULL, &tid);
		}

		WriteData(&m_Header, sizeof(m_Header));
	}
	bResult = (m_hFile != NULL) ? true : false;

	return bResult;
}

unsigned long CCamStreamFile::ReadData(void* data, unsigned long datasize)
{
//	DWORD dwResult;
//	DWORD dwLastError;
	unsigned long ulBytesRead = 0;
	while (datasize && (m_ulValidBufferSize[m_ulCurrentBuffer] != 0))
	{
		DWORD dwBytesToCopy = min(datasize, m_ulValidBufferSize[m_ulCurrentBuffer] - m_ulCurrentBufferMarker);
		memcpy((void*)((DWORD)data+ulBytesRead), &(m_pBuffer[m_ulCurrentBuffer][m_ulCurrentBufferMarker]), dwBytesToCopy);
		datasize -= dwBytesToCopy;
		m_ulCurrentBufferMarker += dwBytesToCopy;
		ulBytesRead += dwBytesToCopy;

		// if we filled up one buffer, then flush it out
		if (m_ulCurrentBufferMarker >= m_ulValidBufferSize[m_ulCurrentBuffer])
		{
			WaitForSingleObject(m_hOpDone, INFINITE);
			SetEvent(m_hStartOp);
			WaitForSingleObject(m_hOpStarted, INFINITE);

			// update book keeping variables
			m_ulCurrentBuffer = ((m_ulCurrentBuffer + 1) & 1);
			m_ulCurrentBufferMarker = 0;
		}
//		else
//			m_ulCurrentBufferMarker += dwBytesToCopy;
	}
	return ulBytesRead;	
}

bool CCamStreamFile::ReadFrame(void* data, unsigned long& preTimeStamp, unsigned long& postTimeStamp)
{
	unsigned long junk;
				// discard 4 high bytes for now TODO: fix this
	return ((ReadData(&preTimeStamp, 4) == 4) &&
			(ReadData(&junk, 4) == 4) &&
			(ReadData(data, GetFrameSize()) == GetFrameSize()) &&
			(ReadData(&postTimeStamp, 4) == 4) &&
			(ReadData(&junk, 4) == 4));
}

bool CCamStreamFile::WriteData(const void* data, unsigned long datasize)
{
//	DWORD dwResult;
//	DWORD dwLastError;
	DWORD dwBytesWritten = 0;
	while (datasize)
	{
		DWORD dwBytesToCopy = min(datasize, m_dwBufferSize - m_ulCurrentBufferMarker);
		memcpy(&(m_pBuffer[m_ulCurrentBuffer][m_ulCurrentBufferMarker]), (void*)((DWORD)data+dwBytesWritten), dwBytesToCopy);
		datasize -= dwBytesToCopy;
		m_ulCurrentBufferMarker += dwBytesToCopy;
		dwBytesWritten += dwBytesToCopy;

		// if we filled up one buffer, then flush it out
		if (m_ulCurrentBufferMarker >= m_dwBufferSize)
		{
			WaitForSingleObject(m_hOpDone, INFINITE);
			SetEvent(m_hStartOp);
			WaitForSingleObject(m_hOpStarted, INFINITE);

			// update book keeping variables
			m_ulCurrentBuffer = ((m_ulCurrentBuffer + 1) & 1);
			m_ulCurrentBufferMarker = 0;

		}
	}
	return true;
}

bool CCamStreamFile::CloseFile()
{
	DWORD dwResult;
	DWORD dwError;
	
	// stop the operation thread, but first, wait for it to finish its things...
	if (WaitForSingleObject(m_hOpStarted, 0) == WAIT_OBJECT_0)
		WaitForSingleObject(m_hOpDone, INFINITE);
	SetEvent(m_hQuitOpThread);
	WaitForSingleObject(m_hOpThreadDone, INFINITE);
	if (!m_bRead)
	{

		// if write, then flush out the last buffer!
//		GetOverlappedResult(m_hFile, &m_Overlapped, &m_dwBytesTransferred, TRUE);
//		m_Overlapped.Offset += m_dwBytesTransferred;
//		if (m_Overlapped.Offset < m_dwBytesTransferred)
//			m_Overlapped.OffsetHigh ++;

		// we can only write data chunks that are multiples of a sector (512 bytes)
		DWORD dwNumSectors = m_ulCurrentBufferMarker / 512;
		if (m_ulCurrentBufferMarker % 512)
			dwNumSectors++;
		dwResult = WriteFile(m_hFile, m_pBuffer[m_ulCurrentBuffer], dwNumSectors*512, &m_dwBytesTransferred, &m_Overlapped);
		dwError = GetLastError();
		GetOverlappedResult(m_hFile, &m_Overlapped, &m_dwBytesTransferred, TRUE);
//		dwResult = WriteFile(m_hFile, m_pBuffer[m_ulCurrentBuffer], m_ulCurrentBufferMarker, &m_dwBytesTransferred, &m_Overlapped);
//		GetOverlappedResult(m_hFile, &m_Overlapped, &m_dwBytesTransferred, TRUE);
	}

	// close file
	CloseHandle(m_hFile);

	// reset all the variables
	m_hFile = INVALID_HANDLE_VALUE;
	m_dwBytesTransferred = 0;
	m_Overlapped.Internal = m_Overlapped.InternalHigh =
		m_Overlapped.Offset = m_Overlapped.OffsetHigh = 0;
	m_ulCurrentBuffer = 0;
	m_ulCurrentBufferMarker = 0;

	return true;
}

DWORD WINAPI CCamStreamFile::ThreadProc(LPVOID lpParameter)
{
	CCamStreamFile* pThis = (CCamStreamFile*)lpParameter;
	if (pThis)
		pThis->OpThread();
	return 0;
}

void CCamStreamFile::OpThread()
{
	HANDLE hArray[2] =
	{
		m_hStartOp,
		m_hQuitOpThread
	};

	DWORD dwResult;
	DWORD dwError;
	while (WaitForMultipleObjects(2, hArray, FALSE, INFINITE) == WAIT_OBJECT_0)
	{
//		printf("writing buffer of %d bytes\r\n", m_dwBufferSize);
		unsigned long curBuff = m_ulCurrentBuffer;
		SetEvent(m_hOpStarted);
		void* buff = m_pBuffer[curBuff];

		// write to file
		if (m_bRead)
			dwResult = ReadFile(m_hFile, buff, m_dwBufferSize, &m_dwBytesTransferred, &m_Overlapped);
		else
			dwResult = WriteFile(m_hFile, buff, m_dwBufferSize, &m_dwBytesTransferred, &m_Overlapped);

		dwError =GetLastError();
		if (!(dwResult || (dwError == ERROR_IO_PENDING)))
		{
			printf("done reading from file!\n");
			m_ulValidBufferSize[curBuff] = 0;
		}
		else
		{
			GetOverlappedResult(m_hFile, &m_Overlapped, &m_dwBytesTransferred, TRUE);

			// advance the file pointer by adjusting the overlapped structure
			// NOTE: this is necessary when using no buffering
			m_Overlapped.Offset += m_dwBytesTransferred;
			m_ulValidBufferSize[curBuff] = m_dwBytesTransferred;
			if (m_Overlapped.Offset < m_dwBytesTransferred)
				m_Overlapped.OffsetHigh ++;
		}

		ResetEvent(m_hOpStarted);
		SetEvent(m_hOpDone);
	}
	printf("exiting thread\n");
	SetEvent(m_hOpThreadDone);
}

void CCamStreamFile::WriteTimestamp()
{
	LARGE_INTEGER ltimeStamp;
	if (QueryPerformanceCounter(&ltimeStamp))
	{
		WriteData(&ltimeStamp, 8);
	}
	else
	{
		DWORD timeStamp = timeGetTime();
		WriteData(&timeStamp, 4);
		timeStamp = 0;
		WriteData(&timeStamp, 4);
	}
}

void CCamStreamFile::WriteNullTimestamp()
{
	DWORD timeStamp = 0xffffffff;
	WriteData(&timeStamp, 4);
	WriteData(&timeStamp, 4);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// a whole bunch of get functions
//////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long CCamStreamFile::GetFrameSize()
{
	return m_Header.frame_size;
}

unsigned long CCamStreamFile::GetWidth()
{
	return m_Header.width;
}

unsigned long CCamStreamFile::GetHeight()
{
	return m_Header.height;
}

unsigned long CCamStreamFile::GetBpp()
{
	return m_Header.bpp;
}

unsigned long CCamStreamFile::GetPixelType()
{
	return m_Header.pixeltype;
}

unsigned long CCamStreamFile::GetXBin()
{
	return m_Header.xbin;
}

unsigned long CCamStreamFile::GetYBin()
{
	return m_Header.ybin;
}

void CCamStreamFile::GetDimension(unsigned long& width, unsigned long& height)
{
	width = m_Header.width;
	height = m_Header.height;
}

void CCamStreamFile::GetBinning(unsigned long& xbin, unsigned long& ybin)
{
	xbin = m_Header.xbin;
	ybin = m_Header.ybin;
}

unsigned long CCamStreamFile::GetEBpp()
{
	return m_Header.ebpp;
}

LARGE_INTEGER CCamStreamFile::GetTimeStampFreq()
{
	return m_Header.timestamp_freq;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// a whole bunch of set functions
//////////////////////////////////////////////////////////////////////////////////////////////////
void CCamStreamFile::SetCCDInfo(char* desc, unsigned long well_size, unsigned long adc_speed)
{
	if (strlen(desc) > 512)
	{
		memcpy(m_Header.CCDInfo.desc, desc, 511);
		m_Header.CCDInfo.desc[511] = 0;
	}
	else
		strcpy(m_Header.CCDInfo.desc, desc);
	m_Header.CCDInfo.well_size = well_size;
	m_Header.CCDInfo.adc_speed = adc_speed;
}

void CCamStreamFile::SetFrameSize(unsigned long frame_size)
{
	m_Header.frame_size = frame_size;
}

void CCamStreamFile::SetWidth(unsigned long width)
{
	m_Header.width = width;
}

void CCamStreamFile::SetHeight(unsigned long height)
{
	m_Header.height = height;
}

void CCamStreamFile::SetBpp(unsigned long bpp)
{
	m_Header.bpp = bpp;
}

void CCamStreamFile::SetPixelType(unsigned long pixtype)
{
	m_Header.pixeltype = pixtype;
}

void CCamStreamFile::SetXBin(unsigned long xbin)
{
	m_Header.xbin = xbin;
}

void CCamStreamFile::SetYBin(unsigned long ybin)
{
	m_Header.ybin = ybin;
}

void CCamStreamFile::SetDimension(unsigned long width, unsigned long height)
{
	m_Header.width = width;
	m_Header.height = height;
}

void CCamStreamFile::SetBinning(unsigned long xbin, unsigned long ybin)
{
	m_Header.xbin = xbin;
	m_Header.ybin = ybin;
}

void CCamStreamFile::SetEBpp(unsigned long ebpp)
{
}

void CCamStreamFile::SetTimeStampFreq(LARGE_INTEGER timestampfreq)
{
}



