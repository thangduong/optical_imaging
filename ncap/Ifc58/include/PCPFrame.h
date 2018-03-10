/******************************************************************************
 *
 * MODULE   
 *		PCPFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCPFrame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:43a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCPFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCPFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCPFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>
#include <Pcplus.h>
#include <PCPcam.h>

#if defined __cplusplus && !defined NOIFCLINK

class CPCVisionPlus;

class IFC_EXT_API CPCPFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPCPFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth,  IFC_COLOR color, DWORD bytesPerFrame=0);
	CPCPFrame();
	virtual ~CPCPFrame();
	void SetFlex(CPCVisionPlus	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);
protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPCPFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPCPFrame(CPCPFrame *fr);
	friend class CPCVisionPlus;
};

#endif

#endif // !defined(AFX_PCPFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
