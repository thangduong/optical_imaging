VERSION 5.00
Begin VB.Form frmCameraSel 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Camera Select"
   ClientHeight    =   1590
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   1695
   ControlBox      =   0   'False
   LinkTopic       =   "Form4"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   PaletteMode     =   2  'Custom
   ScaleHeight     =   1590
   ScaleWidth      =   1695
   StartUpPosition =   1  'CenterOwner
   Begin VB.CommandButton Command1 
      Caption         =   "OK"
      Height          =   375
      Left            =   960
      TabIndex        =   4
      Top             =   120
      Width           =   615
   End
   Begin VB.OptionButton Option1 
      Caption         =   "# 3"
      Height          =   255
      Index           =   3
      Left            =   120
      TabIndex        =   3
      Top             =   1200
      Width           =   735
   End
   Begin VB.OptionButton Option1 
      Caption         =   "# 2"
      Height          =   255
      Index           =   2
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   735
   End
   Begin VB.OptionButton Option1 
      Caption         =   "# 1"
      Height          =   255
      Index           =   1
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   735
   End
   Begin VB.OptionButton Option1 
      Caption         =   "# 0"
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Value           =   -1  'True
      Width           =   735
   End
End
Attribute VB_Name = "frmCameraSel"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    If Style = 1 Then ' Camera
        For i = 0 To 3
            If i < Num_Cameras Then
                Option1(i).Enabled = True
            Else
                Option1(i).Enabled = False
            End If
        Next i

        Me.Caption = "Camera Selection"
        Option1(Current_Camera).value = True
    Else ' Board
        Me.Caption = "Board Selection"
        For i = 0 To 3
            If i < Capture_Boards Then
                Option1(i).Enabled = True
            Else
                Option1(i).Enabled = False
            End If
        Next i
        Option1(Current_Board).value = True
    End If
    
End Sub

Private Sub Option1_Click(index As Integer)
    Dim translation As Single
    
    If Style = 1 Then ' Camera Selection
        Current_Camera = index
    Else '   Board Selection
        Current_Board = index
    End If
    
    ITICam(Current_Camera) = CICapMod_GetCam(CapMod(Current_Board), Current_Camera)
    ' Get the camera's basic attributes

    CICamera_GetAttr ITICam(Current_Camera), attr, True
   
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight
  
   ReDim Host_Frame(Image_DX * SrcBytesPP, Image_DY * NumRingFrames) As Byte
    
    translation = (fMainForm.width / fMainForm.ScaleWidth)
    fMainForm.width = translation * Image_DX
    fMainForm.height = translation * (Image_DY + fMainForm.sbStatusBar.height + fMainForm.tbToolBar.height)
    fMainForm.Display.width = fMainForm.ScaleWidth
    fMainForm.Display.height = fMainForm.ScaleHeight - fMainForm.sbStatusBar.height - fMainForm.tbToolBar.height
    
    If GrabActive = True Then
       grab_IFC
    Else
       snap_IFC
    End If
 
End Sub
