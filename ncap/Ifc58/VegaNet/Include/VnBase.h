

#ifndef __VnBase_h__
#define __VnBase_h__

#include <VnVar.h>
#include <vidsrct.h>
#include <vfw.h>


#define IVS_UTILITY_LIBNAME "VnBase.lib"

#if defined WIN32 &&  !defined VnBase_EXPORTS

#pragma comment(lib, IVS_UTILITY_LIBNAME)

#endif

class CVnVar;
class CVideoSrcDriver;
struct IVideoSrc;
struct IVidSrcCfg;
struct IDistribOS;
struct IImgNode;
struct IProcNode;
struct IVideoStream;
struct IFileNode;

#ifndef __IImgDisplay_FWD_DEFINED__
#define __IImgDisplay_FWD_DEFINED__
typedef interface IImgDisplay IImgDisplay;
#endif 	/* __IImgDisplay_FWD_DEFINED__ */


typedef IVidSrcCfg *PIVidSrcCfg;
typedef IVideoSrc *PIVideoSrc;
typedef IVideoStream *PIVideoStream;
typedef IImgNode *PIImgNode;
typedef IImgDisplay *PIImgDisplay;
typedef IProcNode *PIProcNode;
typedef IFileNode *PIFileNode;

typedef DWORD HNODESPLITTER;

typedef enum {
	FN_MODE_IDLE,
	FN_MODE_READING,
	FN_MODE_WRITING,
	FN_RANDOM_MODE_READING,
	FN_MODE_OP_IN_PROGRESS

} 	FN_MODE_TYPE;


typedef struct _FN_READ_IMAGE FN_READ_IMAGE;
struct _FN_READ_IMAGE {
	FN_READ_IMAGE *next;

	BYTE img[4];
	
};

#define VS_AVI_OPT_NO_LINE_REV		0x00000001
#define VS_AVI_OPT_YUV420PLANAR		0x10000000
#define VS_AVI_OPT_BAYER_BG_GR		0x20000000
#define VS_AVI_OPT_BAYER_GB_RG		0x40000000
#define VS_AVI_OPT_INTERP_54_X		0x80000000


#define FN_MAX_FILE_FRAMES 500000

#define FN_IMAGE_SIGNATURE 0xcafebabe
#define FN_SOUND_SIGNATURE 0xcafedafe
#define FN_SEEK_START_SIGNATURE 0xafadcafe
#define FN_SEEK_TABLE_SIGNATURE 0xafadface

#define FN_WAVE_NAME_LEN 120

typedef struct {
	DWORD tableSignature;
	DWORD numFrames;
//	LONGLONG m_seekTable[1];  // i.e., Table follows
} FN_SEEK_TABLE_DESC;

typedef struct {
	DWORD startSignature;
	LONGLONG seekTableOffset;
	DWORD numFrames;
	LONGLONG soundDescOffset;
	LONGLONG videoStartTime;
	LONGLONG videoEndTime;
} FN_SEEK_START_DESC;



typedef struct {
	DWORD signature;
	VS_INODE_IMG_ATTR imgAttr;
	VS_FRAME_ENCODE encodeKind;
	DWORD encodeSize;
} FN_IMAGE_DESC;

typedef struct {
	DWORD offset;
	ULONGLONG recordStartTime; // Start systime in microseconds
} FN_SOUND_START_REC;

#define MAX_NUM_SOUND_START_RECS 20

typedef struct {
	DWORD signature;
	FN_SOUND_DESC sndDesc;
	char waveFileName[FN_WAVE_NAME_LEN];
	DWORD soundSize;
	ULONGLONG recordStartTime; // Start systime in microseconds
	double sndTimeCorrFactor; // Apply to offset infered time to get real-time
	DWORD numSections;
	FN_SOUND_START_REC sections[MAX_NUM_SOUND_START_RECS];
} FN_SOUND_REC_DESC;


typedef struct {
	DWORD baseFrameOffset; // 0..(m_numDJpegPktFrames-1) 
	DWORD baseFrameSeqnum;
} FN_DESC_DJPEG;

typedef struct {
	FN_IMAGE_DESC b;
	FN_DESC_DJPEG dj;
} FN_IMAGE_DESC_EX;


