Attribute VB_Name = "Module1"
Option Explicit
'trigger varibales
Global TriggerThreadStop As Boolean         'Flag to stop trigger thread functio
Global hTriggerThread As Long               ' Handle to the trigger thread
Global Continuous As Boolean                ' Continuous SW trigger flag
Global BGSW As Boolean                      ' Generate software trigger button value

Public fMainForm As frmMain
Global reti As Integer          'These are function return
Global Style As Integer         ' Style of menu
Global Pr_Stop As Boolean       ' Tells processing loop to exit
Global GrabActive As Boolean    ' If True Grab is active
Global ZoomAutoSize As Boolean  ' If True size image to window
Global Capture_Boards As Integer   '
Global Num_Cameras As Integer
Global Current_Camera As Integer ' 0 to 4
Global Current_Board As Integer ' 0 to Capture_Boards
Global Current_Mode As SINK_KIND
Global BoardNames() As Variant      ' Holds board names


Global ITICam(16) As Long       'Main Camera Pointers
Global CapMod(4) As Long    'CapMod Pointers
Global attr As CAM_ATTR
Global SrcBytesPP As Integer
Global Image_DX As Integer      'Image X Size Vars

Global Image_DY As Integer      'Image y Size Var
Global My_Interrupt As Long     'Interrupt event for display

Global Cam_Source As Long       ' Camera Source ID
Global Host_Source As Long      ' Host source ID
Global Display_Sink As Long     ' Display Sink ID
Global Cam_Conn As Long         ' Camera Connection ID
Global Host_Conn As Long        ' Host Connection ID
Global ImgSrvr As Long          ' Image Server ID

Global Host_Frame() As Byte ' this is the default size
Global Output_Val As Byte
Global Input_Val As Byte
Global Const NumRingFrames = 4

Global PCR_TRIG_SRC As PCR_TRIG_SRC_TYPE
Global PcpTrigSrc As PCP_TRIG_SRC_TYPE
Global IFC_TRIG_SRC As IFC_TRIG_SRC_TYPE
Global IFC_EDGE As IFC_EDGE_TYPE
Global IFC_STROBE_MODE As IFC_STROBE_MODE_TYPE
Global IFC_STROBE_POLARITY As IFC_POLARITY_TYPE
Global IFC_FRAME_RESET_POLARITY As IFC_POLARITY_TYPE
Global IFC_FRAME_RESET_SIZE As IFC_FRAME_RESET_SIZE_TYPE

''''''''''''''''''''''''''''''''''''''''''''''''''''
''''''''''''''''''''''''''''''''''''''''''''''''''''

Sub Main()
    frmSplash.Show
    frmSplash.Refresh
    Set fMainForm = New frmMain
    Pr_Stop = True
    GrabActive = False
    ZoomAutoSize = False
    Current_Camera = 0
    Current_Board = 0
    Current_Mode = IFC_DIB_SINK
    Cam_Source = 0
    Host_Source = 0
    Display_Sink = 0
    Cam_Conn = 0
    Host_Conn = 0
    ImgSrvr = 0
    Num_Cameras = 0
    
    If Not Init_IFC Then
        Unload frmSplash
        MsgBox "Cant Initialize the ITI Capture Board!!"
        Unload frmMain
        End 'Stop Program here
    End If
    Load fMainForm
    Unload frmSplash
    fMainForm.Show
    reti = fMainForm.ScaleMode
    
    CreateSourcesAndSinks
    CreateHostConn
End Sub

Public Function Process(Pr_Select As String) As Boolean
    KillAll
    CreateSourcesAndSinks
    CreateHostConn
    Do While Not Pr_Stop
        ' Freeze in case a grab is in progress
        CICamera_Freeze ITICam(Current_Camera)
        reti = CICamera_Snap_HostBuf(ITICam(Current_Camera), Host_Frame(0, 0), 0, 0, attr.dwWidth, attr.dwHeight)   ' Pass first item in the array
        Select Case Pr_Select
        
        Case "Threshold"
            Threshold Host_Frame
        Case "Invert"
           Invert Host_Frame
        Case "None"
        Case ""
           ' No processing
        Case Else
            MsgBox "Process not supported"
            Process = False
            Exit Function
        End Select
            ' Display host buffer
        CImgConn_Display Host_Conn
        DoEvents
    Loop
