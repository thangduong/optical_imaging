# Microsoft Developer Studio Generated NMAKE File, Based on CGrab.dsp
!IF "$(CFG)" == ""
CFG=CGrab - Win32 Debug
!MESSAGE No configuration specified. Defaulting to CGrab - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "CGrab - Win32 Release" && "$(CFG)" != "CGrab - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CGrab.mak" CFG="CGrab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CGrab - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "CGrab - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "CGrab - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\CGrab.exe"


CLEAN :
	-@erase "$(INTDIR)\CGrab.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\CGrab.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\..\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\CGrab.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CGrab.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ifcapi.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\CGrab.pdb" /machine:I386 /out:"$(OUTDIR)\CGrab.exe" /libpath:"..\..\lib" /libpath:"..\..\host\win32\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CGrab.obj"

"$(OUTDIR)\CGrab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "CGrab - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\CGrab.exe" "$(OUTDIR)\CGrab.bsc"


CLEAN :
	-@erase "$(INTDIR)\CGrab.obj"
	-@erase "$(INTDIR)\CGrab.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\CGrab.bsc"
	-@erase "$(OUTDIR)\CGrab.exe"
	-@erase "$(OUTDIR)\CGrab.ilk"
	-@erase "$(OUTDIR)\CGrab.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "..\..\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\CGrab.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\CGrab.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CGrab.sbr"

"$(OUTDIR)\CGrab.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ifcapi.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\CGrab.pdb" /debug /machine:I386 /out:"$(OUTDIR)\CGrab.exe" /pdbtype:sept /libpath:"..\..\lib" /libpath:"..\..\host\win32\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CGrab.obj"

"$(OUTDIR)\CGrab.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("CGrab.dep")
!INCLUDE "CGrab.dep"
!ELSE 
!MESSAGE Warning: cannot find "CGrab.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "CGrab - Win32 Release" || "$(CFG)" == "CGrab - Win32 Debug"
SOURCE=.\CGrab.c

!IF  "$(CFG)" == "CGrab - Win32 Release"


"$(INTDIR)\CGrab.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "CGrab - Win32 Debug"


"$(INTDIR)\CGrab.obj"	"$(INTDIR)\CGrab.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

