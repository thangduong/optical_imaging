//------------------------------------------------------------------------------
//
//  FILE:           Thread.h
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
//                  St-Laurent, Quebec, Canada
//
//------------------------------------------------------------------------------
// Implement an MFC based thread
//------------------------------------------------------------------------------

#ifndef _THREAD_H_
#define _THREAD_H_


#include "Afxmt.h"                  // Windows MFC for CEvent





class CThread
{

public:

    CThread(void);
    ~CThread(void);

    // Call this to change the priority of the thread
    BOOL SetPriority(int iNewPriority);

    // Call this to register a callback function
    void CallThis(void (*CallbackFunction)(void *pContext));

    // Call this to awake the thread and the callback function will be called
    BOOL AwakeThread(void *pTheContext);

private:

    CWinThread  *m_pTheThread;          // MFC wrapped thread
    CEvent      *m_pEvtWakeUpThread;    // Event used to call the user's callback
    CEvent      *m_pEvtThreadActive;    // Event used to terminates the thread

    BOOL        m_bThreadBusy;          // Callback function has returned

    void (*m_pUserCallback)(void *pContext);    // Ptr 2 user function to call
    void *m_pUserContext;                       // Ptr 2 user context as the callback function parameter

    static UINT TheThreadFunc(LPVOID pThreadFuncParam);

};


#endif	// _THREAD_H_


