% OIP_ORTUNING     Calibrate the monitor
%
%
function [paradigm] = oip_ortuning(varargin);

global NSTIM;

sf = 1; %cpd
paradigm.NSTIM = NSTIM;
paradigm.varargin = varargin;
width = NSTIM.mode.width/8;
height = NSTIM.mode.height/8;
N = 72;
sfpixpercycle = 20;
ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }';
ln = ln + 1;
orList = [linspace(0,180,8) -1];
paradigm.orList = orList;
stimPos = 1:length(orList);
nrep = 5;
paradigm.stimPos = [];
for i=1:nrep
    paradigm.stimPos = [paradigm.stimPos stimPos];
end
paradigm.shuffleForward = randperm(length(paradigm.stimPos));
paradigm.stimPos = paradigm.stimPos(paradigm.shuffleForward);
[junk paradigm.shuffleBackward] = sort(paradigm.stimPos);
for i=1:length(paradigm.orList)
    or = paradigm.orList(i);
    if (or~=-1)
        paradigm.lines{ln} = sprintf('patch grating p%d { centerx %d; centery %d; width %d; height %d; spatialfrequency %d; temporalfrequency 1; textureorientation %d; contrast 25; alpha 255; shape 0 }',...
            i, width/2, height/2, width, height, sfpixpercycle, or);
        ln = ln + 1;
    end
end
for i=1:length(paradigm.stimPos)
    pos = paradigm.stimPos(i);
    if (paradigm.orList(pos)~=-1)
        paradigm.lines{ln} = sprintf('sequence %d 0 p%d', i*N, pos);
        ln = ln + 1;
        paradigm.lines{ln} = sprintf('sequence %d 1 p%d', (i+1)*N, pos);
        ln = ln + 1;
    end
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', i*N+10);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', (i+1)*N-10);    % stop imaging
ln = ln + 1;
end

paradigm.filename = 'oip_ortuning.m';
paradigm.name = 'ortuning';
paradigm.desc = 'Orientation tuning - 2/1/2006';
paradigm.nframes = (i+2)*N;
global EXPERIMENT;
