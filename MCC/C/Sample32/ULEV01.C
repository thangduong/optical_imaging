/*ULEV01.C****************************************************************

 File:                         ULEV01.C

 Library Call Demonstrated:    cbEnableEvent - ON_EXTERNAL_INTERRUPT
                               cbDisableEvent()

 Purpose:                      Generates an event for each pulse set at a
                               digital or counter External Interrupt pin,
                               and reads the digital input at FIRSTPORTA
                               every UpdateSize events.


 Demonstration:                Shows how to enable and respond to events.

 Other Library Calls:          cbErrHandling()
                               cbDConfigPort()
                               cbDIn()

 Special Requirements:         Board 0 must have an external interrupt pin
                               and support the ON_EXTERNAL_INTERRUPT event.


 (c) Copyright 2001-2002, Measurement Computing Corp.
 All rights reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"

#define BOARDNUM     0           /* board number*/
#define PORTNUM      FIRSTPORTA  /* digital port to read ON_EXTERNAL_INTERRUPT event */
#define DIRECTION    DIGITALIN   /* set direction of PortNum to input */
#define UPDATE_SIZE  10          /* controls how often to read FIRSTPORTA and update the display */

int col, row;                       /* column and row location for output */

/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);
void WaitForKeyboardHit();

/* Prototype for the event handler */
void __stdcall MyCallback(int BoardNum, unsigned EventType, unsigned EventData, void* pUserData);



void main ()
    {
    /* Variable Declarations */
    int ULStat          = 0;
    unsigned EventType  = 0;
    unsigned EventSize  = 0;
    unsigned EventCount = 0;
   
    /* 
    Initiate error handling
    
    Parameters:
       PRINTALL   :all warnings and errors encountered will be printed
       DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /*
     Configure FIRSTPORTA for digital input
   
     Parameters:
       BOARDNUM     :the number used by CB.CFG to describe this board.
       PORTNUM      :the input port
       DIRECTION    :sets the port for input
    */
    cbDConfigPort(BOARDNUM, PORTNUM, DIRECTION);

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbEnableEvent with ON_EXTERNAL_INTERRUPT events.\n\n");
    printf ("Each pulse at the External Interrupt pin will generate a interrupt,\n");
    printf ("which in turn results in up to one event per interrupt.\n");
    printf ("If the interrupts are too frequent for us to keep up, each event might\n");
    printf ("be handling several interrupts.\n\n");
    printf ("Press any key to quit.\n\n");
    printf ("Interrupt Count   Event Count   Interrupts Missed   Digital Input\n");
    printf ("---------------   -----------   -----------------   -------------\n");
    GetTextCursor (&col, &row);
    

   /*
    Enable and connect one or more event types to a single user callback
    function using cbEnableEvent().
   
     Parameters:
       BOARDNUM    :the number used by CB.CFG to describe this board
       EventType   :the condition that will cause an event to fire
       EventSize   :only used for ON_DATA_AVAILABLE to determine how
                     many samples to collect before firing an event
       MyCallback  :the address of the user function to call
                             when above event type occurs
       &EventCount :the address of user data that will be passed into
                     MyCallback function

    */
    EventType  = ON_EXTERNAL_INTERRUPT;
    EventSize  = 0;
    EventCount = 0;
    ULStat     = cbEnableEvent(BOARDNUM, EventType, EventSize, MyCallback, &EventCount);

    if (ULStat==NOERRORS)
       WaitForKeyboardHit();  

    /*
      Disable and disconnect all event types with cbDisableEvent()
   
      Since disabling events that were never enabled is harmless,
      we can disable all the events at once.
   
      Parameters:
         BOARDNUM         :the number used by CB.CFG to describe this board
         ALL_EVENT_TYPES  :all event types will be disabled
    */
    cbDisableEvent(BOARDNUM, ALL_EVENT_TYPES);
    if (ULStat==NOERRORS)
       printf("\n\nEvent handling exited by user.");
    else
        printf("Failed to setup event handling.");
}


/***************************************************************************
*
* Name:      MyCallback
*
*   This gets called for each ON_EXTERNAL_INTERRUPT event. For this event type,
*   the EventData supplied curresponds to the number of interrupts that occurred
*   since the event was last enabled.
*
*   The user data that was passed in to cbEnableEvent points to a variable of 
*   'unsigned' integer type and corresponds to the number of events handled.
*
****************************************************************************/
void __stdcall MyCallback(int Bd, unsigned EventType, unsigned InterruptCount, void* pUserData)
{
   unsigned* pEventCount=(unsigned*)pUserData; /* cast the user data to correct type */
   unsigned InterruptsMissed = 0;
   unsigned short DigitalData=0;

   /*
    We only update the display every UPDATE_SIZE events since the work below
    is "expensive." The longer we spend in this handler and the more frequent
    the interrupts occur, the more likely we'll miss interrupts. 
  */
   ++(*pEventCount);
   if ((*pEventCount % UPDATE_SIZE)==0)
      {
      InterruptsMissed = InterruptCount - *pEventCount;

      /*
       Read FIRSTPORTA digital input and display
    
       Parameters:
         Bd           :the number used by CB.CFG to describe this board
         PORTNUM      :the input port
         DigitalData  :the value read from the port
      */
      cbDIn(Bd, PORTNUM, &DigitalData);


      //MoveCursor(col, row);
      printf ("%8d   %14d %16d              0x%.2x\n",
               InterruptCount, *pEventCount, InterruptsMissed, DigitalData);
      }
}



/***************************************************************************
*
* Name:      WaitForKeyboardHit
*
*  Spins in a while loop waiting for a keyboard hit.
*
***************************************************************************/
void WaitForKeyboardHit()
{
   while (!kbhit())
        Sleep(10);
}

/***************************************************************************
*
* Name:      ClearScreen
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






