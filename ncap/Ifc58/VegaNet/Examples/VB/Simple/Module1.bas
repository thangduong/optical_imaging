Attribute VB_Name = "Module1"



Option Explicit

' Authentication service provider constants
' the default should be used.
Private Const RPC_C_AUTHN_NONE                  As Long = 0
Private Const RPC_C_AUTHN_WINNT                 As Long = 10
Private Const RPC_C_AUTHN_DEFAULT               As Long = &HFFFFFFFF

' Authentication level constants
Private Const RPC_C_AUTHN_LEVEL_DEFAULT         As Long = 0
Private Const RPC_C_AUTHN_LEVEL_NONE            As Long = 1
Private Const RPC_C_AUTHN_LEVEL_CONNECT         As Long = 2
Private Const RPC_C_AUTHN_LEVEL_CALL            As Long = 3
Private Const RPC_C_AUTHN_LEVEL_PKT             As Long = 4
Private Const RPC_C_AUTHN_LEVEL_PKT_INTEGRITY   As Long = 5
Private Const RPC_C_AUTHN_LEVEL_PKT_PRIVACY     As Long = 6

' Impersonation level constants
Private Const RPC_C_IMP_LEVEL_ANONYMOUS         As Long = 1
Private Const RPC_C_IMP_LEVEL_IDENTIFY          As Long = 2
Private Const RPC_C_IMP_LEVEL_IMPERSONATE       As Long = 3
Private Const RPC_C_IMP_LEVEL_DELEGATE          As Long = 4

' Constants for the capabilities
Private Const API_NULL                          As Long = 0
Private Const S_OK                              As Long = 0
Private Const EOAC_NONE                         As Long = &H0
Private Const EOAC_MUTUAL_AUTH                  As Long = &H1
Private Const EOAC_CLOAKING                     As Long = &H10
Private Const EOAC_SECURE_REFS                  As Long = &H2
Private Const EOAC_ACCESS_CONTROL               As Long = &H4
Private Const EOAC_APPID                        As Long = &H8

' Function Declaration

Declare Function GetVersion Lib "kernel32" () As Long

Private Declare Function CoInitializeSecurity Lib "OLE32.DLL" ( _
pSD As Any, _
ByVal cAuthSvc As Long, _
asAuthSvc As Long, _
pReserved1 As Any, _
ByVal dwAuthnlevel As Long, _
ByVal dwImpLevel As Long, _
ByVal pAuthInfo As Long, _
ByVal dwCapabilities As Long, _
pvReserved2 As Any _
) As Long

Sub Main()
    ' This must be called in the executable only.
    ' It will fail in the IDE. To avoid any problem,
    ' include it in a conditional compilation block.
    
    #If RUN_IN_IDE Then
    
      Msgbox "You are running in the IDE"<BR/>
    #Else
'    If (0 = 1) Then
    Dim lngHr As Long
    Dim lngAuthn As Long
    
    If (GetVersion() And &H80000000) Then
      MsgBox "VegaNet does Not run under Win95/98/Me, use NT or Win2K"
      Exit Sub
    End If
    
    lngAuthn = RPC_C_AUTHN_NONE
    lngHr = CoInitializeSecurity(ByVal API_NULL, -1, _
        lngAuthn, ByVal API_NULL, _
        RPC_C_AUTHN_LEVEL_NONE, RPC_C_IMP_LEVEL_IDENTIFY, _
        API_NULL, EOAC_NONE, ByVal API_NULL)
    If (S_OK <> lngHr) Then
'        MsgBox "CoInitializeSecurity failed with error code: 0x" _
'       & Trim$(Str$(Hex(lngHr))), vbCritical, _
'       "Application Initialization Failure"
'        Exit Sub
    End If
    
 '   End If
    
    #End If ' RUN_IN_IDE
    
    ' Any additional code you need here.
    Form1.Show ' showing your starting form
End Sub
