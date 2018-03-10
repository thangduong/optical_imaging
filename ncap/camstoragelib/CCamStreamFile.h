////////////////////////////////////////////////////////////////////////////////////////////////////
// CCamStreamFile.h
//
//   Header for class CCamStreamFile.  CCamStreamFile encapsulates code to stream to and from
// cam stream files (.CSF).  Cam stream files contain a stream of continuous images from the camera.
// Each image is contains a pre and post time stamp, and there is a header at the start of the file
// describing the stream.  See CamStreamFileHdr for more info.
//
// REVISION HISTORY
//=================================================================================================
//
// Tuesday	07/15/2003	Thang	- Added this revision history.  
//								- Created this file and class last week.
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CCAMSTREAMFILE_H
#define CCAMSTREAMFILE_H

#include <windows.h>
#include "CamStreamFile.h"

class CCamStreamFile  
{
protected:
	CamStreamFileHdr m_Header;
	unsigned long m_ulCurrentBuffer;
	unsigned long m_ulCurrentBufferMarker;
	unsigned long m_ulValidBufferSize[2];
	char* m_pBuffer[2];
	OVERLAPPED m_Overlapped;
	DWORD m_dwBytesTransferred;
	HANDLE m_hFile;
	bool m_bRead;
	unsigned long m_dwBufferSize;

	// Handles to events that control (or receive status)
	// from the operation thread (OpThread())
	//		m_hStartOp		Set this event to initiate operation
	//		m_hQuitOpThread	Set this event to terminate operation thread
	//		m_hOpDone		This event gets set when operation is done
	//		m_hOpStarted	This event gets set when operation has started
	//		m_hOpThreadDone	This event gets set when the thread is about to quit
	// NOTE: m_hOpDone should initially be set
	HANDLE m_hStartOp;
	HANDLE m_hQuitOpThread;
	HANDLE m_hOpDone;
	HANDLE m_hOpStarted;
	HANDLE m_hOpThreadDone;

	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
	void OpThread();
public:
	CCamStreamFile(DWORD dwBufferSize = (1024*1024*1));
	virtual ~CCamStreamFile();

	////////////////////////////////////////////////////////////////////////////////
	// These functions allow access to information about the stream
	////////////////////////////////////////////////////////////////////////////////
	void SetStreamInfo(
		unsigned long width,
		unsigned long height,
		unsigned long ebpp,
		unsigned long bpp,
		unsigned long xbin,
		unsigned long ybin,
		unsigned long frame_size,
		double expected_fps);
	void GetStreamInfo(
		unsigned long& width,
		unsigned long& height,
		unsigned long& ebpp,
		unsigned long& bpp,
		unsigned long& xbin,
		unsigned long& ybin,
		unsigned long& frame_size,
		double& expected_fps);

	/////////////////////////////////////////////////////////////////////////////////
	// a bunch of set functions
	/////////////////////////////////////////////////////////////////////////////////
	void SetCCDInfo(char* desc, unsigned long well_size, unsigned long adc_speed);
	void SetFrameSize(unsigned long frame_size);
	void SetWidth(unsigned long width);
	void SetHeight(unsigned long height);
	void SetBpp(unsigned long bpp);
	void SetPixelType(unsigned long pixtype);
	void SetXBin(unsigned long xbin);
	void SetYBin(unsigned long ybin);
	void SetDimension(unsigned long width, unsigned long height);
	void SetBinning(unsigned long xbin, unsigned long ybin);
	void SetEBpp(unsigned long ebpp);
	void SetTimeStampFreq(LARGE_INTEGER timestampfreq);

	/////////////////////////////////////////////////////////////////////////////////
	// a whole bunch of get_ functions
	/////////////////////////////////////////////////////////////////////////////////
	CamStreamFileHdr* GetStreamHeader();
	unsigned long GetFrameSize();
	unsigned long GetWidth();
	unsigned long GetHeight();
	unsigned long GetBpp();
	unsigned long GetPixelType();
	unsigned long GetXBin();
	unsigned long GetYBin();
	void GetDimension(unsigned long& width, unsigned long& height);
	void GetBinning(unsigned long& xbin, unsigned long& ybin);
	unsigned long GetEBpp();
	LARGE_INTEGER GetTimeStampFreq();

	// Opens a CSF file.
	//    read = true to open the file for read
	//    read = false to open the file for write
	//    oldStyle = true to read from old style files.  this only works for read
	bool OpenFile(const char* filename, bool read, bool oldStyle = true);
	bool CloseFile();

	////////////////////////////////////////////////////////////////////////////////////
	// These functions are specific for writing to a stream file
	////////////////////////////////////////////////////////////////////////////////////
	bool WriteData(const void* data, unsigned long datasize);
	void WriteTimestamp();
	void WriteNullTimestamp();

	////////////////////////////////////////////////////////////////////////////////////
	// These functions are specific for reading from a stream file
	////////////////////////////////////////////////////////////////////////////////////
	unsigned long ReadData(void* data, unsigned long datasize);
	bool ReadFrame(void* data, unsigned long& preTimeStamp, unsigned long& postTimeStamp);


};

#endif
