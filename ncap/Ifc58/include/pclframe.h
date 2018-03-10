/******************************************************************************
 *
 * MODULE   
 *		PCLFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pclframe.h $
 *		$Revision: 1.1 $
 *		$Modtime: 1/28/00 2:50p $
 *
 * ABSTRACT  
 *		IFC interface of the CPCLFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCLFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_PCLFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

class IFC_EXT_API CPCLFrame;

#include <PCLine.h>
#include <PCLcam.h>

#ifdef __cplusplus
class IFC_EXT_API CPCLFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPCLFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CPCLFrame();
	virtual ~CPCLFrame();
	void SetFlex(CPCLine	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset,PCL_IMAGE_GEOMETRY_TYPE geometry);
	virtual CIFrame *Create(CIFrame *frame);

	PCL_IMAGE_GEOMETRY_TYPE m_geometry;
protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPCLFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPCLFrame(CPCLFrame *fr);
	friend class CPCLine;
};
#endif

#endif // !defined(AFX_PCLFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
