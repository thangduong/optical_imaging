VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form PcvTriggerDlg 
   Caption         =   "PCVision Trigger Aquisition Settings"
   ClientHeight    =   8205
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6405
   ControlBox      =   0   'False
   LinkTopic       =   "Form4"
   ScaleHeight     =   8205
   ScaleWidth      =   6405
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Trigger 
      Caption         =   "Trigger"
      Height          =   2055
      Left            =   240
      TabIndex        =   29
      Top             =   120
      Width           =   5895
      Begin VB.Frame TriggerEnableFrame 
         Caption         =   "Trigger Enable"
         Height          =   1095
         Left            =   240
         TabIndex        =   36
         Top             =   480
         Width           =   1575
         Begin VB.OptionButton EnableTrigger 
            Caption         =   "Enable"
            Height          =   255
            Left            =   240
            TabIndex        =   38
            Top             =   360
            Value           =   -1  'True
            Width           =   1095
         End
         Begin VB.OptionButton DisableTrigger 
            Caption         =   "Disable"
            Height          =   375
            Left            =   240
            TabIndex        =   37
            Top             =   600
            Width           =   1095
         End
      End
      Begin VB.Frame TriggerSourceFrame 
         Caption         =   "Trigger Source"
         Height          =   1095
         Left            =   2040
         TabIndex        =   33
         Top             =   480
         Width           =   1575
         Begin VB.OptionButton TriggerSource 
            Caption         =   "External"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   35
            Top             =   720
            Width           =   975
         End
         Begin VB.OptionButton TriggerSource 
            Caption         =   "Software"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   34
            Top             =   360
            Value           =   -1  'True
            Width           =   975
         End
      End
      Begin VB.Frame TriggerPolarityFrame 
         Caption         =   "Trigger Polarity"
         Height          =   1095
         Left            =   3840
         TabIndex        =   30
         Top             =   480
         Width           =   1695
         Begin VB.OptionButton TriggerPolarity 
            Caption         =   "Falling Edge"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   32
            Top             =   360
            Value           =   -1  'True
            Width           =   1335
         End
         Begin VB.OptionButton TriggerPolarity 
            Caption         =   "Rising Edge"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   31
            Top             =   720
            Width           =   1335
         End
      End
   End
   Begin VB.Frame Strobe 
      Caption         =   "Strobe"
      Height          =   2415
      Left            =   240
      TabIndex        =   16
      Top             =   2400
      Width           =   5895
      Begin VB.Frame StrobeEnableFrame 
         Caption         =   "Strobe Enable"
         Height          =   1095
         Left            =   240
         TabIndex        =   26
         Top             =   480
         Width           =   1575
         Begin VB.OptionButton DisableStrobe 
            Caption         =   "Disable"
            Height          =   375
            Index           =   1
            Left            =   240
            TabIndex        =   28
            Top             =   600
            Width           =   1095
         End
         Begin VB.OptionButton EnableStrobe 
            Caption         =   "Enable"
            Height          =   255
            Left            =   240
            TabIndex        =   27
            Top             =   240
            Value           =   -1  'True
            Width           =   1095
         End
      End
      Begin VB.Frame StrobeModeFrame 
         Caption         =   "Strobe Mode"
         Height          =   1095
         Left            =   2040
         TabIndex        =   23
         Top             =   480
         Width           =   1575
         Begin VB.OptionButton StrobeMode 
            Caption         =   "Fast"
            Height          =   255
            Index           =   0
            Left            =   120
            TabIndex        =   25
            Top             =   600
            Value           =   -1  'True
            Width           =   1215
         End
         Begin VB.OptionButton StrobeMode 
            Caption         =   "Slow"
            Height          =   255
            Index           =   1
            Left            =   120
            TabIndex        =   24
            Top             =   240
            Width           =   1215
         End
      End
      Begin VB.Frame StrobePolarityFrame 
         Caption         =   "Strobe Polarity"
         Height          =   1095
         Left            =   3840
         TabIndex        =   20
         Top             =   480
         Width           =   1695
         Begin VB.OptionButton StrobePolarity 
            Caption         =   "Active Hi"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   22
            Top             =   600
            Value           =   -1  'True
            Width           =   1095
         End
         Begin VB.OptionButton StrobePolarity 
            Caption         =   "Active Low"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   21
            Top             =   240
            Width           =   1095
         End
      End
      Begin VB.Frame StrobeDealyFrame 
         Caption         =   "Strobe Dealy"
         Height          =   615
         Left            =   360
         TabIndex        =   17
         Top             =   1680
         Width           =   5175
         Begin VB.TextBox StrobeDelayVal 
            Enabled         =   0   'False
            Height          =   285
            Left            =   4560
            TabIndex        =   18
            Text            =   "1"
            Top             =   240
            Width           =   495
         End
         Begin ComctlLib.Slider StrobeDealy 
            Height          =   255
            Left            =   120
            TabIndex        =   19
            Top             =   240
            Width           =   4455
            _ExtentX        =   7858
            _ExtentY        =   450
            _Version        =   327682
            Min             =   1
            Max             =   64
            SelStart        =   1
            Value           =   1
         End
      End
   End
   Begin VB.Frame FrameReset 
      Caption         =   "Frame Reset"
      Height          =   2415
      Left            =   240
      TabIndex        =   3
      Top             =   5040
      Width           =   5895
      Begin VB.Frame FrameResetFrame 
         Caption         =   "Frame Reset"
         Height          =   1095
         Left            =   120
         TabIndex        =   13
         Top             =   480
         Width           =   1575
         Begin VB.OptionButton EnableFrameReset 
            Caption         =   "Enable"
            Height          =   375
            Left            =   240
            TabIndex        =   15
            Top             =   240
            Value           =   -1  'True
            Width           =   1095
         End
         Begin VB.OptionButton DisbaleFrameReset 
            Caption         =   "Disable"
            Height          =   255
            Left            =   240
            TabIndex        =   14
            Top             =   720
            Width           =   975
         End
      End
      Begin VB.Frame FrameResetPolarityFrame 
         Caption         =   "Frame Reset Polarity"
         Height          =   1095
         Left            =   2040
         TabIndex        =   10
         Top             =   480
         Width           =   1695
         Begin VB.OptionButton FrameResetPolarity 
            Caption         =   "Active Hi"
            Height          =   255
            Index           =   0
            Left            =   240
            TabIndex        =   12
            Top             =   600
            Width           =   1335
         End
         Begin VB.OptionButton FrameResetPolarity 
            Caption         =   "Active Low"
            Height          =   255
            Index           =   1
            Left            =   240
            TabIndex        =   11
            Top             =   240
            Value           =   -1  'True
            Width           =   1335
         End
      End
      Begin VB.Frame FrameResetSizeFrame 
         Caption         =   "Frame Reset Size"
         Height          =   1095
         Left            =   3960
         TabIndex        =   7
         Top             =   480
         Width           =   1695
         Begin VB.OptionButton FrameResetSize 
            Caption         =   "Offset Period"
            Height          =   375
            Index           =   0
            Left            =   240
            TabIndex        =   9
            Top             =   240
            Value           =   -1  'True
            Width           =   1215
         End
         Begin VB.OptionButton FrameResetSize 
            Caption         =   "One Line"
            Height          =   375
            Index           =   1
            Left            =   240
            TabIndex        =   8
            Top             =   600
            Width           =   1215
         End
      End
      Begin VB.Frame FrameResetDelayFrame 
         Caption         =   "Frame Reset Delay"
         Height          =   615
         Left            =   120
         TabIndex        =   4
         Top             =   1680
         Width           =   5535
         Begin VB.TextBox FrameDealyVal 
            Enabled         =   0   'False
            Height          =   285
            Left            =   4800
            TabIndex        =   5
            Text            =   "1"
            Top             =   240
            Width           =   495
         End
         Begin ComctlLib.Slider FrameDealy 
            Height          =   255
            Left            =   120
            TabIndex        =   6
            Top             =   240
            Width           =   4575
            _ExtentX        =   8070
            _ExtentY        =   450
            _Version        =   327682
            Min             =   1
            Max             =   256
            SelStart        =   1
            Value           =   1
         End
      End
   End
   Begin VB.CommandButton Close 
      Caption         =   "Close"
      Height          =   375
      Left            =   4320
      TabIndex        =   2
      Top             =   7800
      Width           =   1695
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   7800
      Width           =   1335
   End
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   7800
      Width           =   1335
   End
