/******************************************************************************
 *
 * MODULE   
 *		IFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/IFrame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:28a $
 *
 * ABSTRACT  
 *		IFC interface of the CIFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_IFRAME_H__970BD352_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_IFRAME_H__970BD352_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <Iobject.h>
#include <ifctyp.h>
#include <module.h>



typedef struct {
	DWORD currentDx;
	DWORD currentDy;
	DWORD maxDx;
	DWORD maxDy;
	DWORD bytesPerPixel;
	DWORD bitsPerPixel;
	IFC_COLOR color;
} FRAME_ATTR;

typedef FRAME_ATTR *LPFRAME_ATTR;

#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CICapMod;

class IFC_EXT_API CIFrame : public CIobject  
{
public:
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	virtual void GetAttr(LPFRAME_ATTR lpAttr);
	virtual BOOL SetFrameIlace (IFC_ILACE interlaced, IFC_FIELD_STATUS fldStatus);
	virtual BOOL SetCurDimension (DWORD curdx, DWORD curdy);
	virtual CIFrame *Create(CIFrame *frame) {return NULL;};
	CIFrame();
	virtual ~CIFrame();

	static void DeleteAllFrames(pCModule mod);

	CICapMod		*m_mod;
	DWORD            m_maxdx; /* For frame indicates space allocated */
	DWORD            m_maxdy;
	DWORD            m_curdx; /* For frame varies as line width varies */
	DWORD            m_curdy;
	IFC_DEPTH       m_depth; // number of bits-per-pixel
	IFC_DEPTH       m_dispDepth;
    IFC_COLOR   	m_color;
	IFC_ILACE       m_interlaced;
	IFC_FIELD_STATUS m_fldStatus;
	DWORD           m_offset;
	DWORD           m_pagestaken; 
	DWORD           m_pagesused;


	CIFrame		*m_next;	// For the main frame list
	CIFrame		*m_seqNext; // For a sequential frame list

};
#endif

#endif // !defined(AFX_IFRAME_H__970BD352_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
