/******************************************************************************
 *
 * MODULE   
 *		IntrEx.cpp
 *
 * REVISION INFORMATION  
 *		$Logfile: /ifc/examples/PCVision/IntrEx/IntrEx.cpp $
 *		$Revision: 1.1 $
 *		$Modtime: 11/23/99 4:07p $
 *
 * ABSTRACT  
 *		IFC Interrupt Example
 *
 * TECHNICAL NOTES 
 *
 *
 * Copyright 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
// IntrEx.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IntrEx.h"
#include "IntrDlg.h"
#include "camsel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntrExApp

BEGIN_MESSAGE_MAP(CIntrExApp, CWinApp)
	//{{AFX_MSG_MAP(CIntrExApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntrExApp construction

CIntrExApp::CIntrExApp()
{


	for(int i=0; i<THREAD_LAST;i++)
		m_ulCounter[i] = 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CIntrExApp object

CIntrExApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CIntrExApp initialization

BOOL CIntrExApp::InitInstance()
{

	// This example accepts command line argument that is a number of the board to 
	// use (in case the multiple boards are present in the system)
	m_iActiveBoard=0;
	if (m_lpCmdLine && m_lpCmdLine[0])
		sscanf(m_lpCmdLine, "%d", &m_iActiveBoard);

	// initialize PCVision hardware
	if(InitalizeIFC() == FALSE)
		return FALSE;


	m_cam = m_pBrdMod->GetCam(0);

	// initialize interrupt objects
	InitializeIfcIntr();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	CIntrExDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// clean-up IFC
	for(int n=0; n<THREAD_LAST;n++) 
		delete m_pIntrObj[n];

	// clean-up hardware
	RemoveIFC();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


BOOL CIntrExApp::InitalizeIFC()
{
	// following code is a standard initialization of the ITI 
	// boards and will appear in all applications using this hardware
	
	//detect number of PCDIG boards in the system		
	
	
	if(!(m_pBrdMod = IfxCreateCaptureModule("ICP", m_iActiveBoard,"pcvtest.txt")))
	{
		m_pBrdMod = IfxCreateCaptureModule("ICP", m_iActiveBoard);
		
		if(!m_pBrdMod)
		{
			::MessageBox(NULL, "Can't find ITI board", "Error", MB_OK | MB_ICONSTOP);
			return FALSE;
		}
		
		m_cam = m_pBrdMod->GetCam(0);
		CCamSel dg(NULL);
		dg.DoModal();
		
	}
	
	CAM_ATTR attr;
	
	m_cam = m_pBrdMod->GetCam(0);
	
	m_cam->GetAttr(&attr);
	m_cam->Grab();
	m_nCurdx = attr.dwWidth;
	m_nCurdy = attr.dwHeight;
	m_iSrcBitDepth = attr.dwBitsPerPixel;
	
	
	return TRUE;
}


void CIntrExApp::RemoveIFC()
{
	if (m_pBrdMod) {
		delete m_pBrdMod;
		m_pBrdMod=NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CIntrExApp parameter structures and interrupt procedures

//define structure used to pass arguments to interrupt procedure
typedef struct {
	unsigned long *pIntCounter;
	// TODO: below add other data that you want to pass to corresponding 
	//       interrupt procedure
	//
	//
}INTERRUPTPROCARGS;

INTERRUPTPROCARGS InterruptProcArgs[THREAD_LAST];

void IfcIntrProcedure(LPVOID Param)
{
	INTERRUPTPROCARGS *pParam;
	pParam = (INTERRUPTPROCARGS*) Param;
	*(pParam->pIntCounter) += 1;
};



BOOL CIntrExApp::InitializeIfcIntr()
{
	int n;

	for(n=0; n<THREAD_LAST; n++)
	{
		InterruptProcArgs[n].pIntCounter = &m_ulCounter[n];
		m_pIntrObj[n] = new CIfcInterrupt(m_pBrdMod,	n, IfcIntrProcedure, &InterruptProcArgs[n], NULL, NULL);
	}

	return TRUE;
}

