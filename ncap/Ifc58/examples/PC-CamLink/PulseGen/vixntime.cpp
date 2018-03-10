/******************************************************************************
 *
 * MODULE
 *    VixnTime.cpp
 *
 * REVISION INFORMATION
 *    $Logfile: /ifc/examples/CamLink/PulseGen/vixntime.cpp $
 *    $Revision: 1.1 $
 *    $Modtime: 2/21/03 11:30a $
 *
 * ABSTRACT
 *    PC-CamLink Example Program
 *
 * TECHNICAL NOTES
 *
 *
 * Copyright (c) 1999 Imaging Technology, Inc.  All rights reserved.
 *
 ******************************************************************************/
// VixnTime.cpp: implementation of the CVixnTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VixnTime.h"
#include <ifc.h>
#include <PcLink.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVixnTimer::CVixnTimer(PCParentMod mod,double frequency,DWORD microSecondsHigh,DWORD cycleCount)
: CVixn(mod,frequency,cycleCount)
{

	// Initialize Vixn Variables
	m_intrCount = 0;
	m_deltaTime = 0;
	m_ScheduleCount = 0;
	m_microSecondsHigh = microSecondsHigh;
	WriteReg(LNK_OUTPORT_32,0);
}

CVixnTimer::~CVixnTimer()
{
	// Remove as necessary Vixn variables

}

BOOL CVixnTimer::VixnMain()
{
	// Virtual ISR Extension content
	// Note the following code will on most current machines execute
	// within 20 microseconds of the specified interrupt
	// So a Vixn applet can be used to do something which must
	// happen during a vertical blank
	m_deltaTime = ReadTimeMicro();

	// Set the output high, begin the pulse
	WriteReg(LNK_OUTPORT_32,1);

	// Schedule the function SetInactive to be invoked m_microSecondsHigh microseconds later
	Schedule((PFVIXNSCHED)SetInactive,m_microSecondsHigh);

	m_intrCount++;
	return TRUE;
}

BOOL CVixnTimer::SetInactive(void)
{
	// Set the output low, end the pulse
	WriteReg(LNK_OUTPORT_32,0);
	m_ScheduleCount++;
	return TRUE;
}