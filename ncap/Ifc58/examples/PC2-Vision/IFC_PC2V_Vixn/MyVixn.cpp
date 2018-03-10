//------------------------------------------------------------------------------
//
//  FILE:           MyVixn.cpp
//
//  BIRTH DATE:     December 2003
//
//  LANGUAGE:       C++
//
//  LIBRARY:        none
//
//  OS:             Windows 2000 (Win32)
//
//  PLATFORM:       Intel Pentium (IA-32)
//
//  COMPANY:        Coreco Imaging
//
//------------------------------------------------------------------------------
// Implement a class derived from CVixn
//------------------------------------------------------------------------------

#include "PCVision2.h"                      // IFC related
#include "vixni.h"                          // IFC related
#include "MyVixn.h"                         // My Vixn derived class


//------------------------------------------
//              Constructor
//------------------------------------------
CMyVixn::CMyVixn(CICapMod *mod)
: CVixn(mod, P2V_INTR_EOFRM)
{

    m_IntrCount = 0;

}



//------------------------------------------
//              Destructor
//------------------------------------------
CMyVixn::~CMyVixn(void)
{

}



//------------------------------------------
//              VixnMain
//------------------------------------------
// This function is called on an EndOfFrame
//  interrupt.
//------------------------------------------
BOOL CMyVixn::VixnMain(void)
{

    m_LastIntrPeriod = m_IntrPeriod;    // Keep last to compute jitter
    m_IntrPeriod = ReadTimeMicro();     // Get current frame period

    m_IntrCount++;                      // Interrupt Counter

    return TRUE;

}


//------------------------------------------
//        GetFrameInterruptCount
//------------------------------------------
DWORD CMyVixn::GetFrameInterruptCount(void)
{

    return VIXNVAL(m_IntrCount);

}


//------------------------------------------
//        ResetFrameInterruptCount
//------------------------------------------
void CMyVixn::ResetFrameInterruptCount(void)
{

    m_IntrCount = 0;

}


//------------------------------------------
//        GetFrameInterruptPeriod
//------------------------------------------
DWORD CMyVixn::GetFrameInterruptPeriod(void)
{

    return VIXNVAL(m_IntrPeriod);

}



//------------------------------------------
//        GetFrameInterruptLastPeriod
//------------------------------------------
DWORD CMyVixn::GetFrameInterruptLastPeriod(void)
{

    return VIXNVAL(m_LastIntrPeriod);

}


//------------------------------------------
//        ResetFrameInterruptLastPeriod
//------------------------------------------
void CMyVixn::ResetFrameInterruptLastPeriod(void)
{

    m_LastIntrPeriod = 0;

}

