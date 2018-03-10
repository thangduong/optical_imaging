/******************************************************************************
 *
 * MODULE
 *    hiffl.h
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/include/ifchiffl.h $
 *    $Revision: 1.1 $
 *    $Modtime: 10/19/99 10:02a $
 *
 * ABSTRACT
 *        include file for HALO Image File Format Library
 *
 * TECHNICAL NOTES
 *
***************************************************************************/


/*----------------------------------------------------------------------------
| Module    : hiffl.h
|
| Purpose   : include file for HALO Image File Format Library
|
| History   : 04/01/93  DDS
|
| Copyright 1990-1993 Media Cybernetics, Inc.
|-----------------------------------------------------------------------------*/
#ifndef  _INC_HIL
#define  _INC_HIL
#endif

#ifdef _WINDOWS
#define HIL_WINDOWS     1
#endif

#ifdef WIN32
#define HIL_WINDOWS32	1
#endif

#define MAX_IMAGE_WIDTH 8192

#if !defined _INC_WINDOWS && !defined _WINDOWS_
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif  /* __cplusplus */

/*------------------------------------------------------------------------
| IFFMODE:	Open modes
|-----------------------------------------------Tue Jun 04 10:25:31 1991--*/
typedef int IFFMODE;
#define IFFM_READ	    0
#define IFFM_WRITE	    1
#define IFFM_APPEND	    2
#define IFFM_READWRITE	    3
#define IFFM_MEMORY	    0x80

/*------------------------------------------------------------------------
| IFFCLASS:	Image classes
|-----------------------------------------------Tue Aug 21 10:33:14 1990--*/
typedef int IFFCLASS;

typedef int IFFTILEFORMAT;
#define IFFTF_NONE	    0
#define IFFTF_STRIPS	    1
#define IFFTF_TILES	    2

/*------------------------------------------------------------------------
| IFFCOMMAND:	 Commands to IFF_Control
|-----------------------------------------------Fri Apr 05 11:36:16 1991--*/
typedef int IFFCMD;
typedef int IFFCOMMAND;
#define IFFCMD_GETERROR 	0	/* get error code */
#define IFFCMD_GETLINESIZE	1	/* compute line size */
#define IFFCMD_PALETTE		2	/* get or set palette or map */
#define IFFCMD_SETPACKMODE	3	/* set mode for packing/unpacking pixels  */
#define IFFCMD_DESCRIPTION	4	/* get or set image description field	*/
#define IFFCMD_SOFTWARENAME	5	/* get or set software name (TIFF TGA) */
#define IFFCMD_ARTISTNAME	6	/* get or set artist name (TIFF TGA)   */
#define IFFCMD_RESOLUTION	7	/* get dots per meter */
#define IFFCMD_DOCUMENTNAME	8	/* get of set the document name field */
#define IFFCMD_DATETIME 	9	/* get or set the date/time field */
#define IFFCMD_GETNUMIMAGES	10	/* get the number of images */
#define IFFCMD_IMAGESEEK	11	/* seek to the next image */
#define IFFCMD_DELETE		12	/* delete current image */
#define IFFCMD_TILEFORMAT	13	/* set/get the tiling format */
#define IFFCMD_YCCINFO		14	/* set/get YCC information */
#define IFFCMD_YCCRGBCONVERT	15	/* set/get YCC/RGB conversion state */
#define IFFCMD_COLORIMETRY	16	/* set/get Colorimetry info */
#define IFFCMD_CMYKINFO 	17	/* set/get CMYK specific data */

#define IFFCMD_TIFF		0x4000	/* TIFF specific commands */
#define IFFCMD_TIFFTAG		0x4001
#define IFFCMD_TIFFTAGDATA	0x4002
#define IFFCMD_FAXSCALE 	0x4003
#define IFFCMD_PCX		0x4200	/* PCX specific commands */
#define IFFCMD_BMP		0x4400	/* BMP specific commands */
#define IFFCMD_BMP_VERSION	0x4401	/* Windows os2 1.2 os2 2.0 versions */
#define IFFCMD_HCUT		0x4600	/* HALO CUT specific commands */
#define IFFCMD_TGA		0x4800	/* TGA specific commands */
#define IFFCMD_IMG		0x4A00	/* IMG specific commands */
#define IFFCMD_MSP		0x4C00	/* MSP specific commands */
#define IFFCMD_GIF		0x4E00	/* GIF specific commands */
#define IFFCMD_EPSF		0x5000	/* EPSF specific commands */
#define IFFCMD_HFF		0x5200	/* HFF specific commands */
#define IFFCMD_FLAT		0x5400	/* FLAT specific commands */
#define IFFCMD_WPG		0x5600	/* WPG specific commands */
#define IFFCMD_JPEG		0x5700	/* WPG specific commands */
#define IFFCMD_JPEGQ		0x5701	/* Quality */
#define IFFCMD_PCD		0x5800	/* Kodak PCD specific commands */
#define IFFCMD_PCDGETTRANSFORM	0x5801
#define IFFCMD_PCDSETTRANSFORM	0x5802
#define IFFCMD_PCDSETCLASS	0x5803
#define IFFCMD_GETDATASIZE	0x8000	/* OR with this to get the size */

