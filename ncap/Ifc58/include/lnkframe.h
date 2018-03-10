/******************************************************************************
 *
 * MODULE   
 *		LnkFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/lnkframe.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:41a $
 *
 * ABSTRACT  
 *		IFC interface of the CLinkFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_LNKFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_LNKFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

class IFC_EXT_API CLinkFrame;

#include <PCLink.h>
#include <LnkCam.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CLinkFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CLinkFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CLinkFrame();
	virtual ~CLinkFrame();
	void SetFlex(CPCLink	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset,LNK_IMAGE_GEOMETRY_TYPE geometry);
	virtual CIFrame *Create(CIFrame *frame);

	LNK_IMAGE_GEOMETRY_TYPE m_geometry;
protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CLinkFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CLinkFrame(CLinkFrame *fr);
	friend class CPCLink;
};
#endif

#endif // !defined(AFX_PCLFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
