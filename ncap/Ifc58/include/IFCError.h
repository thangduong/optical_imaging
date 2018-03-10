/******************************************************************************
 *
 * MODULE   
 *		IFCError.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IFCError.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:26a $
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

#if !defined(AFX_IFCERROR_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
#define AFX_IFCERROR_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>

#include <ifcclass.h>
#include <IfcOs.h>

#define MKERCODE(facility,code) (((DWORD)(facility) << 16) | (code))
#define ERFACILITY(error) ((error) >> 16)
#define ERCODE(error) ((error) & 0xffffUL)

//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-------------------------------+-------------------------------+
//  |          Facility             |               Code            |
//  +-------------------------------+-------------------------------+
//
//  where
//
//
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

// The following error codes are common for all facilities
typedef enum {
	IFC_ERROR_NONE,
	IFC_ERROR_INVALID_PARAM,
	IFC_ERROR_ALLOC_FAIL,
	IFC_ERROR_FILE_NOT_FOUND,
	IFC_ERROR_UNABLE_TO_OPEN_WRITE_FILE,
	IFC_ERROR_ACCESS_DENIED,
	IFC_ERROR_INVALID_HANDLE,
	IFC_ERROR_INVALID_ACCESS,
	IFC_ERROR_BAD_COMMAND,
	IFC_ERROR_BAD_LENGTH,
	IFC_ERROR_NOT_SUPPORTED,
	IFC_ERROR_DEV_NOT_EXIST,
	IFC_ERROR_BUFFER_OVERFLOW,
	IFC_ERROR_INSUFFICIENT_BUFFER,
	IFC_ERROR_INVALID_NAME,
	IFC_ERROR_MOD_NOT_FOUND,
	IFC_ERROR_BUSY,
	IFC_ERROR_FILE_CORRUPT,
	IFC_ERROR_TIMED_OUT,
	IFC_ERROR_MUTEX_TIME_OUT,
	IFC_ERROR_RESOURCE_LIMIT,
	IFC_ERROR_MEMLOCK_FAIL,			// a memory space could not be used as a DMA target
	IFC_ERROR_BM_NOT_DONE,			// a Bus Master/DMA did not finish in the alloted time
	IFC_ERROR_INVALID_COLOR,		// the color parameter is not valid
	IFC_ERROR_INVALID_X_DX,			// x and/or dx paramter are not valid
	IFC_ERROR_INVALID_Y_DY,			// y and/or dy paramter are not valid
	IFC_ERROR_UNABLE_TO_LOAD_DLL,
	IFC_ERROR_RESOURCE_CREATION_FAILED,
	IFC_ERROR_CALL_FAILED,
	IFC_ERROR_DDRAW_CALL_FAIL,
	IFC_ERROR_API_CALL_FAIL,
	IFC_ERROR_INTREVENT_NOT_SUPPORTED,
	IFC_ERROR_BAD_FILE_SYNTAX,		// Error in file syntax
	IFC_ERROR_AUTHORIZE_FAILURE,
	IFC_WRONG_SERIALNO,				/* application - wrong serial#  */
	IFC_WRONG_OEMNO,				/* application - wrong OEM #            */
	IFC_PRODUCT_EXPIRED,		  	/* application - product expired        */
	IFC_PRODUCT_MAXCNT,				/* application - max execute count exceeded */
	IFC_SWP_BAD_AUTHCODE,		 	/* No valid authorization code found. */
	IFC_SWP_AUTH_FAULT,				/* General Software Protection Authorize fault */
	IFC_ACCESS_ERROR,


} IFC_ERROR_CODE;


// All Facility peculiar error types begin at the following base value
#define FACILITY_UNIQUE_BASE_CODE 0x8000

// To Add a new Error Facility,
//	1. Add a value to the end of type IFC_ERROR_FACILITY
//	2. Define in your header file an error code type whose 
//	   first value is FACILITY_UNIQUE_BASE_CODE
//	For example:
// 
//	typedef enum {
//		MY_FIRST_ERROR=FACILITY_UNIQUE_BASE_CODE,
//		MY_SECOND_ERROR
//  } MY_ERROR_CODE;
//

typedef enum {
	NULL_FACILITY,	

	NUM_ERROR_FACILITIES
} IFC_ERROR_FACILITY;

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CIFCError	 : public CIobject  
{
public:
	void PutLastError(DWORD error,const char *errstr,...);
	void PutLastError(DWORD error,const char *errstr,va_list marker);
	DWORD GetLastError(void);
	void PutLastError(DWORD error);
	CIFCError(CIFCOS *os);
	CIFCError();
	virtual ~CIFCError();
	CIFCOS *m_os;
	DWORD m_lastError;
};
#endif

#ifdef __cplusplus
void IFC_EXT_API IfxPutLastError(DWORD error,const char *errstr,...);
#endif

void IFC_EXT_API IfxPutLastError(DWORD error);
DWORD IFC_EXT_API IfxGetLastError(void);

#ifdef __cplusplus
class IFC_EXT_API CIFCExcept
{
public:
	CIFCExcept(void);
	CIFCExcept(char *errmsg,...);
};
#endif


#endif // !defined(AFX_IFCERROR_H__E554E634_93FD_11D1_AE72_00A0C959E757__INCLUDED_)
