VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form Form2 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Camera Control"
   ClientHeight    =   585
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4860
   LinkTopic       =   "Form2"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   585
   ScaleWidth      =   4860
   ShowInTaskbar   =   0   'False
   Begin ComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   630
      Left            =   0
      TabIndex        =   0
      Top             =   0
      Width           =   4860
      _ExtentX        =   8573
      _ExtentY        =   1111
      ButtonWidth     =   1138
      ButtonHeight    =   953
      AllowCustomize  =   0   'False
      Appearance      =   1
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   9
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Grab"
            Key             =   "Grab"
            Object.ToolTipText     =   "Show Image in Contunuous Grab Mode"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Snap"
            Key             =   "Snap"
            Object.ToolTipText     =   "Show Frozen Image"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Trigger"
            Key             =   "Trigger"
            Object.ToolTipText     =   "Triggered Acquistion Operations"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Button4 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button5 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "DDraw"
            Key             =   "DDraw"
            Object.ToolTipText     =   "Select Direct Draw display mode"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Button6 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "DIB"
            Key             =   "DIB"
            Object.ToolTipText     =   "Select DIB Display Mode"
            Object.Tag             =   ""
            Value           =   1
         EndProperty
         BeginProperty Button7 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   ""
            Object.Tag             =   ""
            Style           =   3
            MixedState      =   -1  'True
         EndProperty
         BeginProperty Button8 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Board"
            Key             =   "Board"
            Object.Tag             =   ""
         EndProperty
         BeginProperty Button9 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Caption         =   "Camera"
            Key             =   "Camera"
            Object.Tag             =   ""
         EndProperty
      EndProperty
      BorderStyle     =   1
      Begin VB.Image Image1 
         Height          =   15
         Left            =   0
         Top             =   600
         Width           =   7575
      End
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Me.Hide
End Sub

Private Sub Toolbar1_ButtonClick(ByVal Button As ComctlLib.Button)
   Select Case Button.Key
   
    Case "Grab"
        Pr_Stop = True
        GrabActive = True
        Button.value = tbrPressed
        Toolbar1.Buttons.Item(2).value = tbrUnpressed
        Toolbar1.Buttons.Item(3).value = tbrUnpressed
        grab_IFC
   Case "Snap"
        Toolbar1.Buttons.Item(1).value = tbrUnpressed
        Toolbar1.Buttons.Item(3).value = tbrUnpressed
        GrabActive = False
        snap_IFC
    Case "Trigger"
        Toolbar1.Buttons.Item(2).value = tbrUnpressed
        Toolbar1.Buttons.Item(1).value = tbrUnpressed
        'GrabActive = False
        trigger_IFC
    Case "Board"
        Style = 0 ' Board
        frmCameraSel.Show 1
    Case "Camera"
        Style = 1 ' Camera
        frmCameraSel.Show 1
    Case "DDraw"
        Toolbar1.Buttons.Item(4).value = 1
        Toolbar1.Buttons.Item(5).value = 0
        Current_Mode = IFC_DDRAW_SINK
        If Toolbar1.Buttons.Item(1).value = tbrPressed Then
            grab_IFC
        End If
    Case "DIB"
        Toolbar1.Buttons.Item(4).value = 0
        Toolbar1.Buttons.Item(5).value = 1
        Current_Mode = IFC_DIB_SINK
        If Toolbar1.Buttons.Item(1).value = tbrPressed Then
            grab_IFC
        End If
    End Select
End Sub
