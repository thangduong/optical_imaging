------------------------------------------------------------------------
Universal Library - Version 5.42
------------------------------------------------------------------------

	Congratulations on purchasing the Universal Library for Windows data 
acquisition applications. The Universal Library provides a fast, simple, 
and powerful way for users to develop sophisticated data acquisition 
applications using data acquisition hardware. 


Universal Library - 32 Bit
----------------------------

------------------------------------------------------------------------------
New Feature (introduced version 5.40)
	- C# and Visual Basic.NET Support
------------------------------------------------------------------------------
The Universal Library now includes object-oriented support for Microsoft's 
.Net Framework. Included are examples and interfaces for both C# and Visual Basic
.NET. All access to the library in .Net  is through the MccDaq namespace, normally 
using the MccBoard or MccService objects. Please see accompanying Function Reference 
and examples for details.

The Universal Library support for .Net requires that the .Net Framework already 
have been installed on the system before attempting to install the Universal 
Library. 

------------------------------------------------------------------------------
New Feature (introduced version 5.40)
	- USB Device Identification
------------------------------------------------------------------------------
For the miniLAB 1008, a new function was introduced to allow users to visually 
identify otherwise identical devices. Calling this function will flash the LED
of device specified by the board number.

The C interface is:

	int cbFlashLED (int BoardNum);
	
		Causes the onboard LED to flash or blink once.

		BoardNum = the index used to specify the board in InstaCal.

------------------------------------------------------------------------------
SoftWIRE 3.1 DAQ Component Update (introduced version 5.40)
------------------------------------------------------------------------------
If you are using the Data Acquisition(DAQ) Components for SoftWIRE 3.1, you may 
wish to update the components. Included in the latest DAQ Components is support 
for new analog input ranges introduced by the PCI-DAS6000 series boards and the 
miniLAB 1008. In addition, support for the new BURSTIO analog input scan mode 
has been added for the miniLAB 1008.
 

------------------------------------------------------------------------------
New Feature (introduced version 5.30)
	- Advanced Timing and Control Configuration (ATCC) 
------------------------------------------------------------------------------
The new family of boards -- the PCI-DAS60XX series boards -- support configurable
timing and control signal connections through ther DAQ Sync and Auxilary Input/Output
connections. See the Functional Description section of the accompanying hardware
manual for details.

Control of these signal connections is provided both through the Board Configuration
page in InstaCAL and through 2 new Universal Library functions, cbSelectSignal 
and cbGetSignal.


   int SelectSignal (int BoardNum, int Direction, int Signal, int Connection, int Polarity)

      Sets the connection and polarity for a give signal type and direction.

      BoardNum = the index used to specify the board in InstaCal.
      Direction = determines whether selecting the source or destination of the signal. 
               - SIGNAL_IN (for selecting the source of a signal)
               - SIGNAL_OUT (for selecting the destination of a signal)
               - DISABLE (for disabling (neither input or output) the
                  SYNC_CLK, ADC_TB_SRC, and DAC_TB_SRC signals)
      Signal = specifies the signal type to be selected.
               ADC_CONVERT       ADC_GATE          ADC_START_TRIG
               ADC_STOP_TRIG     ADC_TB_SRC        ADC_SCANCLK
               ADC_SCAN_STOP     ADC_STARTSCAN     ADC_SSH      
               DAC_UPDATE        DAC_START_TRIG    DAC_TB_SRC
               SYNC_CLK          CTR1_CLK          CTR2_CLK
               DIOGND
      Connection = specifies the physical pin connection for the signal.
               - AUXIN0..AUXIN5  (for the Auxilary Input pins 0 to 5)
               - AUXOUT0..AUXOUT2 (for the Auxilary Output pins 0 to 2)
               - DS_CONNECTOR (for the DAQ Sync connector)
      Polarity = controls the sense or polarity of the signal.
               - POSITIVEEDGE or NEGATIVEEDGE for signal sources(SIGNAL_IN)
               - INVERTED or NONINVERTED for signal destinations(SIGNAL_OUT)
               
        
   int GetSignal(int BoardNum, int Direction, int Signal, int Index, int* Connection, int*Polarity) 

      Retrieves the connection and polarity assigned to the signal type and direction.

      BoardNum = the index used to specify the board in InstaCAL.
      Direction = determines whether selecting the source or destination of the signal. 
      Signal = specifies the configured signal type.
      Index = for output signals which can have multiple destinations, specifies which 
          signal-connection pair to retrieve.
      Connection = specifies the physical pin connection for the signal.
      Polarity = controls the sense or polarity of the signal.
      
       

