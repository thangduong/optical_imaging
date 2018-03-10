/******************************************************************************
 *
 * MODULE   
 *		Camera.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/VnDriver.h $
 *		$Revision: 1.1 $
 *		$Modtime: 6/18/01 3:28p $
 *
 * ABSTRACT  
 *		IFC interface of the CVideoSrc class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c)1998-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_VnDriver_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)
#define AFX_VnDriver_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000





#if 0

#define DECL_VS_FUNCV(rt,fname,plist) lfx \
rt CIfcVsDrv::fname plist lfx\
{ lfx\
	if (!m_cam)	{ lfx\
		VsConsole( #fname ": VidSrc not connected"); lfx\
		return; lfx\
	} lfx\
	m_cam->fname plist; lfx\
	return;lfx\
}


#define DECL_VS_FUNC(rt,fname,plist) lfx \
rt CIfcVsDrv::fname plist lfx\
{ lfx\
	if (!m_cam)	{ lfx\
		VsConsole( #fname ": VidSrc not connected"); lfx\
		return (rt)0; lfx\
	} lfx\
	return m_cam->fname plist; lfx\
}

#endif



#include <VidSrcT.h>
#include <VnBase.h>

#define DECL_VS_FUNC(rt,fname,plist) virtual rt fname plist {\
	VsConsole("Function " #fname " not supported");\
	return (rt)0;\
	}

#define DECL_VS_FUNCV(rt,fname,plist) virtual rt fname plist {\
	VsConsole("Function " #fname " not supported");\
	}



#ifdef __cplusplus

class IVS_EXT_API CVideoSrcDriver 
{
public:

	virtual ~CVideoSrcDriver();

	DECL_VS_FUNC( HVSINTERRUPT, CreateInterruptObject,(VS_ICAP_INTR_EVENT intrEvent,BOOL eventSetting=TRUE));

	DECL_VS_FUNC(  BOOL ,Connect,(LPSTR videoSrcName,LPVSPROPS vidSrcProps, DWORD numParams, VSPARAM params[]));

	DECL_VS_FUNC(  BOOL ,AcqParamSupported,(VS_ACQ_PARAMS_TYPE paramID));
	DECL_VS_FUNC(  double ,GetAcqParam,(VS_ACQ_PARAMS_TYPE paramID,DWORD index=0));
	DECL_VS_FUNCV( void ,SetAcqParam,(VS_ACQ_PARAMS_TYPE paramID, double value,DWORD index=0));
	DECL_VS_FUNCV( void ,GetParamCaps,(VS_ACQ_PARAMS_TYPE paramID,PVS_PARAM_CAPS lpParamCaps));
	DECL_VS_FUNC(  VS_ACQ_PARAMS_TYPE ,GetFirstParam,(DWORD paramGroupMask=VS_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE));
	DECL_VS_FUNC(  VS_ACQ_PARAMS_TYPE ,GetNextParam,(VS_ACQ_PARAMS_TYPE paramID,DWORD paramGroupMask=VS_ALL_PARAM_GROUPS,BOOL includeChildGroups=TRUE));

	DECL_VS_FUNC(  VS_PARAM_GROUP_TYPE ,GetFirstParamGroup,(VS_PARAM_GROUP_TYPE parentGroupID=VS_PGRP_TOP_LEVEL));
	DECL_VS_FUNC(  VS_PARAM_GROUP_TYPE ,GetNextParamGroup,(VS_PARAM_GROUP_TYPE groupID));
	DECL_VS_FUNCV( void ,GetGroupProperties,(VS_PARAM_GROUP_TYPE groupID,PVS_PARAM_GROUP_PROPS lpGroupProps));
	DECL_VS_FUNC(  VS_PARAM_GROUP_TYPE ,GetParentGroup,(VS_PARAM_GROUP_TYPE childGroupID));


	DECL_VS_FUNC(  BOOL ,GetFirstEnumArg,(VS_ACQ_PARAMS_TYPE paramID, VS_ENUM_ARG *arg));
	DECL_VS_FUNC(  BOOL ,GetNextEnumArg,(VS_ACQ_PARAMS_TYPE paramID, VS_ENUM_ARG *arg));
	DECL_VS_FUNC(  BOOL ,IsArgSupported,(VS_ACQ_PARAMS_TYPE paramID, double arg));
	DECL_VS_FUNC(  double ,ClosestArgSupported,(VS_ACQ_PARAMS_TYPE paramID, double arg));
	DECL_VS_FUNC(  char *,GetArgName,(VS_ACQ_PARAMS_TYPE paramID, double dArg));
	DECL_VS_FUNC(  double ,GetArgValue,(VS_ACQ_PARAMS_TYPE paramID, const char *szArgName));

	DECL_VS_FUNC(  BOOL ,SetLutFunction,(VS_LUTID_TYPE lutID,VSLUTFUNC func,DWORD *constants,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_INTELLI_WIDTH));
	DECL_VS_FUNCV( void ,ReadLutBuf,(VS_LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, pVOID buf,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_FULL_WORD));
	DECL_VS_FUNCV( void ,WriteLutBuf,(VS_LUTID_TYPE lutID, DWORD lutAdr,DWORD numEntries,pVOID buf,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_FULL_WORD));

	DECL_VS_FUNC(  BOOL ,WriteLutToFile,(VS_LUTID_TYPE lutID, DWORD lutAdr, DWORD numEntries, LPSTR szFileName, VS_LUT_PORTION_TYPE lutPortion=VS_LUT_FULL_WORD));
	DECL_VS_FUNC(  BOOL ,LoadLutFromFile,(VS_LUTID_TYPE lutID, LPSTR szFileName));

	DECL_VS_FUNC(  DWORD ,ReadLutLoc,(VS_LUTID_TYPE lutID, DWORD lutAdr,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_FULL_WORD));
	DECL_VS_FUNCV( void ,WriteLutLoc,(VS_LUTID_TYPE lutID,DWORD lutAdr,DWORD val,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_FULL_WORD));
	DECL_VS_FUNCV( void ,LinearizeLut,(VS_LUTID_TYPE lutID,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_INTELLI_WIDTH));
	DECL_VS_FUNCV( void ,FloodLUT,(VS_LUTID_TYPE lutID,DWORD val,VS_LUT_PORTION_TYPE lutPortion=VS_LUT_INTELLI_WIDTH));
	DECL_VS_FUNCV( void ,InvertLut,(VS_LUTID_TYPE lutID, VS_LUT_PORTION_TYPE lutPortion));
	DECL_VS_FUNCV( void ,ThresholdLut,(VS_LUTID_TYPE lutID, const DWORD dwThreshold, VS_LUT_PORTION_TYPE lutPortion));
	DECL_VS_FUNCV( void ,OffsetLut,(VS_LUTID_TYPE lutID, const long lOffset, VS_LUT_PORTION_TYPE lutPortion));
	DECL_VS_FUNCV( void ,BitReverseLinearLut,(VS_LUTID_TYPE lutID, VS_LUT_PORTION_TYPE lutPortion));

	DECL_VS_FUNCV( void ,RgbToHsiLUT,(VS_LUTID_TYPE lutID, VS_LUT_PORTION_TYPE lutPortion));
	DECL_VS_FUNCV( void ,GetLUTCaps,(LPVS_LUTCAP caps));
	DECL_VS_FUNCV( void ,SetLutPathPage,(VS_LUTID_TYPE lutID,VS_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum));

	DECL_VS_FUNCV( void ,SetLutHostPage,(VS_LUTID_TYPE lutID,VS_LUT_PIX_SIZE_TYPE pxSize,DWORD pageNum,BOOL leftJustify));
		// leftJustify -- Shift LUT entries to the left so that the pixel bits are the most siginificant of 16

	DECL_VS_FUNCV( void ,SetWindowGen,(short x, short y, short dx, short dy));
	DECL_VS_FUNC(  BOOL ,SetCameraType,(LPCSTR camName,BOOL updateHW=TRUE));
	DECL_VS_FUNC(  LPCSTR ,GetNextCamType,(void));
	DECL_VS_FUNC(  LPCSTR ,GetFirstCamType,(void));
	DECL_VS_FUNCV( void ,Snap,(void));
	DECL_VS_FUNCV( void ,Grab,(void));


	DECL_VS_FUNC(  HVSGRAB ,Grab,(DWORD dwOptions,pBYTE dest, int ringNumFrames,int totalNumFrames=VS_INFINITE_FRAMES, int x=0, int y=0, int dx=0, int dy=0));
	DECL_VS_FUNC(  HVSGRAB ,Grab,(DWORD dwOptions,pBYTE dests[], int ringNumFrames,int totalNumFrames=VS_INFINITE_FRAMES, int x=0, int y=0, int dx=0, int dy=0));
	DECL_VS_FUNC(  HVSGRAB ,Grab,(DWORD dwOptions,pBYTE dest, int ringNumFrames, LPVS_AOI_DESC aoiDesc,int totalNumFrames=VS_INFINITE_FRAMES));

	DECL_VS_FUNCV( void ,GrabLock,(HVSGRAB grabID, int seqNum));
	DECL_VS_FUNCV( void ,GrabRelease,(HVSGRAB grabID, int seqNum));
	DECL_VS_FUNC(  int ,GrabWaitFrame,(HVSGRAB grabID, BYTE **frameAddr=NULL, int FrameSeqNum=VS_WAIT_NEWER_FRAME, DWORD milliseconds=VS_WAIT_FOREVER, BOOL lock=TRUE, VS_GRAB_EXT_ATTR *ExtendedAttr=NULL));
	DECL_VS_FUNC(  int ,GrabWaitFrameRead,(HVSGRAB grabID,VS_FRAME_ENCODE encode,BYTE *dest, DWORD *bytesAvailable,int FrameSeqNum=VS_WAIT_NEWER_FRAME, DWORD milliseconds=VS_WAIT_FOREVER,  VS_GRAB_EXT_ATTR *ExtendedAttr=NULL));
	DECL_VS_FUNC(  int ,DecodeFrame,(BYTE *src,DWORD numSrcBytes,VS_FRAME_ENCODE encode, DWORD &dx, DWORD &dy,VS_COLOR color, DWORD bitsPerPixel, BYTE *dest));

	DECL_VS_FUNC(  int ,Freeze,(HVSGRAB grabID=NULL));
	DECL_VS_FUNC(  BOOL ,GrabGetExtAttr,(HVSGRAB grabID, int ringSeqNum, VS_GRAB_EXT_ATTR *ExtendedAttr));


	DECL_VS_FUNC(  BOOL ,Snap,( pBYTE dest,short x=0, short y=0, short dx=0, short dy=0));
	DECL_VS_FUNC(  BOOL ,SeqSnap,(pBYTE dest, int numFrames,short x=0, short y=0, short dx=0, short dy=0,DWORD dwMilliseconds=VS_WAIT_FOREVER));
	DECL_VS_FUNC(  pBYTE ,SeqSnapPhys,(DWORD numFrames, DWORD destOffset=0, short x=0, short y=0, short dx=0, short dy=0, DWORD dwMilliseconds=VS_WAIT_FOREVER,DWORD *acquiredDys=NULL));
	DECL_VS_FUNC(  int ,WaitPhysFrame,(BYTE **frameAddr=NULL, int FrameSeqNum=VS_WAIT_NEWER_FRAME, DWORD dwMilliseconds=VS_WAIT_FOREVER,DWORD *acquiredDy=NULL));

	DECL_VS_FUNC(  BOOL ,SetZoom,(float xZoom, float yZoom));
	DECL_VS_FUNCV( void ,GetZoomCaps,(LPVS_ZOOMCAP lpCaps));
	DECL_VS_FUNC(  BOOL ,ReadArea, (short x,short y,short dx,short dy,BYTE *destadr,DWORD dest_dx=0,DWORD readOptions = 0));
	DECL_VS_FUNCV( void ,LineReverseRead ,(short x,short y,short dx,short dy,short destlinebytes, BYTE *destadr, DWORD readOptions=0));
	DECL_VS_FUNCV( void ,ReadDestPitchArea ,(short x,short y,short dx,short dy, short destlinebytes, DWORD physdest, DWORD readOptions=0));
	DECL_VS_FUNCV( void ,GetAttr,(LPVS_CAM_ATTR lpAttr, BOOL zoomCorrected=TRUE));
	DECL_VS_FUNCV( void ,SetReadColorRemap,(BOOL bEnabled));

	DECL_VS_FUNC(  DWORD ,ReadReg,(REGID reg));
	DECL_VS_FUNCV( void ,WriteReg,(REGID reg, DWORD val));


	DECL_VS_FUNC(  char *,ParamValToString,(VS_ACQ_PARAMS_TYPE paramID, double dVal, char *szResult));
	DECL_VS_FUNC(  double, ParamStringToVal,(VS_ACQ_PARAMS_TYPE paramID, const char *szVal));

	DECL_VS_FUNC(  BOOL, QueryUIParamUpdate,(double &dVal,VS_ACQ_PARAMS_TYPE paramID,DWORD index=0,void *pParentCWnd=NULL));

	DECL_VS_FUNC(  BOOL, ParamGroupEditDlgExist,(VS_PARAM_GROUP_TYPE GroupID));
	DECL_VS_FUNC(  BOOL, DoParamGroupEditDialog,(VS_PARAM_GROUP_TYPE GroupID, void *pParentCWnd,VS_ACQ_PARAMS_TYPE focalParam=VSP_ALL_CAM_PARAMS_ID));

	DECL_VS_FUNC(  BOOL, ParamIsApplicable,(VS_ACQ_PARAMS_TYPE paramID, DWORD index=0, char *ReasonNotApplicable=NULL));
	DECL_VS_FUNC(  BOOL, GroupIsApplicable,(VS_PARAM_GROUP_TYPE groupID, char *ReasonNotApplicable=NULL));

	DECL_VS_FUNCV( void, PrintParamAttributes,(VS_ACQ_PARAMS_TYPE paramID=VSP_ALL_CAM_PARAMS_ID,VS_PARAM_GROUP_TYPE parentGroupID=VS_PGRP_TOP_LEVEL,HANDLE file=NULL));

	DECL_VS_FUNC(  BOOL, CameraIsReserved,(LPCSTR camName=NULL));

	DECL_VS_FUNC(  BOOL, TransformSupported,(VS_TRANSFORM_TYPE eTransform));
	DECL_VS_FUNC(  BOOL ,SetTransform,(VS_TRANSFORM_TYPE eTransform));
	DECL_VS_FUNC(  VS_TRANSFORM_TYPE, GetCurrentTransform,(void));
	DECL_VS_FUNC(  BOOL, QueryUICameraType,(void));

	DECL_VS_FUNC(  DWORD, GetPortNum,(void));
	DECL_VS_FUNC(  BOOL, SetPortNum,(DWORD portNum));
	DECL_VS_FUNC(  DWORD, GetNumPorts,(void));
	DECL_VS_FUNC(  DWORD, AddCameraType,(LPSTR strNewCamName, LPSTR strExistCamName));

	DECL_VS_FUNC(  BOOL, WriteCameraFile,(const char *szCamFileName, const char *szCameraName));
	DECL_VS_FUNC(  BOOL, ProcessCamerasInConfigFile,(const char *szCfgFileName ));

	DECL_VS_FUNC(  BOOL, ReadUserConfigFile,(const char *szCfgFileName));
	DECL_VS_FUNC(  BOOL, WriteUserConfigFile,(const char *szCfgFileName));


	DECL_VS_FUNC(BOOL,GetReadCaps,(VS_READCAP *lpCaps));
	DECL_VS_FUNC(BOOL,ClearInterrupt,(HVSINTERRUPT hIntrObj));
	DECL_VS_FUNC(BOOL,DeleteInterruptObject,(HVSINTERRUPT hIntrObj));
	DECL_VS_FUNC(BOOL,WaitInterrupt,(HVSINTERRUPT hIntrObj, DWORD milliSeconds));

	DECL_VS_FUNCV( void, InportInterruptPolarity,( VS_EDGE_TYPE intrEdge,DWORD channelNum));
	DECL_VS_FUNC( DWORD, InportVal,(DWORD channelNum));
	DECL_VS_FUNCV( void, InportMode,(BOOL strobed,VS_EDGE_TYPE latchEdge,DWORD channelNum));
	DECL_VS_FUNCV( void, OutportVal,(DWORD val,DWORD channelNum));
	DECL_VS_FUNCV( void, OutportStrobeVal,(VS_LEVEL_TYPE val,DWORD channelNum));

	void* IVSAPI operator new(size_t nSize);
	void* IVSAPI operator new(size_t nSize,void* p);
	void  IVSAPI operator delete(void* p);
#if _MSC_VER >= 1200
	void IVSAPI operator delete(void* p, void* pPlace);
#endif

	// for file name/line number tracking using DEBUG_NEW
	void* IVSAPI operator new(size_t nSize, LPCSTR lpszFileName, int nLine);

#if _MSC_VER >= 1200
	void IVSAPI operator delete(void* p, LPCSTR lpszFileName, int nLine);
#endif

protected:

};


typedef CVideoSrcDriver *PCVideoSrcDriver;

#endif




// Driver must export IVS_CREATE_VIDEO_SRC_FUNC_NAME function with the following prototype
typedef PCVideoSrcDriver (IVSAPI *PIVS_CREATE_VIDEO_SOURCE) (LPSTR videoSrcName,LPVSPROPS vidSrcProps, DWORD numParams, VSPARAM params[]);

#define IVS_CREATE_VIDEO_SRC_FUNC_NAME "IvsCreateVideoSource"


typedef int (IVSAPI *PIVS_DETECT_REG_VID_SRCS)(DWORD options);
#define IVS_DETECT_VIDEO_SRC_FUNC_NAME "IvsDetectAndRegVideoSources"

// Driver implementation must include a line to implement the create functions, example:
//
// IMPL_CREATE_VID_SRC(CIfcVsDrv)
// Where CIfcVsDrv is derived from CVideoSrcDriver 

#ifdef __cplusplus
extern "C" {
#endif


PCVideoSrcDriver __declspec(dllexport) IVSAPI IvsCreateVideoSource(LPSTR videoSrcName, LPVSPROPS vidSrcProps, DWORD numParams, VSPARAM params[]);
int __declspec(dllexport) IVSAPI IvsDetectAndRegVideoSources(DWORD options);


#ifdef __cplusplus
}
#endif


#define IMPL_CREATE_VID_SRC(drvClass) \
PCVideoSrcDriver __declspec(dllexport) IVSAPI IvsCreateVideoSource(LPSTR videoSrcName, LPVSPROPS vidSrcProps, DWORD numParams, VSPARAM params[])\
{\
	PCVideoSrcDriver drv;\
	drv =  new drvClass();\
	if (!drv->Connect(videoSrcName,vidSrcProps,numParams,params)) {\
		delete drv;\
		drv = NULL;\
	}\
	return drv;\
}


#endif // !defined(AFX_CAMERA_H__962D5A85_7C6C_11D1_AE6B_00A0C959E757__INCLUDED_)


