% OIP_ONEGRAT   A single grating stimulation
%
%   To parameters:
%       EYE, OR, SF, TF, contrast, 
%       sec), OFFSET, TAIL, DURATION (in seconds)
%       
%       EYE: 0 = left, 1 = right
%       OR: orientation in degrees
%       SF: spatial frequency in cycles per degrees
%       TF: temporal frequency in cycles per sec
%
%
function [paradigm] = oip_onegrat(varargin);

if (length(varargin)>0)
if (length(varargin{1})>1)
    varargin = varargin{1};
end
end

global NSTIM;
if ((length(varargin)>0) & (length(varargin{1})~=0))
    eye = varargin{1};
else
    eye = 0;
end
if ((length(varargin)>1) & (length(varargin{2})~=0))
    orientation = varargin{2};
else
    orientation = 0;
end
if ((length(varargin)>2) & (length(varargin{3})~=0))
    sf = varargin{3};
else
    sf = .4;
end
if ((length(varargin)>3) & (length(varargin{4})~=0))
    tf = varargin{4};
else
    tf = 4;
end
if ((length(varargin)>4) & (length(varargin{5})~=0))
    contrast = varargin{5};
else
    contrast = .50;
end
if ((length(varargin)>5) & (length(varargin{6})~=0))
    offset = varargin{6} * NSTIM.framerate;
else
    offset = NSTIM.framerate * 5;
end
offset = round(offset);
if ((length(varargin)>6) & (length(varargin{7})~=0))
    tail = varargin{7} * NSTIM.framerate;
else
    tail = NSTIM.framerate * 20;
end
tail = round(tail);
if ((length(varargin)>7) & (length(varargin{8})~=0))
    duration = varargin{8} * NSTIM.framerate;
else
    duration = NSTIM.framerate * 2;
end
duration = round(duration);

paradigm.param.eye = eye;
paradigm.param.orientation = orientation;
paradigm.param.sf = sf;
paradigm.param.tf = tf;
paradigm.param.offset = offset;
paradigm.param.tail = tail;
paradigm.NSTIM = NSTIM;
paradigm.varargin = varargin;
paradigm.param.contrast = contrast;
paradigm.param.sf_pixPerCycle = round(deg2pix(1)/sf);
OFFSET = eye * NSTIM.mode.width/2;
ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }'; 
ln = ln+1;
if (eye == 3)
	paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
        'spatialfrequency %d; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; alpha 255; shape 0 }'],...
        NSTIM.mode.width/2, NSTIM.mode.height/2, NSTIM.mode.width, NSTIM.mode.height,...
        paradigm.param.sf_pixPerCycle, tf, orientation, round(contrast*127));
else
    paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
        'spatialfrequency %d; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; alpha 255; shape 0 }'],...
        NSTIM.mode.width/4 + OFFSET, NSTIM.mode.height/2, NSTIM.mode.width/2, NSTIM.mode.height,...
        paradigm.param.sf_pixPerCycle, tf, orientation, round(contrast*127));
end
ln = ln+1;
randomJit = round(rand*1000);
paradigm.lines{ln} = sprintf('fsequence stimpatch %d %d', offset+randomJit, offset+randomJit+duration);
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', randomJit);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', randomJit+offset+duration+tail);      % start imaging
ln = ln + 1;
paradigm.param.randomJit = randomJit;
paradigm.filename = 'oip_onegrat.m';
paradigm.name = 'onegrat';
paradigm.desc = 'Single grating - 2/10/2006 v2';
paradigm.nframes = randomJit+offset+duration+tail+5;
global EXPERIMENT;
