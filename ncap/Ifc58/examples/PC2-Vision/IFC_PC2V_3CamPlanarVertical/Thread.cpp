//------------------------------------------------------------------------------
//
//  FILE:           Thread.cpp
//
//  BIRTH DATE:     December 2002
//
//  LANGUAGE:       C++
//
//  LIBRARY:        -MFC (Visual C++ V6.0)
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
// Implement an MFC based thread
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Thread.h"


//------------------------------------------
//              Constructor
//------------------------------------------
CThread::CThread()
{

    // Manual reset Event used to terminates the thread
    m_pEvtThreadActive = new CEvent(FALSE, TRUE, NULL, NULL);
    m_pEvtThreadActive->SetEvent();

    // Manual reset Event used to wake-up the thread
    m_pEvtWakeUpThread = new CEvent();
    m_pEvtWakeUpThread->ResetEvent();

    // Start thread and pass "this" parameter
    m_pTheThread = AfxBeginThread (TheThreadFunc, this);

    // Prevent MFC from deleting the thread, we will do it ourself in the destructor

    m_pTheThread->m_bAutoDelete = FALSE;

    // User's information not yet defined

    m_pUserCallback = NULL;
    m_pUserContext = NULL;

    // Internal lock preventing multiple awakenings

    m_bThreadBusy = FALSE;

}



//------------------------------------------
//              Destructor
//------------------------------------------
CThread::~CThread(void)
{
DWORD dwRetry;
DWORD dwExitCode;


    // Terminate the thread

    m_pEvtThreadActive->ResetEvent();              // Used to terminate the thread

    dwRetry = 10;       // Wait (a limited time) for the thread to terminate and delete it
    while (dwRetry > 0)
    {
        ::GetExitCodeThread(m_pTheThread->m_hThread, &dwExitCode);
        if (dwExitCode == 0)
        {
            delete m_pTheThread;
            m_pTheThread = NULL;
            break;
        }
        else
        {
            Sleep(300);
            dwRetry--;
        }
    }
    if (dwRetry == 0)
    {
        AfxMessageBox(_T("The CThread did not terminate normally !!!"));
        delete m_pTheThread;
        m_pTheThread = NULL;
    }

    // Release the sync objects related to the Display thread

    delete m_pEvtThreadActive;
    delete m_pEvtWakeUpThread;

}




//------------------------------------------
//              SetPriority
//------------------------------------------
// Call this to register a callback function
// and it's passed parameter.
//------------------------------------------
BOOL CThread::SetPriority(int iNewPriority)
{

    return (m_pTheThread->SetThreadPriority(iNewPriority));

}


//------------------------------------------
//              CallThis
//------------------------------------------
// Call this to register a callback function
// and it's passed parameter.
//------------------------------------------
void CThread::CallThis(void (*CallbackFunction)(void *pContext))
{

    m_pUserCallback = CallbackFunction;

}


//------------------------------------------
//              AwakeThread
//------------------------------------------
// Call this to awake the thread an be called
//------------------------------------------
BOOL CThread::AwakeThread(void *pTheContext)
{

    if (m_bThreadBusy)
    {
        return FALSE;
    }

    m_pUserContext = pTheContext;
    m_bThreadBusy = TRUE;

    m_pEvtWakeUpThread->SetEvent();

    return TRUE;

}




//------------------------------------------
//          TheThreadFunc
//------------------------------------------
// Thread's Main Working Function
//------------------------------------------
UINT CThread::TheThreadFunc(LPVOID pThreadFuncParam)
{
CThread *pMyClass;


    //------------------------------------------
    // As a Static fct, I have no access to my class's members,
    // so I need a ptr to it.

    pMyClass = (CThread *)pThreadFuncParam;

    //------------------------------------------
    // Begin the main working loop

    while (pMyClass->m_pEvtThreadActive->Lock(0))
    {
        // Loop until owner awake me...

        if (pMyClass->m_pEvtWakeUpThread->Lock(100))
        {
            if (pMyClass->m_pUserCallback)
            {
                pMyClass->m_pUserCallback(pMyClass->m_pUserContext);
                pMyClass->m_pUserContext = NULL;
                pMyClass->m_pEvtWakeUpThread->ResetEvent();
                pMyClass->m_bThreadBusy = FALSE;          // Callback function has returned
            }
        }

    }  // while thread active

    return 0;               // This thread will now terminate (after this return)
}
