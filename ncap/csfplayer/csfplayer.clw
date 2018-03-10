; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCsfplayerDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "csfplayer.h"

ClassCount=2
Class1=CCsfplayerApp
Class2=CCsfplayerDlg

ResourceCount=4
Resource2=IDR_MAINFRAME
Resource3=IDR_MENU1
Resource4=IDD_CSFPLAYER_DIALOG

[CLS:CCsfplayerApp]
Type=0
HeaderFile=csfplayer.h
ImplementationFile=csfplayer.cpp
Filter=N

[CLS:CCsfplayerDlg]
Type=0
HeaderFile=CCsfplayerDlg.h
ImplementationFile=CCsfplayerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CCsfplayerDlg



[DLG:IDD_CSFPLAYER_DIALOG]
Type=1
Class=CCsfplayerDlg
ControlCount=3
Control1=IDC_IMG,static,1342177280
Control2=IDC_FRAMEID,static,1342308352
Control3=IDC_FRAMERATE,static,1342308352

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_QUIT
Command3=ID_ACTION_PLAY
Command4=ID_ACTION_STOP
CommandCount=4

