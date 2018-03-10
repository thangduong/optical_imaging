/******************************************************************************
 *
 * MODULE   
 *		dsptype.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/disptype.h $
 *		$Revision: 1.1 $
 *		$Modtime: 2/20/04 9:15a $
 *
 * ABSTRACT 
 *	Standard definitions for the IFCDSP.DLL
 *
 * TECHNICAL NOTES 
 *
 * 
 * Copyright (c) 1998-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _DISPTYPE_H_
#define _DISPTYPE_H_

#ifdef __midl 

typedef long VS_HWND;
typedef long VS_HDC;

#else

#ifdef WIN32
#include <windows.h>

 #ifndef STRICT
  #define DEFINE_VS_HWND struct HWND##__ { int unused; }; typedef struct HWND##__ *VS_HWND
  #define DEFINE_VS_HDC  struct HDC##__ { int unused; }; typedef struct HDC##__ *VS_HDC
  DEFINE_VS_HWND;
  DEFINE_VS_HDC;
 #else
  #define VS_HWND HWND
  #define VS_HDC HDC
 #endif

#else//#ifdef WIN32

 #define VS_HWND void *
 #define VS_HDC void *

#endif //#ifdef WIN32

#endif //#ifdef __midl

// source kinds
typedef enum VS_SRC_KIND {	
	VS_NONE_SRC,
	VS_VIDEO_SRC, 
	VS_HOST_BUFFER_SRC, 
	VS_IMAGE_SRC,
	VS_LAST_SRC	//always last
} VS_SRC_KIND;

// sink kinds
typedef enum VS_SINK_KIND {	
	VS_NONE_SINK,
	VS_DIB_SINK, 
	VS_DDRAW_SINK, 
	VS_YCRCB_SINK, 
	VS_LAST_SINK	//keep this always last
} VS_SINK_KIND;

//overlay kinds
typedef enum VS_OVERLAY_KIND {	
	VS_NONE_OVERLAY,
	VS_SW_OVERLAY,
	VS_HW_OVERLAY
} VS_OVERLAY_KIND;


//default flag to CImgConn: sink type not defined, no overlay, no live image
#define VS_DEFAULT_FLAG	0
//indicates DIB sink
#define VS_DIB_SINK_FLAG		1
//indicates DDRAW sink
#define VS_DDRAW_SINK_FLAG		2
//indicates YCRCB sink
#define VS_YCRCB_SINK_FLAG		4
//indicates IMG sink
#define VS_IMG_SINK_FLAG		8
//indicates software overlay
#define VS_SW_OVERLAY_FLAG		0x100
//indicates hardware overlay
#define VS_HW_OVERLAY_FLAG		0x200

#define VS_BAYER_GB_RG_FLAG 1<<10
#define VS_BAYER_BG_GR_FLAG 1<<11
#define VS_BAYER_GB_RG_DEZIPPER_FLAG  1<<12
#define VS_BAYER_BG_GR_DEZIPPER_FLAG  1<<13
#define VS_BAYER_GB_RG_GOLD_EAGLE_FLAG  1<<14
#define VS_BAYER_BG_GR_GOLD_EAGLE_FLAG  1<<15


//indicates live image 
#define VS_LIVE_IMAGE_FLAG		0x10000


//converts from pixels to overlay units using 'stretch' value stretching
#ifndef VSP2OVER
#define VSP2OVER(x,stretch) ((short)( (DWORD)(x) * 1000L / (stretch)))
#endif
//converts from overlay units to pixels using 'stretch' value stretching
#ifndef VSOVER2P
#define VSOVER2P(x,stretch) ((short)( (DWORD)(x) * (stretch)/1000L))
#endif


#define VS_STRETCH_TO_FIT -1.0

#endif //_DSPTYPE_H_