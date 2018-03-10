VERSION 2.00
Begin Form frmDigIn 
   Caption         =   "Universal Library Digital Bit Input"
   ClientHeight    =   3480
   ClientLeft      =   105
   ClientTop       =   1545
   ClientWidth     =   4890
   Height          =   3885
   Left            =   45
   LinkMode        =   1  'Source
   LinkTopic       =   "Form1"
   ScaleHeight     =   3480
   ScaleWidth      =   4890
   Top             =   1200
   Width           =   5010
   Begin CommandButton cmdStopRead 
      Caption         =   "Quit"
      Default         =   -1  'True
      Height          =   495
      Left            =   3720
      TabIndex        =   20
      Top             =   2760
      Width           =   855
   End
   Begin Timer tmrReadInputs 
      Interval        =   200
      Left            =   4320
      Top             =   840
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   0
      Left            =   4320
      TabIndex        =   1
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   1
      Left            =   3960
      TabIndex        =   2
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   2
      Left            =   3600
      TabIndex        =   3
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   3
      Left            =   3240
      TabIndex        =   4
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   4
      Left            =   2520
      TabIndex        =   5
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   5
      Left            =   2160
      TabIndex        =   6
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   6
      Left            =   1800
      TabIndex        =   7
      Top             =   2160
      Width           =   255
   End
   Begin Label lblShowBitVal 
      Alignment       =   2  'Center
      ForeColor       =   &H00FF0000&
      Height          =   255
      Index           =   7
      Left            =   1440
      TabIndex        =   0
      Top             =   2160
      Width           =   255
   End
   Begin Label lblBitVal 
      Alignment       =   1  'Right Justify
      Caption         =   "Bit Value:"
      Height          =   255
      Left            =   240
      TabIndex        =   8
      Top             =   2160
      Width           =   975
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "0"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   7
      Left            =   4320
      TabIndex        =   17
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "1"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   6
      Left            =   3960
      TabIndex        =   16
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "2"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   5
      Left            =   3600
      TabIndex        =   15
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "3"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   4
      Left            =   3240
      TabIndex        =   14
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "4"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   3
      Left            =   2520
      TabIndex        =   13
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "5"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   2
      Left            =   2160
      TabIndex        =   12
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "6"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   1
      Left            =   1800
      TabIndex        =   11
      Top             =   1800
      Width           =   255
   End
   Begin Label lblShowBitNum 
      Alignment       =   2  'Center
      Caption         =   "7"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   -1  'True
      Height          =   255
      Index           =   0
      Left            =   1440
      TabIndex        =   10
      Top             =   1800
      Width           =   255
   End
   Begin Label lblBitNum 
      Alignment       =   1  'Right Justify
      Caption         =   "Bit Number:"
      Height          =   255
      Left            =   120
      TabIndex        =   9
      Top             =   1800
      Width           =   1095
   End
   Begin Label lblInstruct 
      Alignment       =   2  'Center
      Caption         =   "Input a TTL logic level at Port A inputs to change Bit Value:"
      ForeColor       =   &H000000FF&
      Height          =   495
      Left            =   960
      TabIndex        =   19
      Top             =   840
      Width           =   3135
   End
   Begin Label lblDemoFunction 
      Alignment       =   2  'Center
      Caption         =   "Demonstration of cbDBitIn()"
      FontBold        =   -1  'True
      FontItalic      =   0   'False
      FontName        =   "MS Sans Serif"
      FontSize        =   8.25
      FontStrikethru  =   0   'False
      FontUnderline   =   0   'False
      Height          =   375
      Left            =   240
      TabIndex        =   18
      Top             =   240
      Width           =   4455
   End
End
'ULDI02.MAK================================================================

' File:                         ULDI02.MAK

' Library Call Demonstrated:    cbDBitIn%()

' Purpose:                      Reads the status of single digital input bit.

' Demonstration:                Configures FIRSTPORTA & FIRSTPORTB for input
'                               and reads the bit values.
'                               Unstable bit values are due to the nature
'                               of the 8255 input ports when left floating.

' Other Library Calls:          cbDConfigPort%()
'                               cbErrHandling%()

' Special Requirements:         Board 0 must have a digital input port.
'                               Digital value on an input channel.

' (c) Copyright 1995-2002, Measurement Computing Corp.
' All rights reserved.
'==========================================================================

Const BoardNum = 0              ' Board number
Const PortNum% = FIRSTPORTA     ' use first digital port
Const PortType% = PortNum%      ' set port type to programmable
Const Direction% = DIGITALIN    ' program port for input mode

Sub cmdStopRead_Click ()

   End

End Sub

Sub Form_Load ()

   ' declare revision level of Universal Library

   ULStat% = cbDeclareRevision(CURRENTREVNUM)
   
   ' Initiate error handling
   '  activating error handling will trap errors like
   '  bad channel numbers and non-configured conditions.
   '  Parameters:
   '    PRINTALL    :all warnings and errors encountered will be printed
   '    DONTSTOP    :if an error is encountered, the program will not stop,
   '                 errors must be handled locally


   ULStat% = cbErrHandling(PRINTALL, DONTSTOP)
   If ULStat% <> 0 Then Stop

   ' If cbErrHandling% is set for STOPALL or STOPFATAL during the program
   ' design stage, Visual Basic will be unloaded when an error is encountered.
   ' We suggest trapping errors locally until the program is ready for compiling
   ' to avoid losing unsaved data during program design.  This can be done by
   ' setting cbErrHandling options as above and checking the value of ULStat%
   ' after a call to the library. If it is not equal to 0, an error has occurred.
   
   ' configure FIRSTPORTA for digital input
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board.
   '    PortNum%    :the input port
   '    Direction%  :sets the port for input or output
 
  
   ULStat% = cbDConfigPort(BoardNum, PortNum%, Direction%)
   If ULStat% <> 0 Then Stop

End Sub

Sub tmrReadInputs_Timer ()

   ' read the bits of FIRSTPORTA digital input and display
   
   '  Parameters:
   '    BoardNum    :the number used by CB.CFG to describe this board
   '    PortType    :the type of port
   '    BitNum%     :the number of the bit to read from the port
   '    BitValue%   :the value read from the port

   For i% = 0 To 7
      BitNum% = i%
      ULStat% = cbDBitIn(BoardNum, PortType%, BitNum%, BitValue%)
      If ULStat% <> 0 Then Stop

      lblShowBitVal(i%).Caption = Format$(BitValue%, "0")
   Next i%

End Sub

