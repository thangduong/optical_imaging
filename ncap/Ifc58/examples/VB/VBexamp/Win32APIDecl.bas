Attribute VB_Name = "Win32APIDecl"
Declare Function CloseHandle Lib "kernel32" (ByVal hObject As Long) As Long
Declare Function WaitForSingleObject Lib "kernel32" (ByVal hHandle As Long, ByVal dwMilliseconds As Long) As Long
Declare Function CreateThread Lib "kernel32" (ByVal lpThreadAttributes As Long, ByVal dwStackSize As Long, ByVal lpStartAddress As Long, ByVal lpParameter As Long, ByVal dwCreationFlags As Long, lpThreadId As Long) As Long
Declare Function Sleep Lib "kernel32" (ByVal delay As Long) As Long
Declare Function memset Lib "MSVCRT" (ByRef dest As Long, ByVal c As Integer, ByVal count As Long) As Long

