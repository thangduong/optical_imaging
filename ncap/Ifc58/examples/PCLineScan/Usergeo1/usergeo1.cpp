/******************************************************************************
 *
 * MODULE   
 *		usergeo1.cpp
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/examples/LineScan/usergeo1/usergeo1.cpp $
 *		$Revision: 1.1 $
 *		$Modtime: 3/22/00 4:18p $
 *
 * ABSTRACT  
 *		IFC PCLineScan User Geometry Example
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#include "stdafx.h"

// The User Geometry DLL must export the following 2 functions
extern "C" DWORD IFCCALL UserGeometryLoad(CPCLine *pcd,DWORD *oct,DWORD srcOffset,DWORD dx,DWORD dy,DWORD bytesPerPixel);
extern "C" BOOL IFCCALL UserGeometryProperties(CPCLine *pcd,LPPCL_USER_GEO_PROP lpProps);

// Note: This functionality is only for advanced users who must accomodate a camera
// for which none of the standard geometries apply.
// UserGeometryLoad must load up the OCT table as appropriate for the camera tap geometry
// See the PCDig Hardware manual for a description of the OCT
// The following example UserGeometryLoad and UserGeometryProperties functions
// are for the PCD_4CHAN_INTERLEAVE_CONVERGE geometry

// To create and use a user-defined camera geometry:
// 1. Create the user-defined camera geometry DLL (which this example does).
// 2. Copy the produced DLL to your %SystemRoot%\system32 directory
// 3. In the camera parameter definition specify  USER_DEFINED_GEO = usergeo1

DWORD IFCCALL UserGeometryLoad(CPCLine *pcd,DWORD *oct,DWORD srcOffset,DWORD dx,DWORD dy,DWORD bytesPerPixel)
{
	DWORD bytesPerLine;
	DWORD OCTIndex=0;
	DWORD y;
	DWORD src;
	DWORD	bcount;
	DWORD thisCount;
	bytesPerLine = dx * bytesPerPixel;
	
	pcd->WriteReg(PCL_OCTSWAP_32,PCL_OCT_WORD_SWAP);			
	for (y=0; y < (dy*2) ; y++) {
		if (y&1) 
			src = srcOffset + ((y>>1)+1)*bytesPerLine - 8;
		else
			src = srcOffset + (y>>1)*bytesPerLine;
		bcount = bytesPerLine / 2; // half-line byte count
		while (bcount > 0) {
			if (y&1) {
				oct[OCTIndex++] = PCLineMakeBackwardOCTEntry(src,bcount,&thisCount,1);
				src -= 2*thisCount;
			}
			else {
				oct[OCTIndex++] = PCLineMakeForwardOCTEntry(src,bcount,&thisCount,1);
				src += 2*thisCount;
			}
			bcount -= thisCount;
		}
	}
	
    return OCTIndex;
}


BOOL IFCCALL UserGeometryProperties(CPCLine *pcd,LPPCL_USER_GEO_PROP lpProps)
{
	if (lpProps) {
		lpProps->BMStepSize = 1;
		lpProps->numHorzTaps = 4;
		lpProps->numVertTaps = 1;
		lpProps->sForm = PCL_16BIT_2TAP;
	    return TRUE;
	}
	else
		return FALSE;
}



BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

