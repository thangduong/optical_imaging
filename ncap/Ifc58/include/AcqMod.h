/******************************************************************************
 *
 * MODULE   
 *		AcqMod.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/AcqMod.h $
 *		$Revision: 1.1 $
 *		$Modtime: 11/21/03 9:29a $
 *
 * ABSTRACT  
 *		IFC interface of the CAcqMod class.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1998 (c) 1998 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#if !defined(AFX_ACQMOD_H__1C94D442_8905_11D1_AE6E_00A0C959E757__INCLUDED_)
#define AFX_ACQMOD_H__1C94D442_8905_11D1_AE6E_00A0C959E757__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define MAX_NUM_CAMERA_MODULES 8

#include <ifcstd.h>
#include <ifcclass.h>
#include <Module.h>
#include <ChildMod.h>
#include <Camera.h>

#if defined __cplusplus && !defined NOIFCLINK
class IFC_EXT_API CAcqMod : public CChildMod  
{
public:
	virtual void ReleaseActiveCamera();
	virtual CICamera * GetActiveCamera();
	CAcqMod();
	virtual ~CAcqMod();

	virtual CICamera * GetCam(DWORD camPortNum);
	CICamera	*m_pCameras[MAX_NUM_CAMERA_MODULES];
	CICamera	*m_ActiveCamera; // when only one camera can be active at once
	OS_sem_t	m_ActiveCameraMutex;
	WORD m_wStartPort;

protected:
	IFC_DECLARE_DYNCREATE(CAcqMod)
};
#endif

#endif // !defined(AFX_ACQMOD_H__1C94D442_8905_11D1_AE6E_00A0C959E757__INCLUDED_)
