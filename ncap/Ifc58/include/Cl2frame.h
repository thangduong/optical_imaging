/******************************************************************************
 *
 * MODULE   
 *		CL2Frame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/Cl2frame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 5/02/03 3:27p $
 *
 * ABSTRACT  
 *		IFC interface of the CPC2LinkFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_CL2FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_CL2FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

class IFC_EXT_API CPC2LinkFrame;

#include <PC2Link.h>
#include <CL2Cam.h>

#ifdef __cplusplus
class IFC_EXT_API CPC2LinkFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPC2LinkFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CPC2LinkFrame();
	virtual ~CPC2LinkFrame();
	void SetFlex(CPC2Link	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);

	CL2_IMAGE_GEOMETRY_TYPE m_geometry;

protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPC2LinkFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPC2LinkFrame(CPC2LinkFrame *fr);
	friend class CPC2Link;
};
#endif

#endif // !defined(AFX_CL2FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
