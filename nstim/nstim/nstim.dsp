# Microsoft Developer Studio Project File - Name="nstim" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=nstim - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "nstim.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "nstim.mak" CFG="nstim - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "nstim - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "nstim - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../ui" /I "../debug" /I "../d3d" /I "../interface" /I "../tcpip" /I "../util" /I "../lpt" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib ../lib/d3dx9d.lib ../lib/dxguid.lib ../lib/d3d9.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"../../bin/nstim.exe"

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../ui" /I "../debug" /I "../d3d" /I "../interface" /I "../tcpip" /I "../util" /I "../lpt" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib d3dx9.lib dxguid.lib d3d9.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /debug /machine:I386 /out:"../../bin/nstim.exe"

!ENDIF 

# Begin Target

# Name "nstim - Win32 Release"
# Name "nstim - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CIniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimApp.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimAtomCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimAtomGammaElt.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimBinaryNoisePatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimBitArrayPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimBlankPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimBuiltInAtomFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimCmdEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimColorRectPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimExecAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimFloatPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimGratingPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimIntArrayPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimIntPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimLeechAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimListCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimLptAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimLptCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimOIGratingPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimPatchCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimSMGratingPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimStringPatchParam.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimTestGratingPatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CNStimViewportAtom.cpp
# End Source File
# Begin Source File

SOURCE=.\INStimApp_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimAtom_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimAtomFactory_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimCmd_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimEngine_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimParam_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimPatch_i.c
# End Source File
# Begin Source File

SOURCE=.\INStimProfile_i.c
# End Source File
# Begin Source File

SOURCE=.\nstim.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CIniFile.h
# End Source File
# Begin Source File

SOURCE=.\CNStimApp.h
# End Source File
# Begin Source File

SOURCE=.\CNStimAtom.h
# End Source File
# Begin Source File

SOURCE=.\CNStimAtomCmd.h
# End Source File
# Begin Source File

SOURCE=.\CNStimAtomGammaElt.h
# End Source File
# Begin Source File

SOURCE=.\CNStimBinaryNoisePatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimBitArrayPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimBlankPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimBuiltInAtomFactory.h
# End Source File
# Begin Source File

SOURCE=.\CNStimCmdEngine.h
# End Source File
# Begin Source File

SOURCE=.\CNStimColorRectPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimEngine.h
# End Source File
# Begin Source File

SOURCE=.\CNStimExecAtom.h
# End Source File
# Begin Source File

SOURCE=.\CNStimFloatPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimGratingPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimIntArrayPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimIntPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimLeechAtom.h
# End Source File
# Begin Source File

SOURCE=.\CNStimListCmd.h
# End Source File
# Begin Source File

SOURCE=.\CNStimLptAtom.h
# End Source File
# Begin Source File

SOURCE=.\CNStimLptCmd.h
# End Source File
# Begin Source File

SOURCE=.\CNStimOIGratingPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimPatchCmd.h
# End Source File
# Begin Source File

SOURCE=.\CNStimPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimProfile.h
# End Source File
# Begin Source File

SOURCE=.\CNStimSequence.h
# End Source File
# Begin Source File

SOURCE=.\CNStimSMGratingPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimStringPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\CNStimTestGratingPatch.h
# End Source File
# Begin Source File

SOURCE=.\CNStimViewportAtom.h
# End Source File
# Begin Source File

SOURCE=.\INStimApp.h
# End Source File
# Begin Source File

SOURCE=.\INStimAtom.h
# End Source File
# Begin Source File

SOURCE=.\INStimCmd.h
# End Source File
# Begin Source File

SOURCE=.\INStimEngine.h
# End Source File
# Begin Source File

SOURCE=.\INStimPatch.h
# End Source File
# Begin Source File

SOURCE=.\INStimPatchFactory.h
# End Source File
# Begin Source File

SOURCE=.\INStimPatchParam.h
# End Source File
# Begin Source File

SOURCE=.\INStimProfile.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# Begin Group "idl"

# PROP Default_Filter "*.idl"
# Begin Source File

SOURCE=.\INStimApp.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimApp.idl

"INStimApp.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimApp.idl

"INStimApp.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimAtom.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimAtom.idl

"INStimAtom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimAtom.idl

"INStimAtom.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimAtomFactory.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimAtomFactory.idl

"INStimAtomFactory.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimAtomFactory.idl

"INStimAtomFactory.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimCmd.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimCmd.idl

"INStimCmd.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimCmd.idl

"INStimCmd.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimCmdEngine.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimCmdEngine.idl

"INStimCmdEngine.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimCmdEngine.idl

"INStimCmdEngine.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimEngine.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimEngine.idl

"INStimEngine.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimEngine.idl

"INStimEngine.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimParam.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimParam.idl

"INStimParam.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimParam.idl

"INStimParam.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimPatch.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimPatch.idl

"INStimPatch.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimPatch.idl

"INStimPatch.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\INStimProfile.idl

!IF  "$(CFG)" == "nstim - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimProfile.idl

"INStimProfile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ELSEIF  "$(CFG)" == "nstim - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build
InputPath=.\INStimProfile.idl

"INStimProfile.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	midl $(InputPath) /I "../interface"

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\..\WinIo\lib\WinIo.lib
# End Source File
# End Target
# End Project
