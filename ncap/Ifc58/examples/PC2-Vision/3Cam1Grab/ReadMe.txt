========================================================================
       MICROSOFT FOUNDATION CLASS LIBRARY : 3Cam1Grab
========================================================================


AppWizard has created this 3Cam1Grab application for you.  This application
not only demonstrates the basics of using the Microsoft Foundation classes
but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your 3Cam1Grab application.

3Cam1Grab.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    C3Cam1GrabApp application class.

3Cam1Grab.cpp
    This is the main application source file that contains the application
    class C3Cam1GrabApp.

3Cam1Grab.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
	Developer Studio.

res\3Cam1Grab.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file 3Cam1Grab.rc.

res\3Cam1Grab.rc2
    This file contains resources that are not edited by Microsoft 
	Developer Studio.  You should place all resources not
	editable by the resource editor in this file.

3Cam1Grab.clw
    This file contains information used by ClassWizard to edit existing
    classes or add new classes.  ClassWizard also uses this file to store
    information needed to create and edit message maps and dialog data
    maps and to create prototype member functions.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the
    CMainFrame class.  Edit this toolbar bitmap along with the
    array in MainFrm.cpp to add more toolbar buttons.

/////////////////////////////////////////////////////////////////////////////

AppWizard creates one document type and one view:

3Cam1GrabDoc.h, 3Cam1GrabDoc.cpp - the document
    These files contain your C3Cam1GrabDoc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via C3Cam1GrabDoc::Serialize).

3Cam1GrabView.h, 3Cam1GrabView.cpp - the view of the document
    These files contain your C3Cam1GrabView class.
    C3Cam1GrabView objects are used to view C3Cam1GrabDoc objects.

res\3Cam1GrabDoc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the C3Cam1GrabDoc class.  This icon is included by the main
    resource file 3Cam1Grab.rc.


/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named 3Cam1Grab.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Developer Studio reads and updates this file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, and your application is 
in a language other than the operating system's current language, you
will need to copy the corresponding localized resources MFC40XXX.DLL
from the Microsoft Visual C++ CD-ROM onto the system or system32 directory,
and rename it to be MFCLOC.DLL.  ("XXX" stands for the language abbreviation.
For example, MFC40DEU.DLL contains resources translated to German.)  If you
don't do this, some of the UI elements of your application will remain in the
language of the operating system.

/////////////////////////////////////////////////////////////////////////////
