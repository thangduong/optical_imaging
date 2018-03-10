; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCamSel
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "seqsnap.h"
LastPage=0

ClassCount=17
Class1=CSeqsnapApp
Class2=CSeqsnapDoc
Class3=CSeqsnapView
Class4=CMainFrame

ResourceCount=10
Resource1=IDD_ABOUTBOX
Resource2=IDD_PROPTRG
Class5=CAboutDlg
Class6=CDlgsnap
Resource3=IDD_DLGSNAP
Resource4=IDD_LUTFLOOR
Resource5=IDD_GRABTRIG
Class7=CTrgSheet
Class8=CStrbProp
Class9=CFRstProp
Class10=CTrigPro
Resource6=IDD_DLGWIN
Class11=CCamSel
Class12=CDlgwin
Class13=CHwZoom
Resource7=IDD_CAMSEL
Class14=CLutThrsh
Resource8=IDD_HWZOOM
Class15=COutPort
Resource9=IDD_OUTPORT
Class16=CDualTap
Class17=CTrgGrab
Resource10=IDR_MAINFRAME

[CLS:CSeqsnapApp]
Type=0
HeaderFile=seqsnap.h
ImplementationFile=seqsnap.cpp
Filter=N
LastObject=CSeqsnapApp

[CLS:CSeqsnapDoc]
Type=0
HeaderFile=seqsnapd.h
ImplementationFile=seqsnapd.cpp
BaseClass=CDocument
Filter=N
VirtualFilter=DC
LastObject=CSeqsnapDoc

[CLS:CSeqsnapView]
Type=0
HeaderFile=seqsnapv.h
ImplementationFile=seqsnapv.cpp
BaseClass=CView
Filter=C
VirtualFilter=VWC
LastObject=CSeqsnapView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC



[CLS:CAboutDlg]
Type=0
HeaderFile=seqsnap.cpp
ImplementationFile=seqsnap.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_VIEW_TOOLBAR
Command2=ID_VIEW_STATUS_BAR
Command3=ID_CMDS_SEQSNAP
Command4=ID_CMDS_TRIGOPS
Command5=ID_CMDS_SELECTCAM
Command6=ID_CMDS_WRITETIFF
Command7=ID_CMDS_READTIFF
Command8=ID_CMDS_HWOVERLAY
Command9=ID_CMDS_PERFORMANCE
Command10=ID_CMDS_OUTPORT
Command11=ID_CMDS_INPORT
Command12=ID_CMDS_WINDOWGEN
Command13=ID_CMDS_HWZOOM
Command14=ID_CMDS_SWOVERLAY
Command15=ID_LUT_LINEAR
Command16=ID_LUT_INVERT
Command17=ID_LUT_THRESH
Command18=ID_APP_ABOUT
CommandCount=18

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DLGSNAP]
Type=1
Class=CDlgsnap
ControlCount=7
Control1=IDC_SLIDER2,msctls_trackbar32,1342242825
Control2=IDC_SNAP,button,1342242816
Control3=IDC_NUMFRAMES,edit,1350639744
Control4=IDC_STATIC,static,1342308352
Control5=IDC_PLAY,button,1342242816
Control6=IDC_LIVE,button,1342242816
Control7=IDOK,button,1342242816

[CLS:CDlgsnap]
Type=0
HeaderFile=Dlgsnap.h
ImplementationFile=Dlgsnap.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgsnap

[DLG:IDD_PROPTRG]
Type=1
Class=CTrigPro
ControlCount=13
Control1=IDC_TRGSOFT,button,1342308361
Control2=IDC_TrigDifferential,button,1342177289
Control3=IDC_TTLTRIG,button,1342177289
Control4=IDC_OPTO_COUPLED,button,1342177289
Control5=IDC_POLFALL,button,1342308361
Control6=IDC_TACTHIGH,button,1342177289
Control7=IDC_GD_DISABLE,button,1342308361
Control8=IDC_GD_ENABLE,button,1342177289
Control9=IDCANCEL,button,1342242816
Control10=ID_APPLY,button,1342242817
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,button,1342177287

[CLS:CStrbProp]
Type=0
HeaderFile=StrbProp.h
ImplementationFile=StrbProp.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_STRB_DIS

[CLS:CFRstProp]
Type=0
HeaderFile=FRstProp.h
ImplementationFile=FRstProp.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=dWC
LastObject=IDC_FRONOUTPUT

[CLS:CTrgSheet]
Type=0
HeaderFile=TrgSheet.h
ImplementationFile=TrgSheet.cpp
BaseClass=CPropertySheet
Filter=W
LastObject=CTrgSheet
VirtualFilter=hWC

