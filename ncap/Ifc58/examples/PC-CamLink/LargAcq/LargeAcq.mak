# Microsoft Developer Studio Generated NMAKE File, Based on LargeAcq.dsp
!IF "$(CFG)" == ""
CFG=LargeAcq - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LargeAcq - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LargeAcq - Win32 Release" && "$(CFG)" != "LargeAcq - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LargeAcq.mak" CFG="LargeAcq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LargeAcq - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LargeAcq - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LargeAcq - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\LargeAcq.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\LargeAcq.obj"
	-@erase "$(INTDIR)\LargeAcq.pch"
	-@erase "$(INTDIR)\LargeAcq.res"
	-@erase "$(INTDIR)\LargeAcqDoc.obj"
	-@erase "$(INTDIR)\LargeAcqView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\LargeAcq.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LargeAcq.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LargeAcq.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LargeAcq.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\LargeAcq.pdb" /machine:I386 /out:"$(OUTDIR)\LargeAcq.exe" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\LargeAcq.obj" \
	"$(INTDIR)\LargeAcqDoc.obj" \
	"$(INTDIR)\LargeAcqView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\LargeAcq.res"

"$(OUTDIR)\LargeAcq.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\LargeAcq.exe" "$(OUTDIR)\LargeAcq.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\Dlgsnap.sbr"
	-@erase "$(INTDIR)\LargeAcq.obj"
	-@erase "$(INTDIR)\LargeAcq.pch"
	-@erase "$(INTDIR)\LargeAcq.res"
	-@erase "$(INTDIR)\LargeAcq.sbr"
	-@erase "$(INTDIR)\LargeAcqDoc.obj"
	-@erase "$(INTDIR)\LargeAcqDoc.sbr"
	-@erase "$(INTDIR)\LargeAcqView.obj"
	-@erase "$(INTDIR)\LargeAcqView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\LargeAcq.bsc"
	-@erase "$(OUTDIR)\LargeAcq.exe"
	-@erase "$(OUTDIR)\LargeAcq.ilk"
	-@erase "$(OUTDIR)\LargeAcq.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LargeAcq.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\LargeAcq.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LargeAcq.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\Dlgsnap.sbr" \
	"$(INTDIR)\LargeAcq.sbr" \
	"$(INTDIR)\LargeAcqDoc.sbr" \
	"$(INTDIR)\LargeAcqView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr"

"$(OUTDIR)\LargeAcq.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\LargeAcq.pdb" /debug /machine:I386 /out:"$(OUTDIR)\LargeAcq.exe" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\LargeAcq.obj" \
	"$(INTDIR)\LargeAcqDoc.obj" \
	"$(INTDIR)\LargeAcqView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\LargeAcq.res"

"$(OUTDIR)\LargeAcq.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("LargeAcq.dep")
!INCLUDE "LargeAcq.dep"
!ELSE 
!MESSAGE Warning: cannot find "LargeAcq.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "LargeAcq - Win32 Release" || "$(CFG)" == "LargeAcq - Win32 Debug"
SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\Dlgsnap.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\Dlgsnap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\Dlgsnap.obj"	"$(INTDIR)\Dlgsnap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\LargeAcq.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\LargeAcq.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\LargeAcq.obj"	"$(INTDIR)\LargeAcq.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\LargeAcq.rc

"$(INTDIR)\LargeAcq.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\LargeAcqDoc.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\LargeAcqDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\LargeAcqDoc.obj"	"$(INTDIR)\LargeAcqDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\LargeAcqView.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\LargeAcqView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\LargeAcqView.obj"	"$(INTDIR)\LargeAcqView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\LargeAcq.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\LargeAcq.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LargeAcq.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LargeAcq.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgThrd.cpp

!IF  "$(CFG)" == "LargeAcq - Win32 Release"


"$(INTDIR)\TrgThrd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ELSEIF  "$(CFG)" == "LargeAcq - Win32 Debug"


"$(INTDIR)\TrgThrd.obj"	"$(INTDIR)\TrgThrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\LargeAcq.pch"


!ENDIF 


!ENDIF 

