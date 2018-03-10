/******************************************************************************
 *
 * MODULE   
 *		ClrSpace.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ClrSpace.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:36a $
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

#if !defined(AFX_CLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
#define AFX_CLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifctyp.h>
#include <ifcos.h>
#include <camera.h>

#define IFC_BAYOPT_LINE_REVERSE		1
#define IFC_BAYOPT_YCRCB			2
#define IFC_BAYOPT_10BIT_SRC		4
#define IFC_BAYOPT_12BIT_SRC		8
#define	IFC_BAYOPT_PIX_LEAST_SIG 0x10




#define CORBUFFER_BAYER_METHOD_INTERPOLATE	1
#define CORBUFFER_BAYER_METHOD_GOLDEN_EAGLE 2
#define CORBUFFER_BAYER_METHOD_EAGLE		4
#define CORBUFFER_BAYER_ALIGN_GB_RG	0x10
#define CORBUFFER_BAYER_ALIGN_BG_GR	0x20
#define CORBUFFER_BAYER_ALIGN_RG_GB	0x40
#define CORBUFFER_BAYER_ALIGN_GR_BG	0x80

typedef enum {
	IFC_YCRCBTORGB16,
	IFC_YCRCBTORGB24,
	IFC_YCRCBTORGB32
} IFC_YCRCBTORGB;

typedef enum {
	IFC_RGB16TOYCRCB,
	IFC_RGB24TOYCRCB,
	IFC_RGB32TOYCRCB,
} IFC_RGBTOYCRCB;


typedef struct {
	float redGain;
	float greenGain;
	float blueGain;

} IFC_BAYER_EXT_ATTR,*PIFC_BAYER_EXT_ATTR;


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CClrSpace : public CIobject 
{
public:
	static BOOL RGBToYCrCb(pBYTE dest, pBYTE src, DWORD src_bytes, IFC_RGBTOYCRCB mode);
	static BOOL YCrCbToRGB(pBYTE dest, pBYTE src, DWORD src_bytes, IFC_YCRCBTORGB mode, BOOL redMostSig=FALSE);
	static BOOL YCrCbToRGBReverse(pBYTE iDest, pBYTE src, DWORD width, DWORD height, IFC_YCRCBTORGB mode);


	CClrSpace();
	virtual ~CClrSpace();

};

#endif

#ifdef __cplusplus
extern "C" {
#endif


BOOL IFCCALL IfxBayerFilterConvert(DWORD options,IFC_BAYER_FILTER_TYPE filterType, pBYTE dest, pBYTE src, DWORD width,DWORD height, IFC_COLOR targetColor, PIFC_BAYER_EXT_ATTR extAttr);

#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_CLRSPACE_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