End Function

Function GetCommandLine(Optional MaxArgs)
   'Declare variables.
   Dim c, cmdLine, CmdLnLen, InArg, i, NumArgs
   'See if MaxArgs was provided.
   If IsMissing(MaxArgs) Then MaxArgs = 10
   'Make array of the correct size.
   ReDim ArgArray(MaxArgs)
   NumArgs = 0: InArg = False
   'Get command line arguments.
   cmdLine = Command()
   CmdLnLen = Len(cmdLine)
   'Go thru command line one character
   'at a time.
   For i = 1 To CmdLnLen
      c = Mid(cmdLine, i, 1)
      'Test for space or tab.
      If (c <> " " And c <> vbTab) Then
         'Neither space nor tab.
         'Test if already in argument.
         If Not InArg Then
         'New argument begins.
         'Test for too many arguments.
            If NumArgs = MaxArgs Then Exit For
            NumArgs = NumArgs + 1
            InArg = True
         End If
         'Concatenate character to current argument.
         ArgArray(NumArgs) = ArgArray(NumArgs) & c
      Else
         'Found a space or tab.
         'Set InArg flag to False.
         InArg = False
      End If
   Next i
   'Resize array just enough to hold arguments.
   ReDim Preserve ArgArray(NumArgs + 1)
   ArgArray(NumArgs + 1) = 0
   'Return Array in Function name.
   GetCommandLine = ArgArray()
End Function





Public Function Init_IFC() As Boolean
    ' Sequence through boards
    ' Create object for each board
On Error GoTo init_ifc_err
    
    Dim index As Long
    Dim capdone As Boolean
    ReDim cmdLine(4)
    'Dim BoardNames() As Variant
    BoardNames = Array("ICP", "PCD", "PCR", "PCL", "PCP", "LNK", "BDT", "P2V", "CL2", "")
    capdone = False
    index = 0
    Current_Board = 0
    Current_Camera = 0
    cmdLine = GetCommandLine(4)
    Capture_Boards = 0
    If cmdLine(1) <> 0 Then
        CapMod(Current_Board) = IFC_IfxCreateCaptureModule(cmdLine(1), index, cmdLine(1) & "test.txt")
        If CapMod(Capture_Boards) = 0 Then
            CapMod(Capture_Boards) = IFC_IfxCreateCaptureModule(cmdLine(1), 0, "")
        End If
        If CapMod(Current_Board) = 0 Then
            MsgBox "No " & cmdLine(1) & " ITI Capture module installed, or Config File " & cmdLine(1) & "test.txt not found.", vbCritical, "ERROR: Program will exit"
        Else
            Capture_Boards = 1
        End If
    Else
        Do While BoardNames(index) <> ""
            CapMod(Capture_Boards) = IFC_IfxCreateCaptureModule(BoardNames(index), 0, BoardNames(index) & "test.txt")
            If CapMod(Capture_Boards) = 0 Then
                CapMod(Capture_Boards) = IFC_IfxCreateCaptureModule(BoardNames(index), 0, "")
            End If
            If CapMod(Capture_Boards) <> 0 Then
                Capture_Boards = Capture_Boards + 1
            End If
            index = index + 1
        Loop
    End If
    
    
    
    If CapMod(Current_Board) = 0 Then
            MsgBox "No ITI Capture module installed, or required Config File not found", vbCritical, "ERROR: Program will exit"
            Init_IFC = False
            Exit Function
    End If
    
    index = 0
    capdone = False
    Do While index < 4 And capdone = False
        ITICam(index) = CICapMod_GetCam(CapMod(Current_Board), index)
        If ITICam(index) = 0 Then
            capdone = True
        Else
            index = index + 1
        End If
    Loop
        
    Num_Cameras = index
    
    ' Get the camera's basic attributes

    CICamera_GetAttr ITICam(Current_Camera), attr, True
       
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight
    ReDim Host_Frame(Image_DX * SrcBytesPP, Image_DY * NumRingFrames) As Byte
    Init_IFC = True
    ' MsgBox "Number of boards found: " & Capture_Boards, vbInformation, "Info"
