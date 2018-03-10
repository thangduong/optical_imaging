VERSION 5.00
Object = "{5AF5BCD8-0E45-11D5-B186-00105A0F576C}#1.0#0"; "VegaNet.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   8160
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   11880
   LinkTopic       =   "Form1"
   ScaleHeight     =   544
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   792
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Configure 
      Caption         =   "Configure"
      Height          =   615
      Left            =   10080
      TabIndex        =   12
      Top             =   6840
      Width           =   1335
   End
   Begin VB.Timer Timer1 
      Interval        =   99
      Left            =   9480
      Top             =   7800
   End
   Begin VB.ComboBox FillStyles 
      Height          =   315
      ItemData        =   "simple.frx":0000
      Left            =   9960
      List            =   "simple.frx":001C
      TabIndex        =   10
      Text            =   "Solid"
      Top             =   6000
      Width           =   1695
   End
   Begin VB.ComboBox OverlayType 
      Height          =   315
      ItemData        =   "simple.frx":0072
      Left            =   9960
      List            =   "simple.frx":007F
      TabIndex        =   9
      Text            =   "Software"
      Top             =   5160
      Width           =   1695
   End
   Begin VB.ComboBox SolidColor 
      Height          =   315
      ItemData        =   "simple.frx":009A
      Left            =   9960
      List            =   "simple.frx":00AD
      TabIndex        =   6
      Text            =   "Magenta"
      Top             =   4320
      Width           =   1695
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Clear Overlay"
      Height          =   495
      Left            =   10200
      TabIndex        =   5
      Top             =   1320
      Width           =   1215
   End
   Begin VB.ComboBox ColorSel 
      Height          =   315
      ItemData        =   "simple.frx":00D2
      Left            =   9960
      List            =   "simple.frx":00E5
      TabIndex        =   3
      Text            =   "Red"
      Top             =   3480
      Width           =   1695
   End
   Begin VB.ComboBox OverlayObj 
      Height          =   315
      ItemData        =   "simple.frx":010A
      Left            =   9960
      List            =   "simple.frx":011D
      TabIndex        =   1
      Text            =   "Ellipse"
      Top             =   2640
      Width           =   1695
   End
   Begin VEGANETLib.VnDisplay VnDisplay1 
      Height          =   7200
      Left            =   120
      TabIndex        =   0
      Top             =   720
      Width           =   9600
      _Version        =   65536
      _ExtentX        =   16933
      _ExtentY        =   12700
      _StockProps     =   8
      YcrcbKeyColor   =   16777088
      StretchToFit    =   -1  'True
      OverlayKind     =   2
   End
   Begin VEGANETLib.VnVideoSrc VnVideoSrc1 
      Left            =   9600
      Top             =   120
      _Version        =   65536
      _ExtentX        =   2778
      _ExtentY        =   1296
      _StockProps     =   0
   End
   Begin VB.Label Label5 
      Caption         =   "Fill Style"
      Height          =   255
      Left            =   9960
      TabIndex        =   11
      Top             =   5760
      Width           =   1695
   End
   Begin VB.Label Label4 
      Caption         =   "Overlay Kind"
      Height          =   255
      Left            =   9960
      TabIndex        =   8
      Top             =   4920
      Width           =   1695
   End
   Begin VB.Label Label3 
      Caption         =   "Solid Color"
      Height          =   255
      Left            =   9960
      TabIndex        =   7
      Top             =   4080
      Width           =   1455
   End
   Begin VB.Label Label2 
      Caption         =   "Pen Color"
      Height          =   255
      Left            =   9960
      TabIndex        =   4
      Top             =   3240
      Width           =   1455
   End
   Begin VB.Label Label1 
      Caption         =   "Drawing Object"
      Height          =   255
      Left            =   9960
      TabIndex        =   2
      Top             =   2400
      Width           =   1695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim hOvItem As Long
Dim hLongE As Long
Dim hTallE As Long

Dim MouseDownX As Long
Dim MouseDownY As Long

Dim outlineColor As Long
Dim solColor As Long
Dim tCount As Long

