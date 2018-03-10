/******************************************************************************
 *
 * MODULE   
 *		x64Frame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/x64frame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 10/10/03 2:11p $
 *
 * ABSTRACT  
 *		IFC interface of the Cx64Frame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2003 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_X64FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_X64FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

class IFC_EXT_API Cx64Frame;

#include <x64.h>
#include <X64Cam.h>

#ifdef __cplusplus
class IFC_EXT_API Cx64Frame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,Cx64Frame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	Cx64Frame();
	virtual ~Cx64Frame();
	void SetFlex(Cx64	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);

	X64_IMAGE_GEOMETRY_TYPE m_geometry;
	CX64Cam *m_cam;

protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,Cx64Frame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	Cx64Frame(Cx64Frame *fr);
	friend class Cx64;
};
#endif

#endif // !defined(AFX_X64FRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
