# Microsoft Developer Studio Generated NMAKE File, Based on PiPAcq.dsp
!IF "$(CFG)" == ""
CFG=PiPAcq - Win32 Debug
!MESSAGE No configuration specified. Defaulting to PiPAcq - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "PiPAcq - Win32 Release" && "$(CFG)" != "PiPAcq - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PiPAcq.mak" CFG="PiPAcq - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PiPAcq - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PiPAcq - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "PiPAcq - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\PiPAcq.exe"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\LargeAcqDoc.obj"
	-@erase "$(INTDIR)\LargeAcqView.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\PiPAcq.obj"
	-@erase "$(INTDIR)\PiPAcq.pch"
	-@erase "$(INTDIR)\PiPAcq.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\PiPAcq.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PiPAcq.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PiPAcq.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PiPAcq.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\PiPAcq.pdb" /machine:I386 /out:"$(OUTDIR)\PiPAcq.exe" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\LargeAcqDoc.obj" \
	"$(INTDIR)\LargeAcqView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PiPAcq.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\PiPAcq.res"

"$(OUTDIR)\PiPAcq.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\PiPAcq.exe" "$(OUTDIR)\PiPAcq.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\Dlgsnap.sbr"
	-@erase "$(INTDIR)\LargeAcqDoc.obj"
	-@erase "$(INTDIR)\LargeAcqDoc.sbr"
	-@erase "$(INTDIR)\LargeAcqView.obj"
	-@erase "$(INTDIR)\LargeAcqView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\PiPAcq.obj"
	-@erase "$(INTDIR)\PiPAcq.pch"
	-@erase "$(INTDIR)\PiPAcq.res"
	-@erase "$(INTDIR)\PiPAcq.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\PiPAcq.bsc"
	-@erase "$(OUTDIR)\PiPAcq.exe"
	-@erase "$(OUTDIR)\PiPAcq.ilk"
	-@erase "$(OUTDIR)\PiPAcq.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PiPAcq.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\PiPAcq.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\PiPAcq.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\Dlgsnap.sbr" \
	"$(INTDIR)\LargeAcqDoc.sbr" \
	"$(INTDIR)\LargeAcqView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PiPAcq.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr"

"$(OUTDIR)\PiPAcq.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\PiPAcq.pdb" /debug /machine:I386 /out:"$(OUTDIR)\PiPAcq.exe" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\LargeAcqDoc.obj" \
	"$(INTDIR)\LargeAcqView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PiPAcq.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\PiPAcq.res"

"$(OUTDIR)\PiPAcq.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("PiPAcq.dep")
!INCLUDE "PiPAcq.dep"
!ELSE 
!MESSAGE Warning: cannot find "PiPAcq.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "PiPAcq - Win32 Release" || "$(CFG)" == "PiPAcq - Win32 Debug"
SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\Dlgsnap.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\Dlgsnap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\Dlgsnap.obj"	"$(INTDIR)\Dlgsnap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\LargeAcqDoc.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\LargeAcqDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\LargeAcqDoc.obj"	"$(INTDIR)\LargeAcqDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\LargeAcqView.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\LargeAcqView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\LargeAcqView.obj"	"$(INTDIR)\LargeAcqView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\PiPAcq.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\PiPAcq.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\PiPAcq.obj"	"$(INTDIR)\PiPAcq.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 

SOURCE=.\PiPAcq.rc

"$(INTDIR)\PiPAcq.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\PiPAcq.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\PiPAcq.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\PiPAcq.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\PiPAcq.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgThrd.cpp

!IF  "$(CFG)" == "PiPAcq - Win32 Release"


"$(INTDIR)\TrgThrd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ELSEIF  "$(CFG)" == "PiPAcq - Win32 Debug"


"$(INTDIR)\TrgThrd.obj"	"$(INTDIR)\TrgThrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\PiPAcq.pch"


!ENDIF 


!ENDIF 