#define VS_MAX_IFRAMES 20

typedef struct {
	VS_INODE_IMG_ATTR frameAttr[VS_MAX_IFRAMES];
	DWORD stagingOffx[VS_MAX_IFRAMES];
	DWORD stagingOffy[VS_MAX_IFRAMES];
	DWORD frameOffsets[VS_MAX_IFRAMES+1]; // Contains frameLegendOffsets for DJPEG
	DWORD frameLegendLen; // Length (in bytes) of frame Legend in the data field
	DWORD jpgWidth;
	DWORD jpgHeight;
	DWORD jpgBaseOffset;
	DWORD jpgLen;
	DWORD dataLen;
	BYTE data[4];
} VS_DJPEG_PACKET, *PVS_DJPEG_PACKET;



typedef int (*pfCONSOLEHDLR)(const char *, va_list);

typedef BOOL   (IVSAPI *pNodeProcFunc)(BYTE *imgPtr, void *pProcessArg, BYTE *payload, DWORD PayloadSize);
typedef BOOL   (IVSAPI *pAlphaBlendFunc)(BYTE *imgPtr, void *pProcessArg);

typedef BOOL   (IVSAPI *pConvProgressFunc)( DWORD numFramesConverted, DWORD totalNumFrames, void*param);


int IVS_EXT_API VsConsole(const char *format, ...);
int IVS_EXT_API VsConsoleV(const char * fmt, va_list marker);



