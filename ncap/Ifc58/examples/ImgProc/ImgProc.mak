# Microsoft Developer Studio Generated NMAKE File, Based on ImgProc.dsp
!IF "$(CFG)" == ""
CFG=ImgProc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ImgProc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ImgProc - Win32 Release" && "$(CFG)" != "ImgProc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImgProc.mak" CFG="ImgProc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImgProc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ImgProc - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "ImgProc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\ImgProc.exe" "$(OUTDIR)\ImgProc.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\ImgProc.obj"
	-@erase "$(INTDIR)\ImgProc.pch"
	-@erase "$(INTDIR)\ImgProc.res"
	-@erase "$(INTDIR)\ImgProc.sbr"
	-@erase "$(INTDIR)\ImgProcDoc.obj"
	-@erase "$(INTDIR)\ImgProcDoc.sbr"
	-@erase "$(INTDIR)\ImgProcView.obj"
	-@erase "$(INTDIR)\ImgProcView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ImgProc.bsc"
	-@erase "$(OUTDIR)\ImgProc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ImgProc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ImgProc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ImgProc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\ImgProc.sbr" \
	"$(INTDIR)\ImgProcDoc.sbr" \
	"$(INTDIR)\ImgProcView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr"

"$(OUTDIR)\ImgProc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\ImgProc.pdb" /machine:I386 /out:"$(OUTDIR)\ImgProc.exe" /libpath:"../../host/win32/lib" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ImgProc.obj" \
	"$(INTDIR)\ImgProcDoc.obj" \
	"$(INTDIR)\ImgProcView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\ImgProc.res"

"$(OUTDIR)\ImgProc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ImgProc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\ImgProc.exe" "$(OUTDIR)\ImgProc.bsc"


CLEAN :
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\ImgProc.obj"
	-@erase "$(INTDIR)\ImgProc.pch"
	-@erase "$(INTDIR)\ImgProc.res"
	-@erase "$(INTDIR)\ImgProc.sbr"
	-@erase "$(INTDIR)\ImgProcDoc.obj"
	-@erase "$(INTDIR)\ImgProcDoc.sbr"
	-@erase "$(INTDIR)\ImgProcView.obj"
	-@erase "$(INTDIR)\ImgProcView.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ImgProc.bsc"
	-@erase "$(OUTDIR)\ImgProc.exe"
	-@erase "$(OUTDIR)\ImgProc.ilk"
	-@erase "$(OUTDIR)\ImgProc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ImgProc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ImgProc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ImgProc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\ImgProc.sbr" \
	"$(INTDIR)\ImgProcDoc.sbr" \
	"$(INTDIR)\ImgProcView.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr"

"$(OUTDIR)\ImgProc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\ImgProc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\ImgProc.exe" /pdbtype:sept /libpath:"../../host/win32/lib" /libpath:"../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\ImgProc.obj" \
	"$(INTDIR)\ImgProcDoc.obj" \
	"$(INTDIR)\ImgProcView.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\ImgProc.res"

"$(OUTDIR)\ImgProc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("ImgProc.dep")
!INCLUDE "ImgProc.dep"
!ELSE 
!MESSAGE Warning: cannot find "ImgProc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ImgProc - Win32 Release" || "$(CFG)" == "ImgProc - Win32 Debug"
SOURCE=.\CamSel.cpp

"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\ImgProc.cpp

"$(INTDIR)\ImgProc.obj"	"$(INTDIR)\ImgProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\ImgProc.rc

"$(INTDIR)\ImgProc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ImgProcDoc.cpp

"$(INTDIR)\ImgProcDoc.obj"	"$(INTDIR)\ImgProcDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\ImgProcView.cpp

"$(INTDIR)\ImgProcView.obj"	"$(INTDIR)\ImgProcView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ImgProc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ImgProc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ImgProc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ImgProc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\ImgProc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ImgProc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgThrd.cpp

"$(INTDIR)\TrgThrd.obj"	"$(INTDIR)\TrgThrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ImgProc.pch"



!ENDIF 

