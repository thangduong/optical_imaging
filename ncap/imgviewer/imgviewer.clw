; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImgviewerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "imgviewer.h"

ClassCount=2
Class1=CImgviewerApp
Class2=CImgviewerDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDD_IMGVIEWER_DIALOG
Resource4=IDR_MENU1

[CLS:CImgviewerApp]
Type=0
HeaderFile=imgviewer.h
ImplementationFile=imgviewer.cpp
Filter=N

[CLS:CImgviewerDlg]
Type=0
HeaderFile=CImgviewerDlg.h
ImplementationFile=CImgviewerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=ID_FILE_OPEN



[DLG:IDD_IMGVIEWER_DIALOG]
Type=1
Class=CImgviewerDlg
ControlCount=0

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_QUIT
CommandCount=2