Private Const SmallRadius                  As Long = 30
Private Const LargeRadius                  As Long = 80
Private Const ElipsiCenX                  As Long = 130
Private Const ElipsiCenY                  As Long = 130
Private Const PI                  As Double = 3.14159
Dim EllipsiOn As Boolean



Private Sub ColorSel_Click()
    Select Case ColorSel.Text
    Case "Red" ' None
    outlineColor = &HFF&
    Case "Green"
    outlineColor = &HFF00&
    Case "Blue"
    outlineColor = &HFF0000
    Case "Magenta"
    outlineColor = &HFF00FF
    Case "Cyan"
    outlineColor = &HFFFF00
    End Select
    
End Sub


Private Sub Command1_Click()
VnDisplay1.ClearOverlay
hOvItem = 0
hLongE = 0
hTallE = 0
EllipsiOn = True
End Sub



Private Sub Command2_Click()

End Sub

Private Sub Configure_Click()
VnDisplay1.ClearOverlay
hOvItem = 0
hLongE = 0
hTallE = 0
EllipsiOn = False

FormCfg.Show 1

End Sub

Private Sub FillStyles_Click()

    Select Case FillStyles.Text
    Case "HorzLine"
    VnDisplay1.FillStyle = fsHorizontalLine
    Case "VertLine"
    VnDisplay1.FillStyle = fsVerticalLine
    Case "UpDiagonal"
    VnDisplay1.FillStyle = fsUpwardDiagonal
    Case "DownDiagonal"
    VnDisplay1.FillStyle = fsDownwardDiagonal
    Case "Cross"
    VnDisplay1.FillStyle = fsCross
    Case "DiaonalCross"
    VnDisplay1.FillStyle = fsDiagonalCross
    Case "Solid"
    VnDisplay1.FillStyle = fsSolid
    Case "Hollow"
    VnDisplay1.FillStyle = fsHollow
    
    End Select

End Sub


Private Sub Form_Load()
Dim stat As Long

EllipsiOn = False

hOvItem = 0
hLongE = 0
hTallE = 0
MouseDownX = 0
MouseDownY = 0
outlineColor = 255
solColor = &HFF00FF
tCount = 0

Load FormCfg

VnDisplay1.ScrollBars = sbBoth
'VnDisplay1.YcrcbKeyColor = &H1000003&
VnDisplay1.OverlayKind = osSoftwareOverlay
'VnDisplay1.StretchToFit = True
VnDisplay1.DrawStyle = dsDash
VnDisplay1.EnableToolBar = True
VnDisplay1.SetZoom 1#, 1#


'Uncomment following line to do an Explicit connect rather than a QueryConnect
'stat = VnVideoSrc1.Connect("nodeName", "iti.pcp.0")
If Not VnVideoSrc1.QueryConnect Then
    SendKeys "%({F4})"
End If
'VnVideoSrc1.Freeze 0

VnVideoSrc1.ConnectOutputTo 0, VnDisplay1
    ' Start Video source grabbing, use JPEG encoding for video if source and display are not local
    ' to each other

If (VnVideoSrc1.GetVideoSrcName = "ITI.PCR.0") Then
    VnVideoSrc1.SetAcqParam VSP_COLOR_SPACE_CONV, VS_CSC_RGB_TO_RGB, 0
    VnVideoSrc1.SetAcqParam VSP_PIXEL_COLOR, VS_RGB, 0
End If

stat = VnVideoSrc1.GrabToImgNode(VS_FRAME_DJPEG_ENCODE, 2, -1, 0, 0, 0, 0)

FormCfg.VnConfig1.AttachVideoSrc VnVideoSrc1

VnDisplay1.DrawWidth = 5
VnDisplay1.FillColor = solColor
'hEllipse = VnDisplay1.OvEllipse(200, 200, 350, 300, &HFFFF00)
'hBox = VnDisplay1.OvRectangle(250, 100, 400, 180, &HFFFF00)
'hText = VnDisplay1.OvText(50, 50, &HF000F0, "Overlay Text")

End Sub


Private Sub Form_Unload(Cancel As Integer)
VnVideoSrc1.FreezeImgNode
VnVideoSrc1.Disconnect 0
Unload FormCfg

End Sub




