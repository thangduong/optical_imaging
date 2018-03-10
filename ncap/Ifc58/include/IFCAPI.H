#include <ifc.h>
#include <pcdcam.h>
#include <lnkcam.h>
#include <nspcam.h>

#ifdef __cplusplus
extern "C" {
#endif

/* CICamera Class */
void IFCCALL CICamera_ReleaseCamFrame(CICamera *pCamera, CIFrame *frame);
pCIFrame IFCCALL CICamera_GetCamFrame(CICamera *pCamera);
pCInterrupt IFCCALL CICamera_CreateInterruptObject(CICamera *pCamera, ICAP_INTR_EVENT intrEvent);
void IFCCALL CICamera_UpdateParams(CICamera *pCamera);
BOOL IFCCALL CICamera_AcqParamSupported(CICamera *pCamera,ACQ_PARAMS_TYPE paramID);
double IFCCALL CICamera_GetAcqParam(CICamera *pCamera,ACQ_PARAMS_TYPE paramID,DWORD index);
void IFCCALL CICamera_SetAcqParam(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, double value,DWORD index);
void IFCCALL CICamera_GetParamCaps(CICamera *pCamera,ACQ_PARAMS_TYPE paramID,PIFC_PARAM_CAPS lpParamCaps);
ACQ_PARAMS_TYPE IFCCALL CICamera_GetFirstParam(CICamera *pCamera,DWORD paramGroupMask);
ACQ_PARAMS_TYPE IFCCALL CICamera_GetNextParam(CICamera *pCamera,ACQ_PARAMS_TYPE paramID,DWORD paramGroupMask);
IFC_PARAM_GROUP_TYPE IFCCALL CICamera_GetFirstParamGroup(CICamera *pCamera);
IFC_PARAM_GROUP_TYPE IFCCALL CICamera_GetNextParamGroup(CICamera *pCamera,IFC_PARAM_GROUP_TYPE groupID);
void IFCCALL CICamera_GetGroupProperties(CICamera *pCamera,IFC_PARAM_GROUP_TYPE groupID,PIFC_PARAM_GROUP_PROPS lpGroupProps);
BOOL IFCCALL CICamera_GetFirstEnumArg(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, IFC_ENUM_ARG *arg);
BOOL IFCCALL CICamera_GetNextEnumArg(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, IFC_ENUM_ARG *arg);
BOOL IFCCALL CICamera_IsArgSupported(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, double arg);
double IFCCALL CICamera_ClosestArgSupported(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, double arg);
pSTRING IFCCALL CICamera_GetArgName(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, double dArg);
double IFCCALL CICamera_GetArgValue(CICamera *pCamera,ACQ_PARAMS_TYPE paramID, const char *szArgName);
BOOL IFCCALL CICamera_SetLutFunction(CICamera *pCamera,LUTID_TYPE lutID,IFCLUTFUNC func,DWORD *constants,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_ReadLutBuf(CICamera *pCamera,LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_WriteLutBuf(CICamera *pCamera,LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,LUT_PORTION_TYPE lutPortion);
DWORD IFCCALL CICamera_ReadLutLoc(CICamera *pCamera,LUTID_TYPE lutID, DWORD lutAdr,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_WriteLutLoc(CICamera *pCamera,LUTID_TYPE lutID,DWORD lutAdr,DWORD val,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_LinearizeLut(CICamera *pCamera,LUTID_TYPE lutID,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_FloodLUT(CICamera *pCamera,LUTID_TYPE lutID,DWORD val,LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_InvertLut(CICamera *pCamera,LUTID_TYPE lutID, LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_ThresholdLut(CICamera *pCamera,LUTID_TYPE lutID, const DWORD dwThreshold, LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_OffsetLut(CICamera *pCamera,LUTID_TYPE lutID, const long lOffset, LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_RgbToHsiLUT(CICamera *pCamera,LUTID_TYPE lutID, LUT_PORTION_TYPE lutPortion);
void IFCCALL CICamera_GetLUTCaps(CICamera *pCamera,LPLUTCAP caps);
void IFCCALL CICamera_SetLutPathPage(CICamera *pCamera,LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum);
void IFCCALL CICamera_SetLutHostPage(CICamera *pCamera,LUTID_TYPE lutID,IFC_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum,BOOL leftJustify);
void IFCCALL CICamera_SetWindowGen(CICamera *pCamera,short x, short y, short dx, short dy);
BOOL IFCCALL CICamera_SetCameraType(CICamera *pCamera,pSTRING camName,BOOL updateHW);
pSTRING IFCCALL CICamera_GetNextCamType(CICamera *pCamera);
pSTRING IFCCALL CICamera_GetFirstCamType(CICamera *pCamera);
int IFCCALL CICamera_Freeze(CICamera *pCamera);
int IFCCALL CICamera_FreezeEx(CICamera *pCamera, HIFCGRAB grabID);

void IFCCALL CICamera_Snap(CICamera *pCamera);
void IFCCALL CICamera_Grab(CICamera *pCamera);
BOOL IFCCALL CICamera_Grab_HostBuf(CICamera *pCamera,pBYTE dest, int ringNumFrames,int totalNumFrames, short x, short y, short dx, short dy);
HIFCGRAB IFCCALL CICamera_Grab_HostBufEx(CICamera *pCamera, DWORD dwOptions, pBYTE dest, int ringNumFrames,int totalNumFrames, short x, short y, short dx, short dy);
HIFCGRAB IFCCALL CICamera_Grab_HostBufListEx(CICamera *pCamera, DWORD dwOptions, pBYTE dest[], int ringNumFrames,int totalNumFrames, short x, short y, short dx, short dy);

void IFCCALL CICamera_GrabLock(CICamera *pCamera,int seqNum);
void IFCCALL CICamera_GrabLockEx(CICamera *pCamera, HIFCGRAB grabID, int seqNum);
void IFCCALL CICamera_GrabRelease(CICamera *pCamera,int seqNum);
void IFCCALL CICamera_GrabReleaseEx(CICamera *pCamera, HIFCGRAB grabID, int seqNum);

int IFCCALL CICamera_GrabWaitFrame(CICamera *pCamera,BYTE **frameAddr, int FrameSeqNum, DWORD milliseconds, BOOL lock,DWORD *acquiredDy );
int IFCCALL CICamera_GrabWaitFrameEx(CICamera *pCamera,HIFCGRAB grabID,BYTE **frameAddr, int FrameSeqNum, DWORD milliseconds, BOOL lock, DWORD *acquiredDy , GRAB_EXT_ATTR *ExtendedAttr );

int IFCCALL CICamera_GrabFrameSeqNum(CICamera *pCamera,int frameRingNum);
int IFCCALL CICamera_GrabFrameSeqNumEx(CICamera *pCamera, HIFCGRAB grabID, int frameRingNum);
BOOL IFCCALL CICamera_GetGrabStats(CICamera *pCamera, HIFCGRAB grabID,IFC_GRAB_STATS *stats);
BOOL IFCCALL CICamera_GrabGetExtAttr(CICamera *pCamera, HIFCGRAB grabID, int seqNum, GRAB_EXT_ATTR *ExtendedAttr);


BOOL IFCCALL CICamera_Snap_HostBuf(CICamera *pCamera, pBYTE dest,short x, short y, short dx, short dy);
BOOL IFCCALL CICamera_SeqSnap(CICamera *pCamera, pBYTE dest, int numFrames,short x, short y, short dx, short dy, DWORD dwMilliseconds);
pBYTE IFCCALL CICamera_SeqSnapPhys(CICamera *pCamera, DWORD numFrames, DWORD destOffset, short x, short y, short dx, short dy, DWORD dwMilliseconds, DWORD *acquiredDys);
int IFCCALL CICamera_WaitPhysFrame(CICamera *pCamera, BYTE **frameAddr, int FrameSeqNum, DWORD dwMilliseconds,DWORD *acquiredDy);

BOOL IFCCALL CICamera_TrigRead(CICamera *pCamera,short x, short y, short dx, short dy, pBYTE dest);
BOOL IFCCALL CICamera_WaitTrig(CICamera *pCamera,long waitTime);
BOOL IFCCALL CICamera_TrigSnap(CICamera *pCamera,DWORD trigSource);
BOOL IFCCALL CICamera_StartTrigOps(CICamera *pCamera);
BOOL IFCCALL CICamera_StopTrigOps(CICamera *pCamera);
BOOL IFCCALL CICamera_SetZoom(CICamera *pCamera,float xZoom, float yZoom);
void IFCCALL CICamera_GetZoomCaps(CICamera *pCamera,LPZOOMCAP lpCaps);
BOOL IFCCALL CICamera_ReadArea (CICamera *pCamera,short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx,DWORD readOptions );
void IFCCALL CICamera_LineReverseRead (CICamera *pCamera,short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr, DWORD readOptions);
void IFCCALL CICamera_ReadDestPitchArea (CICamera *pCamera,short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions);
void IFCCALL CICamera_GetAttr(CICamera *pCamera,LPCAM_ATTR lpAttr, BOOL zoomCorrected);
void IFCCALL CICamera_GetReadCaps(CICamera *pCamera,LPREADCAP lpCaps);
void IFCCALL CICamera_SetReadColorRemap(CICamera *pCamera,BOOL bEnabled);
DWORD IFCCALL CICamera_ReadReg(CICamera *pCamera,REGID reg);
void IFCCALL CICamera_WriteReg(CICamera *pCamera,REGID reg, DWORD val);
BOOL IFCCALL CICamera_UpdateParamFromCfg(CICamera *pCamera,CConfig *cfg,IFC_PARAM_KIND parmType,DWORD numVals,double *paramVal);
BOOL IFCCALL CICamera_WriteParamToCfg(CICamera *pCamera,CConfig *cfg, IFC_PARAM_KIND parmType, DWORD numVals, double *paramVal);

BOOL IFCCALL CICamera_WriteUartCommand(CICamera *pCamera, BYTE *cmd,DWORD numBytes, DWORD uartIndex);
BOOL IFCCALL CICamera_ReadUartCommand(CICamera *pCamera, BYTE *cmd,DWORD numBytesToRead, DWORD *numBytesRead,DWORD uartIndex);
BOOL IFCCALL CICamera_UartCommandResponse(CICamera *pCamera, BYTE *cmd,DWORD numCmdBytes,BYTE *response,DWORD numBytesToRead, DWORD *numBytesRead,DWORD uartIndex);

BOOL IFCCALL CICamera_TransformSupported(CICamera *pCamera,IFC_TRANSFORM_TYPE eTransform);
BOOL IFCCALL CICamera_SetTransform(CICamera *pCamera,IFC_TRANSFORM_TYPE eTransform);
IFC_TRANSFORM_TYPE IFCCALL CICamera_GetCurrentTransform(CICamera *pCamera);
DWORD IFCCALL CICamera_GetPortNum(CICamera *pCamera);
ACQ_PARAMS_TYPE IFCCALL CICamera_GetParamAlias(CICamera *pCamera, ACQ_PARAMS_TYPE paramID);


/* CICapMod class */
pCInterrupt IFCCALL CICapMod_CreateInterruptObject(CICapMod *capMod,CICamera *cam,ICAP_INTR_EVENT intrEvent);
BOOL IFCCALL CICapMod_CreateSeqFrame(CICapMod *capMod,int frameCnt,CIFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
pCIFrame IFCCALL CICapMod_CreateFrame(CICapMod *capMod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
void IFCCALL CICapMod_DeleteAllFrames(CICapMod *capMod);
void IFCCALL CICapMod_Cleanup(CICapMod *capMod);
pCIFrame IFCCALL CICapMod_GetCamFrame(CICapMod *capMod,CICamera *cam);
void IFCCALL CICapMod_ReleaseCamFrame(CICapMod *capMod,CICamera *camera,CIFrame * frame);
void IFCCALL CICapMod_GrabRelease(CICapMod *capMod,HIFCGRAB grabID, int seqNum);
void IFCCALL CICapMod_GrabLock(CICapMod *capMod,HIFCGRAB grabID, int seqNum);
int IFCCALL CICapMod_GrabStop(CICapMod *capMod,HIFCGRAB grabID);
int IFCCALL CICapMod_GrabWaitFrame(CICapMod *capMod,HIFCGRAB grabID, BYTE **frameAddr, int FrameSeqNum, DWORD milliseconds, BOOL lock,DWORD *acquiredDy); 
HIFCGRAB IFCCALL CICapMod_Grab_HostBuf(CICapMod *capMod,CICamera *camera, DWORD dwModes, pBYTE dest, int ringNumFrames,int totalNumFrames, short x, short y, short dx, short dy) ;     
int IFCCALL CICapMod_GrabFrameSeqNum(CICapMod *capMod,HIFCGRAB grabID,int frameRingNum) ; 
BOOL IFCCALL CICapMod_SeqSnap(CICapMod *capMod,CICamera *camera, pBYTE dest, int numFrames,short x, short y, short dx, short dy);    
BOOL IFCCALL CICapMod_Snap_HostBuf(CICapMod *capMod,CICamera *camera, pBYTE dest,short x, short y, short dx, short dy);    
BOOL IFCCALL CICapMod_GetGrabPhysStats(CICapMod *capMod, IFC_GRABPHYS_STATS *stats);

HTRIGOP IFCCALL CICapMod_StartTrigOps(CICapMod *capMod,CICamera *camera);
BOOL IFCCALL CICapMod_TrigRead(CICapMod *capMod,HTRIGOP trigOp,short x, short y, short dx, short dy, pBYTE dest);
BOOL IFCCALL CICapMod_WaitTrig(CICapMod *capMod,HTRIGOP trigOp,long waitTime);
BOOL IFCCALL CICapMod_TrigSnap(CICapMod *capMod,HTRIGOP trigOp,DWORD trigSource); 
BOOL IFCCALL CICapMod_StopTrigOps(CICapMod *capMod,HTRIGOP trigOp);
BOOL IFCCALL CICapMod_SetZoom(CICapMod *capMod,CICamera *camera,float xZoom, float yZoom);
void IFCCALL CICapMod_GetZoomCaps(CICapMod *capMod,CICamera *camera,LPZOOMCAP lpCaps);
void IFCCALL CICapMod_GetReadCaps(CICapMod *capMod,LPREADCAP lpCaps);
void IFCCALL CICapMod_SetReadColorRemap(CICapMod *capMod,BOOL bEnabled);
void IFCCALL CICapMod_Freeze(CICapMod *capMod,CICamera *camera);
void IFCCALL CICapMod_Snap(CICapMod *capMod,CICamera *camera);
void IFCCALL CICapMod_Grab(CICapMod *capMod,CICamera *camera);
void IFCCALL CICapMod_ReleaseCamMutex(CICapMod *capMod,CICamera *camera);
pCIFrame IFCCALL CICapMod_GetCamMutex(CICapMod *capMod,CICamera *camera);
pCICamera IFCCALL CICapMod_GetCam(CICapMod *capMod,DWORD camPortNum);
BOOL IFCCALL CICapMod_Create(CICapMod *capMod,char *modname,DWORD seqnum);
BOOL IFCCALL CICapMod_Create_FromConfig(CICapMod *capMod,DWORD seqnum, char *cfgFile);
BOOL IFCCALL CICapMod_WriteConfigFile(CICapMod *capMod,const char *szCfgFileName, IFC_CFG_CAMERA_SPECIFIER eCamFlag ); 
BOOL IFCCALL CICapMod_WriteConfigFile_CamName(CICapMod *capMod,const char *szCfgFileName, const char *szCameraName);
WORD IFCCALL CICapMod_OutportStrobeVal(CICapMod *capMod,IFC_LEVEL_TYPE val,DWORD channelNum); 
void IFCCALL CICapMod_OutportVal(CICapMod *capMod,WORD val,DWORD channelNum); 
void IFCCALL CICapMod_InportMode(CICapMod *capMod,BOOL strobed,IFC_EDGE_TYPE latchEdge,DWORD channelNum); 
WORD IFCCALL CICapMod_InportVal(CICapMod *capMod,DWORD channelNum); 
WORD IFCCALL CICapMod_InportInterruptPolarity(CICapMod *capMod, IFC_EDGE_TYPE intrEdge,DWORD channelNum); 
BOOL IFCCALL CICapMod_SeqGrab(CICapMod *capMod,DWORD frameCnt,CIFrame **frames);
//BOOL IFCCALL CICapMod_TrigSnap(CICapMod *capMod,CIFrame *frame,DWORD trigSource); 
//BOOL IFCCALL CICapMod_WaitTrig(CICapMod *capMod,CIFrame *frame,long waitTime);
BOOL IFCCALL CICapMod_SnapAsync(CICapMod *capMod,CIFrame *frame);
//BOOL IFCCALL CICapMod_SeqSnap(CICapMod *capMod,DWORD frameCnt,CIFrame **frames);
BOOL IFCCALL CICapMod_SeqSnapAsync(CICapMod *capMod,DWORD frameCnt,CIFrame **frames);
short IFCCALL CICapMod_Acqbits(CICapMod *capMod, CIFrame *frame, short mode);
BOOL IFCCALL CICapMod_WaitStartVB (CICapMod *capMod, CIFrame *frame);
BOOL IFCCALL CICapMod_WaitVertBlank (CICapMod *capMod,CIFrame *frame);
BOOL IFCCALL CICapMod_WaitNotVB (CICapMod *capMod, CIFrame *frame, BOOL vbsync);
BOOL IFCCALL CICapMod_WaitAcq(CICapMod *capMod,CIFrame *frame);
void IFCCALL CICapMod_ReadDestPitchArea (CICapMod *capMod,CICamera *cam, short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions); 
BOOL IFCCALL CICapMod_LineReverseRead (CICapMod *capMod,CICamera *cam, short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr,DWORD readOptions); 
BOOL IFCCALL CICapMod_ReadArea (CICapMod *capMod,CICamera *cam, short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx,DWORD readOptions ) ;  
float IFCCALL CICapMod_ReadPerformance(CICapMod *capMod) ;
//IFC_INTREVENT IFCCALL CICapMod_ModInterruptEvent(CICapMod *capMod,CICamera *cam,ICAP_INTR_EVENT intrEvent){return IFC_INTREVENT_INVALID;};
PIFC_CAMERA_DEF_TYPE IFCCALL CICapMod_FindCameraType(CICapMod *capMod,const char *camName);
void IFCCALL CICapMod_ProcessCameraFileList(CICapMod *capMod,const char *szListFileName);
void IFCCALL CICapMod_ProcessCameraFilesInDir(CICapMod *capMod,const pSTRING szPath, BOOL bRecurse ); 
pSTRING IFCCALL CICapMod_GetFirstCamType(CICapMod *capMod);
pSTRING IFCCALL CICapMod_GetNextCamType(CICapMod *capMod);
PIFC_CAMERA_DEF_TYPE IFCCALL CICapMod_AddCameraType(CICapMod *capMod,pSTRING strNewCamName, pSTRING strExistingCamName);
DWORD IFCCALL CICapMod_ContiguousMemAvailable(CICapMod *capMod);
BOOL IFCCALL CICapMod_EnableJitGrabMemLock(CICapMod *capMod);
DWORD IFCCALL CICapMod_SetAcqTimeout(CICapMod *capMod, DWORD dwMilliSeconds);
DWORD IFCCALL CICapMod_GetAcqTimeout(CICapMod *capMod);
MEMLOCKHDL IFCCALL CICapMod_LockMem(CICapMod *capMod, BYTE *ptr,DWORD dwSize);
void IFCCALL CICapMod_UnLockMem(CICapMod *capMod, MEMLOCKHDL memLockHandle);



pSTRING IFCCALL CModule_ModName(CModule *mod);
BOOL IFCCALL CModule_IfxGetBoardParam(CModule *mod,IFC_HW_PARAMS eParamId,DWORD *param);
DWORD IFCCALL CModule_Revision(CModule *mod);
DWORD IFCCALL CModule_GetLastError(CModule *mod);


/* CImgConn class */
void IFCCALL CImgConn_Display(CImgConn *imgConn);
BOOL IFCCALL CImgConn_Create(CImgConn *imgConn);
BOOL IFCCALL CImgConn_StartLiveImage(CImgConn *imgConn,CICamera *cam, ICAP_INTR_EVENT intrEvent , WORD InterruptScale );  
BOOL IFCCALL CImgConn_StopLiveImage(CImgConn *imgConn);
BOOL IFCCALL CImgConn_LiveImageSuspend(CImgConn *imgConn);
BOOL IFCCALL CImgConn_LiveImageResume(CImgConn *imgConn);
double IFCCALL CImgConn_GetLiveImageFPS(CImgConn *imgConn);
IFC_HDC IFCCALL CImgConn_GetOverlayDC(CImgConn *imgConn);
void IFCCALL CImgConn_ReleaseOverlayDC(CImgConn *imgConn,IFC_HDC hDC);
void IFCCALL CImgConn_EnableOverlay(CImgConn *imgConn,BOOL bEnable);
//CCallBackServer *IFCCALL CImgConn_GetImgServer(CImgConn *imgConn);
pCImgSrc IFCCALL CImgConn_GetSrc(CImgConn *imgConn);
pCImgSink IFCCALL CImgConn_GetSink(CImgConn *imgConn);
pCOverlay IFCCALL CImgConn_GetOverlay(CImgConn *imgConn);	
WORD IFCCALL CImgConn_GetOverlayWidth(CImgConn *imgConn);
WORD IFCCALL CImgConn_GetOverlayHeight(CImgConn *imgConn);
DWORD IFCCALL CImgConn_GetOverlayMaxStretch(CImgConn *imgConn);
WORD IFCCALL CImgConn_GetOverlayBitsPP(CImgConn *imgConn) ;
DWORD IFCCALL CImgConn_GetOverlayMinStretch(CImgConn *imgConn);
OVERLAY_KIND IFCCALL CImgConn_GetOverlayKind(CImgConn *imgConn) ;

/* CImgFile class */
BOOL IFCCALL CImgFile_ReadFile(CImgFile *imgFile,BYTE *dest); 
BOOL IFCCALL CImgFile_WriteFile(CImgFile *imgFile,BYTE *src, DWORD dx, DWORD dy, WORD bitsPerPixel, IFFCLASS_TYPE imgClass, IFFCOMPRESSION_TYPE imgCompress);   
BOOL IFCCALL CImgFile_ImageFileProps(CImgFile *imgFile,LPIMGFILEPROPS props); 

/* CImgSink class */

WORD IFCCALL CImgSink_GetAoiStartX(CImgSink *imgSink) ;
WORD IFCCALL CImgSink_GetAoiStartY(CImgSink *imgSink) ;
WORD IFCCALL CImgSink_GetWidth(CImgSink *imgSink) ;
WORD IFCCALL CImgSink_GetHeight(CImgSink *imgSink) ;
WORD IFCCALL CImgSink_GetLinePitch(CImgSink *imgSink) ;
void IFCCALL CImgSink_SetAoiPos(CImgSink *imgSink,const WORD wxAoiStart, const WORD wyAoiStart);
void IFCCALL CImgSink_GetAoiPos(CImgSink *imgSink,WORD *pwxAoiStart, WORD *pwyAoiStart)  ;
//void IFCCALL CImgSink_GetAoiPos(CImgSink *imgSink,RECT *pRect)  ;
IFC_HWND IFCCALL CImgSink_GetSinkWindow(CImgSink *imgSink);
void IFCCALL CImgSink_GetZoom(CImgSink *imgSink,double *ZoomX, double *ZoomY) ;
void IFCCALL CImgSink_SetZoom(CImgSink *imgSink,double ZoomX, double ZoomY);
double IFCCALL CImgSink_GetZoomX(CImgSink *imgSink) ;
double IFCCALL CImgSink_GetZoomY(CImgSink *imgSink) ;
BOOL IFCCALL CImgSink_ResizeWindow(CImgSink *imgSink);
BOOL IFCCALL CImgSink_Create(CImgSink *imgSink);
pCImgSink IFCCALL CImgSink_MakeCopy(CImgSink *imgSink);
pBYTE  IFCCALL CImgSink_GetBufferAddr(CImgSink *imgSink) ;
WORD IFCCALL CImgSink_GetBitsPP(CImgSink *imgSink) ;
DWORD IFCCALL CImgSink_GetMinStretch(CImgSink *imgSink);
DWORD IFCCALL CImgSink_GetMaxStretch(CImgSink *imgSink);
BOOL IFCCALL CImgSink_SetDestColorKey(CImgSink *imgSink,DWORD dwNewColorKey);
BOOL IFCCALL CImgSink_SetRemapColor(CImgSink *imgSink,int iFirstIndex, int iLastIndex, COLORREF RemapColor);
DWORD IFCCALL CImgSink_GetDestColorKey(CImgSink *imgSink);
DWORD IFCCALL CImgSink_GetColorKeyRep(CImgSink *imgSink,COLORREF color) ;
SINK_KIND IFCCALL CImgSink_GetKind(CImgSink *imgSink)  ;

/* CImgSrc class */

BOOL IFCCALL CImgSrc_Create(CImgSrc *imgSrc);
WORD IFCCALL CImgSrc_FrameWidth(CImgSrc *imgSrc)  ;
WORD IFCCALL CImgSrc_FrameHeight(CImgSrc *imgSrc)  ;
void IFCCALL CImgSrc_SetAoiPos(CImgSrc *imgSrc,const WORD wxAoiStart, const WORD wyAoiStart);
void IFCCALL CImgSrc_GetAoiPos(CImgSrc *imgSrc,WORD *pwxAoiStart, WORD *pwyAoiStart)  ;
WORD IFCCALL CImgSrc_GetAoiStartX(CImgSrc *imgSrc)  ;
WORD IFCCALL CImgSrc_GetAoiStartY(CImgSrc *imgSrc)  ;
WORD IFCCALL CImgSrc_GetWidth(CImgSrc *imgSrc) ;
WORD IFCCALL CImgSrc_GetHeight(CImgSrc *imgSrc) ;
WORD IFCCALL CImgSrc_GetLinePitch (CImgSrc *imgSrc) ;
WORD IFCCALL CImgSrc_GetBitsPP(CImgSrc *imgSrc) ;
IFC_COLOR IFCCALL CImgSrc_GetColor(CImgSrc *imgSrc) ;
SRC_KIND IFCCALL CImgSrc_GetKind(CImgSrc *imgSrc) ;
pCICamera IFCCALL CImgSrc_GetCamera(CImgSrc *imgSrc) ;
pBYTE IFCCALL CImgSrc_GetBufferAddr(CImgSrc *imgSrc) ;
void IFCCALL CImgSrc_SetBufferAddr(CImgSrc *imgSrc,BYTE *pBuffer);
DWORD IFCCALL CImgSrc_SetOptions(pCImgSrc imgSrc, DWORD dwOptions);


/* CInterrupt class */

BOOL IFCCALL CInterrupt_Connected(CInterrupt *intr);
//pSTRING IFCCALL CInterrupt_MakeIntrSemaName(CInterrupt *intr,pCModule mod,IFC_INTREVENT intrEvent,char *semaName);
BOOL IFCCALL CInterrupt_Clear(CInterrupt *intr);
BOOL IFCCALL CInterrupt_Wait(CInterrupt *intr,DWORD dwMilliseconds);
IFC_INTR_WAIT_TYPE IFCCALL CInterrupt_WaitIntrOrEventSet(CInterrupt *intr,DWORD dwMilliseconds, OS_event_t event1, OS_event_t event2, OS_event_t event3);   
void IFCCALL CInterrupt_Rearm(CInterrupt *intr);
HANDLE IFCCALL CInterrupt_EventHandle(CInterrupt *intr);
void IFCCALL IFC_IfxDeleteCInterrupt(pCInterrupt intr);


/* COverlay class */

BOOL IFCCALL COverlay_Create(COverlay *overlay);
IFC_HDC IFCCALL COverlay_GetOverlayDC(COverlay *overlay);
void IFCCALL COverlay_ReleaseOverlayDC(COverlay *overlay,IFC_HDC hDC);
WORD IFCCALL COverlay_GetBitsPP(COverlay *overlay) ;
WORD IFCCALL COverlay_GetWidth(COverlay *overlay);
WORD IFCCALL COverlay_GetHeight(COverlay *overlay);
DWORD IFCCALL COverlay_GetMinStretch(COverlay *overlay);
DWORD IFCCALL COverlay_GetMaxStretch(COverlay *overlay);
BOOL IFCCALL COverlay_LockOverlay(COverlay *overlay);
BOOL IFCCALL COverlay_UnlockOverlay(COverlay *overlay);
OVERLAY_KIND IFCCALL COverlay_GetKind(COverlay *overlay);
void IFCCALL COverlay_Enable(COverlay *overlay,BOOL bEnable); 
BOOL IFCCALL COverlay_IsEnabled(COverlay *overlay)  ;

/* CPCDig Class */
BOOL IFCCALL CPCDig_SetAcqTriggerEvents(CICapMod *capMod,PCD_TRIG_MODE_TYPE startEvent , PCD_TRIG_MODE_TYPE stopEvent,DWORD numFramesPerTrig);

/* CPCLink Class */
BOOL IFCCALL CPCLink_SetAcqTriggerEvents(CICapMod *capMod,LNK_TRIG_MODE_TYPE startEvent , LNK_TRIG_MODE_TYPE stopEvent, DWORD numFramesPerTrig);

/* Global Functions */
/* Create CapMod */
pCICapMod IFCCALL IFC_IfxCreateCaptureModule(char *modName,DWORD seqnum, char *cfgFile);
pCICapMod IFCCALL IFC_IfxCreateParentModule(char *modName, DWORD seqnum, char *cfgFile, BOOL inspectOnly);

/* Create CImgConn */
pCImgConn IFCCALL IFC_IfxCreateImgConn_Cam(	
				CICamera *pCamera, 
				IFC_HWND hWnd, 
				DWORD Flags , 
				ICAP_INTR_EVENT intrEvent , 
				int iScale ); 

pCImgConn IFCCALL IFC_IfxCreateImgConn_HostBuf(
				BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP, 
				IFC_HWND hwnd, 
				IFC_COLOR eColor , 
				DWORD Flags , 
				CICamera *cam, ICAP_INTR_EVENT intrEvent ,  
				int iScale , 
				pBoolFunc pFunc , void *pArg);  

pCImgConn IFCCALL IFC_IfxCreateImgConn(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink,		
				DWORD Flags , 
				CICamera *cam , ICAP_INTR_EVENT intrEvent ,  
				int iScale ); 

pCImgConn IFCCALL IFC_IfxCreateImgConn_WithOverlay(
				CImgSrc *pImgSrc, 
				CImgSink *pImgSink, 
				COverlay *pOverlay, 
				DWORD Flags , 
				CICamera *cam, ICAP_INTR_EVENT intrEvent ,  
				int iScale ); 
/* Create CImgSrc */

pCImgSrc IFCCALL IFC_IfxCreateImgSrc_HostBuf(BYTE *pImgBuffer, CAM_ATTR * pCamAttr);
pCImgSrc IFCCALL IFC_IfxCreateImgSrc_Area(BYTE *pImgBuffer, WORD wWidth, WORD wHeight, WORD wImgBitsPP ,IFC_COLOR eColor,  
			  WORD wxAoiStart, WORD wyAoiStart, WORD wAoiWidth, WORD wAoiHeight);    
pCImgSrc IFCCALL IFC_IfxCreateImgSrc_Cam(CICamera *pCamera, WORD wxAoiStart, WORD wyAoiStart, WORD wAoiWidth, WORD wAoiHeight);    


/* Create CImgSink */
pCImgSink IFCCALL IFC_IfxCreateImgSink(IFC_HWND hWnd, SINK_KIND Kind, WORD wSinkStartX, WORD wSinkStartY,	WORD width, WORD height);

/* Creat COverlay */
pCOverlay IFCCALL IFC_IfxCreateOverlay(OVERLAY_KIND Kind,WORD wWidth, WORD wHeight);

/* Create CImgFile */
pCImgFile IFCCALL IFC_IfxCreateImgFile(pSTRING fileName);

void IFCCALL IFC_IfxDeleteImgSrc( pCImgSrc pImgSrc );
void IFCCALL IFC_IfxDeleteImgSink( pCImgSink pImgSink );
void IFCCALL IFC_IfxDeleteImgConn( pCImgConn pImgConn );
void IFCCALL IFC_IfxDeleteOverlay( pCOverlay pOverlay );
void IFCCALL IFC_IfxDeleteImgFile( pCImgFile pImgFile );
void IFCCALL IFC_IfxDeleteCaptureModule( pCICapMod pCapMod );

void IFCCALL IFC_IfxSetConsoleHandler(pfCONSOLEHDLR handler);
DWORD IFC_EXT_API IFC_IfxGetLastError(void);


pSTRING IFCCALL IFC_strcpy(pSTRING dst, pSTRING src);

PCIntrCallback IFCCALL IFC_IfxCreateIntrCallback(pCModule pMod, IFC_INTREVENT iEvent, pIntrCallBackFunc func, LPVOID pParam);
void IFCCALL IFC_IfxDeleteIntrCallback(PCIntrCallback hCallback);

pCInterrupt IFCCALL IFC_IfxCreateInterrupt(pCModule mod,IFC_INTREVENT intrEvent);
PCParentMod IFCCALL IFC_IfxCreateVirtualParentModule(char *modName, DWORD seqnum, char *cfgFile, char *DaughterModNames);
BOOL IFCCALL IFC_IfxWriteImgFile(pSTRING fileName,BYTE *src, DWORD dx, DWORD dy, WORD bitsPerPixel, IFFCLASS_TYPE imgClass, IFFCOMPRESSION_TYPE imgCompress);
BOOL IFCCALL IFC_IfxReadImgFile(pSTRING fileName,BYTE *dest,LPIMGFILEPROPS props);

pCITIMods IFCCALL IFC_IfxCreateITIMods(void);
void IFCCALL IFC_IfxDeleteITIMods(pCITIMods itiMods);
BOOL IFCCALL CITIMods_GetFirst(CITIMods *itiMods, LPITI_PARENT_MOD mod);
BOOL IFCCALL CITIMods_GetNext(CITIMods *itiMods, LPITI_PARENT_MOD mod);


/* CIFCOS class */
double IFCCALL CIFCOS_GetSystimeMicrosecs(void);
DWORD IFCCALL CIFCOS_GetSystimeMillisecs(void);

/* CPCVision2 class */
BOOL IFCCALL CPCVision2_SwitchCameraDefineStart(CICapMod *capMod);
BOOL IFCCALL CPCVision2_SwitchCameraDefineEnd(CICapMod *capMod);
BOOL IFCCALL CPCVision2_SwitchCameraGrab(CICapMod *capMod);
BOOL IFCCALL CPCVision2_SwitchCameraSnap(CICapMod *capMod, DWORD numFrames);
BOOL IFCCALL CPCVision2_SwitchCameraFreeze(CICapMod *capMod);
BOOL IFCCALL CPCVision2_SetFrameDelaySequence(CICapMod *capMod, DWORD *camPortSeq, DWORD numCameras, IFC_TRIG_SRC_TYPE trigSrc);
BOOL IFCCALL CPCVision2_FrameDelaySnap(CICapMod *capMod, IFC_TRIG_SRC_TYPE trigSrc, pBYTE dest, short x, short y, short dx, short dy, DWORD dwMilliseconds);
BOOL IFCCALL CPCVision2_FrameDelayWait(CICapMod *capMod, DWORD dwMilliseconds);

/* CPCVision class */
void IFCCALL CPCVision_SetYCRCBacqMode(CICapMod *capMod, BOOL bMode);
BOOL IFCCALL CPCVision_GetYCRCBacqMode(CICapMod *capMod);

BOOL IFCCALL CNetSightII_AdvancedIOEnqueueDecision(CICapMod *capMod, NSP_REJECTOR_ID_TYPE rejectorID, DWORD objectIndex, NSP_AIO_DECISION_TYPE decision);


BOOL IFCCALL IFC_IfxBayerFilterConvert(DWORD options,IFC_BAYER_FILTER_TYPE filterType, pBYTE dest, pBYTE src, DWORD width, DWORD height, IFC_COLOR targetColor, PIFC_BAYER_EXT_ATTR extAttr);

#ifdef __cplusplus
}
#endif
