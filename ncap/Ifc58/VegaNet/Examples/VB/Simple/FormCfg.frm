VERSION 5.00
Object = "{5AF5BCD8-0E45-11D5-B186-00105A0F576C}#1.0#0"; "VegaNet.ocx"
Begin VB.Form FormCfg 
   Caption         =   "FormCfg"
   ClientHeight    =   6495
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8820
   LinkTopic       =   "Form2"
   ScaleHeight     =   6495
   ScaleWidth      =   8820
   StartUpPosition =   3  'Windows Default
   Begin VEGANETLib.VnConfig VnConfig1 
      Height          =   5535
      Left            =   240
      TabIndex        =   0
      Top             =   600
      Width           =   8175
      _Version        =   65536
      _ExtentX        =   14420
      _ExtentY        =   9763
      _StockProps     =   0
   End
End
Attribute VB_Name = "FormCfg"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
VnConfig1.AttachVideoSrc Form1.VnVideoSrc1

End Sub