------------------------------------------------------------------------------
New Feature - Bitwise Digital Configuration (version 5.21)
------------------------------------------------------------------------------
The new family of boards -- the PCI-DAS60XX series boards -- support a bitwise
configurable port called AUXPORT. To support this new board feature, a new 
function was introduced into the library -- cbDConfigBit. It is similar to 
cbDConfigPort, except that you must also specify the bit number as well as 
the port type to configure as DIGITALIN or DIGITALOUT:

   int cbDConfigBit (int BoardNum, int PortType, int BitNum, int Direction)

      BoardNum = the index used to specify the board in InstaCAL.
      PortType = AUXPORT.
      BitNum   = zero-based index specifying the bit to be configured.
      Direction = DIGITALIN or DIGITALOUT.



##############################################################################
              IMPORTANT CHANGES (version 5.20 changes)
##############################################################################

The Universal Library now supports concurrent analog input and output scans
for PCI boards that are capable of both paced analog input and outputs.  
Since more than one background operation can be active at one time, an extra 
parameter was added to 'cbGetStatus' and 'cbStopBackground' to identify the 
background operation. One consequence is that applications that already use 
either of these functions will require updating upon recompiling or rebuilding 
with the latest header files (cbw.h for C/C++, cbw.bas for Visual Basic, or 
cbw.pas).

This extra parameter has been appended to the end of the parameter list for 
each function:

   int cbGetStatus(int BoardNum, int Functiontype);
   int cbStopBackground(int BoardNum, int FunctionType);

   where 'FunctionType' identifies the background operation and can be:
      AIFUNCTION - to specify analog input scans started with cbAInScan 
                   or cbAPretrig.
      AOFUNCTION - to specify analog output scans started with cbAOutScan.
      DIFUNCTION - to specify digital input scans started with cbDInScan.
      DOFUNCTION - to specify digital output scans started with cbDOutScan.
      CTRFUNCTION - to specify background counter operations started with 
                    cbCStoreOnInt.


HOWEVER, IF YOU DO NOT NEED THIS NEW FEATURE AND YOU DO NOT WANT TO UPDATE 
YOUR CURRENT APPLICATIONS, YOU CAN STILL RECOMPILE OR REBUILD YOUR 
APPLICATIONS. EITHER:
   (1) USE THE HEADER FILES FROM PRIOR VERSIONS OF THE UNIVERSAL LIBRARY. OR 
   (2) MODIFY THE HEADER ENTRIES. REMOVE THE 'FunctionType' PARAMETER FROM 
       ALL ENTRIES IN THE HEADERS, REPLACE ALL INSTANCES OF 'cbGetIOStatus' 
       WITH 'cbGetStatus' IN THE HEADERS, AND REPLACE ALL INSTANCES OF 
       'cbStopIOBackground' WITH 'cbStopBackground' IN THE HEADERS.
	   (NOTE THAT THE LEGACY FUNCTION PROTOTYPES ARE INCLUDED IN COMMENTS 
	    WITHIN EACH HEADER FILE AND ARE DENOTED BY THE STRING 
	   'Legacy Function Prototypes'.)



NOTE THAT APPLICATIONS THAT HAVE ALREADY BEEN BUILT USING AN EARLIER VERSION
OF THE UNIVERSAL LIBRARY WILL CONTINUE TO WORK WITH THIS RELEASE WITHOUT MODIFICATION.


------------------------------------------------------------------------------
New Feature - Event Notification (introduced in version 5.20)
------------------------------------------------------------------------------
The Universal Library now supports a new mechanism for updating the status on
background operations with some DAS boards and for custom interrupt handling
with some DIO or CTR boards. Details describing this new feature can be found
in the Functions Reference of the Online Help under 'cbEnableEvent'and
'cbDisableEvent'. Board support is included in the User's Guide of the Online
Help under the board specific information.


------------------------------------------------------------------------------
Function Prototype Corrections (introduced in version 5.20)
------------------------------------------------------------------------------
Prior releases of the Universal Library included several mismatches between
parameter types in the Delphi or Visual Basic function prototypes and the
library DLL. These mismatches have been corrected with the 5.20 release of the
Universal Library. However, these corrections may lead to incompatibilities
with some existing applications that require rebuilding or recompiling. To
avoid these incompatibilities without changing existing applications, either
use prior header files when rebuilding or recompiling applications, or reverse
the changes described below in appropriate header file. (Note that the legacy
function prototypes are included in comments within each header file and are 
denoted by the string 'Legacy Function Prototypes'.)

