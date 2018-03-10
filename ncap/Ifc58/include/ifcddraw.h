/******************************************************************************
 * 
 * MODULE   
 *		ifcddraw.h
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/include/ifcddraw.h $
 *		$Revision: 1.1 $
 *		$Modtime: 8/29/02 10:16a $
 *
 * ABSTRACT 
 *	Header file for Direct Draw support manager.
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright (c) 1998-2001 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/

#ifndef _IFCDDRAW_H_
#define _IFCDDRAW_H_
#ifdef WIN32 

#include <ddraw.h>
#include <ifcstd.h>
#include <dsptype.h>
#include <Iobject.h>

typedef enum {
	PRIMARY_SURF_STD,
	PRIMARY_SURF_LEFT


} IFC_PRIMARY_SURF_TYPE;


//{secret}
class IFC_EXT_API CIfcDDraw : public CIobject  
{
friend BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD reason,LPVOID reserved);
//methods
public: 
	CIfcDDraw();
	~CIfcDDraw();
	
	LPDIRECTDRAW Connect();
	void Disconnect();
	LPDIRECTDRAW GetDDrawObject();
	LPDIRECTDRAWSURFACE GetPrimarySurface();
	HPALETTE CreateNewPalette(HDC hdc, pBYTE red, pBYTE green, pBYTE blue);
	BOOL UseFlatDriver();
	DWORD GetVgaAddress();
	DDSURFACEDESC *GetPrimarySurfDesc();
	DDCAPS *GetDDrawCaps();
	DWORD DetectVgaAddress(LPDIRECTDRAWSURFACE pDDSurface);
	BOOL SetActivePrimary(IFC_PRIMARY_SURF_TYPE primaryType);
	IFC_PRIMARY_SURF_TYPE GetActivePrimary() { return m_activePrimaryType;};

	LPDIRECTDRAWCLIPPER GetPrimSurfClipper();

private:
	LPDIRECTDRAW Create();
	void Destroy();
	BOOL CreatePrimarySurface();
	BOOL DetectVgaMapping();
	BOOL CreatePrimSurfClipper();

//attributes
private:
	HINSTANCE			m_hDDrawLib;		//handle to DDRAW.DLL
	LPDIRECTDRAW		m_pDDObject;		//ddraw object
	LPDIRECTDRAWSURFACE m_pDDSPrimary;		//DirectDraw primary surface
	DDSURFACEDESC	    m_DDSPrimaryDesc;   //DirectDraw primary surface desciption struct
	DDCAPS				m_DDCaps;
	LPDIRECTDRAWCLIPPER m_pDDrawClipper;	//primary surface clipper

	BOOL				m_bUseFlatDriver ;	//flag to store information about flat adressing
	DWORD				m_dwLinearBuffVgaAddr;	//address of vga buffer
	int					m_iConnectionCount;	//keeps current number of DDraw users
	IFC_PRIMARY_SURF_TYPE m_activePrimaryType;

	LPDIRECTDRAWSURFACE m_pDDSPrimaryLeft;		//DirectDraw primary surface
	DDSURFACEDESC	    m_DDSPrimaryLeftDesc;   //DirectDraw primary surface desciption struct

};


inline BOOL IFC_EXT_API UpdateDescAndLockSurface(LPDIRECTDRAWSURFACE pDDSurfToLock, LPDDSURFACEDESC  pDDSurfaceDescr);

typedef CIfcDDraw *PCIfcDDraw;

PCIfcDDraw IFC_EXT_API IfxGetGlobalDDrawObject();

//extern CIfcDDraw g_DDrawObject;



#endif //WIN32
#endif // _CDDRAW_H_