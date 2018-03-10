% OIP_INTRINSIC_OR_REVCOR   Reverse correlation in orientation (slow for intrinsic)
%
%     PARAMETERS ARE:
%          CenterX, CenterY, Width, Height, SF, TF, OrList
%
%
function [paradigm] = oip_intrinsic_or_revcor;

global NSTIM;

paradigm.filename = 'oip_intrinsic_or_revcor_lr.m';
paradigm.filedate = 'Mar 26, 2006';
paradigm.frate = NSTIM.framerate;
ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }';
ln = ln + 1;
paradigm.CenterX = NSTIM.mode.width/4;
paradigm.CenterY = NSTIM.mode.height/2;
paradigm.Width = NSTIM.mode.width/2;
paradigm.Height = NSTIM.mode.height;
paradigm.Sf = 0.1;
paradigm.Tf = 2;
paradigm.Orlist = 0:30:330;
paradigm.Contrast = 127;
paradigm.Luminance = 127;
paradigm.PreCap = 5;        % # of seconds camera goes on before stimulating
paradigm.PostCap = 15;      % # of seconds stim goes off before stopping camera
seq = [1:(length(paradigm.Orlist)*2)];
paradigm.StimSeq = [];
paradigm.NREP = 10;
for rep = 1:paradigm.NREP
    paradigm.StimSeq = [paradigm.StimSeq seq(randperm(length(seq)))];
end
paradigm.CondTime = 1;      % condition time in seconds
fpc = round(paradigm.CondTime*paradigm.frate);
oipcmd = sprintf(['patch oigrating stimpatch { FramesPerCond %d; NumCond %d; Shape 0; Width %0.2f; Height %0.2f; CenterX %0.2f; CenterY %0.2f'],...
            fpc, 2*length(paradigm.Orlist), paradigm.Width, paradigm.Height, paradigm.CenterX, paradigm.CenterY);

for i=1:length(paradigm.Orlist)
    condPatch = sprintf('; CenterX_%d %0.2f; CenterY_%d %0.2f; Contrast_%d %0.2f; Luminance_%d %0.2f; Orientation_%d %0.2f; SpatialFrequency_%d %0.2f_cpd; TemporalFrequency_%d %0.2f',...
        i, paradigm.CenterX, i, paradigm.CenterY, i, paradigm.Contrast, i, paradigm.Luminance, i, paradigm.Orlist(i), i, paradigm.Sf, i, paradigm.Tf);
    oipcmd = [oipcmd condPatch];
end

for j=1:length(paradigm.Orlist)
    i = j+length(paradigm.Orlist);
    condPatch = sprintf('; CenterX_%d %0.2f; CenterY_%d %0.2f; Contrast_%d %0.2f; Luminance_%d %0.2f; Orientation_%d %0.2f; SpatialFrequency_%d %0.2f_cpd; TemporalFrequency_%d %0.2f',...
        i, paradigm.CenterX+paradigm.Width, i, paradigm.CenterY, i, paradigm.Contrast, i, paradigm.Luminance, i, paradigm.Orlist(j), i, paradigm.Sf, i, paradigm.Tf);
    oipcmd = [oipcmd condPatch];
end

stimSeq = '; stimseq ';
for i=1:(length(paradigm.StimSeq)-1)
    stimSeq = [stimSeq num2str(paradigm.StimSeq(i)) ','];
end
stimSeq = [stimSeq num2str(paradigm.StimSeq(end))];

oipcmd = [oipcmd stimSeq ' }'];

paradigm.lines{ln} = oipcmd;
ln = ln + 1;
paradigm.lines{ln} = 'sequence 5 2 cameratrig Value 1';
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 0 stimpatch', 5+round(paradigm.PreCap*paradigm.frate));
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 1 stimpatch', 5+round(paradigm.PreCap*paradigm.frate)+fpc*length(paradigm.StimSeq));
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', 5+fpc * length(paradigm.StimSeq)+round(paradigm.PostCap*paradigm.frate)+round(paradigm.PreCap*paradigm.frate));
ln = ln + 1;
paradigm.nframes = 5+fpc * length(paradigm.StimSeq)+round(paradigm.PostCap*paradigm.frate)+round(paradigm.PreCap*paradigm.frate)+10;
%ln = ln + 1;
%paradigm.lines{ln} = 

% patch oigrating og { NumCond 2; Shape 1; 
% Width 100; Height 100; CenterX 100; CenterY 100; 
% StimSeq 1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2; 
% FramesPerCond 360; TemporalFrequency_1 1;SpatialFrequency_1 50; 
% Contrast_1 127; Luminance_1 127; Orientation_1 90; SpatialFrequency_2 50; 
% Contrast_2 127; Luminance_2 127; Orientation_2 45; TemporalFrequency_2 2;};