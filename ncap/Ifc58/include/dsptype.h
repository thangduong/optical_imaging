/******************************************************************************
 *
 * MODULE   
 *		dsptype.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/dsptype.h $
 *		$Revision: 1.1 $
 *		$Modtime: 9/04/03 10:05a $
 *
 * ABSTRACT 
 *	Standard definitions for the IFCDSP.DLL
 *
 * TECHNICAL NOTES 
 *
 * 
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _DSPTYPE_H_
#define _DSPTYPE_H_

#ifdef WIN32
#include <windows.h>

 #ifndef STRICT
  #define DEFINE_IFC_HWND struct HWND##__ { int unused; }; typedef struct HWND##__ *IFC_HWND
  #define DEFINE_IFC_HDC  struct HDC##__ { int unused; }; typedef struct HDC##__ *IFC_HDC
  DEFINE_IFC_HWND;
  DEFINE_IFC_HDC;
 #else
  #define IFC_HWND HWND
  #define IFC_HDC HDC
 #endif

#else//#ifdef WIN32

 #define IFC_HWND void *
 #define IFC_HDC void *

#endif //#ifdef WIN32

// source kinds
typedef enum 
{	
	NONE_SRC,
	CAMERA_SRC, 
	HOST_BUFFER_SRC, 
	IMAGE_SRC,
	LAST_SRC	//always last
} SRC_KIND;

// sink kinds
typedef enum 
{	
	NONE_SINK,
	DIB_SINK, 
	DDRAW_SINK, 
	YCRCB_SINK, 
	IMAGE_SINK,
	LAST_SINK	//keep this always last
} SINK_KIND;

//overlay kinds
typedef enum
{	
	NONE_OVERLAY,
	SW_OVERLAY,
	HW_OVERLAY
} OVERLAY_KIND;


//default flag to CImgConn: sink type not defined, no overlay, no live image
#define IFC_DEFAULT_FLAG	0
//indicates DIB sink
#define IFC_DIB_SINK		1<<0
//indicates DDRAW sink
#define IFC_DDRAW_SINK		1<<1
//indicates YCRCB sink
#define IFC_YCRCB_SINK		1<<2
//indicates IMG sink
#define IFC_IMG_SINK		1<<3
//indicates software overlay
#define IFC_SW_OVERLAY		1<<8
//indicates hardware overlay
#define IFC_HW_OVERLAY		1<<9
//indicates bayer filter input type IFC_BAYER_GB_RG
#define IFC_BAYER_GB_RG_FLAG 1<<10
#define IFC_BAYER_BG_GR_FLAG 1<<11
#define IFC_BAYER_GB_RG_DEZIPPER_FLAG  1<<12
#define IFC_BAYER_BG_GR_DEZIPPER_FLAG  1<<13
#define IFC_BAYER_GB_RG_GOLD_EAGLE_FLAG  1<<14
#define IFC_BAYER_BG_GR_GOLD_EAGLE_FLAG  1<<15


//indicates live image 
#define IFC_LIVE_IMAGE		1<<16


//converts from pixels to overlay units using 'stretch' value stretching
#ifndef IFCP2OVER
#define IFCP2OVER(x,stretch) ((short)( (DWORD)(x) * 1000L / (stretch)))
#endif
//converts from overlay units to pixels using 'stretch' value stretching
#ifndef IFCOVER2P
#define IFCOVER2P(x,stretch) ((short)( (DWORD)(x) * (stretch)/1000L))
#endif

#endif //_DSPTYPE_H_