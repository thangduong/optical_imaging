/******************************************************************************
 *
 * MODULE   
 *		IFC.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifc.h $
 *		$Revision: 1.1 $
 *		$Modtime: 6/16/03 1:25p $
 *
 * ABSTRACT  
 *		IFC interface 
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2003 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(_IFC__INCLUDED_)
#define _IFC__INCLUDED_

#include <ifcbuild.h>

#if defined WIN32 && !defined _IFCDLL && !defined NOIFCLINK
#ifndef _WIN32_WCE
	#pragma comment(lib, IFC_CORE_LIBNAME)
	#pragma comment(lib, IFC_DISPLAY_LIBNAME)
#else
	#pragma comment(lib, "ifcce.lib")
#endif
#endif

#ifdef WIN32
#pragma pack(push,ifc_core_packing)
#pragma pack(8)
#endif

#include <ifcstd.h>
#include <ifctyp.h>
#include <icapmod.h>
#include <camera.h>
#include <intrupt.h>
#include <ITIMods.h>
#include <imgconn.h>
#include <imgsrc.h>
#include <imgsink.h>
#include <modfacty.h>
#include <camsrc.h> 
#include <hbufsrc.h>
#include <ovlsrc.h>
#include <hwovlsrc.h>
#include <swovlsrc.h>
#include <ycrcbsnk.h>
#include <ddawsink.h>
#include <dibsink.h>
#include <imgfile.h>
#include <ifcavi.h>
#include <pcdig.h>
#include <pcrgb.h>
#include <PCLink.h>
#include <PCPlus.h>
#include <PCVision.h>


#ifdef WIN32
#pragma pack(pop,ifc_core_packing)
#endif


#if defined __cplusplus && !defined NOIFCLINK

BOOL IFCCALL CheckIfcVersionResolution(DWORD sizeofCICamera,DWORD sizeofCICapMod,DWORD sizeofCModule,
					DWORD sizeofCPCDig, DWORD sizeofCPcRgb, DWORD sizeofCPCLink, DWORD sizeofCPCVisionPlus, DWORD sizeofCPCVision);

static BOOL __IfcVerCheck = CheckIfcVersionResolution(sizeof(CICamera),sizeof(CICapMod),sizeof(CModule),
					sizeof(CPCDig), sizeof(CPcRgb), sizeof(CPCLink), sizeof(CPCVisionPlus), sizeof(CPCVision) );

#endif

#endif
