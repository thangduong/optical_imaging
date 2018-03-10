# Microsoft Developer Studio Generated NMAKE File, Based on Seqsnap.dsp
!IF "$(CFG)" == ""
CFG=seqsnap - Win32 Debug
!MESSAGE No configuration specified. Defaulting to seqsnap - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "seqsnap - Win32 Release" && "$(CFG)" != "seqsnap - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Seqsnap.mak" CFG="seqsnap - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "seqsnap - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "seqsnap - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "seqsnap - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Seqsnap.exe"


CLEAN :
	-@erase "$(INTDIR)\avi.obj"
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\ColorDlg.obj"
	-@erase "$(INTDIR)\CscDlg.obj"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\Dlgwin.obj"
	-@erase "$(INTDIR)\HwZoom.obj"
	-@erase "$(INTDIR)\LutThrsh.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\OutPort.obj"
	-@erase "$(INTDIR)\procthrd.obj"
	-@erase "$(INTDIR)\seqsnap.obj"
	-@erase "$(INTDIR)\Seqsnap.pch"
	-@erase "$(INTDIR)\seqsnap.res"
	-@erase "$(INTDIR)\seqsnapd.obj"
	-@erase "$(INTDIR)\seqsnapv.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrigGrabDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Seqsnap.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\Seqsnap.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\seqsnap.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Seqsnap.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=vfw32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Seqsnap.pdb" /machine:I386 /out:"$(OUTDIR)\Seqsnap.exe" /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\avi.obj" \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ColorDlg.obj" \
	"$(INTDIR)\CscDlg.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\Dlgwin.obj" \
	"$(INTDIR)\HwZoom.obj" \
	"$(INTDIR)\LutThrsh.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OutPort.obj" \
	"$(INTDIR)\procthrd.obj" \
	"$(INTDIR)\seqsnap.obj" \
	"$(INTDIR)\seqsnapd.obj" \
	"$(INTDIR)\seqsnapv.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\TrigGrabDlg.obj" \
	"$(INTDIR)\seqsnap.res"

"$(OUTDIR)\Seqsnap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Seqsnap.exe" "$(OUTDIR)\Seqsnap.bsc"


CLEAN :
	-@erase "$(INTDIR)\avi.obj"
	-@erase "$(INTDIR)\avi.sbr"
	-@erase "$(INTDIR)\CamSel.obj"
	-@erase "$(INTDIR)\CamSel.sbr"
	-@erase "$(INTDIR)\ColorDlg.obj"
	-@erase "$(INTDIR)\ColorDlg.sbr"
	-@erase "$(INTDIR)\CscDlg.obj"
	-@erase "$(INTDIR)\CscDlg.sbr"
	-@erase "$(INTDIR)\Dlgsnap.obj"
	-@erase "$(INTDIR)\Dlgsnap.sbr"
	-@erase "$(INTDIR)\Dlgwin.obj"
	-@erase "$(INTDIR)\Dlgwin.sbr"
	-@erase "$(INTDIR)\HwZoom.obj"
	-@erase "$(INTDIR)\HwZoom.sbr"
	-@erase "$(INTDIR)\LutThrsh.obj"
	-@erase "$(INTDIR)\LutThrsh.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\OutPort.obj"
	-@erase "$(INTDIR)\OutPort.sbr"
	-@erase "$(INTDIR)\procthrd.obj"
	-@erase "$(INTDIR)\procthrd.sbr"
	-@erase "$(INTDIR)\seqsnap.obj"
	-@erase "$(INTDIR)\Seqsnap.pch"
	-@erase "$(INTDIR)\seqsnap.res"
	-@erase "$(INTDIR)\seqsnap.sbr"
	-@erase "$(INTDIR)\seqsnapd.obj"
	-@erase "$(INTDIR)\seqsnapd.sbr"
	-@erase "$(INTDIR)\seqsnapv.obj"
	-@erase "$(INTDIR)\seqsnapv.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TrgThrd.obj"
	-@erase "$(INTDIR)\TrgThrd.sbr"
	-@erase "$(INTDIR)\TrigGrabDlg.obj"
	-@erase "$(INTDIR)\TrigGrabDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Seqsnap.bsc"
	-@erase "$(OUTDIR)\Seqsnap.exe"
	-@erase "$(OUTDIR)\Seqsnap.ilk"
	-@erase "$(OUTDIR)\Seqsnap.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Seqsnap.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\seqsnap.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Seqsnap.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\avi.sbr" \
	"$(INTDIR)\CamSel.sbr" \
	"$(INTDIR)\ColorDlg.sbr" \
	"$(INTDIR)\CscDlg.sbr" \
	"$(INTDIR)\Dlgsnap.sbr" \
	"$(INTDIR)\Dlgwin.sbr" \
	"$(INTDIR)\HwZoom.sbr" \
	"$(INTDIR)\LutThrsh.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\OutPort.sbr" \
	"$(INTDIR)\procthrd.sbr" \
	"$(INTDIR)\seqsnap.sbr" \
	"$(INTDIR)\seqsnapd.sbr" \
	"$(INTDIR)\seqsnapv.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TrgThrd.sbr" \
	"$(INTDIR)\TrigGrabDlg.sbr"

