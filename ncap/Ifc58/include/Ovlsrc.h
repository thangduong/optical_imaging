/******************************************************************************
 *
 * MODULE   
 *		ovlsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/OVLSRC.H $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:39a $
 *
 * ABSTRACT 
 *	Header file for overlay base class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef	_OVLSRC_H
#define _OVLSRC_H

#include <iobject.h>
#include <ifcstd.h>
#include <dsptype.h>


/////////////////////////////////////////////////////////////////////
//COverlay
//////////////////////////////////////////////////////////////////////
#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API COverlay : public CIobject
{
friend class CImgDibSink;
friend class CSwOverlay;
friend class CHwOverlay;
//member functions
public:
	COverlay(WORD dx, WORD dy);
	virtual ~COverlay();

	virtual BOOL Create();
	virtual IFC_HDC GetOverlayDC();
	virtual void ReleaseOverlayDC(IFC_HDC hDC);
	WORD GetBitsPP() const;
	WORD GetWidth();
	WORD GetHeight();
	virtual DWORD GetMinStretch();
	virtual DWORD GetMaxStretch();
	BOOL LockOverlay();
	BOOL UnlockOverlay();
	OVERLAY_KIND GetKind() { return m_OverlayKind;};

	void Enable(BOOL bEnable); 
	BOOL IsEnabled() const ;

private:
	virtual BOOL MergeOverlay(CImgSink *pSink);
	virtual BOOL CopyMergeOverlay(CImgSrc* pSrc, CImgSink* pSink);
	void SetBitsPP(WORD wBits);


//attributes
public:

private:

protected:
	HANDLE		m_hAccessSemaphore;
	WORD		m_wBitsPP;
	WORD		m_wWidth;
	WORD		m_wHeight;
	OVERLAY_KIND	m_OverlayKind;
	BOOL		m_bEnabled;
};
#endif

typedef COverlay *PCOverlay;

IFC_EXT_API COverlay *IfxCreateOverlay(OVERLAY_KIND Kind,WORD wWidth, WORD wHeight);

#define IFC_DECLARE_DYN_OVERLAY(baseClass) static baseClass *CreateObject(WORD wWidth,	WORD wHeight);

#define IFC_IMPLEMENT_DYN_OVERLAY(deriveClass,baseClass) \
baseClass *deriveClass::CreateObject(WORD wWidth,WORD wHeight) \
{ \
	return new deriveClass(wWidth,wHeight); \
} 

typedef PCOverlay (*pfOverlayCreate)(WORD wWidth, WORD wHeight);

BOOL IFCCALL IfxAddOverlayClass(pfOverlayCreate create,OVERLAY_KIND Kind);
void IFCCALL IfxCloseOverlayFactory(void);

#define IFC_ADD_FACTORY_OVERLAY_CLASS(OverlayClass,kind) \
int _var_##OverlayClass = IfxAddOverlayClass(OverlayClass::CreateObject,(kind));


#endif // #ifndef _OVLSRC_H
