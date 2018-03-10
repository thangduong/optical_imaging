/******************************************************************************
 *
 * MODULE   
 *		CfgFile.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/CfgFile.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/01/04 10:43a $
 *
 * ABSTRACT  
 *		IFC interface of the CCfgFile class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2004 Coreco Imaging, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CFGFILE_H__1CCC57E1_8B30_11D1_A574_00A0C959E757__INCLUDED_)
#define AFX_CFGFILE_H__1CCC57E1_8B30_11D1_A574_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// System includes
#include <ifcstd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <ifcclass.h>


#ifndef _WIN32_WCE
#include <io.h>
#include <fcntl.h>
#include <time.h>
#else
#define _MAX_FNAME 128
#define _MAX_EXT	128
#ifndef MAX_PATH
#define MAX_PATH	260
#endif
#define _MAX_DRIVE	260
#define _MAX_DIR	260
#endif

typedef enum {
	IFC_FOPEN_READ,
	IFC_FOPEN_WRITE
} IFC_FOPEN_TYPE;

#define IFC_MAX_CFG_FILE_LINELEN 256

typedef char FILELINE[IFC_MAX_CFG_FILE_LINELEN];
#define IFC_MAX_NUM_PRESERVED_COMMENT_LINES 40

typedef struct {
	DWORD m_numPreservedCommentLines;
	FILELINE m_szPreservedCommentLine[IFC_MAX_NUM_PRESERVED_COMMENT_LINES];	
} IFC_PRESERVE_COMMENT_REC, *PIFC_PRESERVE_COMMENT_REC;


#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CCfgFile  
{
public:

	enum
	{
		CFG_EOF = -1
	};

	CCfgFile(const char *cfgFileName, IFC_FOPEN_TYPE eOpenType = IFC_FOPEN_READ);
	virtual ~CCfgFile();
	char *TrimLeft(char *szIn);
	char *GetFileName();
	char *GetLine(DWORD dwLineNum);
	BOOL IsEmpty();
	void PutLineBase(char *szLine);
	void PutLine(char *szLine,...);
    void CreateWriteBuffer();
	void SetReplacementWindow(long lStartIndex, long lEndIndex);
	BOOL Write();

	char m_szCfgFileName[_MAX_PATH];				// config file name
	char m_szFileNameNP[_MAX_FNAME + _MAX_EXT];		// config file name without path.

	DWORD m_dwNumCfgLines;
	FILELINE *m_szCfgLines;		// ptr to array of file content, NULL terminated 
	char *m_data;				// ptr to array of file content, NULL terminated 

	// These two members "window" the module section in the
	// read buffer to be replaced when writing out.
	long m_lReplaceSectionStartIndex;
	long m_lReplaceSectionEndIndex;

	FILELINE *m_szCfgLineBufOut;	// ptr to array of file content, NULL terminated 
	WORD m_curIndexOut;

	DWORD m_numPreservedCommentLines;
	FILELINE m_szPreservedCommentLine[IFC_MAX_NUM_PRESERVED_COMMENT_LINES];	

};
#endif

#if defined( __cplusplus )
extern "C" {
#endif

pCCfgFile IFCCALL IfxCreateCCfgFile(const char *cfgFileName, IFC_FOPEN_TYPE eOpenType);
void IFCCALL IfxDeleteCCfgFile(CCfgFile *cfg);

#ifdef __cplusplus
}
#endif




#endif // !defined(AFX_CFGFILE_H__1CCC57E1_8B30_11D1_A574_00A0C959E757__INCLUDED_)
