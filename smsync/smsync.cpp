// smsync.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "smsync.h"
#include "CSmsyncDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmsyncApp

BEGIN_MESSAGE_MAP(CSmsyncApp, CWinApp)
	//{{AFX_MSG_MAP(CSmsyncApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSmsyncApp construction

CSmsyncApp::CSmsyncApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSmsyncApp object

CSmsyncApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSmsyncApp initialization

BOOL CSmsyncApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	mydlg = new CSmsyncDlg;
	m_pMainWnd = mydlg;
	/*int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
*/
	((CSmsyncDlg*)m_pMainWnd)->Create(IDD_SMSYNC_DIALOG);
	m_pMainWnd->ShowWindow(SW_NORMAL);
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return true;
}

int CSmsyncApp::Run() 
{
	// TODO: Add your specialized code here and/or call the base class

	MSG msg;
	bool bDone = false;
	while (!bDone) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			} else {
				TranslateMessage(&msg);
				DispatchMessage(&msg); 
			}
		}
		if ((!bDone) && m_pMainWnd)
			((CSmsyncDlg*)m_pMainWnd)->ProcessAdcData();
	}

	return ExitInstance(); //CWinApp::Run();
}
/*
	short status;
	long curCount;
	long curIndex;
	MccAdcStreamType* pMccAdcStream = (MccAdcStreamType*)lpParameter;
	SetEvent(pMccAdcStream->hInThreadFunc);
//	printf("in thread func...\n");

	long lLastIndex = 0;
	long expectedSamplingRate = pMccAdcStream->lSamplingRate;
	long msSleepTime = 1000;		// sleep time in ms (1 second by default because we allocate 5 sec of data)

	// allocate 5 seconds of data!
	pMccAdcStream->lNumPoints = (pMccAdcStream->iHighChan - pMccAdcStream->iLowChan + 1) * (pMccAdcStream->lSamplingRate * 5);
	pMccAdcStream->hWinBuff = cbWinBufAlloc(pMccAdcStream->lNumPoints);


//	printf("waiting for event to start thread...\n");
	WaitForSingleObject(pMccAdcStream->hStreamThreadShouldStart, INFINITE);
	cbAInScan(pMccAdcStream->iBoardNum, pMccAdcStream->iLowChan, pMccAdcStream->iHighChan, pMccAdcStream->lNumPoints, 
		&(pMccAdcStream->lSamplingRate), pMccAdcStream->iRange, pMccAdcStream->hWinBuff, 
		BACKGROUND | CONTINUOUS);
	SetEvent(pMccAdcStream->hStreamThreadStarted);
//	printf("thread started...\n");

//	printf("calling init\n");

	MccInitAdfHdr(&(pMccAdcStream->OutFileHdr),
		pMccAdcStream->iBoardNum, pMccAdcStream->lSamplingRate, pMccAdcStream->iLowChan, pMccAdcStream->iHighChan, 
		pMccAdcStream->iRange, pMccAdcStream->nBits, pMccAdcStream->dRangeLow, pMccAdcStream->dRangeHigh);


	// open the ADF file and write the header to it!
	pMccAdcStream->fp = fopen(pMccAdcStream->filename, "wb");
	if (pMccAdcStream->fp == NULL)
		printf("file poitner is null. what's your problem!\n");
//	printf("filename = %s\n", pMccAdcStream->filename);
	fwrite(&(pMccAdcStream->OutFileHdr), 1, sizeof(pMccAdcStream->OutFileHdr), pMccAdcStream->fp);

//	printf("sampling rate = %d\n", pMccAdcStream->lSamplingRate);	
	msSleepTime = pMccAdcStream->lSamplingRate * msSleepTime / expectedSamplingRate;

	unsigned long ulExpectedPointsNew = (pMccAdcStream->iHighChan - pMccAdcStream->iLowChan + 1)*(msSleepTime * pMccAdcStream->lSamplingRate) / 1000;
//	printf("ulExpectedPointsNew = %d\n", ulExpectedPointsNew);

	unsigned short* temp = (unsigned short*)(pMccAdcStream->hWinBuff);
	unsigned long ulPointsNew = 0;
	unsigned long ulSampsDeviation = 0;			// number of samples deviated from the expected!
	pMccAdcStream->ulPointsWritten = 0;
	pMccAdcStream->ulNumCycles = 0;
//	printf("entering loop...");
	while (!pMccAdcStream->bStreamThreadShouldQuit)
	{
		Sleep(msSleepTime); 
		cbGetStatus(pMccAdcStream->iBoardNum, &status, &curCount, &curIndex, AIFUNCTION);

		if (curIndex == -1)
			continue;

		// copy data from lLastIndex to curIndex
		if (lLastIndex < curIndex)
		{
			// copy data from lLastIndex to and including curIndex
			fwrite(&temp[lLastIndex], 2, curIndex - lLastIndex, pMccAdcStream->fp);
			ulPointsNew = curIndex - lLastIndex;
			pMccAdcStream->ulPointsWritten += ulPointsNew;
		}
		else
		{
			// copy data from lLastIndex to and including end of buffer
			fwrite(&temp[lLastIndex], 2, pMccAdcStream->lNumPoints - lLastIndex, pMccAdcStream->fp);
			ulPointsNew = pMccAdcStream->lNumPoints - lLastIndex;
	
			// copy data from start of buffer to and including curIndex
			fwrite(temp, 2, curIndex, pMccAdcStream->fp);
			ulPointsNew += curIndex;

			pMccAdcStream->ulPointsWritten += ulPointsNew;
		}


		ulSampsDeviation = abs(ulPointsNew - ulExpectedPointsNew) / (pMccAdcStream->iHighChan - pMccAdcStream->iLowChan + 1);

//		printf("lLastIndex = %d, curIndex = %d, points collected = %d\n", lLastIndex, curIndex,
//			pMccAdcStream->ulPointsWritten);
//		printf("new = %d exp = %d dev=  %d\n",
//			ulPointsNew, ulExpectedPointsNew, ulSampsDeviation);
		if (ulSampsDeviation > (unsigned long)((pMccAdcStream->lSamplingRate * msSleepTime / 1000)))
		{
			printf("WARNING: deviation exceeds half cycles on cycle %d\n",
				pMccAdcStream->ulNumCycles);
		}
		lLastIndex = curIndex;
		pMccAdcStream->ulNumCycles++;
	}

	fclose(pMccAdcStream->fp);
//	printf("all done.  stopping now\n");
	cbStopBackground(pMccAdcStream->iBoardNum, AIFUNCTION);
	ResetEvent(pMccAdcStream->hStreamThreadStarted);
	SetEvent(pMccAdcStream->hStreamThreadDone);
	ResetEvent(pMccAdcStream->hInThreadFunc);
	return 0;
*/

int CSmsyncApp::ExitInstance() 
{
	delete mydlg;
	return CWinApp::ExitInstance();
}