Exit Function
init_ifc_err:
    
    If MsgBox(Err.Description & " Continue?", vbYesNo, "ERROR!!!") = vbYes Then
        Resume Next
    Else
        Exit Function
    End If
  
            

End Function
Public Function grab_IFC()
    CICamera_GetAttr ITICam(Current_Camera), attr, True
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight
    CICamera_Freeze ITICam(Current_Camera)
    CICamera_Grab ITICam(Current_Camera) ' needed to start board acquisition
    KillAll
    CreateSourcesAndSinks
    CreateCamConn
    CreateCamServer
End Function
Public Function snap_IFC()
 '   CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_DISABLE, 0
    CICamera_Freeze ITICam(Current_Camera)
    CICamera_Snap ITICam(Current_Camera) ' needed to tell board to snap an image
    KillAll
    CreateSourcesAndSinks
    CreateCamConn
    CImgConn_Display Cam_Conn
End Function
Public Function trigger_IFC()
    
    Select Case CModule_ModName(CapMod(Current_Board))
    
    Case "PCR"
    PcrTriggerDlg.Show 1
    
    Case "ICP"
    PcvTriggerDlg.Show 1
    
    Case "PCP"
    PcpTriggerDlg.Show 1

    Case "P2V"
    P2vTriggerDlg.Show 1

    
    Case "PCD"
    MsgBox "This example does not support PCD board"
    
    Case "PCL"
    MsgBox "This example does not support PCL board"
    
    Case "LNK"
    MsgBox "This example does not support CamLink board"
    
    Case "BDT"
    MsgBox "This example does not support BanditII board"
    
    End Select
End Function

Public Function PcrTriggerThread() As Long
    Dim Grab_HostBuf_ret
    Dim iSeqNum As Long
    Dim frameAddr As Long
    Dim acquiredDy As Long
    
    CICamera_GetAttr ITICam(Current_Camera), attr, True
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight

    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Enable, 0
    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_SRC, PCR_TRIG_SRC, 0
    KillAll
    CreateSourcesAndSinks
    CreateHostConn
    CICamera_Freeze ITICam(Current_Camera)
    Grab_HostBuf_ret = CICamera_Grab_HostBuf(ITICam(Current_Camera), Host_Frame(0, 0), NumRingFrames, -1, 0, 0, 0, 0)
    Sleep 20
Do Until TriggerThreadStop = True
    If (PCR_TRIG_SRC = PCR_SOFT_TRIG) Then
        If (Continuous = True Or BGSW = True) Then
            BGSW = False
            CICamera_SetAcqParam ITICam(Current_Camera), P_GEN_SW_TRIGGER, 1, 0
        End If
    End If
    
    iSeqNum = CICamera_GrabWaitFrame(ITICam(Current_Camera), frameAddr, -1, 10, True, 0&)
    If (iSeqNum >= 0) Then
    CImgSrc_SetBufferAddr Host_Source, frameAddr
    CImgConn_Display Host_Conn
    CICamera_GrabRelease ITICam(Current_Camera), iSeqNum
    End If

Loop
    CICamera_Freeze (ITICam(Current_Camera))
    PcrTriggerThread = 0
End Function

Public Function PcpTriggerThread() As Long
    Dim Grab_HostBuf_ret
    Dim iSeqNum As Long
    Dim frameAddr As Long
    Dim acquiredDy As Long
    
    CICamera_GetAttr ITICam(Current_Camera), attr, True
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight

    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Enable, 0
    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_SRC, PcpTrigSrc, 0
    KillAll
    CreateSourcesAndSinks
    CreateHostConn
    CICamera_Freeze ITICam(Current_Camera)
    Grab_HostBuf_ret = CICamera_Grab_HostBuf(ITICam(Current_Camera), Host_Frame(0, 0), NumRingFrames, -1, 0, 0, 0, 0)
    Sleep 20