/*------------------------------------------------------------------------
| IFFPACKMODE:	 Packing modes
|-----------------------------------------------Tue Jun 04 10:24:43 1991--*/
typedef int IFFPACKMODE;
#define IFFPM_PACKED	    0
#define IFFPM_UNPACKED	    1
#define IFFPM_LEFTJUSTIFIED 2
#define IFFPM_NORMALIZED    3
#define IFFPM_RAW	    4

/*------------------------------------------------------------------------
| IFFSEQUENCE:	Line sequences
|-----------------------------------------------Tue Jun 04 10:25:02 1991--*/
typedef int IFFSEQUENCE;
#define IFFSEQ_TOPDOWN	    0	/* most */
#define IFFSEQ_BOTTOMUP     1	/* BMP and TGA compressed */
#define IFFSEQ_INTERLACED   2	/* for GIF */

/*------------------------------------------------------------------------
| IFFERROR:	Possible errors
|-----------------------------------------------Fri Apr 05 11:36:03 1991--*/
typedef int IFFERROR;
#define IFFERR_NONE	    0	/* no error	*/
#define IFFERR_HANDLELIMIT  1	/* too many open files */
#define IFFERR_PARAMETER    2	/* programmer error */
#define IFFERR_NOTSUPPORTED 3	/* feature not supported by format */
#define IFFERR_NOTAVAILABLE 4	/* item not available */
#define IFFERR_MEMORY	    5	/* insufficient memory */
#define IFFERR_IMAGE	    6	/* bad image data (decompression error) */
#define IFFERR_HEADER	    7	/* header has bad fields */
#define IFFERR_IO_OPEN	    8	/* error on open() */
#define IFFERR_IO_CLOSE     9	/* error on close() */
#define IFFERR_IO_READ	    10	/* error on read() */
#define IFFERR_IO_WRITE     11	/* error on write() */
#define IFFERR_IO_SEEK	    12	/* error on lseek() */
#define IFFERR_FILENOTFOUND 13	/* file not found */
#define IFFERR_UNKNOWN_FF	14	/* unknown file format */
#define IFFERR_INV_SIZE 	15	/* invalid width / height */

/*------------------------------------------------------------------------
| IFFCOMPRESSION:	Compression options
|-----------------------------------------------Fri Apr 05 11:36:41 1991--*/
typedef int IFFCOMPRESSION;

/*------------------------------------------------------------------------
| Date Time structure for IFF
|-----------------------------------------------Tue Sept 06 16:18:05 1991--*/
typedef struct
{
    short Year;
    short Month;
    short Day;
    short Hour;
    short Minute;
    short Second;
} IFF_DATETIME;

/* struct for setting YCC info, a 0 in any field causes it to be ignored */
typedef struct
{
    short   HSubSampling;	/* Horizontal sub sampling */
    short   VSubSampling;	/* Vertical sub sampling */
    short   Coefficients[3];	/* in 10000ths */
    short   Positioning;	/* 1=centered, 2=cosited */
} IFF_YCCINFO;

typedef struct
{
    short	DotRange[2];	    /* in sample values */
    char  *	TargetPrinter;	    /* ASCII */
} IFF_CMYKINFO;

typedef struct
{
    short   ReferenceBlackWhite[6];	/* in sample values */
    short   WhitePoint[2];		/* in 10000ths */
    short   PrimaryChromaticities[6];	/* in 10000ths */
} IFF_COLORIMETRY;

/*------------------------------------------------------------------------
| Types for multiple images
|-----------------------------------------------Tue Sept 06 16:18:05 1991--*/
typedef int IFFIMAGETYPE;
#define IFFIT_PRIMARY	    0
#define IFFIT_THUMBNAIL     1
#define IFFIT_MASK	    2

/*-----------------------------------------------------------------
| Bitmap types
|------------------------------------------------------------------*/
typedef int IFFBMPVERSION;
#define IFFBV_WIN_3	    0x10	/* Windows 3.0 */
#define IFFBV_OS2_1	    0x20	/* OS2 1.2 */
#define IFFBV_OS2_2S	    0x40	/* OS2 2.0 single image */
#define IFFBV_OS2_2M	    0x41	/* OS2 2.0 multiple image */

