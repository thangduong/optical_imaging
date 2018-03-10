VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.3#0"; "comctl32.ocx"
Begin VB.Form frmMain 
   Caption         =   "VBExample"
   ClientHeight    =   7335
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9675
   LinkTopic       =   "Form1"
   PaletteMode     =   2  'Custom
   ScaleHeight     =   489
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   645
   StartUpPosition =   3  'Windows Default
   Begin ComctlLib.Toolbar tbToolBar 
      Align           =   1  'Align Top
      Height          =   660
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   9675
      _ExtentX        =   17066
      _ExtentY        =   1164
      ButtonWidth     =   1191
      ButtonHeight    =   1005
      AllowCustomize  =   0   'False
      Appearance      =   1
      ImageList       =   "ImageList1"
      _Version        =   327682
      BeginProperty Buttons {0713E452-850A-101B-AFC0-4210102A8DA7} 
         NumButtons      =   3
         BeginProperty Button1 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Camera"
            Object.ToolTipText     =   "Camera Control"
            Object.Tag             =   ""
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "IO"
            Object.ToolTipText     =   "IO Control"
            Object.Tag             =   ""
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {0713F354-850A-101B-AFC0-4210102A8DA7} 
            Key             =   "Process"
            Object.ToolTipText     =   "Processing Control"
            Object.Tag             =   ""
            ImageIndex      =   3
         EndProperty
      EndProperty
      BorderStyle     =   1
   End
   Begin VB.Frame Display 
      BorderStyle     =   0  'None
      Height          =   5655
      Left            =   0
      TabIndex        =   2
      Top             =   600
      Width           =   8175
   End
   Begin VB.Timer Update_Status 
      Interval        =   1000
      Left            =   7680
      Top             =   5400
   End
   Begin ComctlLib.StatusBar sbStatusBar 
      Align           =   2  'Align Bottom
      Height          =   270
      Left            =   0
      TabIndex        =   0
      Top             =   7065
      Width           =   9675
      _ExtentX        =   17066
      _ExtentY        =   476
      SimpleText      =   ""
      _Version        =   327682
      BeginProperty Panels {0713E89E-850A-101B-AFC0-4210102A8DA7} 
         NumPanels       =   5
         BeginProperty Panel1 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   1
            Object.Width           =   6376
            Text            =   "Board: 0"
            TextSave        =   "Board: 0"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Capture Board selected"
         EndProperty
         BeginProperty Panel2 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "Camera: 0"
            TextSave        =   "Camera: 0"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Current Camera"
         EndProperty
         BeginProperty Panel3 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Text            =   "Mode: DIB"
            TextSave        =   "Mode: DIB"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
         BeginProperty Panel4 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            AutoSize        =   2
            Text            =   "0 X 0"
            TextSave        =   "0 X 0"
            Key             =   ""
            Object.Tag             =   ""
            Object.ToolTipText     =   "Image Size"
         EndProperty
         BeginProperty Panel5 {0713E89F-850A-101B-AFC0-4210102A8DA7} 
            Style           =   5
            AutoSize        =   2
            TextSave        =   "3:27 PM"
            Key             =   ""
            Object.Tag             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComDlg.CommonDialog dlgCommonDialog 
      Left            =   2880
      Top             =   6360
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin ComctlLib.ImageList ImageList1 
      Left            =   2040
      Top             =   6360
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   32
      ImageHeight     =   32
      MaskColor       =   12632256
      _Version        =   327682
      BeginProperty Images {0713E8C2-850A-101B-AFC0-4210102A8DA7} 
         NumListImages   =   3
         BeginProperty ListImage1 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Frmmain.frx":0000
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Frmmain.frx":019A
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {0713E8C3-850A-101B-AFC0-4210102A8DA7} 
            Picture         =   "Frmmain.frx":04B4
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin VB.Menu mnuExit 
      Caption         =   "&Exit"
   End
   Begin VB.Menu mnu_Options 
      Caption         =   "Options"
      Begin VB.Menu mnu_Zoom 
         Caption         =   "Auto Zoom"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpBar1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About VBExample..."
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function OSWinHelp% Lib "user32" Alias "WinHelpA" (ByVal hwnd&, ByVal HelpFile$, ByVal wCommand%, dwData As Any)

