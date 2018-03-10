; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImgProc.h"
ODLFile=ImgProc.odl
LastPage=0

ClassCount=7
Class1=CImgProcApp
Class2=CImgProcDoc
Class3=CImgProcView
Class4=CMainFrame
Class7=CTrigGrabDlg

ResourceCount=8
Resource1="IDD_DLGAOI"
Resource2=IDR_IMGPROTYPE
Resource3=IDD_CAMSEL
Resource4=IDR_CHILDFRAME
Resource5="IDR_IMGPROTYPE"
Class5=CAboutDlg
Class6=CChildFrame
Resource6=IDD_ABOUTBOX
Resource7=IDR_MAINFRAME
Resource8=IDD_DLGAOI

[CLS:CImgProcApp]
Type=0
HeaderFile=ImgProc.h
ImplementationFile=ImgProc.cpp
Filter=N

[CLS:CImgProcDoc]
Type=0
HeaderFile=ImgProcDoc.h
ImplementationFile=ImgProcDoc.cpp
Filter=N

[CLS:CImgProcView]
Type=0
HeaderFile=ImgProcView.h
ImplementationFile=ImgProcView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CMDIFrameWnd
VirtualFilter=fWC


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ImgProc.cpp
ImplementationFile=ImgProc.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_VIEW_TOOLBAR
Command2=ID_VIEW_STATUS_BAR
Command3=ID_WINDOW_NEW
Command4=ID_WINDOW_CASCADE
Command5=ID_WINDOW_TILE_HORZ
Command6=ID_WINDOW_ARRANGE
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_IMGPROTYPE]
Type=1
Class=CImgProcView
Command1=ID_VIEW_TOOLBAR
Command2=ID_VIEW_STATUS_BAR
Command3=ID_WINDOW_NEW
Command4=ID_WINDOW_CASCADE
Command5=ID_WINDOW_TILE_HORZ
Command6=ID_WINDOW_ARRANGE
Command7=ID_APP_ABOUT
CommandCount=7

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_CAMSEL]
Type=1
Class=CTrigGrabDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_LIST_CAMNAME,listbox,1352728833
Control3=IDC_STATIC,button,1342177287

[CLS:CTrigGrabDlg]
Type=0
HeaderFile=TrigGrabDlg.h
ImplementationFile=TrigGrabDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTrigGrabDlg
VirtualFilter=dWC

[DLG:"IDD_DLGAOI"]
Type=1
Class=?
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WGEN_X,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_WGEN_Y,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_WGEN_DX,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_WGEN_DY,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287
Control13=IDC_RELATIVE,button,1342373897
Control14=IDC_ABSOLUTE,button,1342242825
Control15=IDC_STATIC,button,1342177287

[DLG:IDD_DLGAOI]
Type=1
Class=?
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_WGEN_X,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_WGEN_Y,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_WGEN_DX,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_WGEN_DY,edit,1350631552
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,button,1342177287

[MNU:"IDR_IMGPROTYPE"]
Type=1
Class=?
Command1=ID_VIEW_TOOLBAR
Command2=ID_VIEW_STATUS_BAR
Command3=ID_WINDOW_NEW
Command4=ID_WINDOW_CASCADE
Command5=ID_WINDOW_TILE_HORZ
Command6=ID_WINDOW_ARRANGE
Command7=ID_APP_ABOUT
CommandCount=7

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_CMDS_SELCAM
Command2=ID_WINDOW_NEW
CommandCount=2

[TB:IDR_CHILDFRAME]
Type=1
Class=?
Command1=ID_CMDS_GRABAOI
Command2=ID_LUT_LINEAR
Command3=ID_LUT_INVERT
Command4=ID_DELTA
Command5=ID_MIRROR
CommandCount=5