/*------------------------------------------------------------------------
| association declarations - not used with windows
|-----------------------------------------------Tue Jun 04 09:18:05 1991--*/
int  HifflHCUTAssociate(pVOID);
int  HifflPCXAssociate(pVOID);
int  HifflTIFFAssociate(pVOID);
int  HifflMSPAssociate(pVOID);
int  HifflEPSAssociate(pVOID);
int  HifflIMGAssociate(pVOID);
int  HifflTGAAssociate(pVOID);
int  HifflBMPAssociate(pVOID);
int  HifflGIFAssociate(pVOID);
int  HifflFLATAssociate(pVOID);
int  HifflRASAssociate(pVOID);
int  HifflAPOLLOAssociate(pVOID);
int  HifflJPEGAssociate(pVOID);
int  HifflPICTAssociate(pVOID);
int  HifflKODAKAssociate(pVOID);

#if defined(HIL_WINDOWS32)
#define IFFLIB_HALOCUT          "IFFCUT32.DLL"
#define IFFLIB_HCUT             "IFFCUT32.DLL"
#define IFFLIB_PCX              "IFFPCX32.DLL"
#define IFFLIB_TIFF             "IFFTIF32.DLL"
#define IFFLIB_MSP              "IFFMSP32.DLL"
#define IFFLIB_EPS              "IFFEPS32.DLL"
#define IFFLIB_IMG              "IFFIMG32.DLL"
#define IFFLIB_TGA              "IFFTGA32.DLL"
#define IFFLIB_BMP              "IFFBMP32.DLL"
#define IFFLIB_GIF              "IFFGIF32.DLL"
#define IFFLIB_FLAT             "IFFFLT32.DLL"
#define IFFLIB_RAS              "IFFRAS32.DLL"
#define IFFLIB_APOLLO           "IFFAP32.DLL"
#define IFFLIB_JPEG             "IFFJPG32.DLL"
#define IFFLIB_PICT		"IFFPCT32.DLL"
#define IFFLIB_KODAK		"IFFKDK32.DLL"
#elif defined(HIL_WINDOWS)
#define IFFLIB_HALOCUT          "IFFHCUT.DLL"
#define IFFLIB_HCUT             "IFFHCUT.DLL"
#define IFFLIB_PCX              "IFFPCX.DLL"
#define IFFLIB_TIFF             "IFFTIFF.DLL"
#define IFFLIB_MSP              "IFFMSP.DLL"
#define IFFLIB_EPS              "IFFEPS.DLL"
#define IFFLIB_IMG              "IFFIMG.DLL"
#define IFFLIB_TGA              "IFFTGA.DLL"
#define IFFLIB_BMP              "IFFBMP.DLL"
#define IFFLIB_GIF              "IFFGIF.DLL"
#define IFFLIB_FLAT             "IFFFLAT.DLL"
#define IFFLIB_RAS              "IFFRAS.DLL"
#define IFFLIB_APOLLO           "IFFAP.DLL"
#define IFFLIB_JPEG             "IFFJPEG.DLL"
#define IFFLIB_PICT		"IFFPICT.DLL"
#define IFFLIB_KODAK		"IFFKODAK.DLL"
#elif defined(HIL_OS2)
#define IFFLIB_HALOCUT          "IFFHCUT"
#define IFFLIB_HCUT             "IFFHCUT"
#define IFFLIB_PCX              "IFFPCX"
#define IFFLIB_TIFF             "IFFTIFF"
#define IFFLIB_MSP              "IFFMSP"
#define IFFLIB_EPS              "IFFEPS"
#define IFFLIB_IMG              "IFFIMG"
#define IFFLIB_TGA              "IFFTGA"
#define IFFLIB_BMP              "IFFBMP"
#define IFFLIB_GIF              "IFFGIF"
#define IFFLIB_FLAT             "IFFFLAT"
#define IFFLIB_RAS              "IFFRAS"
#define IFFLIB_APOLLO           "IFFAP"
#define IFFLIB_JPEG             "IFFJPEG"
#define IFFLIB_PICT		"IFFPICT"
#define IFFLIB_KODAK		"IFFKODAK"
#else
#define IFFLIB_HALOCUT		((pVOID)HifflHCUTAssociate)
#define IFFLIB_HCUT		((pVOID)HifflHCUTAssociate)
#define IFFLIB_PCX		((pVOID)HifflPCXAssociate)
#define IFFLIB_TIFF		((pVOID)HifflTIFFAssociate)
#define IFFLIB_MSP		((pVOID)HifflMSPAssociate)
#define IFFLIB_EPS		((pVOID)HifflEPSAssociate)
#define IFFLIB_IMG		((pVOID)HifflIMGAssociate)
#define IFFLIB_TGA		((pVOID)HifflTGAAssociate)
#define IFFLIB_BMP		((pVOID)HifflBMPAssociate)
#define IFFLIB_GIF		((pVOID)HifflGIFAssociate)
#define IFFLIB_FLAT		((pVOID)HifflFLATAssociate)
#define IFFLIB_RAS		((pVOID)HifflRASAssociate)
#define IFFLIB_APOLLO		((pVOID)HifflAPOLLOAssociate)
#define IFFLIB_JPEG		((pVOID)HifflJPEGAssociate)
#define IFFLIB_PICT		((pVOID)HifflPICTAssociate)
#define IFFLIB_KODAK		((pVOID)HifflKODAKAssociate)
#endif

