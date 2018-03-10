/******************************************************************************
 *
 * MODULE   
 *		PCVFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCVFrame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:43a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCVFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCVFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
#define AFX_PCVFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>
#include <PCVision.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CPCVFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPCVFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CPCVFrame();
	virtual ~CPCVFrame();
	void SetFlex(CPCVision	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);


protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPCVFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPCVFrame(CPCVFrame *fr);
	friend class CPCVision;
};
#endif

#endif // !defined(AFX_PCVFRAME_H__970BD353_AF79_11D1_AE7A_00A0C959E757__INCLUDED_)
