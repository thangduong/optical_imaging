VERSION 5.00
Begin VB.Form PcrTriggerDlg 
   Caption         =   "PCRgb Trigger Aquisition Settings"
   ClientHeight    =   5385
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7995
   ControlBox      =   0   'False
   LinkTopic       =   "Form4"
   ScaleHeight     =   5385
   ScaleWidth      =   7995
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   615
      Index           =   0
      Left            =   360
      TabIndex        =   3
      Top             =   120
      Width           =   2175
   End
   Begin VB.Frame TriggerSource 
      Caption         =   "     Tigger Source   "
      Height          =   2775
      Left            =   720
      TabIndex        =   2
      Top             =   2400
      Width           =   6135
      Begin VB.OptionButton Option1 
         Caption         =   "Opto-Coupled 0"
         Height          =   255
         Index           =   4
         Left            =   360
         TabIndex        =   13
         Top             =   2040
         Width           =   1575
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Opto-Coupled 1"
         Height          =   255
         Index           =   5
         Left            =   2160
         TabIndex        =   12
         Top             =   2040
         Width           =   1455
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Differential"
         Height          =   255
         Index           =   6
         Left            =   4200
         TabIndex        =   11
         Top             =   2040
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "TTL 0"
         Height          =   255
         Index           =   1
         Left            =   360
         TabIndex        =   10
         Top             =   1320
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "TTL 1"
         Height          =   255
         Index           =   2
         Left            =   2160
         TabIndex        =   9
         Top             =   1320
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "TTL 2"
         Height          =   255
         Index           =   3
         Left            =   4200
         TabIndex        =   8
         Top             =   1320
         Width           =   1095
      End
      Begin VB.OptionButton Option1 
         Caption         =   "Software Trigger"
         Height          =   255
         Index           =   0
         Left            =   360
         TabIndex        =   7
         Top             =   600
         Width           =   1575
      End
   End
   Begin VB.CommandButton Close 
      Caption         =   "Close"
      Height          =   615
      Left            =   5400
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   615
      Left            =   2880
      TabIndex        =   0
      Top             =   120
      Width           =   2175
   End
   Begin VB.Frame SoftwareTriggerControl 
      Caption         =   "Software Trigger Control"
      Height          =   1215
      Left            =   1320
      TabIndex        =   4
      Top             =   960
      Width           =   5055
      Begin VB.CommandButton GSW 
         Caption         =   "Generate Software Trigger"
         Enabled         =   0   'False
         Height          =   615
         Left            =   1920
         TabIndex        =   6
         Top             =   360
         Width           =   2055
      End
      Begin VB.CheckBox Continuous 
         Caption         =   "Continuous"
         Height          =   375
         Left            =   360
         TabIndex        =   5
         Top             =   360
         Value           =   1  'Checked
         Width           =   1095
      End
   End
End
Attribute VB_Name = "PcrTriggerDlg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Close_Click()
Stop_Click
Sleep 999
Unload Me
End Sub

Private Sub Continuous_Click()
If (Continuous.value = 1) Then
    GSW.Enabled = False
Else
    GSW.Enabled = True
End If
End Sub



Private Sub Form_Load()
Module1.hTriggerThread = 0
CICamera_Freeze ITICam(Current_Camera)
Option1(0).value = True
End Sub

Private Sub GSW_Click()
Module1.BGSW = True
End Sub

Private Sub Option1_Click(index As Integer)
PCR_TRIG_SRC = index

If index <> 0 Then
    SoftwareTriggerControl.Enabled = False
Else
     SoftwareTriggerControl.Enabled = True
End If

End Sub

Private Sub Start_Click(index As Integer)
Dim id As Long

Stop_Click
TriggerThreadStop = False
Continuous.Enabled = False
Start(0).Enabled = False
TriggerSource.Enabled = False
Module1.Continuous = Continuous.value
hTriggerThread = CreateThread(0&, 200000, AddressOf Module1.PcrTriggerThread, 0&, 0, VarPtr(id))
End Sub

Private Sub Stop_Click()
Start(0).Enabled = True
TriggerSource.Enabled = True
If (Module1.hTriggerThread <> 0) Then
Dim WaitFuncRet As Long
Dim CloseFuncRet As Long
TriggerThreadStop = True
WaitFuncRet = WaitForSingleObject(Module1.hTriggerThread, INFINITE)
CloseFuncRet = CloseHandle(Module1.hTriggerThread)
Module1.hTriggerThread = 0
End If

Continuous.Enabled = True
CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Disable, 0

End Sub


