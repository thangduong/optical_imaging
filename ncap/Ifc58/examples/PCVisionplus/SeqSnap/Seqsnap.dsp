# Microsoft Developer Studio Project File - Name="seqsnap" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=seqsnap - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Seqsnap.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Seqsnap.mak" CFG="seqsnap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "seqsnap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "seqsnap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ifc/examples/PCVisionplus/Seqsnap", VAVAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "seqsnap - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /machine:I386 /libpath:"../../../host/win32/lib" /libpath:"../../../lib"

!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib"

!ENDIF 

# Begin Target

# Name "seqsnap - Win32 Release"
# Name "seqsnap - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\avi.cpp
# End Source File
# Begin Source File

SOURCE=.\CamSel.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CscDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgsnap.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlgwin.cpp
# End Source File
# Begin Source File

SOURCE=.\HwZoom.cpp
# End Source File
# Begin Source File

SOURCE=.\LutThrsh.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\OutPort.cpp
# End Source File
# Begin Source File

SOURCE=.\procthrd.cpp
# End Source File
# Begin Source File

SOURCE=.\seqsnap.cpp
# End Source File
# Begin Source File

SOURCE=.\seqsnap.rc
# End Source File
# Begin Source File

SOURCE=.\seqsnapd.cpp
# End Source File
# Begin Source File

SOURCE=.\seqsnapv.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TrgThrd.cpp
# End Source File
# Begin Source File

SOURCE=.\TrigGrabDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\avi.h
# End Source File
# Begin Source File

SOURCE=.\CamSel.h
# End Source File
# Begin Source File

SOURCE=.\ColorDlg.h
# End Source File
# Begin Source File

SOURCE=.\CscDlg.h
# End Source File
# Begin Source File

SOURCE=.\Dlgsnap.h
# End Source File
# Begin Source File

SOURCE=.\Dlgwin.h
# End Source File
# Begin Source File

SOURCE=.\HwZoom.h
# End Source File
# Begin Source File

SOURCE=.\LutThrsh.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\OutPort.h
# End Source File
# Begin Source File

SOURCE=.\PROCTHRD.H
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\seqsnap.h
# End Source File
# Begin Source File

SOURCE=.\SEQSNAPD.H
# End Source File
# Begin Source File

SOURCE=.\SEQSNAPV.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TrgSheet.h
# End Source File
# Begin Source File

SOURCE=.\TrgThrd.h
# End Source File
# Begin Source File

SOURCE=.\TrigGrabDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\a_rgb_planar_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\blue_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\green_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\red_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\rgb_24_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\rgb_button.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\rgb_planar_button.bmp
# End Source File
# Begin Source File

SOURCE=.\res\seqsnap.ico
# End Source File
# Begin Source File

SOURCE=.\res\seqsnap.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SEQSNAPD.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\TOOLBAR1.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
