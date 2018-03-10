/******************************************************************************
 *
 * MODULE   
 *		ImgFile.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ImgFile.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:24a $
 *
 * ABSTRACT  
 *		IFC interface of the CImgFile class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IMGFILE_H__F8DB9AF5_97F5_11D1_AE73_00A0C959E757__INCLUDED_)
#define AFX_IMGFILE_H__F8DB9AF5_97F5_11D1_AE73_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>

typedef enum {
	TIFF_IMGFILE=1,
	PCX_IMGFILE,
	BMP_IMGFILE,
	CUT_IMGFILE,
	FLF_IMGFILE,
	JPEG_IMGFILE,
	RAW_IMGFILE
} IFC_IMGFILE_TYPE;

// Image class type for TIFF files
typedef enum {
	IFFCL_BILEVEL		, // 1 BPP 
	IFFCL_GRAY	    	, // 2,4,6,8 BPP 
	IFFCL_PALETTE	    , // 2,4,6,8 BPP 
	IFFCL_RGB	    	, // 24 BPP chunky 
	IFFCL_RGBPLANAR   	, // 24 BPP in 8 bit planes 
	IFFCL_RGBA	    	, // 32 BPP chunky 
	IFFCL_RGBAPLANAR   , // 32 BPP in four 8 bit planes
	IFFCL_CMYK,
	IFFCL_YCC,
	IFFCL_CIELAB,
	IFFCL_YCRCB

} IFFCLASS_TYPE;

// Image Compression type for TIFF files
typedef enum {
	IFFCOMP_NONE,	// no compression 
	IFFCOMP_DEFAULT,	// whatever is defined for the format 
	IFFCOMP_RLE,	// various RLE schemes (PACKBITS in TIFF) 
	IFFCOMP_CCITT1D,	// TIFF modified G3 
	IFFCOMP_CCITTG3,	// TIFF raw G3	
	IFFCOMP_CCITTG4,	// TIFF G4	
	IFFCOMP_LZW,	// Lempel-Zif	
	IFFCOMP_LZWHPRED,	// LZW with TIFF horizontal differencing 
	IFFCOMP_JPEG,	// JPEG compression 
} IFFCOMPRESSION_TYPE;

typedef struct {
	IFC_IMGFILE_TYPE kind;
	DWORD dx;
	DWORD dy;
	WORD  bitsPerPixel;
	DWORD imgClass;
		// IFFCLASS for TIFF files
	DWORD imgCompress;
		// IFFCOMPRESSION for TIFF files
} IMGFILEPROPS;

typedef struct {
	DWORD imgQuality;    // For lossy compressions [0-100] where highest quality is 100.

} IMGFILE_EXT_WR_PARAMS,*PIMGFILE_EXT_WR_PARAMS;

typedef IMGFILEPROPS *LPIMGFILEPROPS;

#define IFC_MAX_IMG_FILENAME_LEN 200

typedef CImgFile *PCImgFile;

PCImgFile IFCCALL IfxCreateImgFile(pSTRING fileName);

#if defined __cplusplus && !defined NOIFCLINK

BOOL IFCCALL IfxWriteImgFile(pSTRING fileName,BYTE *src, DWORD dx, DWORD dy, WORD bitsPerPixel, IFFCLASS_TYPE imgClass=IFFCL_GRAY, IFFCOMPRESSION_TYPE imgCompress=IFFCOMP_DEFAULT, PIMGFILE_EXT_WR_PARAMS extParms=NULL);
BOOL IFCCALL IfxReadImgFile(pSTRING fileName,BYTE *dest,LPIMGFILEPROPS props=NULL);


class IFC_EXT_API CImgFile  
{
public:
	virtual BOOL ReadFile(BYTE *dest)=0;
	virtual BOOL WriteFile(BYTE *src, DWORD dx, DWORD dy, WORD bitsPerPixel, IFFCLASS_TYPE imgClass=IFFCL_GRAY, IFFCOMPRESSION_TYPE imgCompress=IFFCOMP_DEFAULT, PIMGFILE_EXT_WR_PARAMS extParms=NULL)=0;
	virtual BOOL ImageFileProps(LPIMGFILEPROPS props)=0;
	CImgFile(pSTRING fileName);
	virtual ~CImgFile();

friend PCImgFile IFCCALL IfxCreateImgFile(pSTRING fileName);

protected:
	char m_FileName[IFC_MAX_IMG_FILENAME_LEN];
};
#endif

#define IFC_DECLARE_DYN_IMGFILE(baseClass) static baseClass *CreateObject(pSTRING szFileName);

#define IFC_IMPLEMENT_DYN_IMGFILE(deriveClass,baseClass) \
baseClass *deriveClass::CreateObject(pSTRING szFileName) \
{ \
	return new deriveClass(szFileName); \
} 

typedef PCImgFile (*pfImgFileCreate)(pSTRING fileName);

BOOL IFCCALL IfxAddImgFileClass(pfImgFileCreate create,char *fileExt);
void IFCCALL IfxCloseImageFileFactory(void);

#define IFC_ADD_FACTORY_IMGFILE_CLASS(fileClass,fileExt) \
int _var_##fileClass = IfxAddImgFileClass(fileClass::CreateObject,(fileExt));


#endif // !defined(AFX_IMGFILE_H__F8DB9AF5_97F5_11D1_AE73_00A0C959E757__INCLUDED_)