[CLS:CTrigPro]
Type=0
HeaderFile=TrigPro.h
ImplementationFile=TrigPro.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_NEXT_PANE
VirtualFilter=idWC

[DLG:IDD_CAMSEL]
Type=1
Class=CCamSel
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_LIST_CAMNAME,listbox,1352728833
Control3=IDC_STATIC,button,1342177287

[CLS:CCamSel]
Type=0
HeaderFile=CamSel.h
ImplementationFile=CamSel.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CMDS_SEQSNAP
Command2=ID_CMDS_SELECTCAM
Command3=ID_CMDS_TRIGOPS
Command4=ID_CMDS_WRITETIFF
Command5=ID_CMDS_READTIFF
Command6=ID_CMDS_SWOVERLAY
Command7=ID_CMDS_HWOVERLAY
Command8=ID_CMDS_PERFORMANCE
Command9=ID_LUT_LINEAR
Command10=ID_LUT_INVERT
Command11=ID_LUT_THRESH
Command12=ID_CMDS_OUTPORT
Command13=ID_CMDS_INPORT
Command14=ID_CMDS_WINDOWGEN
Command15=ID_CMDS_HWZOOM
CommandCount=15

[DLG:IDD_LUTFLOOR]
Type=1
Class=CLutThrsh
ControlCount=4
Control1=IDC_LUTTHRESH,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,button,1342177287

[CLS:CLutThrsh]
Type=0
HeaderFile=LutThrsh.h
ImplementationFile=LutThrsh.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CLutThrsh

[DLG:IDD_OUTPORT]
Type=1
Class=COutPort
ControlCount=6
Control1=IDC_OUTPORT_VAL,edit,1350631552
Control2=IDC_GENSTROBE,button,1342242819
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352

[CLS:COutPort]
Type=0
HeaderFile=OutPort.h
ImplementationFile=OutPort.cpp
BaseClass=CDialog
Filter=D
LastObject=COutPort
VirtualFilter=dWC

[DLG:IDD_DLGWIN]
Type=1
Class=CDlgwin
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WGEN_X,edit,1350631552
Control5=IDC_EDIT5,static,1342308352
Control6=IDC_WGEN_Y,edit,1350631552
Control7=IDC_STATIC3,static,1342308352
Control8=IDC_WGEN_DX,edit,1350631552
Control9=IDC_STATIC4,static,1342308352
Control10=IDC_WGEN_DY,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287

[CLS:CDlgwin]
Type=0
HeaderFile=Dlgwin.h
ImplementationFile=Dlgwin.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgwin

[CLS:CHwZoom]
Type=0
HeaderFile=HwZoom.h
ImplementationFile=HwZoom.cpp
BaseClass=CDialog
Filter=D
LastObject=CHwZoom
VirtualFilter=dWC

[DLG:IDD_HWZOOM]
Type=1
Class=CHwZoom
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_XZ_NO,button,1342308361
Control4=IDC_XZ_2,button,1342177289
Control5=IDC_STATIC,button,1342177287
Control6=IDC_YZ_NO,button,1342308361
Control7=IDC_YZ_2,button,1342177289
Control8=IDC_STATIC,button,1342177287

[CLS:CDualTap]
Type=0
HeaderFile=DualTap.h
ImplementationFile=DualTap.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDualTap

[DLG:IDD_GRABTRIG]
Type=1
Class=CTrgGrab
ControlCount=22
Control1=IDC_TRIG_START_DISABLE,button,1342308361
Control2=IDC_RADIO2,button,1342177289
Control3=IDC_RADIO4,button,1342177289
Control4=IDC_RADIO6,button,1342177289
Control5=IDC_RADIO7,button,1342177289
Control6=IDC_RADIO3,button,1342177289
Control7=IDC_RADIO8,button,1342177289
Control8=IDC_TRGSTART,button,1342242816
Control9=IDC_TRGSTOP,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_TRGTIME,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_TRIG_END_DISABLE,button,1342308361
Control16=IDC_RADIO10,button,1342177289
Control17=IDC_RADIO11,button,1342177289
Control18=IDC_RADIO12,button,1342177289
Control19=IDC_RADIO13,button,1342177289
Control20=IDC_RADIO14,button,1342177289
Control21=IDC_RADIO15,button,1342177289
Control22=IDC_STATIC,button,1342177287

[CLS:CTrgGrab]
Type=0
HeaderFile=TrgGrab.h
ImplementationFile=TrgGrab.cpp
BaseClass=CPropertyPage 
Filter=D
LastObject=IDC_TRIG1_SET
VirtualFilter=dWC

