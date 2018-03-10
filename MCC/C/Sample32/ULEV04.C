/*ULEV04.C****************************************************************

File:                         ULEV04.C

Library Call Demonstrated:    cbEnableEvent & cbDisableEvent, 
                              ON_SCAN_ERROR and ON_END_OF_AO_SCAN event handling

Purpose:                      Enables and binds event handlers or callback
                              functions to several event conditions.

Demonstration:                Shows how to enable and respond to events.
                              Also, demonstrates the use of the UserData parameter
                              in the cbEnableEvent and the event handler

Other Library Calls:          cbAOutScan
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must support cbAOutScan and cbEnableEvent


Copyright (c) 2001-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "..\cbw.h"



#define BOARDNUM     0
#define CHANNEL      0
#define PRECOUNT     0
#define TOTALCOUNT   10000
#define RATE         1000
#define PI           3.1415926


/* 
   Structure holding scan information to 
   be shared between event handler and main thread of execution.

   This will be passed to the event handlers via the UserData parameter.
*/
typedef struct {
   BOOL Status;
   int BoardNum;
   int LowChan;
   int HighChan;
   int TotalCount;
   int PreCount;
   int Rate;
   int Range;
   unsigned short* DataBuffer;
   int Options;
} TDaq;

int row, col;           // where to put the output

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);
void DoSomethingElse(TDaq* pdaq);

/* Prototype for the event handlers */
void __stdcall MyCallback(int bd, unsigned EventType, unsigned EventData, void* UserData);
void __stdcall OnErrCallback(int bd, unsigned EventType, unsigned EventData, void* UserData);



void main ()
{
    /* Variable Declarations */
   TDaq daq = { IDLE, BOARDNUM, CHANNEL, CHANNEL, TOTALCOUNT,
                PRECOUNT, RATE, BIP5VOLTS, NULL, BACKGROUND };
   int ULStat = 0;
   unsigned EventType = 0;
   unsigned EventSize = 0;
   float volts = 0.0f;
   int i=0; 
   /* 
     Initiate error handling
     Parameters:
          PRINTALL :all warnings and errors encountered will be printed
          DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);
    
    /* set up the display screen */
   ClearScreen();
   printf ("Demonstration of cbEnableEvent with cbAOutScan with ON_SCAN_ERROR\n");
   printf ("and ON_END_OF_AO_SCAN events.\n\n");

   printf ("Completion of the scan, and scan errors both generate events that \n");
   printf ("call the appropriate event handler.\n\n");
   printf ("Meanwhile, we'll DoSomethingElse until we get a keypress or the scan completes.\n\n");
   
   printf ("Status: ");
   GetTextCursor (&col, &row);
   printf ("IDLE\n");
    
   
    /*
      Install event handlers for event conditions.
   
      Parameters:
         BoardNum                       : The board for which the EventType conditions
                                             will generate an event.
         EventType = ON_END_OF_AO_SCAN  : Generate an event upon scan completion or end
         EventSize                      : Not used for ON_END_OF_AO_SCAN
         MyCallback                     : Call MyCallback upon generation of an event.
         &daq                           :the address of user data that will be passed into
                                             MyCallback function. 
    */
    EventType = ON_END_OF_AO_SCAN;
    EventSize = 0;
    ULStat = cbEnableEvent(daq.BoardNum, EventType, EventSize, MyCallback, &daq);
    if (ULStat!=NOERRORS)
      {
       printf("Failed to setup event handlers.\n\n");
      cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);
      return ;
      }

    EventType = ON_SCAN_ERROR;
    EventSize = 0;
    ULStat = cbEnableEvent(daq.BoardNum, EventType, EventSize, OnErrCallback, &daq);
    if (ULStat!=NOERRORS)
      {
      printf("Failed to setup event handlers.\n\n");
      cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);
      return ;
      }
    

    
    /* Allocate the data buffer*/
    daq.DataBuffer = (unsigned short*)cbWinBufAlloc(daq.TotalCount);

    /* Calculate waveform and store in buffer */
    for(i=0; i<daq.TotalCount; ++i)          
      {
      volts = 4.995f* (float)sin(2*PI*i/daq.TotalCount);
      cbFromEngUnits(daq.BoardNum, daq.Range, volts, daq.DataBuffer + i);
      }

   /* Start the scan..*/
    daq.Status = RUNNING;
    cbAOutScan(daq.BoardNum, daq.HighChan, daq.LowChan, daq.TotalCount, 
                        &(daq.Rate), daq.Range, (HGLOBAL)daq.DataBuffer, daq.Options);
    
    /* if started, DoSomethingElse until scan completes or the user strikes a key */
    if (ULStat==NOERRORS)
      {
      MoveCursor(col, row);
      printf("RUNNING\n");
      DoSomethingElse(&daq);
      }

    daq.Status = IDLE;
    
    /* Be sure scan has been stopped before attempting to cbDisableEvent 
       Parameters:
       BoardNum    : the number used by CB.CFG to describe this board 
       FunctionType: D/A operation (AOFUNCTIOM)*/  
    ULStat = cbStopBackground (daq.BoardNum,AOFUNCTION);

    /* Free the data buffer */
    cbWinBufFree((HGLOBAL)daq.DataBuffer);
    daq.DataBuffer = NULL;

    /*
      Disconnect and uninstall event handlers
      We can disable all the events at once, and disabling events
      that were never enabled is harmless
  
      Parameters:
         BoardNum          : board for which scan conditions produce events.
         ALL_EVENT_TYPES   : disalbe all events
    */
    cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);
    
    if (ULStat==NOERRORS)
       printf("\n\nEvent handling completed.");
    else
        printf("Failed to setup event handling.");
}



