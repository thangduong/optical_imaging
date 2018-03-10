Attribute VB_Name = "Processing"
Public Sub Invert(ByRef h_Buffer() As Byte)
    Dim x As Integer
    Dim y As Integer
    For y = 0 To Image_DY
        For x = 0 To Image_DX * SrcBytesPP
            h_Buffer(x, y) = 255 - h_Buffer(x, y)
        Next x
    Next y
End Sub

Public Sub Threshold(ByRef h_Buffer() As Byte)
   For x = 0 To Image_DX * SrcBytesPP
        For y = 0 To Image_DY
            If h_Buffer(x, y) > 128 Then
                h_Buffer(x, y) = 244
            Else
                h_Buffer(x, y) = 10
            End If
        Next y
    Next x
End Sub
