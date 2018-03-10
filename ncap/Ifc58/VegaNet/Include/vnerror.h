
/******************************************************************************
 *
 * MODULE   
 *		IFCError.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/VegaNet/include/vnerror.h $
 *		$Revision: 1.1 $
 *		$Modtime: 3/16/01 9:53a $
 *
 * ABSTRACT  
 *		IFC interface of the CIFCError class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_VnError_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
#define AFX_VnError_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "vidsrct.h"

// The following error codes are common for all facilities
typedef enum {
	VS_ERROR_NONE,
	VS_ERROR_INVALID_PARAM,
	VS_ERROR_ALLOC_FAIL,
	VS_ERROR_FILE_NOT_FOUND,
	VS_ERROR_UNABLE_TO_OPEN_WRITE_FILE,
	VS_ERROR_ACCESS_DENIED,
	VS_ERROR_INVALID_HANDLE,
	VS_ERROR_INVALID_ACCESS,
	VS_ERROR_BAD_COMMAND,
	VS_ERROR_BAD_LENGTH,
	VS_ERROR_NOT_SUPPORTED,
	VS_ERROR_DEV_NOT_EXIST,
	VS_ERROR_BUFFER_OVERFLOW,
	VS_ERROR_INSUFFICIENT_BUFFER,
	VS_ERROR_INVALID_NAME,
	VS_ERROR_MOD_NOT_FOUND,
	VS_ERROR_BUSY,
	VS_ERROR_FILE_CORRUPT,
	VS_ERROR_TIMED_OUT,
	VS_ERROR_MUTEX_TIME_OUT,
	VS_ERROR_RESOURCE_LIMIT,
	VS_ERROR_MEMLOCK_FAIL,			// a memory space could not be used as a DMA target
	VS_ERROR_BM_NOT_DONE,			// a Bus Master/DMA did not finish in the alloted time
	VS_ERROR_INVALID_COLOR,		// the color parameter is not valid
	VS_ERROR_INVALID_X_DX,			// x and/or dx paramter are not valid
	VS_ERROR_INVALID_Y_DY,			// y and/or dy paramter are not valid
	VS_ERROR_UNABLE_TO_LOAD_DLL,
	VS_ERROR_RESOURCE_CREATION_FAILED,
	VS_ERROR_CALL_FAILED,
	VS_ERROR_DDRAW_CALL_FAIL,
	VS_ERROR_API_CALL_FAIL,
	VS_ERROR_INTREVENT_NOT_SUPPORTED,
	VS_ERROR_BAD_FILE_SYNTAX,		// Error in file syntax
	VS_ERROR_AUTHORIZE_FAILURE,
	VS_WRONG_SERIALNO,				/* application - wrong serial#  */
	VS_WRONG_OEMNO,				/* application - wrong OEM #            */
	VS_PRODUCT_EXPIRED,		  	/* application - product expired        */
	VS_PRODUCT_MAXCNT,				/* application - max execute count exceeded */
	VS_SWP_BAD_AUTHCODE,		 	/* No valid authorization code found. */
	VS_SWP_AUTH_FAULT,				/* General Software Protection Authorize fault */
	VS_ACCESS_ERROR,


} VS_ERROR_CODE;



#ifdef __cplusplus
void IVSCALL VsPutLastError(DWORD error,const char *errstr,...);
#endif

void IVSCALL VsPutLastError(DWORD error);
DWORD IVSCALL VsGetLastError(void);



#endif // !defined(AFX_IFCERROR_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