Private Sub Form_Activate()
    If Pr_Stop And Not GrabActive Then  ' if No processing going on...
        If Form2.Toolbar1.Buttons.Item(2).value <> tbrPressed Then
            snap_IFC
        End If
    End If
End Sub

Private Sub Form_Load()
    Dim translation As Single

    translation = (Me.width / Me.ScaleWidth)
    Me.width = translation * Image_DX
    Me.height = translation * (Image_DY + sbStatusBar.height + tbToolBar.height)
   
    Load Form1
'    Form1.Hide
    
    Load Form2
 '   Form2.Hide
        
    Load Form3
  '  Form3.Hide
    
End Sub

Private Sub Form_Resize()
    Display.width = fMainForm.ScaleWidth
    If (fMainForm.ScaleHeight - sbStatusBar.height - tbToolBar.height > 0) Then
        Display.height = fMainForm.ScaleHeight - sbStatusBar.height - tbToolBar.height
    Else
        Display.height = 0
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    Dim i As Integer
    If Me.WindowState <> vbMinimized Then
        SaveSetting App.Title, "Settings", "MainLeft", Me.Left
        SaveSetting App.Title, "Settings", "MainTop", Me.Top
        SaveSetting App.Title, "Settings", "MainWidth", Me.width
        SaveSetting App.Title, "Settings", "MainHeight", Me.height
    End If
    Unload Form1
    Unload Form2
    Unload Form3
    Pr_Stop = True  ' Stop any processing, if there is
    Shutdown_IFC
End Sub

Private Sub mnu_Zoom_Click()
    mnu_Zoom.Checked = Not mnu_Zoom.Checked
    If mnu_Zoom.Checked Then
        ZoomAutoSize = True
    Else
        ZoomAutoSize = False
    End If
End Sub

Private Sub mnuExit_Click()
    Pr_Stop = True  ' Stop any processing, if there is
    Unload Me
End Sub

Private Sub mnuHelpAbout_Click()
    frmAbout.Show vbModal, Me
End Sub
Private Sub mnuViewStatusBar_Click()
    If mnuViewStatusBar.Checked Then
        sbStatusBar.Visible = False
        mnuViewStatusBar.Checked = False
    Else
        sbStatusBar.Visible = True
        mnuViewStatusBar.Checked = True
    End If
End Sub


Private Sub mnuViewToolbar_Click()
    If mnuViewToolbar.Checked Then
        tbToolBar.Visible = False
        mnuViewToolbar.Checked = False
    Else
        tbToolBar.Visible = True
        mnuViewToolbar.Checked = True
    End If
End Sub

Private Sub tbToolBar_ButtonClick(ByVal Button As ComctlLib.Button)

    Select Case Button.Key

        Case "Camera"
            'To Do
            Form2.Show 0
            
        Case "IO"
            Form3.Show 0 ' Modal form
            
        Case "Process"
            Form1.Show 1 ' Modal

        Case Else
            'To Do
            MsgBox "No handler for this button!!!"
    End Select
End Sub

Private Sub mnuHelpContents_Click()
    Dim nRet As Integer
    
    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 3, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If
End Sub


Private Sub mnuHelpSearch_Click()
    Dim nRet As Integer

    'if there is no helpfile for this project display a message to the user
    'you can set the HelpFile for your application in the
    'Project Properties dialog
    If Len(App.HelpFile) = 0 Then
        MsgBox "Unable to display Help Contents. There is no Help associated with this project.", vbInformation, Me.Caption
    Else
        On Error Resume Next
        nRet = OSWinHelp(Me.hwnd, App.HelpFile, 261, 0)
        If Err Then
            MsgBox Err.Description
        End If
    End If
End Sub

Private Sub Update_Status_Timer()
    sbStatusBar.Panels(1).Text = "Board: " & Current_Board
    sbStatusBar.Panels(2).Text = "Camera: " & Current_Camera
    If Current_Mode = IFC_DDRAW_SINK Then
        sbStatusBar.Panels(3).Text = "Mode: DDRAW"
    Else
        sbStatusBar.Panels(3).Text = "Mode: DIB"
    End If
        
    sbStatusBar.Panels(4).Text = Image_DX & "X" & Image_DY
End Sub
