/*ULAI13.C****************************************************************

File:                         ULAI13.C

Library Call Demonstrated:    cbAInScan(), sampling mode options.

Purpose:                      Scans a range of A/D Input Channels and
                              stores the sample data in an array using
                              a user specified sampling mode.

Demonstration:                Displays the analog input on two channels.

Other Library Calls:          cbErrHandling()

Special Requirements:         Board 0 must have an A/D converter.
                              Analog signals on two input channels.
                              board must support the mode selected.

Copyright (c) 1993-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col, I, J;
    int BoardNum = 0;
    int UDStat = 0;
    int LowChan = 0;
    int HighChan = 1;
    int SampMode = -1;
    int Gain = BIP5VOLTS;
    long Count = 2048;
    long Rate = 3125;
    unsigned Options;
    WORD *ADData;     /* array must be dimensioned Count + 512 */
    float EngUnits;
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   UDStat = cbDeclareRevision(&RevLevel);

    ADData = malloc ((size_t) (Count*sizeof(unsigned)) );

    if (!ADData) /*make sure it is a valid pointer*/
        {
        printf("\nout of memory\n");
        exit(1);
        }

    /* Initiate error handling
       Parameters:
          PRINTALL :all warnings and errors encountered will be printed
          DONTSTOP :program will continue even if error occurs.
                     Note that STOPALL and STOPFATAL are only effective in 
                     Windows applications, not Console applications. 
   */
    cbErrHandling (PRINTALL, DONTSTOP);

    /* set up the display screen */
    ClearScreen();
    printf ("Demonstration of cbAInScan() using sampling mode options\n\n");

    /* Collect the values with cbAInScan()
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :low channel of the scan
            HighChan    :high channel of the scan
            Count       :the total number of A/D samples to collect
            Rate        :sample rate in samples per second
            Gain        :the gain for the board
            DataBuffer[]:the array for the collected data values
            Options     :data collection options */

    while (1)  /* infinite loop */
        {
        MoveCursor(4,4);
        /* select mode */
        while (SampMode < 0 || SampMode > 3)
            {
            MoveCursor(4,4);
            printf ("Please select the sampling mode(1 to 3):\n\n");
            printf ("                                SINGLEIO --> 1\n");
            printf ("                                DMAIO -----> 2\n");
            printf ("                                BLOCKIO ---> 3\n");
            printf ("                                   Quit ---> 0\n\n");
            printf ("                             Your Choice --> ");
            scanf ("%d",&SampMode);
            printf(" ");
            }

        switch (SampMode)
            {
            case 0:
                free(ADData);
                exit(1);
            case 1:
                Options = CONVERTDATA + SINGLEIO;
                break;
            case 2:
                Options = CONVERTDATA + DMAIO;
                break;
            case 3:
                Options = CONVERTDATA + BLOCKIO;
                break;
            default:
                break;
            }

                GetTextCursor (&Col, &Row);
                MoveCursor (1, 20);
        UDStat = cbAInScan (BoardNum, LowChan, HighChan, Count, &Rate,
                                                 Gain, ADData, Options);
                if (UDStat > 0)  /* If error then erase it */
                        {
                        MoveCursor (0, 21);
                        printf("%75s");
                        MoveCursor (0, 23);
                        printf("%75s");
                        }
                MoveCursor (Col, Row); /* Restore Cursor*/

        SampMode = -1;

        /* display the data */
        for (J = 0; J < 2; J++)       /* loop through the channels */
            {
            printf ("\nThe first 5 values on Channel %u are ", J);
            GetTextCursor (&Col, &Row);

            for (I = 0; I < 5; I++)   /* loop through the values & print */
                {
                MoveCursor (Col, Row + I);
                UDStat = cbToEngUnits (BoardNum, Gain, ADData[I*2+J], &EngUnits);
                printf ("%.2f", EngUnits);
                }
            printf ("\n");
            }

        GetTextCursor (&Col, &Row);
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