Do Until TriggerThreadStop = True
    If (PcpTrigSrc = PCP_SOFT_TRIG) Then
        If (Continuous = True Or BGSW = True) Then
            BGSW = False
            CICamera_SetAcqParam ITICam(Current_Camera), P_GEN_SW_TRIGGER, 1, 0
        End If
    End If
    
    iSeqNum = CICamera_GrabWaitFrame(ITICam(Current_Camera), frameAddr, -1, 10, True, 0&)
    If (iSeqNum >= 0) Then
    CImgSrc_SetBufferAddr Host_Source, frameAddr
    CImgConn_Display Host_Conn
    CICamera_GrabRelease ITICam(Current_Camera), iSeqNum
    End If

Loop
    CICamera_Freeze (ITICam(Current_Camera))
    PcpTriggerThread = 0
End Function


Public Function PcvTriggerThread() As Long
    Dim hTrigOp As Long
    Dim TrigSnapRet As Long
    Dim WaitTrigRet As Long
    Dim TrigReadRet As Long
    Dim StopTrigOpsRet As Long
    Dim frameAddr As Long
    Dim acquiredDy As Long
    
    
    CICamera_GetAttr ITICam(Current_Camera), attr, True
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight
    
    KillAll
    CreateSourcesAndSinks
    CreateHostConn
    CICamera_Freeze ITICam(Current_Camera)


    hTrigOp = CICapMod_StartTrigOps(CapMod(Current_Board), ITICam(Current_Camera))
    
    
    If (hTrigOp <> 0&) Then
            TrigSnapRet = CICapMod_TrigSnap(CapMod(Current_Board), hTrigOp, 0)
            If (IFC_TRIG_SRC = IFC_SOFT_TRIG) Then
                CICamera_SetAcqParam ITICam(Current_Camera), P_GEN_SW_TRIGGER, 1, 0
            End If
            
            Do Until TriggerThreadStop = True
               WaitTrigRet = CICapMod_WaitTrig(CapMod(Current_Board), hTrigOp, 1000)
               TrigSnapRet = CICapMod_TrigSnap(CapMod(Current_Board), hTrigOp, 1)
               If (IFC_TRIG_SRC = IFC_SOFT_TRIG) Then
                CICamera_SetAcqParam ITICam(Current_Camera), P_GEN_SW_TRIGGER, 1, 0
               End If
              
               TrigReadRet = CICapMod_TrigRead(CapMod(Current_Board), hTrigOp, 0, 0, Image_DX, Image_DY, Host_Frame(0, 0))
               CImgConn_Display Host_Conn
               
            Loop
            
    End If
    
    WaitTrigRet = CICapMod_WaitTrig(CapMod(Current_Board), hTrigOp, 0)
    StopTrigOpsRet = CICapMod_StopTrigOps(CapMod(Current_Board), hTrigOp)
    
    KillAll
    CICamera_Freeze (ITICam(Current_Camera))
    PcvTriggerThread = 0
End Function


Public Function P2vTriggerThread() As Long
    Dim Grab_HostBuf_ret
    Dim iSeqNum As Long
    Dim frameAddr As Long
    Dim acquiredDy As Long
    
    CICamera_GetAttr ITICam(Current_Camera), attr, True
    SrcBytesPP = attr.dwBytesPerPixel
    Image_DX = attr.dwWidth
    Image_DY = attr.dwHeight

    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_ENABLE, IFC_Enable, 0
    CICamera_SetAcqParam ITICam(Current_Camera), P_TRIGGER_SRC, IFC_TRIG_SRC, 0
    KillAll
    CreateSourcesAndSinks
    CreateHostConn
    CICamera_Freeze ITICam(Current_Camera)
    Grab_HostBuf_ret = CICamera_Grab_HostBuf(ITICam(Current_Camera), Host_Frame(0, 0), NumRingFrames, -1, 0, 0, 0, 0)
    Sleep 20
