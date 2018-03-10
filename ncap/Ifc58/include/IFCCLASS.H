/******************************************************************************
 *
 * MODULE   
 *		ifcclass.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IFCCLASS.H $
 *		$Revision: 1.1 $
 *		$Modtime: 11/01/04 10:44a $
 *
 * ABSTRACT  
 *		IFC Standard Data Types
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2004 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/


#ifndef _IFC_IFCCLASS_DEF
#define _IFC_IFCCLASS_DEF


#include <iobject.h>

#ifdef __cplusplus
class IFC_EXT_API CICapMod;
class IFC_EXT_API CICamera;
class IFC_EXT_API CImgSrc;
class IFC_EXT_API CImgSink;
class IFC_EXT_API COverlay;
class IFC_EXT_API CCallBackServer;
class IFC_EXT_API CImgConn;
class IFC_EXT_API CRegister;
class IFC_EXT_API CModFactory;
class IFC_EXT_API CModule;
class IFC_EXT_API CIFCError;
class IFC_EXT_API CChildMod;
class IFC_EXT_API CIFrame;
class IFC_EXT_API CImgFile;
class IFC_EXT_API CInterrupt;
class IFC_EXT_API CConfig;
class IFC_EXT_API CCfgFile;
class IFC_EXT_API CIobject;
class IFC_EXT_API CPCDFrame;
class IFC_EXT_API CPCDCam;
class IFC_EXT_API CPCLFrame;
class IFC_EXT_API CPCLCam;
class IFC_EXT_API CPCLine;
class IFC_EXT_API CPCRFrame;
class IFC_EXT_API CPCRCam;
class IFC_EXT_API CPcRgb;
class IFC_EXT_API CPCPFrame;
class IFC_EXT_API CPCPCam;
class IFC_EXT_API CPCVisionPlus;
class IFC_EXT_API CRebelDigFrame;
class IFC_EXT_API CRebelDigCam;
class IFC_EXT_API CRebelDig;
class IFC_EXT_API CPCDig;
class IFC_EXT_API CPCTstDig;
class IFC_EXT_API CPCVFrame;
class IFC_EXT_API CPCVCam;
class IFC_EXT_API CPCVision;
class IFC_EXT_API CParentMod;
class IFC_EXT_API CIFCBus;
class IFC_EXT_API CAcqMod;
class IFC_EXT_API CIFCOS;
class IFC_EXT_API CAmVCam;
class IFC_EXT_API CITIMods;

#else

typedef void CICapMod;
typedef void CICamera;
typedef void CImgSrc;
typedef void CImgSink;
typedef void COverlay;
typedef void CCallBackServer;
typedef void CImgConn;
typedef void CRegister;
typedef void CModFactory;
typedef void CModule;
typedef void CIFCError;
typedef void CChildMod;
typedef void CIFrame;
typedef void CImgFile;
typedef void CInterrupt;
typedef void CConfig;
typedef void CCfgFile;
typedef void CIobject;
typedef void CPCDFrame;
typedef void CPCDCam;
typedef void CPCRFrame;
typedef void CPCRCam;
typedef void CPcRgb;
typedef void CPCLFrame;
typedef void CPCLCam;
typedef void CPCLine;
typedef void CPCPFrame;
typedef void CPCPCam;
typedef void CPCVisionPlus;
typedef void CRebelDigFrame;
typedef void CRebelDigCam;
typedef void CRebelDig;
typedef void CPCDig;
typedef void CPCTstDig;
typedef void CPCVFrame;
typedef void CPCVCam;
typedef void CAmVCam;
typedef void CPCVision;
typedef void CParentMod;
typedef void CIFCBus;
typedef void CAcqMod;
typedef void CIFCOS;
typedef void CITIMods;


#endif

typedef CIFrame * pCIFrame;
typedef CICamera * pCICamera;
typedef CICapMod * pCICapMod;
typedef CImgSrc * pCImgSrc;
typedef CImgSink * pCImgSink;
typedef CImgConn * pCImgConn;
typedef CInterrupt * pCInterrupt;
typedef CConfig * pCConfig;
typedef CCfgFile * pCCfgFile;
typedef COverlay * pCOverlay;
typedef CImgFile * pCImgFile;
typedef CITIMods * pCITIMods;


#endif
