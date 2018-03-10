# Microsoft Developer Studio Generated NMAKE File, Based on Configurator.dsp
!IF "$(CFG)" == ""
CFG=Configurator - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Configurator - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Configurator - Win32 Release" && "$(CFG)" != "Configurator - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Configurator.mak" CFG="Configurator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Configurator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Configurator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Configurator - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\QConfig.exe"


CLEAN :
	-@erase "$(INTDIR)\CameraMgrDlg.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Configurator.obj"
	-@erase "$(INTDIR)\Configurator.pch"
	-@erase "$(INTDIR)\Configurator.res"
	-@erase "$(INTDIR)\ConfiguratorDoc.obj"
	-@erase "$(INTDIR)\ConfiguratorView.obj"
	-@erase "$(INTDIR)\ConfigureDlg.obj"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\GroupProp.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ModuleDlg.obj"
	-@erase "$(INTDIR)\msflexgrid.obj"
	-@erase "$(INTDIR)\NewCameraDlg.obj"
	-@erase "$(INTDIR)\NotAppl.obj"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\rowcursor.obj"
	-@erase "$(INTDIR)\RuleEdit.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xform.obj"
	-@erase "$(OUTDIR)\QConfig.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Configurator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Configurator.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Configurator.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\QConfig.pdb" /machine:I386 /out:"$(OUTDIR)\QConfig.exe" /libpath:"../../host/win32/lib" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CameraMgrDlg.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Configurator.obj" \
	"$(INTDIR)\ConfiguratorDoc.obj" \
	"$(INTDIR)\ConfiguratorView.obj" \
	"$(INTDIR)\ConfigureDlg.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\GroupProp.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ModuleDlg.obj" \
	"$(INTDIR)\msflexgrid.obj" \
	"$(INTDIR)\NewCameraDlg.obj" \
	"$(INTDIR)\NotAppl.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\rowcursor.obj" \
	"$(INTDIR)\RuleEdit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\xform.obj" \
	"$(INTDIR)\Configurator.res"

"$(OUTDIR)\QConfig.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\QConfig.exe" "$(OUTDIR)\Configurator.bsc"


CLEAN :
	-@erase "$(INTDIR)\CameraMgrDlg.obj"
	-@erase "$(INTDIR)\CameraMgrDlg.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\Configurator.obj"
	-@erase "$(INTDIR)\Configurator.pch"
	-@erase "$(INTDIR)\Configurator.res"
	-@erase "$(INTDIR)\Configurator.sbr"
	-@erase "$(INTDIR)\ConfiguratorDoc.obj"
	-@erase "$(INTDIR)\ConfiguratorDoc.sbr"
	-@erase "$(INTDIR)\ConfiguratorView.obj"
	-@erase "$(INTDIR)\ConfiguratorView.sbr"
	-@erase "$(INTDIR)\ConfigureDlg.obj"
	-@erase "$(INTDIR)\ConfigureDlg.sbr"
	-@erase "$(INTDIR)\font.obj"
	-@erase "$(INTDIR)\font.sbr"
	-@erase "$(INTDIR)\GroupProp.obj"
	-@erase "$(INTDIR)\GroupProp.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ModuleDlg.obj"
	-@erase "$(INTDIR)\ModuleDlg.sbr"
	-@erase "$(INTDIR)\msflexgrid.obj"
	-@erase "$(INTDIR)\msflexgrid.sbr"
	-@erase "$(INTDIR)\NewCameraDlg.obj"
	-@erase "$(INTDIR)\NewCameraDlg.sbr"
	-@erase "$(INTDIR)\NotAppl.obj"
	-@erase "$(INTDIR)\NotAppl.sbr"
	-@erase "$(INTDIR)\picture.obj"
	-@erase "$(INTDIR)\picture.sbr"
	-@erase "$(INTDIR)\rowcursor.obj"
	-@erase "$(INTDIR)\rowcursor.sbr"
	-@erase "$(INTDIR)\RuleEdit.obj"
	-@erase "$(INTDIR)\RuleEdit.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xform.obj"
	-@erase "$(INTDIR)\xform.sbr"
	-@erase "$(OUTDIR)\Configurator.bsc"
	-@erase "$(OUTDIR)\QConfig.exe"
	-@erase "$(OUTDIR)\QConfig.ilk"
	-@erase "$(OUTDIR)\QConfig.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Configurator.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Configurator.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Configurator.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CameraMgrDlg.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\Configurator.sbr" \
	"$(INTDIR)\ConfiguratorDoc.sbr" \
	"$(INTDIR)\ConfiguratorView.sbr" \
	"$(INTDIR)\ConfigureDlg.sbr" \
	"$(INTDIR)\font.sbr" \
	"$(INTDIR)\GroupProp.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ModuleDlg.sbr" \
	"$(INTDIR)\msflexgrid.sbr" \
	"$(INTDIR)\NewCameraDlg.sbr" \
	"$(INTDIR)\NotAppl.sbr" \
	"$(INTDIR)\picture.sbr" \
	"$(INTDIR)\rowcursor.sbr" \
	"$(INTDIR)\RuleEdit.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\xform.sbr"

