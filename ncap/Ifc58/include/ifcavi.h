/******************************************************************************
 *
 * MODULE   
 *		IfcAvi.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifcavi.h $
 *		$Revision: 1.1 $
 *		$Modtime: 7/03/01 10:30a $
 *
 * ABSTRACT  
 *		IFC interface of the AVI file functions
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998-2001 (c) Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IFCAVI_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
#define AFX_IFCAVI_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifctyp.h>
#include <ifcos.h>


#ifdef __cplusplus
extern "C" {
#endif



BOOL  IFCCALL IfxAcquireToAviFile(DWORD context,DWORD frameSeqnum, BYTE *buff); 

void  IFCCALL IfxCleanupAcquireToAviFile(DWORD context);


DWORD IFCCALL IfxSetupAcquireToAviFile(LPSTR fname, DWORD dx,DWORD dy,DWORD bits, DWORD fps,
											BOOL logical_bitmap,BOOL compressFlag,
                                 			DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, 
                                 			DWORD dwKeyFrameEvery);

BOOL  IFCCALL IfxSaveToAviFile(DWORD n_frames,BOOL logical_bitmap, LPSTR fname, BYTE   *buff, 
                                 DWORD dx,DWORD dy,DWORD bits, DWORD fps,BOOL compressFlag,
                                 DWORD dwBytesPerSecond, DWORD fccHandler, DWORD dwQuality, DWORD dwKeyFrameEvery);




#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_IFCAVI_H__E36F2682_B43B_11D1_AE7B_00A0C959E757__INCLUDED_)
