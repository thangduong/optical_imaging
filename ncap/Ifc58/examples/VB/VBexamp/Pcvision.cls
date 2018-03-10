VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "PC-RGB"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Description = "This is a class that is defined for a PC-RGB board"
Attribute VB_Ext_KEY = "SavedWithClassBuilder" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"
'local variable(s) to hold property value(s)
Private mvarBoard As Integer 'local copy
Private mvarCamera As Integer 'local copy
Private Pointer As Long
Public Property Let Camera(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Camera = 5
    mvarCamera = vData
End Property


Public Property Get Camera() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Camera
    Camera = mvarCamera
End Property


Public Function Display(ByVal Win_Handle As Long, Mode As Integer) As Boolean
End Function

Public Property Let Board(ByVal vData As Integer)
'used when assigning a value to the property, on the left side of an assignment.
'Syntax: X.Board = 5
    mvarBoard = vData
End Property


Public Property Get Board() As Integer
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.Board
    Board = mvarBoard
End Property



