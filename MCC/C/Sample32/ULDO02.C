/*ULDO02.C****************************************************************

File:                         ULDO02.C

Library Call Demonstrated:    cbDBitOut()

Purpose:                      Sets the state of a single digital output bit.

Demonstration:                Configures FIRSTPORTA for output and
                              writes a bit value to the port.

Other Library Calls:          cbDConfigPort()
                              cbErrHandling()

Special Requirements:         Board 0 must have a digital output port.


Copyright (c) 1995-2002, Measurement Computing Corp.
All Rights Reserved.
***************************************************************************/


/* Include files */
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include "..\cbw.h"


/* Prototypes */
void ClearScreen (void);
void GetTextCursor (int *x, int *y);
void MoveCursor (int x, int y);


void main ()
    {
    /* Variable Declarations */
    int Row, Col;
    int BoardNum = 0;
    int ULStat = 0;
    int PortNum, PortType, Direction;
    int DataValue;
    int BitLevel;
    int BitNum;
    WORD BitValue;
    int hilo;
    float    RevLevel = (float)CURRENTREVNUM;

  /* Declare UL Revision Level */
   ULStat = cbDeclareRevision(&RevLevel);

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
    printf ("Demonstration of cbDBitOut()\n\n");

    GetTextCursor (&Col, &Row);

    /* configure FIRSTPORTA for digital output
        Parameters:
            BoardNum    :the number used by CB.CFG to describe this board.
            PortNum     :the output port
            Direction   :sets the port for input or output */
    PortNum = FIRSTPORTA;
    Direction = DIGITALOUT;
    ULStat = cbDConfigPort (BoardNum, PortNum, Direction);

    /* get a user value to write to the port */
    DataValue = 8;
    while (DataValue > 7)
        {
        MoveCursor (Col, Row);
        printf ("Which bit would you like to set(0 to 7)? --> ");
        scanf ("%i", &DataValue);
        }
    BitLevel = 2;
    while (BitLevel > 1)
        {
        MoveCursor (Col, Row+2);
        printf ("Set high(1) or low(0)? --> ");
        scanf ("%i", &BitLevel);
        }

    MoveCursor (Col, Row + 4);
    printf ("Bit %u on port A was set to a %u.\n\n",DataValue,BitLevel);

    printf ("Bit   Value (X = Don't Care)\n");

    /* write the value to FIRSTPORTA as single bits */
    for (BitNum = 0; BitNum < 8; BitNum++) /* loop through the bits */
        {
        /* parse data value into individual bits */
        hilo = 'X';
        if ((BitNum == DataValue) && (BitLevel == 1))
            {
            BitValue = 1;
            hilo = '1';
            }
        else if ((BitNum == DataValue) && (BitLevel == 0))
            {
            BitValue = 0;
            hilo = '0';
            }

        printf (" %u      %c\n", BitNum, hilo);

        /* write BitValue to BitNum of FIRSTPORTA
            Parameters:
                BoardNum    :the number used by CB.CFG to describe this board
                PortType    :must be FIRSTPORTA or AUXPORT
                BitNum      :the number of the bit to be set to BitValue
                BitValue    :the value written to the port   */

        PortType=FIRSTPORTA;
        if (BitNum == DataValue)
            ULStat = cbDBitOut (BoardNum, PortType, BitNum, BitValue);
        }

    MoveCursor (1, 20);
    printf ("\n");
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