#define IFF_MAXHANDLES	4		/* max number of open files */


/* -----------------------------------------------------------------------
  Structures
------------------------------------------------------------------------ */
/*------------------------------------------------------------------------
| The File Parameter Block
|-----------------------------------------------Tue Jun 04 09:17:46 1991--*/
typedef struct FileParamBlk
{
    pVOID	    Library;		    /* library association  */
    int             Width;                  /* Width of image in pixels */
    int             Height;                 /* Height of image in pixels */
    IFFCLASS        ImageClass;             /* image class */
    int             Bits;                   /* Number of bits per sample */
    IFFCOMPRESSION  Compression;            /* defined above */
    IFFSEQUENCE     Sequence;               /* read/write sequence */
    int             hIff;                   /* IFF internal Handle */
} IFF_FPB,  * pIFF_FPB;

typedef IFF_FPB  *  * ppIFF_FPB;

#ifdef WIN32
#define HILAPI __cdecl
#else
#define HILAPI ITEXCALL
#endif
/*------------------------------------------------------------------------
| IFF function prototypes
|-----------------------------------------------Fri Apr 05 09:47:26 1991--*/
IFFERROR HILAPI HifflOpen(pIFF_FPB FPB, pSTRING FileName, IFFMODE Mode);
IFFERROR HILAPI HifflClose(pIFF_FPB FPB);
IFFERROR HILAPI HifflRead(pIFF_FPB FPB, pSTRING Buffer, int NumLines);
IFFERROR HILAPI HifflWrite(pIFF_FPB FPB, pSTRING Buffer, int NumLines);
IFFERROR HILAPI HifflSeek(pIFF_FPB FPB, int Line);
IFFERROR HILAPI HifflControl(pIFF_FPB FPB, IFFCMD Command, short sParam, long lParam, pVOID pParam);
pVOID	 HILAPI HifflIdentify(pVOID FileName, int bFile);

typedef int (HILAPI _vopen)(pSTRING, int, int);
typedef int (HILAPI _vclose)(int);
typedef int (HILAPI _vread)(int, pVOID, int);
typedef int (HILAPI _vwrite)(int, pVOID, int);
typedef long (HILAPI _vlseek)(int, long, int);


typedef struct HifflIOFuncs
{
    _vopen  *vopen;
    _vclose *vclose;
    _vread  *vread;
    _vwrite *vwrite;
    _vlseek *vlseek;

    pVOID  userdata;
} IFFIOF,  * LPIFFIOF;

typedef struct HifflMemStruct
{
    long    pos;
    long    alloced;
    long    length;
    pVOID  data;
} IFFIOM,  * LPIFFIOM;

HANDLE	HILAPI	HifflPackOpen(WORD ToBits, WORD ToPad, WORD ToJustify,
		    WORD FromBits, WORD FromPad, WORD FromJustify, WORD Length);
void	HILAPI	HifflPackLine(HANDLE hPack, pVOID To, pVOID From);
void	HILAPI	HifflPackClose(HANDLE hPack);


typedef int IFFINF;
typedef int  * LPIFFINF;
#define IFFINF_FILEFORMAT	0
#define IFFINF_WIDTH		1
#define IFFINF_HEIGHT		2
#define IFFINF_CLASS		3
#define IFFINF_BITSPERPLANE	4
#define IFFINF_COMPRESSION	5
#define IFFINF_SEQUENCE 	6
#define IFFINF_RESOLUTIONX	7
#define IFFINF_RESOLUTIONY	8

IFFERROR HILAPI HifflInfo(pVOID FileName, int bFile, pDWORD lplArray, LPIFFINF lpCmds, WORD Count);

#ifdef HIL_MAC
extern short HifflMacVRefNum;
extern OSErr HifflMacOSErr;
#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */
