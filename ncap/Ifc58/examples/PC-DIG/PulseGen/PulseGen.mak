# Microsoft Developer Studio Generated NMAKE File, Based on PulseGen.dsp
!IF "$(CFG)" == ""
CFG=PulseGen - Win32 Debug
!MESSAGE No configuration specified. Defaulting to PulseGen - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PulseGen - Win32 Release" && "$(CFG)" != "PulseGen - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PulseGen.mak" CFG="PulseGen - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PulseGen - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PulseGen - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "PulseGen - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\PulseGen.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\PulseGen.obj"
	-@erase "$(INTDIR)\PulseGen.pch"
	-@erase "$(INTDIR)\PulseGen.res"
	-@erase "$(INTDIR)\PulseGenDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vixntime.obj"
	-@erase "$(OUTDIR)\PulseGen.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PulseGen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PulseGen.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PulseGen.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\PulseGen.pdb" /machine:I386 /out:"$(OUTDIR)\PulseGen.exe" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\PulseGen.obj" \
	"$(INTDIR)\PulseGenDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vixntime.obj" \
	"$(INTDIR)\PulseGen.res"

"$(OUTDIR)\PulseGen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PulseGen - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\PulseGen.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\PulseGen.obj"
	-@erase "$(INTDIR)\PulseGen.pch"
	-@erase "$(INTDIR)\PulseGen.res"
	-@erase "$(INTDIR)\PulseGenDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vixntime.obj"
	-@erase "$(OUTDIR)\PulseGen.exe"
	-@erase "$(OUTDIR)\PulseGen.ilk"
	-@erase "$(OUTDIR)\PulseGen.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PulseGen.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PulseGen.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PulseGen.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\PulseGen.pdb" /debug /machine:I386 /out:"$(OUTDIR)\PulseGen.exe" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\PulseGen.obj" \
	"$(INTDIR)\PulseGenDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\vixntime.obj" \
	"$(INTDIR)\PulseGen.res"

"$(OUTDIR)\PulseGen.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("PulseGen.dep")
!INCLUDE "PulseGen.dep"
!ELSE 
!MESSAGE Warning: cannot find "PulseGen.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PulseGen - Win32 Release" || "$(CFG)" == "PulseGen - Win32 Debug"
SOURCE=.\CamSel.cpp

"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PulseGen.pch"


SOURCE=.\PulseGen.cpp

"$(INTDIR)\PulseGen.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PulseGen.pch"


SOURCE=.\PulseGen.rc

"$(INTDIR)\PulseGen.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\PulseGenDlg.cpp

"$(INTDIR)\PulseGenDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PulseGen.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "PulseGen - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PulseGen.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\PulseGen.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PulseGen - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PulseGen.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\PulseGen.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\vixntime.cpp

"$(INTDIR)\vixntime.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PulseGen.pch"



!ENDIF 

