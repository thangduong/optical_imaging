# Microsoft Developer Studio Project File - Name="ncaplib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ncaplib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ncaplib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ncaplib.mak" CFG="ncaplib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ncaplib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ncaplib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ncaplib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../WinIo/include" /I "../Ifc58/include" /I "../../nstim/tcpip" /I "../../nstim/interface" /I "../../nstim/ui" /I "../camstoragelib" /I "../../nstim/nstim" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ncaplib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../WinIo/include" /I "../Ifc58/include" /I "../../nstim/tcpip" /I "../../nstim/interface" /I "../../nstim/ui" /I "../camstoragelib" /I "../../nstim/nstim" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "ncaplib - Win32 Release"
# Name "ncaplib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CFreqPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\CHighContrastPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\CHistPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\CImgPreviewWnd.cpp
# End Source File
# Begin Source File

SOURCE=..\..\nstim\nstim\CIniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\CLinePlot.cpp
# End Source File
# Begin Source File

SOURCE=.\CLUTPreviewWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CMinMaxPlot.cpp
# End Source File
# Begin Source File

SOURCE=.\CNCapCmdEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\CNCapEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\CNCapProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\CPrevWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CTemporalPlot.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CFreqPlot.h
# End Source File
# Begin Source File

SOURCE=.\CHighContrastPreview.h
# End Source File
# Begin Source File

SOURCE=.\CHistPlot.h
# End Source File
# Begin Source File

SOURCE=.\CImgPreviewWnd.h
# End Source File
# Begin Source File

SOURCE=..\..\nstim\nstim\CIniFile.h
# End Source File
# Begin Source File

SOURCE=.\CLinePlot.h
# End Source File
# Begin Source File

SOURCE=.\CLUTPreviewWnd.h
# End Source File
# Begin Source File

SOURCE=.\CMinMaxPlot.h
# End Source File
# Begin Source File

SOURCE=.\CNCapCmdEngine.h
# End Source File
# Begin Source File

SOURCE=.\CNCapEngine.h
# End Source File
# Begin Source File

SOURCE=.\CNCapProfile.h
# End Source File
# Begin Source File

SOURCE=.\CPrevWnd.h
# End Source File
# Begin Source File

SOURCE=.\CTemporalPlot.h
# End Source File
# End Group
# End Target
# End Project
