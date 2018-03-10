VERSION 5.00
Object = "{5AF5BCD8-0E45-11D5-B186-00105A0F576C}#1.0#0"; "VegaNet.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   10275
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10860
   LinkTopic       =   "Form1"
   ScaleHeight     =   10275
   ScaleWidth      =   10860
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Start 
      Caption         =   "Start"
      Height          =   495
      Left            =   9840
      TabIndex        =   2
      Top             =   1800
      Width           =   975
   End
   Begin VB.CommandButton Stop 
      Caption         =   "Stop"
      Height          =   495
      Left            =   9840
      TabIndex        =   1
      Top             =   2400
      Width           =   975
   End
   Begin VEGANETLib.VnDisplay VnDisplay1 
      Height          =   7455
      Left            =   120
      TabIndex        =   0
      Top             =   480
      Width           =   9495
      _Version        =   65536
      _ExtentX        =   16748
      _ExtentY        =   13150
      _StockProps     =   8
   End
   Begin VEGANETLib.VnVideoSrc VnVideoSrc1 
      Left            =   8160
      Top             =   240
      _Version        =   65536
      _ExtentX        =   2143
      _ExtentY        =   1085
      _StockProps     =   0
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Private Sub Form_Load()


If Not VsConnected Then
    VnVideoSrc1.QueryConnect
'Uncomment following line to do an Explicit connect rather than a QueryConnect
'stat = VnVideoSrc1.Connect("nodeName", "iti.pcp.0")
    VsConnected = True
End If

VnDisplay1.ScrollBars = sbBoth
'VnDisplay1.YcrcbKeyColor = &H1000003&
VnDisplay1.YcrcbKeyColor = 200
VnDisplay1.OverlayKind = osSoftwareOverlay
'VnDisplay1.OverlayKind = osYcrcbWithOverlay
'VnDisplay1.StretchToFit = True
VnDisplay1.DrawStyle = dsDash
VnDisplay1.EnableToolBar = True
VnDisplay1.SetZoom 1#, 1#

End Sub


Private Sub Form_Unload(Cancel As Integer)
Pr_Stop = True

End Sub

Private Sub Start_Click()

Dim ImageWidth As Long
Dim ImageHeight As Long
Dim BytesPerPix As Long
Dim BitsPerPix As Long
Dim ImageColor As VS_COLOR
Dim TotalNumFrames As Long
Dim grabID As Long
Dim frameSeqNum As Long
Dim ringSeqNum As Long
Dim frameAddr As Long

VnVideoSrc1.GetAttr ImageWidth, ImageHeight, BytesPerPix, BitsPerPix, ImageColor
       
ReDim Host_Frame(ImageWidth * BytesPerPix * ImageHeight * NumRingFrames / 4) As Long
Pr_Stop = False
TotalNumFrames = 100000
grabID = VnVideoSrc1.Grab(0, Host_Frame(0), NumRingFrames, TotalNumFrames, 0, 0, 0, 0)
VnDisplay1.CreateBuffDisplay Host_Frame(0), ImageWidth, ImageHeight, BitsPerPix, ImageColor

    Do While Not Pr_Stop
    
        ringSeqNum = VnVideoSrc1.GrabWaitFrame(grabID, frameAddr, -1, 2000, True, frameSeqNum, VS_FRAME_JPEG_ENCODE)
        
        If (ringSeqNum >= 0) Then
            Invert Host_Frame, ringSeqNum, ImageWidth, ImageHeight, BytesPerPix
            VnDisplay1.SetBufferAddr Host_Frame(ImageWidth * BytesPerPix * ImageHeight * ringSeqNum / 4)
            VnDisplay1.Display
            VnVideoSrc1.GrabRelease grabID, ringSeqNum
        End If
        DoEvents
    Loop
    
VnVideoSrc1.Freeze grabID
    

End Sub

Private Sub Stop_Click()
Pr_Stop = True
End Sub
