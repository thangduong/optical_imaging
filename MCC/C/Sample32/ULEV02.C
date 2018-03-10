/*ULEV02.C****************************************************************

File:                         ULEV02.C

Library Call Demonstrated:    cbEnableEvent & cbDisableEvent with  
                              ON_SCAN_ERROR, ON_DATA_AVAILABLE, and 
                              ON_END_OF_AI_SCAN event types

Purpose:                      Enables and binds event handlers or callback
                              functions to several event conditions.

Demonstration:                Shows how to enable and respond to events.
                              Also, demonstrates the use of the UserData parameter
                              in the cbEnableEvent and the event handler

Other Library Calls:          cbAInScan()
                              cbStopBackground()
                              cbErrHandling()

Special Requirements:         Board 0 must support event handling with the
                              above types.


Copyright (c) 2001, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

/*minimum number of samples to collect between ON_DATA_AVAILABLE events*/
#define BLOCKSIZE 100

#define BOARDNUM     0
#define CHANNEL      0   /* A/D channel to read samples from */
#define TOTALCOUNT   10000   /* total number of samples to acquire */
#define RATE         1000   /* per channel sample rate */

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

/* Prototype for the event handler */
void __stdcall MyCallback(int BoardNum, unsigned EventType, unsigned EventData, void* UserData);
void __stdcall OnErrCallback(int BoardNum, unsigned EvetnType, unsigned EventData, void* UserData);



void main ()
    {
    /* Variable Declarations */
    int ulstat = 0;
    TDaq daq = { IDLE, BOARDNUM, CHANNEL, CHANNEL, TOTALCOUNT, 0, 
                 RATE, BIP5VOLTS, NULL, BACKGROUND };
    unsigned EventType = 0;
    unsigned EventSize = 0;

    
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
    printf ("Demonstration of cbEnableEvent with cbAInScan, and ON_SCAN_ERROR, \n");
    printf ("ON_DATA_AVAILABLE and ON_END_OF_AI_SCAN events.\n\n");

    printf ("Acquisition of at least %d new samples, completion of the scan, and scan \nerrors ", BLOCKSIZE);
    printf ("all generate events that call the appropriate event handler.\n\n");
    printf ("Meanwhile, we'll DoSomethingElse until a keystroke or scan completion.\n\n");
   
    printf (" Status: ");
    GetTextCursor (&col, &row);
    printf ("IDLE\n");
    

    /*
    Enable and connect one or more event types to a single user callback
    function using cbEnableEvent().
   
     Parameters:
       daq.BoardNum     :the number used by CB.CFG to describe this board
       EventType        :the condition that will cause an event to fire
       EventSize        :only used for ON_DATA_AVAILABLE to determine how
                           many samples to collect before firing an event. 
                           Note that if scan uses BLOCKIO, ON_DATA_AVAILABLE
                           events will be fired on integer multiples of the 
                           blocksize.
       MyCallback       :the address of the user function to call
                             when above event type occurs
       &daq             :the address of user data that will be passed into
                           MyCallback function. 
    */
    EventType = ON_DATA_AVAILABLE|ON_END_OF_AI_SCAN;
    EventSize = BLOCKSIZE;
    ulstat = cbEnableEvent(daq.BoardNum, EventType, EventSize, MyCallback, &daq);
    if (ulstat!=NOERRORS)
      {
       printf("Failed to setup event handlers.\n\n");
      cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);
      return ;
      }

    /* Since ON_SCAN_ERROR event doesn't use the EventSize, we can set it to anything
       we choose without affecting the ON_DATA_AVAILABLE setting. */
    EventType = ON_SCAN_ERROR;
    EventSize = 0;
    ulstat = cbEnableEvent(daq.BoardNum, EventType, EventSize, OnErrCallback, &daq);
    if (ulstat!=NOERRORS)
      {
       printf("Failed to setup event handlers.\n\n");
      cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);
      return ;
      }
    
    /* allocate the buffer and start the scan */
    daq.DataBuffer = (unsigned short*)cbWinBufAlloc(daq.TotalCount);
    daq.Status = RUNNING;
    ulstat = cbAInScan(daq.BoardNum, daq.LowChan, daq.HighChan, daq.TotalCount,
                           &(daq.Rate), daq.Range, (HGLOBAL)(daq.DataBuffer), daq.Options);
     
    /* if started, DoSomethingElse until scan completes or the user strikes a key */
    if (ulstat==NOERRORS)
      {
      MoveCursor(col, row);
      printf("RUNNING\n");
      DoSomethingElse(&daq);
      }
    
    daq.Status = IDLE;

    /* Be sure scan has been stopped before attempting to cbDisableEvent 
       Parameters:
         BoardNum    :the number used by CB.CFG to describe this board 
         FunctionType: A/D operation (AIFUNCTION)*/  
    cbStopBackground(daq.BoardNum,AIFUNCTION);

    /* Free the data buffer */
    cbWinBufFree((HGLOBAL)daq.DataBuffer);
    daq.DataBuffer = NULL;

    /*
      Disable and disconnect all event types with cbDisableEvent()
   
      Since disabling events that were never enabled is harmless,
      we can disable all the events at once.
   
      Parameters:
         daq.BoardNum         :the number used by CB.CFG to describe this board
         ALL_EVENT_TYPES      :all event types will be disabled
    */
    cbDisableEvent(daq.BoardNum, ALL_EVENT_TYPES);


    if (ulstat==NOERRORS)
       printf("\n\nEvent handling completed.");
    else
        printf("Failed to setup event handling.");
}



