/******************************************************************************
 *
 * MODULE   
 *		ifcstd.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifcstd.h $
 *		$Revision: 1.1 $
 *		$Modtime: 1/17/00 3:06p $
 *
 * ABSTRACT  
 *		IFC Standard Data Types
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
#ifndef _IFC_IFCSTD_DEF
#define _IFC_IFCSTD_DEF

typedef unsigned char   BYTE;           /* unsigned 8 bits */
typedef unsigned short  WORD;           /* unsigned 16 bits */
typedef unsigned long   DWORD;          /* unsigned 32 bits */
typedef int BOOL;			/* Boolean */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


/* Pointers to the following quantities... */
typedef unsigned char    * pBYTE;           /* unsigned 8 bits */
typedef unsigned short   * pWORD;           /* unsigned 16 bits */
typedef unsigned long    * pDWORD;          /* unsigned 32 bits */

/* Pointer to a pointer.. */
typedef unsigned short  **ppWORD;

typedef long  * pLONG;
typedef int  * pINT;
typedef short  *pSHORT;
typedef short  **ppSHORT;
typedef char  *pSTRING;
typedef char  **ppSTRING;
typedef float  *pFLOAT;
typedef float  **ppFLOAT;
typedef void  *pVOID;

#ifndef NULL
#define NULL 0
#endif

#ifdef IFC_IMPORT_ONLY
#define IFC_EXT_API  __declspec(dllimport)
#else
#define IFC_EXT_API  __declspec(dllexport)
#endif

#ifndef _WIN32_WCE
#define IFCAPI __stdcall
#else

#include <ifcce.h>
#define IFCAPI __cdecl
void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext );
char *_strdate( char *datestr );
int isspace( int c );
double atof( const char *string );
int _strnicmp( const char *string1, const char *string2, int count );
char *strrchr( const char *string, int c );
int _stricmp( const char *string1, const char *string2 );
int stricmp( const char *string1, const char *string2 );

#ifndef isxdigit
#define isxdigit(c) (((c) >= '0' && (c) <= '9') || ((c) >= 'a' && (c) <= 'f') || ((c) >= 'A' && (c) <= 'F'))
#endif

#ifndef isspace
#define isspace(c) (((c) == ' '  && (c) == '\t'))
#endif

#ifndef isdigit
#define isdigit(c) (((c) >= '0' && (c) <= '9'))
#endif

#ifndef isalnum
#define isalnum(c) (((c) >= '0' && (c) <= '9') || ((c) >= 'a' && (c) <= 'z') || ((c) >= 'A' && (c) <= 'Z'))
#endif

int strcmpi (char * dst, char * src);
char *getenv( const char *varname );

#define _inp(x) 0
#define _inpw(x) 0
#define _inpd(x) 0
#define _outp(x,y) (0)
#define _outpw(x,y) (0)
#define _outpd(x,y) (0)
#endif

#define IFCCALL IFC_EXT_API IFCAPI

#define OSHANDLE HANDLE

#define IFC_GRAB_SERVICE_FBONAME __TEXT("IFCGrabServiceMapObj")


#endif
