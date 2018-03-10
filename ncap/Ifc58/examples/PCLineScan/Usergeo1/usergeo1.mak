# Microsoft Developer Studio Generated NMAKE File, Based on usergeo1.dsp
!IF "$(CFG)" == ""
CFG=usergeo1 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to usergeo1 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "usergeo1 - Win32 Release" && "$(CFG)" != "usergeo1 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "usergeo1.mak" CFG="usergeo1 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "usergeo1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "usergeo1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "usergeo1 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\usergeo1.dll"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\usergeo1.obj"
	-@erase "$(INTDIR)\usergeo1.pch"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\usergeo1.dll"
	-@erase "$(OUTDIR)\usergeo1.exp"
	-@erase "$(OUTDIR)\usergeo1.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USERGEO1_EXPORTS" /Fp"$(INTDIR)\usergeo1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\usergeo1.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\usergeo1.pdb" /machine:I386 /out:"$(OUTDIR)\usergeo1.dll" /implib:"$(OUTDIR)\usergeo1.lib" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\usergeo1.obj"

"$(OUTDIR)\usergeo1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\usergeo1.dll"
   copy release\*.dll %SystemRoot%\system32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "usergeo1 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\usergeo1.dll" "$(OUTDIR)\usergeo1.bsc"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\usergeo1.obj"
	-@erase "$(INTDIR)\usergeo1.pch"
	-@erase "$(INTDIR)\usergeo1.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\usergeo1.bsc"
	-@erase "$(OUTDIR)\usergeo1.dll"
	-@erase "$(OUTDIR)\usergeo1.exp"
	-@erase "$(OUTDIR)\usergeo1.ilk"
	-@erase "$(OUTDIR)\usergeo1.lib"
	-@erase "$(OUTDIR)\usergeo1.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USERGEO1_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\usergeo1.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\usergeo1.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\usergeo1.sbr"

"$(OUTDIR)\usergeo1.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\usergeo1.pdb" /debug /machine:I386 /out:"$(OUTDIR)\usergeo1.dll" /implib:"$(OUTDIR)\usergeo1.lib" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\usergeo1.obj"

"$(OUTDIR)\usergeo1.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\usergeo1.dll" "$(OUTDIR)\usergeo1.bsc"
   copy debug\*.dll %SystemRoot%\system32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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
!IF EXISTS("usergeo1.dep")
!INCLUDE "usergeo1.dep"
!ELSE 
!MESSAGE Warning: cannot find "usergeo1.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "usergeo1 - Win32 Release" || "$(CFG)" == "usergeo1 - Win32 Debug"
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "usergeo1 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USERGEO1_EXPORTS" /Fp"$(INTDIR)\usergeo1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\usergeo1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "usergeo1 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "USERGEO1_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\usergeo1.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\usergeo1.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\usergeo1.cpp

!IF  "$(CFG)" == "usergeo1 - Win32 Release"


"$(INTDIR)\usergeo1.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\usergeo1.pch"


!ELSEIF  "$(CFG)" == "usergeo1 - Win32 Debug"


"$(INTDIR)\usergeo1.obj"	"$(INTDIR)\usergeo1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\usergeo1.pch"


!ENDIF 


!ENDIF 

