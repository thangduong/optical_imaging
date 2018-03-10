/******************************************************************************
 *
 * MODULE   
 *		camsrc.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/camsrc.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:38a $
 *
 * ABSTRACT 
 *	Header file for frame buffer image source.
 *
 * TECHNICAL NOTES 
 *
 * 
 * Copyright (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _CAMSRC_H
#define _CAMSRC_H

#include <ifcstd.h>
#include <dsptype.h>
#include <imgsrc.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CCamImgSrc : public CImgSrc  
{
//member functions
public:
	CCamImgSrc(CICamera *pCamera);
	CCamImgSrc(CICamera *pCamera, WORD wxAoiStart, WORD wyAoiStart, WORD wWidth, WORD wHeight);
	~CCamImgSrc();

	virtual BYTE *GetBufferAddr(DWORD options=0);
	virtual BOOL Create();
	CICamera *GetCamera() const;

private:

protected:

//attributes
public:

private:
	CICamera *m_pCamera;  

};
#endif

#endif //_FBUFSRC_H
