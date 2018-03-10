VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form Form3 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "IO control"
   ClientHeight    =   5220
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4350
   LinkTopic       =   "Form3"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   5220
   ScaleWidth      =   4350
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame1 
      Caption         =   "Input"
      Height          =   3495
      Left            =   1680
      TabIndex        =   15
      Top             =   240
      Width           =   1095
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   0
         Left            =   600
         Shape           =   3  'Circle
         Top             =   360
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   1
         Left            =   600
         Shape           =   3  'Circle
         Top             =   720
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   2
         Left            =   600
         Shape           =   3  'Circle
         Top             =   1080
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   3
         Left            =   600
         Shape           =   3  'Circle
         Top             =   1440
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   4
         Left            =   600
         Shape           =   3  'Circle
         Top             =   1800
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   5
         Left            =   600
         Shape           =   3  'Circle
         Top             =   2160
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   6
         Left            =   600
         Shape           =   3  'Circle
         Top             =   2520
         Width           =   135
      End
      Begin VB.Shape ISL 
         FillColor       =   &H0000FF00&
         FillStyle       =   0  'Solid
         Height          =   135
         Index           =   7
         Left            =   600
         Shape           =   3  'Circle
         Top             =   2880
         Width           =   135
      End
      Begin VB.Label Input 
         Caption         =   "0"
         Height          =   255
         Index           =   0
         Left            =   360
         TabIndex        =   24
         Top             =   360
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "1"
         Height          =   255
         Index           =   1
         Left            =   360
         TabIndex        =   23
         Top             =   720
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "2"
         Height          =   255
         Index           =   2
         Left            =   360
         TabIndex        =   22
         Top             =   1080
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "3"
         Height          =   255
         Index           =   3
         Left            =   360
         TabIndex        =   21
         Top             =   1440
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "4"
         Height          =   255
         Index           =   4
         Left            =   360
         TabIndex        =   20
         Top             =   1800
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "5"
         Height          =   255
         Index           =   5
         Left            =   360
         TabIndex        =   19
         Top             =   2160
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "6"
         Height          =   255
         Index           =   6
         Left            =   360
         TabIndex        =   18
         Top             =   2520
         Width           =   255
      End
      Begin VB.Label Input 
         Caption         =   "7"
         Height          =   255
         Index           =   7
         Left            =   360
         TabIndex        =   17
         Top             =   2880
         Width           =   255
      End
      Begin VB.Label Label3 
         Caption         =   "#"
         Height          =   255
         Left            =   240
         TabIndex        =   16
         Top             =   3120
         Width           =   615
      End
   End
   Begin VB.CommandButton Command2 
      Caption         =   "OK"
      Height          =   495
      Left            =   3120
      TabIndex        =   14
      Top             =   360
      Width           =   975
   End
   Begin VB.TextBox txtMS 
      Enabled         =   0   'False
      Height          =   285
      Left            =   240
      TabIndex        =   10
      Text            =   "50"
      Top             =   3840
      Width           =   495
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Start Monitor"
      Height          =   375
      Left            =   1560
      TabIndex        =   9
      Top             =   3840
      Width           =   1335
   End
   Begin VB.Frame Frame2 
      Caption         =   "Output"
      Height          =   3495
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   1095
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "4"
         Height          =   255
         Index           =   4
         Left            =   240
         TabIndex        =   8
         Top             =   1800
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "5"
         Height          =   255
         Index           =   5
         Left            =   240
         TabIndex        =   7
         Top             =   2160
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "6"
         Height          =   255
         Index           =   6
         Left            =   240
         TabIndex        =   6
         Top             =   2520
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "7"
         Height          =   255
         Index           =   7
         Left            =   240
         TabIndex        =   5
         Top             =   2880
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "3"
         Height          =   255
         Index           =   3
         Left            =   240
         TabIndex        =   4
         Top             =   1440
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "2"
         Height          =   255
         Index           =   2
         Left            =   240
         TabIndex        =   3
         Top             =   1080
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "1"
         Height          =   255
         Index           =   1
         Left            =   240
         TabIndex        =   2
         Top             =   720
         Width           =   375
      End
      Begin VB.CheckBox Out 
         Alignment       =   1  'Right Justify
         Caption         =   "0"
         Height          =   255
         Index           =   0
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   375
      End
   End
   Begin VB.Timer Status_Timer 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   3240
      Top             =   1200
   End
   Begin ComctlLib.Slider Slider1 
      Height          =   375
      Left            =   120
      TabIndex        =   12
      Top             =   4680
      Width           =   3975
      _ExtentX        =   7011
      _ExtentY        =   661
      _Version        =   327682
      Min             =   1
      Max             =   100
      SelStart        =   50
      Value           =   50
   End
   Begin VB.Label Label5 
      Alignment       =   2  'Center
      Caption         =   "Monitor Interval"
      Height          =   255
      Left            =   120
      TabIndex        =   13
      Top             =   4320
      Width           =   3975
   End
   Begin VB.Label Label6 
      Caption         =   "ms"
      Height          =   255
      Left            =   840
      TabIndex        =   11
      Top             =   3840
      Width           =   255
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()
     If Status_Timer.Enabled Then
        Status_Timer.Enabled = False
        Command1.Caption = "Start Monitor"
    Else
        Status_Timer.Enabled = True
        Command1.Caption = "Stop Monitor"
    End If
End Sub

Private Sub Command2_Click()
    If Status_Timer.Enabled Then ' If Monitoring
        Command1_Click  ' Stop Monitor
    End If
    Me.Hide
End Sub

Private Sub Out_Click(Index As Integer)
    For x = 0 To 7
    If Out(x).value Then
        Output_Val = Output_Val And 255 - (2 ^ x)
    Else
        Output_Val = Output_Val Or (2 ^ x)
    End If
    Next
    CICapMod_OutportVal CapMod(Current_Board), Output_Val, 0
End Sub

Private Sub Slider1_Click()
    Status_Timer.Interval = Slider1.value
    txtMS.Text = Str(Slider1.value)
End Sub

Private Sub Slider1_Scroll()
    Slider1_Click
End Sub

Private Sub Status_Timer_Timer()
    Input_Val = CICapMod_InportVal(CapMod(Current_Board), 0)
    Label3.Caption = "# " & Input_Val
    For i = 0 To 7
        If ((2 ^ i) And Input_Val) = (2 ^ i) Then ' Put IFC read port # code here
            ISL(i).FillColor = &HFF& 'Red
        Else
            ISL(i).FillColor = 65280    'Green
        End If
    Next i
End Sub
