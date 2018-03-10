/******************************************************************************
 *
 * MODULE   
 *		ClrSpace.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/VnClrSpc.h $
 *		$Revision: 1.1 $
 *		$Modtime: 2/19/04 6:03p $
 *
 * ABSTRACT  
 *		IFC interface of the CClrSpace class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_VNCLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
#define AFX_VNCLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <vidsrct.h>



#ifdef __cplusplus

extern "C" {
#endif

BOOL IVSCALL VnRGBToYCrCb(pBYTE dest, pBYTE src, DWORD src_bytes, VS_RGBTOYCRCB mode);
BOOL IVSCALL VnYCrCbToRGB(pBYTE dest, pBYTE src, DWORD src_bytes, VS_YCRCBTORGB mode, BOOL redMostSig);
BOOL IVSCALL VnYCrCbToRGBReverse(pBYTE iDest, pBYTE src, DWORD width, DWORD height, VS_YCRCBTORGB mode);

#define VS_BAYOPT_LINE_REVERSE 1

BOOL IVSCALL VnBayerFilterConvert(DWORD options,VS_BAYER_FILTER_TYPE filterType, pBYTE dest, pBYTE src, DWORD width, DWORD height, VS_COLOR targetColor, PVS_BAYER_EXT_ATTR extAttr);


#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_CLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
