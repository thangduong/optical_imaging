unit Ai02;
{
ULAI02.DPR================================================================

 File:                         AI02.PAS

 Library Call Demonstrated:    cbAInScan(), FOREGROUND mode

 Purpose:                      Scans a range of A/D Input Channels and stores
                               the sample data in an array.

 Demonstration:                Displays the analog input on two channels.

 Other Library Calls:          cbErrHandling()

 Special Requirements:         Board 0 must have an A/D converter.
                               Analog signals on two input channels.

 (c) Copyright 1995 - 2002, Measurement Computing Corp.
 All rights reserved.
==========================================================================
}
interface

uses
  SysUtils, WinTypes, WinProcs, Messages, Classes, Graphics, Controls,
  Forms, Dialogs, StdCtrls, ExtCtrls, cbw;

type
  TfrmAInScan = class(TForm)
    tmrAIn: TTimer;
    cmdStart: TButton;
    cmdQuit: TButton;
    Memo1: TMemo;
    procedure tmrAInTimer(Sender: TObject);
    procedure cmdStartClick(Sender: TObject);
    procedure cmdQuitClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
   frmAInScan: TfrmAInScan;

implementation

{$R *.DFM}

var
   ULStat:                Integer;
   MemHandle:             Integer;
   ErrorString:           string;
   ErrReporting:          Integer;
   ErrHandling:           Integer;
   ADData:                array[0..600] of Word;
   x:                     Integer;
   Revlevel:              Single;

const
   BoardNum:              Integer = 0;
   Count:                 Integer = 600;
   FirstPoint:            LongInt = 0;
   Rate:                  LongInt = 1000;
   LowChan:               Integer = 0;
   HighChan:              Integer = 1;
   Range:                 LongInt = BIP5VOLTS;
   Options:               Integer = CONVERTDATA;


procedure TfrmAInScan.FormCreate(Sender: TObject);
begin
  {declare Revision Level}
   RevLevel := CURRENTREVNUM;
   ULStat := cbDeclareRevision(RevLevel);

   {set up internal error handling for the Universal Library}

   ErrReporting := PRINTALL;       {set Universal Library to print all errors}
   ErrHandling := STOPALL;         {set Universal Library to stop on errors}
   ULStat := cbErrHandling(ErrReporting, ErrHandling);

   {set up a buffer in Windows to contain the data}
   MemHandle := cbWinBufAlloc (Count);
   Memo1.Text := 'Click start to acquire data';
end;

procedure TfrmAInScan.cmdStartClick(Sender: TObject);
begin
   tmrAIn.Enabled := True;
end;

procedure TfrmAInScan.tmrAInTimer(Sender: TObject);
begin
   {
    Collect the values with cbAInScan()
        Parameters:  (see Initialization section)
            BoardNum    :the number used by CB.CFG to describe this board
            LowChan     :low channel of the scan
            HighChan    :high channel of the scan
            Count       :the total number of A/D samples to collect
            Rate        :sample rate in samples per second
            Gain        :the gain for the board
            MemHandle   :Windows memory set up with cbWinBufAlloc()
            Options     :data collection options
   }
   ULStat := cbAInScan(BoardNum, LowChan, HighChan,
                    Count, Rate, Range, MemHandle, Options);
   If ULStat <> 0 then exit;
   Memo1.Text := '';
   x := 0;
   {
   Transfer the data from the Windows buffer to an array.  This data
   could also be accessed directly using a pointer.
   }
   ULStat := cbWinBufToArray (MemHandle, ADData[0], FirstPoint, Count);
   If ULStat <> 0 then exit;
   while x < 8 do
   begin
      Memo1.Lines.Add (Format('Channel 0: %d', [ADData[x]]));
      Memo1.Lines.Add (Format('Channel 1: %d', [ADData[x + 1]]));
      Memo1.Lines.Add ('');
      Inc(x, 2);
   end;
end;

procedure TfrmAInScan.cmdQuitClick(Sender: TObject);
begin
   tmrAIn.Enabled := False;
   ULStat := cbWinBufFree (MemHandle);
   Close;
end;

end.