Do Until TriggerThreadStop = True
    If (IFC_TRIG_SRC = IFC_SOFT_TRIG) Then
        If (Continuous = True Or BGSW = True) Then
            BGSW = False
            CICamera_SetAcqParam ITICam(Current_Camera), P_GEN_SW_TRIGGER, 1, 0
        End If
    End If
    
    iSeqNum = CICamera_GrabWaitFrame(ITICam(Current_Camera), frameAddr, -1, 10, True, 0&)
    If (iSeqNum >= 0) Then
    CImgSrc_SetBufferAddr Host_Source, frameAddr
    CImgConn_Display Host_Conn
    CICamera_GrabRelease ITICam(Current_Camera), iSeqNum
    End If

Loop
    CICamera_Freeze (ITICam(Current_Camera))
    P2vTriggerThread = 0
End Function


Public Function Shutdown_IFC()
    KillAll
    Dim index As Integer
    For index = 0 To (Capture_Boards - 1)
        IFC_IfxDeleteCaptureModule CapMod(index)
    Next index
    ' Put IFC exit stuff here
End Function

Public Sub Display_Buffer(ByVal WindowHandle As Long, ByRef Buffer() As Byte)
    If Cam_Conn <> 0 Then
        CImgConn_Display Cam_Conn
    End If
End Sub

Public Function KillServer()
End Function

Public Function KillConnections()
    If Cam_Conn Then
        IFC_IfxDeleteImgConn Cam_Conn
        Cam_Conn = 0
    End If
   
    If Host_Conn Then
        IFC_IfxDeleteImgConn Host_Conn
        Host_Conn = 0
    End If
End Function

Public Function KillSources()
    If Host_Source Then
        IFC_IfxDeleteImgSrc Host_Source
        Host_Source = 0
    End If
    If Cam_Source Then
        IFC_IfxDeleteImgSrc Cam_Source
        Cam_Source = 0
    End If
End Function

Public Function KillSinks()
    If Display_Sink Then
        IFC_IfxDeleteImgSink Display_Sink
        Display_Sink = 0
    End If
End Function

Public Function CreateSinks()
    Display_Sink = IFC_IfxCreateImgSink(fMainForm.Display.hwnd, Current_Mode, 0, 0, Image_DX, Image_DY)
End Function

Public Function CreateSources()
    Host_Source = IFC_IfxCreateImgSrc_HostBuf(Host_Frame(0, 0), attr)
    Cam_Source = IFC_IfxCreateImgSrc_Cam(ITICam(Current_Camera), 0, 0, Image_DX, Image_DY)
End Function

Public Function CreateHostConn()
    Host_Conn = IFC_IfxCreateImgConn(Host_Source, Display_Sink, Current_Mode, ITICam(Current_Camera), ICAP_INTR_EOF, 2)
    If ZoomAutoSize Then
        CImgSink_SetZoom Display_Sink, IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT
    Else
        CImgSink_SetZoom Display_Sink, 1#, 1#
    End If
End Function

Public Function CreateCamConn()
    If ZoomAutoSize Then
        CImgSink_SetZoom Display_Sink, IFC_STRETCH_TO_FIT, IFC_STRETCH_TO_FIT
    Else
        CImgSink_SetZoom Display_Sink, 1#, 1#
    End If
    Cam_Conn = IFC_IfxCreateImgConn(Cam_Source, Display_Sink, Current_Mode + IFC_LIVE_IMAGE, ITICam(Current_Camera), ICAP_INTR_EOF, 2)
End Function

Public Function KillAll()
    KillServer
    KillConnections
    KillSources
    KillSinks
End Function

Public Function CreateSourcesAndSinks()
    CreateSinks
    CreateSources
End Function

Public Function CreateCamServer()
End Function





