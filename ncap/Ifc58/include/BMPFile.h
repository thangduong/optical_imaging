/******************************************************************************
 *
 * MODULE   
 *		BMPFile.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/BMPFile.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/10/01 1:31p $
 *
 * ABSTRACT  
 *		IFC interface of the CBMPFile class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/


#if !defined(AFX_BMPFILE_H__65E867C6_D881_11D2_B030_00105A0F576C__INCLUDED_)
#define AFX_BMPFILE_H__65E867C6_D881_11D2_B030_00105A0F576C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <ImgFile.h>

#ifdef __cplusplus
class CBMPFile : public CImgFile  
{
public:
	CBMPFile(pSTRING fileName);
	virtual ~CBMPFile();
	virtual BOOL ReadFile(BYTE *dest);
	virtual BOOL WriteFile(BYTE *src, DWORD dx, DWORD dy, WORD bitsPerPixel, IFFCLASS_TYPE imgClass=IFFCL_GRAY, IFFCOMPRESSION_TYPE imgCompress=IFFCOMP_DEFAULT, PIMGFILE_EXT_WR_PARAMS extParms=NULL);
	virtual BOOL ImageFileProps(LPIMGFILEPROPS props);

	IFC_DECLARE_DYN_IMGFILE(CImgFile)
private:
	int ReadCompressed(BYTE *buf, int len, FILE *fp);

};
#endif

#endif // !defined(AFX_BMPFILE_H__65E867C6_D881_11D2_B030_00105A0F576C__INCLUDED_)
