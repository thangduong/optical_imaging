
#ifndef __VSTREAM_H__
#define __VSTREAM_H__

#include <VnVidSrc.h> 
#include <VnBase.h>
#include <VnVar.h>
#include <VnObject.h>



#define VS_MAX_IFRAMES 20
#define VS_NUM_SPACKETS 3


typedef enum {
	VS_FTYPE_IFRAME,
	VS_FTYPE_DELTAFRAME

} VS_STREAM_FTYPE;

typedef struct {
	DWORD packetNum;
	VS_GRAB_EXT_ATTR frameAttr[VS_MAX_IFRAMES];
	DWORD frameOffsets[VS_MAX_IFRAMES+1]; // Contains frameLegendOffsets for DJPEG
	DWORD frameLegendLen; // Length (in bytes) of frame Legend in the data field
	VS_STREAM_FTYPE frameType[VS_MAX_IFRAMES];
	DWORD jpgWidth;
	DWORD jpgHeight;
	DWORD jpgBaseOffset;
	DWORD jpgLen;
	DWORD stagingAreaOffset;
	DWORD dataLen;
	BYTE data[4];
} VS_STREAM_PACKET;



class IVSV_EXT_API CVideoStreamServer : public CVnObject {

	public:

	CVideoStreamServer(IVideoSrc *VnDriver, PVS_STREAM_PARAMS params);
	virtual ~CVideoStreamServer();

	DWORD VideoServerThread();

	BOOL WaitStreamPacket( BYTE *dest, DWORD bytesAvailable, DWORD *bytesRead, DWORD milliseconds);

	IVideoSrc *m_iVideoSrc;
	CVideoSrcDriver *m_videoSrcDrv;

	HANDLE m_hthread;
	VS_STREAM_PARAMS m_params;
	volatile BOOLEAN m_shutdown;
	VS_STREAM_PACKET *m_sPackets[VS_NUM_SPACKETS];
	VS_CAM_ATTR m_attr;
	DWORD m_frameSize;
	DWORD m_sPacketLen;
	DWORD m_ConservativeCompressFactor;

	DWORD m_packetNum[VS_NUM_SPACKETS]; // 0 is empty packet
	HANDLE m_packetMutexs[VS_NUM_SPACKETS];
	HANDLE m_newPacketSema;
	BOOL m_autoFrameRate;
	DWORD m_numConsumedPackets;
	BOOL m_vidSrcLocked;
	ULONGLONG m_lastWaitStreamPacketCallTime;

};



#define INVALID_PACKET_NUM 0x7fffffff

class IVSV_EXT_API CVideoStreamClient : public CVnObject {

	public:


	CVideoStreamClient(IVideoSrc *videoSrc,PVS_STREAM_PARAMS params);
	virtual ~CVideoStreamClient();
	DWORD VideoClientThread();

	BOOL WaitStreamFrame( BYTE *dest, PVS_STREAM_FRAME_ATTR frameAttr, DWORD milliseconds);

	IVideoSrc *m_videoSrcDrv;
	HVIDSTREAMSRV m_hSrvStream;
	IStream *m_pStmPtr;
	HANDLE m_hthread;
	VS_STREAM_PARAMS m_params;
	volatile BOOLEAN m_shutdown;
	VS_STREAM_PACKET *m_sPackets[VS_NUM_SPACKETS];
	DWORD m_sPacketLen;
	DWORD m_curReadPacket;

	VS_CAM_ATTR m_attr;
	DWORD m_frameSize;
	HANDLE m_packetMutexs[VS_NUM_SPACKETS];

	HANDLE m_newPacketSema;
	DWORD m_curReadPacketNum;
	DWORD m_ConservativeCompressFactor;

	ULONGLONG m_lastDisplayTime;
	DWORD m_deltaArriveTime;
	DWORD m_DeltaArriveTimeSum;
	DWORD m_DeltaArriveSamples;
	BYTE *m_stagingArea;
	DWORD m_stagingOffx;
	DWORD m_stagingOffy;


};



#endif