NOTE THAT APPLICATIONS THAT HAVE ALREADY BEEN BUILT USING AN EARLIER VERSION
OF THE UNIVERSAL LIBRARY WILL CONTINUE TO WORK WITH THIS RELEASE WITHOUT
MODIFICATION.

Visual Basic (cbw.bas) 
----------------------
cbCIn() - the 'CBCount' parameter type was changed from a reference to a
          32-bit integer('Long') to a reference to a 16-bit integer('Integer'). 
          
cbGetConfig() - the 'ConfigVal' parameter type was changed from a reference to
          a 16-bit integer('Integer') to a reference to a 32-bit integer
         ('Long'). 


Delphi (cbw.pas)
----------------
cbDBitIn() - the 'BitValue' parameter type was changed from a reference to
             16-bit signed integer('SmallInt') to a reference to a 16-bit
             unsigned integer('Word'). 
 
cbDBitOut() - the 'BitValue' parameter type was changed from a  32-bit signed
             integer('Integer') to a 16-bit unsigned integer('Word'). 

cbGetConfig() - the 'ConfigVal' parameter type was changed from a reference
             to a 16-bit integer('SmallInt') to a reference to a 32-bit
             integer('Integer'). 

cbSetTrigger() - 'LowThreshold' and 'HighThreshold' parameter types were
             changed from 32-bit signed integers('Integer') to 16-bit
             unsigned integers('Word'). 

##############################################################################


Universal Library - 16 Bit
--------------------------

The 16-bit Universal Library API is compatible with applications that were
written to use older versions of the library.


Instacal - 32 Bit
-----------------

	A 32-bit Windows version of our Instacal program is provided for installing, 
configuring, testing, and calibrating our boards in Windows. 

Included in this release is support for configuring the advanced timing and
control signals of the DAQ Sync and Auxilary Input/Output connections of
the PCI-DAS60xx board family. 


Notes for PCI boards Support under Windows 2000 and XP:  
-------------------------------------------------------
If you are upgrading from version 5.11A or older of InstaCal or the Universal Library
in Windows 2000 and XP, you should update the driver using the following procedure:

1)   Install the new version of Instacal or Universal Library
2)   Restart your computer with the PCI boards you wish to use installed 
     in the PC.
3)   Open the System Properties dialog by right clicking on My Computer and 
     selecting Properties from the menu OR opening the Control Panel and
     double clicking on the System icon.
4)   Select the Hardware tab on the System Properties dialog.
5)   Click the Device Manager button.
6)   Look for the DAS Component category and double click it to expand it.  
     You should then see your PCI board listed as a device under DAS 
     Component.
7)   Double click the PCI card for which you want to update the driver.  
     This should open the Properties dialog for that card.
8)   Select the Driver tab on the PCI Card Properties dialog. 
9)   Click the Driver Details button on the PCI Card Properties dialog.  
     If the driver listed is cbulwdm.sys, there is no need to update the      driver.
     Skip step 10 and continue to the Using InstaCal section of the Software 
     Installation manual to configure and test your board.
10)  If the driver listed is not cbulwdm.sys, click OK to return to the 
     Driver tab on the PCI Card Properties dialog. Click the Update Driver
     button to open the Update Device Driver Wizard. Select the defaults for
     each step (including restarting the computer if prompted) and then
     continue below.

Run InstaCal to configure and test your board as described in the Using
InstaCal section of the Software Installation manual.


Notes For PCMCIA Support under Windows 2000:
--------------------------------------------
   This version of Instacal includes Support for PCMCIA cards 
   under Windows-2000. However, on some PC-CARD controllers, 
   the PCMCIA card's CIS has to be updated. 
	
   If you run Inscal32.exe and you get a pop up dialog titled 
   ([PCMCIA card name] Windows 2000 support Failure), you must do the 
   following to enable Windows 2000 support:
1)   Install Instacal software on Win95/Win98 machine
2)   Insert the PCMCIA card
3)   Run Inscal32.exe and install the PCMCIA card
4)   On the target Windows 2000 machine, run Inscal32.exe and reinstall 
     the card
5)   If the ([PCMCIA card name] Windows 2000 support Failure) dialog still 
     pops up after saving the configuration, contact technical support


Instacal - 16 Bit
-----------------

An MS-DOS version of our Instacal program is provided for installing, 
configuring, calibrating, and testing our boards under MS-DOS or Windows 3.1.

A board configuration file created with the 16-bit Instacal program can be used unchanged by the Windows 95/98/NT Instacal and Universal Library.