/***************************************************************************
*
* Name:      MyCallback
*
*   This gets called for each ON_DATA_AVAILABLE and ON_END_OF_AI_SCAN event. 
*   For these event types, the EventData supplied corresponds to the number 
*   of samples acquired since start of the scan. 
*
*   For each event, we'll update the scan with the latest measurement.

*   Upon ON_END_OF_AI_SCAN, we cleanup and reset the Status for the scan. 
*
*   Note that the user data that was passed in to cbEnableEvent points to 
*   TDaq structure holding the scan specific data.
*
****************************************************************************/
void __stdcall MyCallback(int bd, unsigned EventType, unsigned SampleCount, void* pUserData)
{
   /* Cast the UserData to the correct data type. */
   TDaq* pDaq = (TDaq*)pUserData;
   float Volts = 0.0f;

   /* Calculate the location of the latest sample using the EventData(=SampleCount) 
      and the number of channels */
   int ChannelCount = pDaq->HighChan - pDaq->LowChan + 1;
   int SampleIndex = SampleCount - 1;           //since array index start with zero
   SampleIndex -= (SampleIndex % ChannelCount); //we want the start of the channel scan
 
   /* Convert the latest sample to engineering units... */
   cbToEngUnits(bd, pDaq->Range, *(pDaq->DataBuffer+SampleIndex), &Volts);

   /* and display the results.*/
   MoveCursor(1, row+1);
   printf("Sample No.:%8d  Value:%8.4f V", SampleCount, Volts);

   /* if this is the final event...*/
   if (EventType==ON_END_OF_AI_SCAN)
      {
      /* Clean it up..
         Parameters:
             bd    :the number used by CB.CFG to describe this board 
             FunctionType: A/D operation (AIFUNCTION)*/  
      cbStopBackground(bd, AIFUNCTION);

      MoveCursor(col, row);
      printf("Scan Completed!    \n");

      /* and set the Status flag to close out the application. */
      pDaq->Status = IDLE;
      }
}



/***************************************************************************
*
* Name:      OnErrCallback
*
*   This gets called for ON_SCAN_ERROR events. For this event type, the 
*   EventData supplied corresponds to the error code--usually an OVERRUN
*   for cbAInScan. 
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
   if (ErrorNo==OVERRUN)
      {    
      
      /* The BACKGROUND operation must be explicitly stopped
         Parameters:
             BoardNum    :the number used by CB.CFG to describe this board 
             FunctionType:A/D operation (AIFUNCTION)*/  
      cbStopBackground(Bd,AIFUNCTION);

      MoveCursor(1, row+3);
      printf("Scan Aborted by FATAL ERROR!!!\n");

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