/***************************************************************************
*
* Name:      MyCallback
*
*   This gets called for the ON_END_OF_AO_SCAN event. For this event types, 
*   the EventData supplied corresponds to the number of samples output since 
*   the start of the scan. 

*   Upon ON_END_OF_AO_SCAN, we'll cleanup and reset the Status for the scan. 
*
*   Note that the user data that was passed in to cbEnableEvent points to 
*   TDaq structure holding the scan specific data.
*
****************************************************************************/
void __stdcall MyCallback(int bd, unsigned EventType, 
                          unsigned SampleCount, void* pUserData)
{
   /* Cast the UserData to the correct data type. */
   TDaq* pDaq = (TDaq*)pUserData;
   
   /* Cleanup the scan...
      Parameters:
         BoardNum    :the number used by CB.CFG to describe this board 
         FunctionType: D/A operation (AOFUNCTIOM)*/  
   cbStopBackground (bd,AOFUNCTION);

   /* Update the status and display */
   MoveCursor(col, row);
   printf("Scan Completed    \n");
   pDaq->Status = IDLE;
}



/***************************************************************************
*
* Name:      OnErrCallback
*
*   This gets called for ON_SCAN_ERROR events. For this event type, the 
*   EventData supplied corresponds to the error code--usually an UNDERRUN
*   for cbAOutScan. 
*
*   We'll abort the scan and shut down when we detect a fatal error.  
*
*   Note that the user data that was passed in to cbEnableEvent points to 
*   TDaq structure holding the scan specific data.
*
****************************************************************************/
void __stdcall OnErrCallback(int Bd, unsigned EventType, unsigned ErrorNo, void* pUserData)
{
   /* If it's fatal, stop everything and post error message. */
   TDaq* pDaq = (TDaq*)pUserData;

   if (ErrorNo == UNDERRUN)
      {
      cbStopBackground(Bd, AOFUNCTION);

      MoveCursor(1, row+3);
      printf("Scan Aborted by FATAL ERROR!\n");

      pDaq->Status = IDLE;
      }
}



/*****************************************************************************
*
*   Name: DoSomethingElse
*
*   Normally, we would do something else more interesting than counting sheep
*   while waiting to be notified about the scan events, but this is only an
*   example so we'll keep it simple.
*
*   This function waits for a keystroke or pDaq->Status == IDLE flag before 
*   returning.
*
*****************************************************************************/
void DoSomethingElse(TDaq* pDaq)
{
   while(!kbhit() && (pDaq->Status==RUNNING))
      Sleep(10);

   if (pDaq->Status==RUNNING)
      {
      MoveCursor(col, row);
      printf("Scan Aborted by User.\n");
      }
}



/***************************************************************************
*
* Name:      ClearScreen
* Arguments: ---
* Returns:   ---
*
* Clears the screen.
*
***************************************************************************/

#define BIOS_VIDEO   0x10

void
ClearScreen (void)
{
	COORD coordOrg = {0, 0};
	DWORD dwWritten = 0;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE != hConsole)
		FillConsoleOutputCharacter(hConsole, ' ', 80 * 50, coordOrg, &dwWritten);

	MoveCursor(0, 0);

   return;
}


/***************************************************************************
*
* Name:      MoveCursor
* Arguments: x,y - screen coordinates of new cursor position
* Returns:   ---
*
* Positions the cursor on screen.
*
***************************************************************************/


void
MoveCursor (int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD coordCursor;
		coordCursor.X = (short)x;
		coordCursor.Y = (short)y;
		SetConsoleCursorPosition(hConsole, coordCursor);
	}

   return;
}


/***************************************************************************
*
* Name:      GetTextCursor
* Arguments: x,y - screen coordinates of new cursor position
* Returns:   *x and *y
*
* Returns the current (text) cursor position.
*
***************************************************************************/

void
GetTextCursor (int *x, int *y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	*x = -1;
	*y = -1;
	if (INVALID_HANDLE_VALUE != hConsole)
	{
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		*x = csbi.dwCursorPosition.X;
		*y = csbi.dwCursorPosition.Y;
	}

   return;
}






