# Microsoft Developer Studio Generated NMAKE File, Based on Overlay.dsp
!IF "$(CFG)" == ""
CFG=overlay - Win32 Debug
!MESSAGE No configuration specified. Defaulting to overlay - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "overlay - Win32 Release" && "$(CFG)" != "overlay - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Overlay.mak" CFG="overlay - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "overlay - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "overlay - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "overlay - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\overlay.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\OELEM.OBJ"
	-@erase "$(INTDIR)\overlay.obj"
	-@erase "$(INTDIR)\Overlay.pch"
	-@erase "$(INTDIR)\overlay.res"
	-@erase "$(INTDIR)\overlayd.obj"
	-@erase "$(INTDIR)\overlayv.obj"
	-@erase "$(INTDIR)\PROCTHRD.OBJ"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\overlay.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\Overlay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\overlay.res" /i "..\..\include" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Overlay.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\overlay.pdb" /machine:I386 /out:"$(OUTDIR)\overlay.exe" /libpath:"../../lib" /libpath:"../../host/win32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\OELEM.OBJ" \
	"$(INTDIR)\overlay.obj" \
	"$(INTDIR)\overlayd.obj" \
	"$(INTDIR)\overlayv.obj" \
	"$(INTDIR)\PROCTHRD.OBJ" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\overlay.res"

"$(OUTDIR)\overlay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Overlay.exe" "$(OUTDIR)\Overlay.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\mainfrm.obj"
	-@erase "$(INTDIR)\mainfrm.sbr"
	-@erase "$(INTDIR)\OELEM.OBJ"
	-@erase "$(INTDIR)\OELEM.SBR"
	-@erase "$(INTDIR)\overlay.obj"
	-@erase "$(INTDIR)\Overlay.pch"
	-@erase "$(INTDIR)\overlay.res"
	-@erase "$(INTDIR)\overlay.sbr"
	-@erase "$(INTDIR)\overlayd.obj"
	-@erase "$(INTDIR)\overlayd.sbr"
	-@erase "$(INTDIR)\overlayv.obj"
	-@erase "$(INTDIR)\overlayv.sbr"
	-@erase "$(INTDIR)\PROCTHRD.OBJ"
	-@erase "$(INTDIR)\PROCTHRD.SBR"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\stdafx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Overlay.bsc"
	-@erase "$(OUTDIR)\Overlay.exe"
	-@erase "$(OUTDIR)\Overlay.ilk"
	-@erase "$(OUTDIR)\Overlay.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Overlay.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\overlay.res" /i "..\..\include" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Overlay.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\mainfrm.sbr" \
	"$(INTDIR)\OELEM.SBR" \
	"$(INTDIR)\overlay.sbr" \
	"$(INTDIR)\overlayd.sbr" \
	"$(INTDIR)\overlayv.sbr" \
	"$(INTDIR)\PROCTHRD.SBR" \
	"$(INTDIR)\stdafx.sbr"

"$(OUTDIR)\Overlay.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Overlay.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Overlay.exe" /pdbtype:sept /libpath:"../../lib" /libpath:"../../host/win32/lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\mainfrm.obj" \
	"$(INTDIR)\OELEM.OBJ" \
	"$(INTDIR)\overlay.obj" \
	"$(INTDIR)\overlayd.obj" \
	"$(INTDIR)\overlayv.obj" \
	"$(INTDIR)\PROCTHRD.OBJ" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\overlay.res"

"$(OUTDIR)\Overlay.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Overlay.dep")
!INCLUDE "Overlay.dep"
!ELSE 
!MESSAGE Warning: cannot find "Overlay.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "overlay - Win32 Release" || "$(CFG)" == "overlay - Win32 Debug"
SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\mainfrm.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\mainfrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\mainfrm.obj"	"$(INTDIR)\mainfrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\OELEM.CPP

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\OELEM.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\OELEM.OBJ"	"$(INTDIR)\OELEM.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\overlay.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\overlay.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\overlay.obj"	"$(INTDIR)\overlay.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\overlay.rc

"$(INTDIR)\overlay.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\overlayd.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\overlayd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\overlayd.obj"	"$(INTDIR)\overlayd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\overlayv.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\overlayv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\overlayv.obj"	"$(INTDIR)\overlayv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\PROCTHRD.CPP

!IF  "$(CFG)" == "overlay - Win32 Release"


"$(INTDIR)\PROCTHRD.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"


"$(INTDIR)\PROCTHRD.OBJ"	"$(INTDIR)\PROCTHRD.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Overlay.pch"


!ENDIF 

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "overlay - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\Overlay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Overlay.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "overlay - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Overlay.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\stdafx.sbr"	"$(INTDIR)\Overlay.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