"$(OUTDIR)\Seqsnap.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=vfw32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Seqsnap.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Seqsnap.exe" /pdbtype:sept /libpath:"../../../host/win32/lib" /libpath:"../../../lib" 
LINK32_OBJS= \
	"$(INTDIR)\avi.obj" \
	"$(INTDIR)\CamSel.obj" \
	"$(INTDIR)\ColorDlg.obj" \
	"$(INTDIR)\CscDlg.obj" \
	"$(INTDIR)\Dlgsnap.obj" \
	"$(INTDIR)\Dlgwin.obj" \
	"$(INTDIR)\HwZoom.obj" \
	"$(INTDIR)\LutThrsh.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\OutPort.obj" \
	"$(INTDIR)\procthrd.obj" \
	"$(INTDIR)\seqsnap.obj" \
	"$(INTDIR)\seqsnapd.obj" \
	"$(INTDIR)\seqsnapv.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TrgThrd.obj" \
	"$(INTDIR)\TrigGrabDlg.obj" \
	"$(INTDIR)\seqsnap.res"

"$(OUTDIR)\Seqsnap.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Seqsnap.dep")
!INCLUDE "Seqsnap.dep"
!ELSE 
!MESSAGE Warning: cannot find "Seqsnap.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "seqsnap - Win32 Release" || "$(CFG)" == "seqsnap - Win32 Debug"
SOURCE=.\avi.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\avi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\avi.obj"	"$(INTDIR)\avi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\CamSel.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\CamSel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\CamSel.obj"	"$(INTDIR)\CamSel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\ColorDlg.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\ColorDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\ColorDlg.obj"	"$(INTDIR)\ColorDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\CscDlg.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\CscDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\CscDlg.obj"	"$(INTDIR)\CscDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\Dlgsnap.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\Dlgsnap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\Dlgsnap.obj"	"$(INTDIR)\Dlgsnap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\Dlgwin.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\Dlgwin.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\Dlgwin.obj"	"$(INTDIR)\Dlgwin.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\HwZoom.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\HwZoom.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\HwZoom.obj"	"$(INTDIR)\HwZoom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\LutThrsh.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\LutThrsh.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\LutThrsh.obj"	"$(INTDIR)\LutThrsh.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\OutPort.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\OutPort.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\OutPort.obj"	"$(INTDIR)\OutPort.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\procthrd.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\procthrd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\procthrd.obj"	"$(INTDIR)\procthrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\seqsnap.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\seqsnap.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\seqsnap.obj"	"$(INTDIR)\seqsnap.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\seqsnap.rc

"$(INTDIR)\seqsnap.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\seqsnapd.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\seqsnapd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\seqsnapd.obj"	"$(INTDIR)\seqsnapd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\seqsnapv.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\seqsnapv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\seqsnapv.obj"	"$(INTDIR)\seqsnapv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\Seqsnap.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Seqsnap.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Seqsnap.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Seqsnap.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TrgThrd.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\TrgThrd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\TrgThrd.obj"	"$(INTDIR)\TrgThrd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 

SOURCE=.\TrigGrabDlg.cpp

!IF  "$(CFG)" == "seqsnap - Win32 Release"


"$(INTDIR)\TrigGrabDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ELSEIF  "$(CFG)" == "seqsnap - Win32 Debug"


"$(INTDIR)\TrigGrabDlg.obj"	"$(INTDIR)\TrigGrabDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Seqsnap.pch"


!ENDIF 


!ENDIF 