#ifdef __cplusplus
extern "C" {
#endif


BOOL IVSCALL GetEnumVideoSrcProps(DWORD index,LPVSPROPS vidSrcProps);

BOOL IVSCALL AddVideoSrcToReg(LPVSPROPS vidSrcProps );

BOOL IVSCALL GetVideoSrcFromReg(LPCSTR vidSrcName, LPVSPROPS vidSrcProps );


void IVSCALL VnVarChangeType(CVnVar* pDst, VARTYPE vartype, const CVnVar* pSrc);
void IVSCALL VARIANT2VnVar(CVnVar* pDst, const VARIANT* pSrc);


FARPROC IVSCALL VsGetProcAddress(HMODULE hModule,LPCSTR lpProcName,DWORD popCount);

FARPROC IVSCALL VsGetNamedProcAddress(LPCSTR lpDllName,LPCSTR lpFuncName,DWORD popCount);
FARPROC IVSCALL VsGetDescProcAddress(CVSInvokeDesc *procDesc,DWORD popCount);


BOOL IVSCALL VsAddDetectedVideoSrcs(LPCSTR driverDllName, DWORD options);

BOOL IVSCALL VsEncodeFrame(VS_FRAME_ENCODE encode,BYTE *src,VS_COLOR color, DWORD dwWidth,DWORD dwHeight,
			DWORD bitsPerPixel, DWORD bytesAvailable, BYTE *dest,DWORD &bytesUsed,int quality=75);

BOOL IVSCALL VsDecodeFrame(BYTE *src,DWORD numSrcBytes,VS_FRAME_ENCODE encode, DWORD &dx, DWORD &dy, VS_COLOR color, DWORD bitsPerPixel, BYTE *dest);

PIVideoStream IVSCALL VsCreateVideoStream(IVideoSrc *videoSrc,PVS_STREAM_PARAMS params);
void IVSCALL VsDeleteVideoStream(PIVideoStream videoStream);

BOOL IVSCALL VsWaitStreamFrame(HVIDSTREAM videoStream,BYTE *dest, PVS_STREAM_FRAME_ATTR frameAttr, DWORD milliseconds);


// Implementation / private functions

HVIDSTREAMSRV IVSCALL VsCreateVideoStreamServer(IVideoSrc *VnDriver, PVS_STREAM_PARAMS params);

void IVSCALL VsDeleteVideoStreamServer(HVIDSTREAMSRV vidStreamServer);

BOOL IVSCALL VsCtlRegister(LPTSTR m_strPathName);

HRESULT IVSCALL VsInvokeClientFuncBlk(IDistribOS *vidSrc, HVSMESSAGE msgQueue, HVSMESSAGE retQueue, LPSTR funcName, BYTE *paramBlock, DWORD numParamBytes);
HRESULT IVSCALL VsInvokeClientFuncVar(IDistribOS *vidSrc, HVSMESSAGE msgQueue, HVSMESSAGE retQueue, LPSTR funcName, DWORD numParams, VSPARAM params[]);

DWORD IVSCALL VsCreateClientRpcServer(IDistribOS *vidSrc, HVSMESSAGE sendQueue, HVSMESSAGE msgQueue, HVSMESSAGE retQueue);
void IVSCALL VsDeleteClientRpcServer(IDistribOS *vidSrc,HVSMESSAGE sendQueue,HVSMESSAGE retQueue,DWORD hRpcServer);
HRESULT IVSCALL VsTerminateClientRpcServer(IDistribOS *vidSrc, HVSMESSAGE msgQueue, HVSEVENT shutdownEvent);

HRESULT IVSCALL VsServerToClientFileCopy(IDistribOS *vidSrc, LPSTR srcServerFileName, LPSTR dstClientFileName);
HRESULT IVSCALL VsClientToServerFileCopy(IDistribOS *vidSrc, LPSTR srcClientFileName , LPSTR dstServerFileName);
HRESULT IVSCALL VsClientToClientFileCopy(IDistribOS *vidSrc, LPSTR srcClientFileName , LPSTR dstClientFileName);

PIVidSrcCfg IVSCALL VsCreateVidSrcCfg(HRESULT *result);

PIImgNode IVSCALL VsCreateImgNode(IDispatch *src, DWORD srcOutputId, IDispatch *sink, VS_INODE_QMNG_ATTR *attr);

BOOL IVSCALL VsDeleteImgNode(PIImgNode node, VS_PROD_CONSMR_ID_KIND proConId);

HRESULT IVSCALL InvokeNotifyDetachProducer(IDispatch *producer,IDispatch *node, DWORD srcOutputId);
HRESULT IVSCALL InvokeNotifyDetachConsumer(IDispatch *Consumer,IDispatch *node);

HRESULT IVSCALL InvokeActivateConsumer(IDispatch *consumer,VS_REF_VAL_KIND deQKind,BOOL areRemote);
HRESULT IVSCALL InvokeActivateProducer(IDispatch *producer, DWORD srcOutputId, VS_REF_VAL_KIND enQKind, BOOL areRemote);
HRESULT IVSCALL InvokeConsumeFrom(IDispatch *Consumer,IDispatch *imgNode);


HRESULT IVSCALL InvokeReleaseEleRef(IDispatch *provider, DWORD srcOutputId, HBYREFELE deRefHandle);	
LPDISPATCH IVSCALL VsGetRootConsumer(IDispatch *sink);
LPDISPATCH IVSCALL VsGetIVideoSrc(LPDISPATCH vidSrc,BOOL addRef);


HRESULT IVSCALL VsEnqueue(PIImgNode node,VS_INODE_IMG_ATTR *imgAttr,BYTE *frameAddr,BOOL byRef,VS_FRAME_ENCODE Encode,HBYREFELE deRefHandle, BYTE *userPayload, DWORD payloadNumBytes);
HRESULT IVSCALL VsDequeueByVal(PIImgNode node,VS_INODE_IMG_ATTR *imgAttr,BYTE *frameAddr,DWORD bytesAvailable,VS_FRAME_ENCODE Encode, DWORD waitMilliSecs, HVSEVENT preemptEvent, BYTE *userPayload, DWORD *payloadNumBytes);

PIImgDisplay IVSCALL VsCreateDisplayNode(VS_HWND hwnd, DWORD Flags, pNodeProcFunc pFunc, void *pArg);
PIImgDisplay IVSCALL VsCreateVideoSrcDisplay(IVideoSrc *pVidSrc, VS_HWND hwnd, DWORD Flags, VS_ICAP_INTR_EVENT intrEvent, int iScale);
PIImgDisplay IVSCALL VsCreateBuffDisplay(BYTE *pImgBuffer, DWORD wWidth, DWORD wHeight, DWORD wImgBitsPP, VS_HWND hwnd, VS_COLOR eColor, DWORD Flags);
void IVSCALL VsDeleteDisplayNode(PIImgDisplay displayNode);


PIProcNode IVSCALL VsCreateProcessNode(IDistribOS *localToObj);
HRESULT IVSCALL VsDeleteProcessNode(IDistribOS *localToObj, PIProcNode pNode);

BOOL IVSCALL VsCallerLocalToObj(IDistribOS *dosObj);

HPROCESSTHREAD IVSCALL VsCreateServerObjThread(IProcNode *imgProcNode, REFCLSID rclsid, REFIID riid, void  **ppvObject);
void IVSCALL VsDeleteProcessThread(IProcNode *imgProcNode, HPROCESSTHREAD hProcThread, IDispatch *objThread);

HNODESPLITTER IVSCALL VsCreateNodeSplitter(IDistribOS *localToObj, PIProcNode *procNode, VS_FRAME_ENCODE remoteUseEncode);
HRESULT IVSCALL VsDeleteNodeSplitter(HNODESPLITTER nodeSplitter);

PIFileNode IVSCALL VsCreateFileNode(IDistribOS *localToObj);
HRESULT IVSCALL VsDeleteFileNode(PIFileNode fileNode);



HRESULT IVSCALL VsOpenDistribOS(IDistribOS *dosObj);

BOOL IVSCALL VsBuildBlobs(int PixelsPerLine,int linesPerFrame, int featureCount,LPVS_RLE_FEATURE_DESC rleSrc, int &numBlobs, VS_BLOB_DESC* dst, int max_blob_ysize, BOOL tagBlobs);
BOOL IVSCALL VsRleEncode(BYTE *image, DWORD dwWidth, DWORD dwHeight, LPVS_RLE_FEATURE_DESC rleEncode,DWORD numFeaturesSpace,DWORD *numFeatures);

HRESULT IVSCALL TurnOffAuthenticationOnThisInterface(REFIID riid, IUnknown* pUnk2 );

BOOL IVSCALL VnConvertVnmToAvi(char *VnmFileName,char *AviFileName,BOOL compressFlag, DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, DWORD dwKeyFrameEvery);

BOOL IVSCALL VnConvertVnmToAviQuery(HWND hwnd, char *VnmFileName,char *AviFileName,pConvProgressFunc progressCallback, void* cbParam);

BOOL IVSCALL VnConvertVnmToAviCb(char *VnmFileName,char *AviFileName,BOOL compressFlag, DWORD dwBytesPerSecond, 
			   DWORD fccHandler, DWORD dwQuality, DWORD dwKeyFrameEvery, pConvProgressFunc progressCallback, void* cbParam);

BOOL IVSCALL VnConvertVnmToAviEx(char *VnmFileName, char *AviFileName, AVICOMPRESSOPTIONS	*opts,
			pConvProgressFunc progressCallback, void* cbParam);

PAVIFILE IVSCALL VnGetAviFileHandle(DWORD context);

DWORD IVSCALL VnSetupAcquireToAviFileEx(LPSTR fname, DWORD dx, DWORD dy, DWORD bits, DWORD fps_x1000,
											BOOL logical_bitmap,
										    AVICOMPRESSOPTIONS	*opts, DWORD options);

DWORD IVSCALL VnSetupAcquireToAviFileEx2(LPSTR fname, DWORD dx, DWORD dy, DWORD bits, DWORD fps_x1000,
											BOOL logical_bitmap,
										    AVICOMPRESSOPTIONS	*opts, DWORD options, VS_BAYER_EXT_ATTR *bayerExtAttr);


void  IVSCALL VnCleanupAcquireToAviFile(DWORD context);
BOOL IVSCALL VnAcquireToAviFile(DWORD context, DWORD frameSeqnum, BYTE *buff);

DWORD IVSCALL VnAviNumFramesSaved(DWORD context);


BOOL IVSCALL VsQueryCameraType(IVideoSrc *vidSrc);
PIVideoSrc IVSCALL VsQueryCreateVidSrc(IVidSrcCfg *vidSrcCfg, char *nodeName);

void IVSCALL VsDeleteVideoSrc(IVideoSrc *vidSrc);

BOOL IVSCALL VnGetVidSrcNameCmpts(char *vidSrcName, char *name1, char *name2, DWORD *index );

void IVSCALL VnSetAviFrameRate(char *aviFileName, double frameRate);


#ifdef __cplusplus
}
#endif








#endif