Private Sub OverlayType_Click()
Select Case OverlayType.Text
Case "None"
VnDisplay1.OverlayKind = osNoOverlay
Case "YCrCb"
If (VnVideoSrc1.GetVideoSrcName = "ITI.PCR.0") Then
    VnVideoSrc1.FreezeImgNode
    VnVideoSrc1.SetAcqParam VSP_COLOR_SPACE_CONV, VS_CSC_RGB_TO_YCRCB422, 0
    VnVideoSrc1.SetAcqParam VSP_PIXEL_COLOR, VS_YCRCB, 0
    stat = VnVideoSrc1.GrabToImgNode(VS_FRAME_DJPEG_ENCODE, 2, -1, 0, 0, 0, 0)
End If
VnDisplay1.OverlayKind = osYcrcbWithOverlay
Case "Software"
VnDisplay1.OverlayKind = osSoftwareOverlay
End Select
End Sub


Private Sub SolidColor_Click()
    Select Case SolidColor.Text
    Case "Red" ' None
    solColor = &HFF&
    Case "Green"
    solColor = &HFF00&
    Case "Blue"
    solColor = &HFF0000
    Case "Magenta"
    solColor = &HFF00FF
    Case "Cyan"
    solColor = &HFFFF00
    End Select
    VnDisplay1.FillColor = solColor
    
End Sub


Private Sub Timer1_Timer()
Dim d As Double
Dim curFill As Long

If (hLongE <> 0) Then
    VnDisplay1.DeleteOverlayItem hLongE
    hLongE = 0
End If
If (hTallE <> 0) Then
    VnDisplay1.DeleteOverlayItem hTallE
    hTallE = 0
End If

tCount = tCount + 1
If tCount = 60 Then
tCount = 0
End If
If EllipsiOn And VnDisplay1.OverlayKind <> osNoOverlay Then
    d = Sin(tCount * PI / 30) * SmallRadius
    curFill = VnDisplay1.FillStyle
    VnDisplay1.FillStyle = fsHollow
    hTallE = VnDisplay1.OvEllipse(ElipsiCenX - d, ElipsiCenY + LargeRadius, ElipsiCenX + d, ElipsiCenY - LargeRadius, &HFF0000)
    hLongE = VnDisplay1.OvEllipse(ElipsiCenX - LargeRadius, ElipsiCenY + d, ElipsiCenX + LargeRadius, ElipsiCenY - d, &HFF)
    VnDisplay1.FillStyle = curFill
End If

End Sub

Private Sub VnDisplay1_MouseDown(Button As Integer, Shift As Integer, x As Single, y As Single)

MouseDownX = (ScaleX(x, vbTwips, vbPixels) + VnDisplay1.ScrollX) / VnDisplay1.ZoomX
MouseDownY = (ScaleY(y, vbTwips, vbPixels) + VnDisplay1.ScrollY) / VnDisplay1.ZoomY
EllipsiOn = False

End Sub



Private Sub VnDisplay1_MouseMove(Button As Integer, Shift As Integer, x As Single, y As Single)
    Dim xp As Single
    Dim yp As Single
    xp = (ScaleX(x, vbTwips, vbPixels) + VnDisplay1.ScrollX) / VnDisplay1.ZoomX
    yp = (ScaleY(y, vbTwips, vbPixels) + VnDisplay1.ScrollY) / VnDisplay1.ZoomY
   If Button And 1 Then
    'Left Button
    If (hOvItem <> 0) Then
        VnDisplay1.DeleteOverlayItem hOvItem
        hOvItem = 0
    End If
    
    Select Case OverlayObj.Text
    Case "None"
    
    Case "Rectangle"
    hOvItem = VnDisplay1.OvRectangle(MouseDownX, MouseDownY, xp, yp, outlineColor)
    
    Case "Text"
    hOvItem = VnDisplay1.OvText(xp, yp, outlineColor, "Overlay String")
    
    Case "Ellipse"
    hOvItem = VnDisplay1.OvEllipse(MouseDownX, MouseDownY, xp, yp, outlineColor)
    
    Case "Line"
    hOvItem = VnDisplay1.OvLine(MouseDownX, MouseDownY, xp, yp, outlineColor)
    
    End Select
   End If
End Sub

Private Sub VnDisplay1_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
hOvItem = 0
End Sub
