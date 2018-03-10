# Microsoft Developer Studio Generated NMAKE File, Based on IntrEx.dsp
!IF "$(CFG)" == ""
CFG=IntrEx - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IntrEx - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IntrEx - Win32 Release" && "$(CFG)" != "IntrEx - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IntrEx.mak" CFG="IntrEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IntrEx - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "IntrEx - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "IntrEx - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\IntrEx.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\ifcintr.obj"
	-@erase "$(INTDIR)\INTRDLG.OBJ"
	-@erase "$(INTDIR)\IntrEx.obj"
	-@erase "$(INTDIR)\IntrEx.pch"
	-@erase "$(INTDIR)\IntrEx.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TrgGrab.obj"
	-@erase "$(INTDIR)\TrgSheet.obj"
	-@erase "$(INTDIR)\TrigPro.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\IntrEx.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\IntrEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IntrEx.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IntrEx.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\IntrEx.pdb" /machine:I386 /out:"$(OUTDIR)\IntrEx.exe" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ifcintr.obj" \
	"$(INTDIR)\INTRDLG.OBJ" \
	"$(INTDIR)\IntrEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgGrab.obj" \
	"$(INTDIR)\TrgSheet.obj" \
	"$(INTDIR)\TrigPro.obj" \
	"$(INTDIR)\IntrEx.res"

"$(OUTDIR)\IntrEx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\IntrEx.exe" "$(OUTDIR)\IntrEx.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\ifcintr.obj"
	-@erase "$(INTDIR)\ifcintr.sbr"
	-@erase "$(INTDIR)\INTRDLG.OBJ"
	-@erase "$(INTDIR)\INTRDLG.SBR"
	-@erase "$(INTDIR)\IntrEx.obj"
	-@erase "$(INTDIR)\IntrEx.pch"
	-@erase "$(INTDIR)\IntrEx.res"
	-@erase "$(INTDIR)\IntrEx.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgGrab.obj"
	-@erase "$(INTDIR)\TrgGrab.sbr"
	-@erase "$(INTDIR)\TrgSheet.obj"
	-@erase "$(INTDIR)\TrgSheet.sbr"
	-@erase "$(INTDIR)\TrigPro.obj"
	-@erase "$(INTDIR)\TrigPro.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\IntrEx.bsc"
	-@erase "$(OUTDIR)\IntrEx.exe"
	-@erase "$(OUTDIR)\IntrEx.ilk"
	-@erase "$(OUTDIR)\IntrEx.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\IntrEx.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\IntrEx.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IntrEx.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\ifcintr.sbr" \
	"$(INTDIR)\INTRDLG.SBR" \
	"$(INTDIR)\IntrEx.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgGrab.sbr" \
	"$(INTDIR)\TrgSheet.sbr" \
	"$(INTDIR)\TrigPro.sbr"

"$(OUTDIR)\IntrEx.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\IntrEx.pdb" /debug /machine:I386 /out:"$(OUTDIR)\IntrEx.exe" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ifcintr.obj" \
	"$(INTDIR)\INTRDLG.OBJ" \
	"$(INTDIR)\IntrEx.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgGrab.obj" \
	"$(INTDIR)\TrgSheet.obj" \
	"$(INTDIR)\TrigPro.obj" \
	"$(INTDIR)\IntrEx.res"

"$(OUTDIR)\IntrEx.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IntrEx.dep")
!INCLUDE "IntrEx.dep"
!ELSE 
!MESSAGE Warning: cannot find "IntrEx.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IntrEx - Win32 Release" || "$(CFG)" == "IntrEx - Win32 Debug"
SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\ifcintr.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\ifcintr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\ifcintr.obj"	"$(INTDIR)\ifcintr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\INTRDLG.CPP

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\INTRDLG.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\INTRDLG.OBJ"	"$(INTDIR)\INTRDLG.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\IntrEx.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\IntrEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\IntrEx.obj"	"$(INTDIR)\IntrEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\IntrEx.rc

"$(INTDIR)\IntrEx.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\IntrEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\IntrEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\IntrEx.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\IntrEx.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgGrab.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\TrgGrab.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\TrgGrab.obj"	"$(INTDIR)\TrgGrab.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\TrgSheet.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\TrgSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\TrgSheet.obj"	"$(INTDIR)\TrgSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 

SOURCE=.\TrigPro.cpp

!IF  "$(CFG)" == "IntrEx - Win32 Release"


"$(INTDIR)\TrigPro.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ELSEIF  "$(CFG)" == "IntrEx - Win32 Debug"


"$(INTDIR)\TrigPro.obj"	"$(INTDIR)\TrigPro.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IntrEx.pch"


!ENDIF 


!ENDIF 

