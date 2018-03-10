VERSION 5.00
Begin VB.Form Form1 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Image Processing"
   ClientHeight    =   1185
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3555
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   1  'UseZOrder
   ScaleHeight     =   1185
   ScaleWidth      =   3555
   ShowInTaskbar   =   0   'False
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "Stop"
      Height          =   375
      Left            =   2400
      TabIndex        =   3
      Top             =   600
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Start"
      Height          =   375
      Left            =   2400
      TabIndex        =   2
      Top             =   120
      Width           =   975
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "Form1.frx":0000
      Left            =   240
      List            =   "Form1.frx":000D
      Style           =   2  'Dropdown List
      TabIndex        =   1
      Top             =   480
      Width           =   1575
   End
   Begin VB.Label Label7 
      Caption         =   "Processing Algorithm:"
      Height          =   255
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Pr_Stop = False
    GrabActive = False
    snap_IFC
    Form2.Toolbar1.Buttons.Item(2).value = tbrUnpressed
    Form2.Toolbar1.Refresh
    Process (Combo1.Text)
End Sub

Private Sub Command2_Click()
    Pr_Stop = True
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Pr_Stop = True
End Sub
