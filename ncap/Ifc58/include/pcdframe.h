/******************************************************************************
 *
 * MODULE   
 *		PCDFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pcdframe.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:40a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCDFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCDFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_PCDFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>
#include <PCDig.h>
#include <PCDcam.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCDFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPCDFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CPCDFrame();
	virtual ~CPCDFrame();
	void SetFlex(CPCDig	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset,PCD_IMAGE_GEOMETRY_TYPE geometry);
	virtual CIFrame *Create(CIFrame *frame);

	PCD_IMAGE_GEOMETRY_TYPE m_geometry;
protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPCDFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPCDFrame(CPCDFrame *fr);
	friend class CPCDig;
};
#endif

#endif // !defined(AFX_PCDFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