"$(OUTDIR)\Configurator.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\QConfig.pdb" /debug /machine:I386 /out:"$(OUTDIR)\QConfig.exe" /pdbtype:sept /libpath:"../../host/win32/lib" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CameraMgrDlg.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Configurator.obj" \
	"$(INTDIR)\ConfiguratorDoc.obj" \
	"$(INTDIR)\ConfiguratorView.obj" \
	"$(INTDIR)\ConfigureDlg.obj" \
	"$(INTDIR)\font.obj" \
	"$(INTDIR)\GroupProp.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ModuleDlg.obj" \
	"$(INTDIR)\msflexgrid.obj" \
	"$(INTDIR)\NewCameraDlg.obj" \
	"$(INTDIR)\NotAppl.obj" \
	"$(INTDIR)\picture.obj" \
	"$(INTDIR)\rowcursor.obj" \
	"$(INTDIR)\RuleEdit.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\xform.obj" \
	"$(INTDIR)\Configurator.res"

"$(OUTDIR)\QConfig.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Configurator.dep")
!INCLUDE "Configurator.dep"
!ELSE 
!MESSAGE Warning: cannot find "Configurator.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Configurator - Win32 Release" || "$(CFG)" == "Configurator - Win32 Debug"
SOURCE=.\CameraMgrDlg.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\CameraMgrDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\CameraMgrDlg.obj"	"$(INTDIR)\CameraMgrDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\Configurator.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\Configurator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\Configurator.obj"	"$(INTDIR)\Configurator.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\Configurator.rc

"$(INTDIR)\Configurator.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ConfiguratorDoc.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\ConfiguratorDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\ConfiguratorDoc.obj"	"$(INTDIR)\ConfiguratorDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\ConfiguratorView.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\ConfiguratorView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\ConfiguratorView.obj"	"$(INTDIR)\ConfiguratorView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\ConfigureDlg.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\ConfigureDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\ConfigureDlg.obj"	"$(INTDIR)\ConfigureDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\font.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\font.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\font.obj"	"$(INTDIR)\font.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\GroupProp.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\GroupProp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\GroupProp.obj"	"$(INTDIR)\GroupProp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\ModuleDlg.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\ModuleDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\ModuleDlg.obj"	"$(INTDIR)\ModuleDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\msflexgrid.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\msflexgrid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\msflexgrid.obj"	"$(INTDIR)\msflexgrid.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\NewCameraDlg.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\NewCameraDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\NewCameraDlg.obj"	"$(INTDIR)\NewCameraDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\NotAppl.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\NotAppl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\NotAppl.obj"	"$(INTDIR)\NotAppl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\picture.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\picture.obj"	"$(INTDIR)\picture.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\rowcursor.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\rowcursor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\rowcursor.obj"	"$(INTDIR)\rowcursor.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\RuleEdit.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\RuleEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\RuleEdit.obj"	"$(INTDIR)\RuleEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Configurator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Configurator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Configurator.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Configurator.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\xform.cpp

!IF  "$(CFG)" == "Configurator - Win32 Release"


"$(INTDIR)\xform.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"


"$(INTDIR)\xform.obj"	"$(INTDIR)\xform.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Configurator.pch"


!ENDIF 


!ENDIF 

