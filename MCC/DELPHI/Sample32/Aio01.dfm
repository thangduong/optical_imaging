�
 TFRMAINAOUTSCAN 0�
  TPF0TfrmAInAoutScanfrmAInAoutScanLeft� Top� Width�Height�Caption*Simultaneous cbAInScan() and cbAoutScan ()
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.StylefsBold PositionpoScreenCenterOnCreate
FormCreatePixelsPerInch`
TextHeight TLabellblShowADCountLeft� Top� WidthHeight  TLabellblShowADIndexLeft� Top� WidthHeight  TLabellblShowADStatLeft� Top� WidthHeight  TLabelLabel1Left� Top Width<Height	AlignmenttaCenterCaptionqBoard 0 must support simultaneous paced input and paced output. For more inforamtion, see hardware documentation.
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.Style 
ParentFontWordWrap	  TLabelLabel2Left4Top� WidthqHeight	AlignmenttaRightJustifyCaptionCurrent A/D Status:  TLabelLabel3Left9Top� WidthlHeight	AlignmenttaRightJustifyCaptionCurrent A/D Index:  TLabelLabel4Left7Top� WidthnHeight	AlignmenttaRightJustifyCaptionCurrent A/D Count:  TLabellblShowDAStatLeftTop� WidthHeight  TLabellblShowDAIndexLeftTop� WidthHeight  TLabellblShowDACountLeftTop� WidthHeight  TLabelLabel5Left�Top� WidthqHeight	AlignmenttaRightJustifyCaptionCurrent D/A Status:  TLabelLabel6Left�Top� WidthlHeight	AlignmenttaRightJustifyCaptionCurrent D/A Index:  TLabelLabel7Left�Top� WidthnHeight	AlignmenttaRightJustifyCaptionCurrent D/A Count:  TButton
cmdADStartLeft%Top`Width� HeightCaption&Start A/D Background Operation
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.StylefsBold 
ParentFontTabOrder OnClickcmdADStartClick  TButtoncmdQuitLeft#Top5WidthGHeightCaption&QuitTabOrderOnClickcmdQuitClick  TMemoMemo1LeftTop� Width� HeightYLines.StringsData display  TabOrder  TButton	cmdADStopLeft%Top_Width� HeightCaptionStop A/D Background OperationTabOrderVisibleOnClickcmdADStopClick  TPanelPanel1LeftgTopWidth�HeightCaption;Demonstration of Simultaneous cbAInScan() and cbAoutScan ()TabOrder  TButton
cmdDAStartLeft�Top`Width� HeightCaption&Start D/A Background Operation
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.StylefsBold 
ParentFontTabOrderOnClickcmdDAStartClick  TButton	cmdDAStopLeft�Top^Width� HeightCaptionStop D/A Background OperationTabOrderVisibleOnClickcmdDAStopClick  TPanelPanel2Left@Top`WidthHeight� 
BevelOuter	bvLowered
Font.ColorclWindowTextFont.Height�	Font.NameMS Sans Serif
Font.StylefsBold 
ParentFontTabOrder  TTimertmrCheckStatusInterval�OnTimertmrCheckStatusTimerLeft8Top`   