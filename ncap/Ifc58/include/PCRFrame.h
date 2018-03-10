/******************************************************************************
 *
 * MODULE   
 *		PCRFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/PCRFrame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:40a $
 *
 * ABSTRACT  
 *		IFC interface of the CPCRFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_PCRFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_PCRFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>
#include <PcRgb.h>
#include <PCRcam.h>

#if defined __cplusplus && !defined NOIFCLINK

class IFC_EXT_API CPCRFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CPCRFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	CPCRFrame();
	virtual ~CPCRFrame();
	void SetFlex(CPcRgb	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset,PCR_MULTITAP_MODE_TYPE TapMode);
	virtual CIFrame *Create(CIFrame *frame);

	PCR_MULTITAP_MODE_TYPE m_TapMode;
protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CPCRFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CPCRFrame(CPCRFrame *fr);
	friend class CPcRgb;
};

#endif


#endif // !defined(AFX_PCRFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
