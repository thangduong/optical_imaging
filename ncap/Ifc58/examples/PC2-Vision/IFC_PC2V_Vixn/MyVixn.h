//------------------------------------------------------------------------------
//
//  FILE:           MyVixn.h
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

#ifndef _MYVIXN_H_
#define _MYVIXN_H_



class CMyVixn : public CVixn
{

public:

    CMyVixn(CICapMod *mod);
    ~CMyVixn(void);

    virtual BOOL VixnMain(void);

    DWORD GetFrameInterruptCount(void);
    void ResetFrameInterruptCount(void);

    DWORD GetFrameInterruptPeriod(void);
    DWORD GetFrameInterruptLastPeriod(void);
    void ResetFrameInterruptLastPeriod(void);

private:

    CVixnEle m_IntrCount;
    CVixnEle m_IntrPeriod;
    CVixnEle m_LastIntrPeriod;

};


#endif	// _MYVIXN_H_


