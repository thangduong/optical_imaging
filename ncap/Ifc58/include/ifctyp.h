/******************************************************************************
 *
 * MODULE   
 *		IFCTYP.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifctyp.h $
 *		$Revision: 1.1 $
 *		$Modtime: 7/29/99 2:54p $
 *
 * ABSTRACT  
 *		Misc IFC types interface 
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(_IFCTYP__INCLUDED_)
#define _IFCTYP__INCLUDED_

#include <ifcstd.h>



#define INQUIRE -1



typedef enum {
	IFC_PIX8        = 8,
	IFC_PIX10       = 10,
	IFC_PIX12       = 12,
	IFC_PIX16       = 16,
	IFC_PIX24       = 24,
	IFC_PIX32       = 32
} IFC_DEPTH;

typedef enum {
	IFC_MONO,
	IFC_RED,
	IFC_GREEN,
	IFC_BLUE,
	IFC_RGB,
	IFC_RGB_PACK24,
	IFC_MONO_WORD_LO,
	IFC_MONO_WORD_HI,
	IFC_RGB_PLANAR,
	IFC_aRGB_PLANAR,
	IFC_YCRCB,
	IFC_YCRCBMONO,
	IFC_NUM_COLOR_MODES	// Always keep last
} IFC_COLOR;

typedef void *HIFCGRAB;


/* Field status defines */
typedef enum {
	IFC_EVEN_FIELD,                       /* Field status is even */
	IFC_ODD_FIELD,                        /* Field status is odd */
	IFC_NEXT_FIELD                       /* Next field acquisition */
} IFC_FIELD_STATUS;

/* Scan Mode status defines */
typedef enum {
	IFC_NILACED,    /* Scan Mode is No interlace */
	IFC_ILACED		/* Scan Mode is Interlaced */
} IFC_ILACE;	





#endif
