# Microsoft Developer Studio Generated NMAKE File, Based on Grab3.dsp
!IF "$(CFG)" == ""
CFG=Grab3 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Grab3 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Grab3 - Win32 Release" && "$(CFG)" != "Grab3 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Grab3.mak" CFG="Grab3 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Grab3 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Grab3 - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Grab3 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Grab3.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\Grab3.obj"
	-@erase "$(INTDIR)\Grab3.pch"
	-@erase "$(INTDIR)\Grab3.res"
	-@erase "$(INTDIR)\Grab3Doc.obj"
	-@erase "$(INTDIR)\Grab3View.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Grab3.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Grab3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Grab3.res" /i "..\..\..\include" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Grab3.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Grab3.pdb" /machine:I386 /out:"$(OUTDIR)\Grab3.exe" /libpath:"..\..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Grab3.obj" \
	"$(INTDIR)\Grab3Doc.obj" \
	"$(INTDIR)\Grab3View.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\Grab3.res"

"$(OUTDIR)\Grab3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Grab3.exe" "$(OUTDIR)\Grab3.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\Grab3.obj"
	-@erase "$(INTDIR)\Grab3.pch"
	-@erase "$(INTDIR)\Grab3.res"
	-@erase "$(INTDIR)\Grab3.sbr"
	-@erase "$(INTDIR)\Grab3Doc.obj"
	-@erase "$(INTDIR)\Grab3Doc.sbr"
	-@erase "$(INTDIR)\Grab3View.obj"
	-@erase "$(INTDIR)\Grab3View.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Grab3.bsc"
	-@erase "$(OUTDIR)\Grab3.exe"
	-@erase "$(OUTDIR)\Grab3.ilk"
	-@erase "$(OUTDIR)\Grab3.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Grab3.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Grab3.res" /i "..\..\..\include" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Grab3.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\Grab3.sbr" \
	"$(INTDIR)\Grab3Doc.sbr" \
	"$(INTDIR)\Grab3View.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr"

"$(OUTDIR)\Grab3.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Grab3.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Grab3.exe" /pdbtype:sept /libpath:"..\..\..\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\Grab3.obj" \
	"$(INTDIR)\Grab3Doc.obj" \
	"$(INTDIR)\Grab3View.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\Grab3.res"

"$(OUTDIR)\Grab3.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Grab3.dep")
!INCLUDE "Grab3.dep"
!ELSE 
!MESSAGE Warning: cannot find "Grab3.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Grab3 - Win32 Release" || "$(CFG)" == "Grab3 - Win32 Debug"
SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\ChildFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\Grab3.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\Grab3.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\Grab3.obj"	"$(INTDIR)\Grab3.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\Grab3.rc

"$(INTDIR)\Grab3.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Grab3Doc.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\Grab3Doc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\Grab3Doc.obj"	"$(INTDIR)\Grab3Doc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\Grab3View.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\Grab3View.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\Grab3View.obj"	"$(INTDIR)\Grab3View.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Grab3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Grab3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Grab3.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Grab3.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgThrd.cpp

!IF  "$(CFG)" == "Grab3 - Win32 Release"


"$(INTDIR)\TrgThrd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ELSEIF  "$(CFG)" == "Grab3 - Win32 Debug"


"$(INTDIR)\TrgThrd.obj"	"$(INTDIR)\TrgThrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Grab3.pch"


!ENDIF 


!ENDIF 