End
Attribute VB_Name = "PcvTriggerDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Close_Click()
Stop_Click
Sleep 999
Unload Me
End Sub

Private Sub Form_Load()
Module1.hTriggerThread = 0
CICamera_Freeze ITICam(Current_Camera)

IFC_TRIG_SRC = 0
IFC_EDGE = 0
IFC_STROBE_MODE = 0
IFC_STROBE_POLARITY = 0
IFC_FRAME_RESET_POLARITY = 0
IFC_FRAME_RESET_SIZE = 0
End Sub


Private Sub FrameDealy_Click()
FrameDealyVal.Text = Str(FrameDealy.value)
End Sub

Private Sub FrameResetPolarity_Click(index As Integer)
IFC_FRAME_RESET_POLARITY = index
End Sub

Private Sub FrameResetSize_Click(index As Integer)
IFC_FRAME_RESET_SIZE = index
End Sub

Private Sub Start_Click()
Dim id As Long

Stop_Click
TriggerThreadStop = False

   If (EnableTrigger.value) Then
       CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Enable, 0
       CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_POLARITY, IFC_EDGE, 0
       CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_SRC, IFC_TRIG_SRC, 0
           
    If (EnableStrobe.value) Then
        CICamera_SetAcqParam ITICam(Current_Camera), P_STROBE_ENABLE, IFC_Enable, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_STROBE_MODE, IFC_STROBE_MODE, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_STROBE_POLARITY, IFC_STROBE_POLARITY, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_STROBE_DELAY, StrobeDealy.value, 0
        Else
        CICamera_SetAcqParam ITICam(Current_Camera), P_STROBE_ENABLE, IFC_Disable, 0
    End If
    
    If (EnableFrameReset.value) Then
        CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_MODE, IFC_Enable, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_POLARITY, IFC_FRAME_RESET_POLARITY, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_SIZE, IFC_FRAME_RESET_SIZE, 0
        CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_OFFSET, FrameDealy.value, 0
        Else
        CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_MODE, IFC_Disable, 0

    End If

    Module1.hTriggerThread = 0
    hTriggerThread = CreateThread(0&, 200000, AddressOf Module1.PcvTriggerThread, 0&, 0, VarPtr(id))

Else
    MsgBox "Enable trigger and then click Start"

End If

End Sub

Private Sub Stop_Click()
If (Module1.hTriggerThread <> 0) Then
Dim WaitFuncRet As Long
Dim CloseFuncRet As Long
TriggerThreadStop = True
WaitFuncRet = WaitForSingleObject(Module1.hTriggerThread, INFINITE)
CloseFuncRet = CloseHandle(Module1.hTriggerThread)
Module1.hTriggerThread = 0
End If

CICamera_SetAcqParam ITICam(Current_Camera), P_FRAME_RESET_MODE, IFC_Disable, 0
CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Disable, 0
End Sub

Private Sub StrobeDealy_Click()
StrobeDelayVal.Text = Str(StrobeDealy.value)
End Sub

Private Sub StrobeMode_Click(index As Integer)
IFC_STROBE_MODE = index
End Sub

Private Sub StrobePolarity_Click(index As Integer)
IFC_STROBE_POLARITY = index
End Sub

Private Sub TriggerPolarity_Click(index As Integer)
IFC_EDGE = index
End Sub

Private Sub TriggerSource_Click(index As Integer)
IFC_TRIG_SRC = index
End Sub
