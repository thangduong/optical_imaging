/******************************************************************************
 *
 * MODULE   
 *		PCDFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/pv2frame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 1/07/04 11:33a $
 *
 * ABSTRACT  
 *		IFC interface of the CP2VFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2002 Coreco Imaging , Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_P2VFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_P2VFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

#ifdef __cplusplus
class IFC_EXT_API CP2VFrame;
#endif

#include <PCVision2.h>


#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CP2VFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CP2VFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CP2VFrame();
	virtual ~CP2VFrame();
	void SetFlex(CPCVision2	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);

protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CP2VFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CP2VFrame(CP2VFrame *fr);
	friend class CPCVision2;
};
#endif

#endif // !defined(AFX_P2VFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
