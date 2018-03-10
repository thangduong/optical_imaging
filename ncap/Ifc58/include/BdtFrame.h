/******************************************************************************
 *
 * MODULE   
 *		BDTFrame.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/BdtFrame.h $
 *		$Revision: 1.1 $
 *		$Modtime: 3/12/02 3:48p $
 *
 * ABSTRACT  
 *		IFC interface of the CBDTFrame class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2000 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_BDTFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
#define AFX_BDTFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <ifcstd.h>
#include <ifcclass.h>
#include <IFrame.h>
#include <IFCTyp.h>

class CBDTFrame;

#include <Bandit2.h>
#include <BDTcam.h>
#include <ddraw.h>
#include <ifcddraw.h>

class IFC_EXT_API CBDTFrame : public CIFrame  
{
public:
	static void DeleteAllFrames(pCModule mod);
	BOOL CreateSeq(pCModule mod,int frameCnt,CBDTFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	virtual BOOL Create(pCModule mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD bytesPerFrame=0);
	BOOL CreateSurface(DWORD numbytes);
	LPDIRECTDRAWSURFACE CreateYCrCbSurface(DWORD numbytes,DWORD &dwPhysicalAddress);
	BOOL CreateRgbSurface(DWORD numbytes);

	CBDTFrame();
	virtual ~CBDTFrame();
	void SetFlex(CBanditII	*mod, DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color, DWORD offset);
	virtual CIFrame *Create(CIFrame *frame);

	int m_frameCnt;
	DWORD m_dwAlignSizeMask;
	LPDIRECTDRAWSURFACE m_pDDAcquireSurf;
	LPDIRECTDRAWSURFACE m_ycrcb422Surface;
	DWORD m_ycrcb422PhysAddr;

	DDOVERLAYFX			m_ovfx;
	DWORD				m_dwColorKey;

	DWORD m_dwPhysicalAddress;
	int m_curSeqNum;

protected:

private:
	static CIFrame *newFrame(pCModule mod,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	static BOOL newSeqFrame(pCModule mod,int frameCnt,CBDTFrame **frames,DWORD dx, DWORD dy, IFC_DEPTH depth, IFC_COLOR color);
	CBDTFrame(CBDTFrame *fr);
	friend class CBanditII;
};

#endif // !defined(AFX_BDTFRAME_H__582D6F6F_E7BC_11D2_B53F_00A0C99ACB20__INCLUDED_)
