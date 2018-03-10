# Microsoft Developer Studio Project File - Name="Configurator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Configurator - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Configurator.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Configurator.mak" CFG="Configurator - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Configurator - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Configurator - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/ifc/VegaNet/Examples/QuickConfig", EIBBAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Configurator - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Netapi32.lib /nologo /subsystem:windows /machine:I386 /out:"Release\QConfig.exe" /libpath:"../../host/win32/lib" /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "Configurator - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Netapi32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug\QConfig.exe" /pdbtype:sept /libpath:"../../host/win32/lib" /libpath:"../../lib"

!ENDIF 

# Begin Target

# Name "Configurator - Win32 Release"
# Name "Configurator - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\Configurator.cpp
# End Source File
# Begin Source File

SOURCE=.\Configurator.rc
# End Source File
# Begin Source File

SOURCE=.\ConfiguratorDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfiguratorView.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigureDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\GroupProp.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ModuleDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.cpp
# End Source File
# Begin Source File

SOURCE=.\NewCameraDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NotAppl.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\rowcursor.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\UserName.cpp
# End Source File
# Begin Source File

SOURCE=.\xform.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CameraMgrDlg.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\Configurator.h
# End Source File
# Begin Source File

SOURCE=.\ConfiguratorDoc.h
# End Source File
# Begin Source File

SOURCE=.\ConfiguratorView.h
# End Source File
# Begin Source File

SOURCE=.\ConfigureDlg.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\GroupProp.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ModuleDlg.h
# End Source File
# Begin Source File

SOURCE=.\msflexgrid.h
# End Source File
# Begin Source File

SOURCE=.\NewCameraDlg.h
# End Source File
# Begin Source File

SOURCE=.\NotAppl.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\rowcursor.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\UserName.h
# End Source File
# Begin Source File

SOURCE=.\xform.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Configurator.ico
# End Source File
# Begin Source File

