% OIP_CALIBRATE     Calibrate the monitor
%
%
function [paradigm] = oip_calibrate;

width = 640;
height = 480;
N = 120;

ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }';
ln = ln + 1;
paradigm.lumList = 0:255;%round([0 10 20 30 40 50 60 70 80 90 100]*255/100);
paradigm.shuffleForward = randperm(length(paradigm.lumList));
paradigm.lumList = paradigm.lumList(paradigm.shuffleForward);
[junk paradigm.shuffleBackward] = sort(paradigm.lumList);
for i=1:length(paradigm.lumList)
    color = paradigm.lumList(i);
    color = color + bitshift(color,8) + bitshift(color,16);
    paradigm.lines{ln} = sprintf('patch colorrect p%d { centerx %d; centery %d; width %d; height %d; color %d }',...
        i, width/2, height/2, width/2, height/2, color);
    ln = ln + 1;
    paradigm.lines{ln} = sprintf('sequence %d 0 p%d', i*N, i);
    ln = ln + 1;
    paradigm.lines{ln} = sprintf('sequence %d 1 p%d', (i+1)*N, i);
    ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', i*N+10);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', (i+1)*N-10);    % stop imaging
ln = ln + 1;
end

paradigm.filename = 'oip_calibrate.m';
paradigm.name = 'calibrate';
paradigm.desc = 'Luminance calibration of stimulus monitor';
paradigm.nframes = (i+2)*N;
global EXPERIMENT;