SOURCE=.\res\Configurator.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ConfiguratorDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\x.txt
# End Source File
# End Target
# End Project
# Section Configurator : {9F6AA700-D188-11CD-AD48-00AA003C9CB6}
# 	2:5:Class:CRowCursor
# 	2:10:HeaderFile:rowcursor.h
# 	2:8:ImplFile:rowcursor.cpp
# End Section
# Section Configurator : {F0D2F217-CCB0-11D0-A316-00AA00688B10}
# 	2:5:Class:CDataList
# 	2:10:HeaderFile:datalist.h
# 	2:8:ImplFile:datalist.cpp
# End Section
# Section Configurator : {BCEDD283-FC2D-11D0-9CD0-006008058731}
# 	2:5:Class:CChoiceManager
# 	2:10:HeaderFile:choicemanager.h
# 	2:8:ImplFile:choicemanager.cpp
# End Section
# Section Configurator : {BDD1F053-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListSubItems
# 	2:10:HeaderFile:listsubitems.h
# 	2:8:ImplFile:listsubitems.cpp
# End Section
# Section Configurator : {C32CA85D-C898-11CF-B04D-00C04FD61157}
# 	2:5:Class:CChoice
# 	2:10:HeaderFile:choice.h
# 	2:8:ImplFile:choice.cpp
# End Section
# Section Configurator : {B2B2D0A0-4A68-11D1-B1A9-006097C99385}
# 	2:5:Class:CChoiceSinks
# 	2:10:HeaderFile:choicesinks.h
# 	2:8:ImplFile:choicesinks.cpp
# End Section
# Section Configurator : {BDD1F04E-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListItem
# 	2:10:HeaderFile:listitem.h
# 	2:8:ImplFile:listitem.cpp
# End Section
# Section Configurator : {DD979200-4A68-11D1-B1A9-006097C99385}
# 	2:5:Class:CChoiceSink
# 	2:10:HeaderFile:choicesink.h
# 	2:8:ImplFile:choicesink.cpp
# End Section
# Section Configurator : {C32CA855-C898-11CF-B04D-00C04FD61157}
# 	2:5:Class:CChoices
# 	2:10:HeaderFile:choices.h
# 	2:8:ImplFile:choices.cpp
# End Section
# Section Configurator : {5F4DF280-531B-11CF-91F6-C2863C385E30}
# 	2:5:Class:CMSFlexGrid
# 	2:10:HeaderFile:msflexgrid.h
# 	2:8:ImplFile:msflexgrid.cpp
# End Section
# Section Configurator : {E179B270-FC25-11D1-9915-006097C99385}
# 	2:5:Class:C_Grid
# 	2:10:HeaderFile:_grid.h
# 	2:8:ImplFile:_grid.cpp
# End Section
# Section Configurator : {BDD1F051-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CColumnHeader
# 	2:10:HeaderFile:columnheader.h
# 	2:8:ImplFile:columnheader.cpp
# End Section
# Section Configurator : {6262D3A0-531B-11CF-91F6-C2863C385E30}
# 	2:21:DefaultSinkHeaderFile:msflexgrid.h
# 	2:16:DefaultSinkClass:CMSFlexGrid
# End Section
# Section Configurator : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section Configurator : {AA859DE4-44BE-11D0-B08C-00C04FD61157}
# 	2:5:Class:CChoiceFilter
# 	2:10:HeaderFile:choicefilter.h
# 	2:8:ImplFile:choicefilter.cpp
# End Section
# Section Configurator : {BDD1F055-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListSubItem
# 	2:10:HeaderFile:listsubitem.h
# 	2:8:ImplFile:listsubitem.cpp
# End Section
# Section Configurator : {AA859DE3-44BE-11D0-B08C-00C04FD61157}
# 	2:5:Class:CTags
# 	2:10:HeaderFile:tags.h
# 	2:8:ImplFile:tags.cpp
# End Section
# Section Configurator : {BDD1F04C-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CListItems
# 	2:10:HeaderFile:listitems.h
# 	2:8:ImplFile:listitems.cpp
# End Section
# Section Configurator : {F0D2F219-CCB0-11D0-A316-00AA00688B10}
# 	2:21:DefaultSinkHeaderFile:datalist.h
# 	2:16:DefaultSinkClass:CDataList
# End Section
# Section Configurator : {F780D94D-CEE0-11CF-B04D-00C04FD61157}
# 	2:5:Class:CTypes
# 	2:10:HeaderFile:types.h
# 	2:8:ImplFile:types.cpp
# End Section
# Section Configurator : {BDD1F050-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CColumnHeaders
# 	2:10:HeaderFile:columnheaders.h
# 	2:8:ImplFile:columnheaders.cpp
# End Section
# Section Configurator : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section Configurator : {BDD1F049-858B-11D1-B16A-00C0F0283628}
# 	2:5:Class:CParamsListView
# 	2:10:HeaderFile:paramslistview.h
# 	2:8:ImplFile:paramslistview.cpp
# End Section
# Section Configurator : {BDD1F04B-858B-11D1-B16A-00C0F0283628}
# 	2:21:DefaultSinkHeaderFile:paramslistview.h
# 	2:16:DefaultSinkClass:CParamsListView
# End Section
# Section Configurator : {C32CA857-C898-11CF-B04D-00C04FD61157}
# 	2:5:Class:CCategory
# 	2:10:HeaderFile:category.h
# 	2:8:ImplFile:category.cpp
# End Section
# Section Configurator : {A8014380-BDC7-11D0-B218-00C04FD70811}
# 	2:5:Class:CDesignTimeControlSite
# 	2:10:HeaderFile:designtimecontrolsite.h
# 	2:8:ImplFile:designtimecontrolsite.cpp
# End Section
# Section Configurator : {277FC3F2-E90F-11D0-B767-0000F81E081D}
# 	2:21:DefaultSinkHeaderFile:_grid.h
# 	2:16:DefaultSinkClass:C_Grid
# End Section
