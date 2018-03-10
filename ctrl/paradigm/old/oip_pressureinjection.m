% OIP_PRESSUREINJECTION Image the response to a pressure injection of a solution
%
%   To parameters:
%       duration, snapbefore, snapafter, randomJit
%
%   Hook camera to bit 4, pressure injection to bit 5
function [paradigm] = oip_pressureinjection(varargin);

global NSTIM;

if ((length(varargin)>0) & (length(varargin{1})~=0))
    duration = varargin{1} * NSTIM.framerate;
else
    duration = NSTIM.framerate;
end
duration = round(duration);

if ((length(varargin)>1) & (length(varargin{2})~=0))
    snapBefore = varargin{2} * NSTIM.framerate;
else
    snapBefore = NSTIM.framerate;
end
snapBefore = round(snapBefore);

if ((length(varargin)>2) & (length(varargin{3})~=0))
    snapAfter = varargin{3} * NSTIM.framerate;
else
    snapAfter = NSTIM.framerate;
end
snapAfter = round(snapAfter);

if ((length(varargin)>3) & (length(varargin{4})~=0))
    randomJit = varargin{4} * NSTIM.framerate;
else
    randomJit = NSTIM.framerate;
end
randomJit = round(rand*randomJit);

paradigm.NSTIM = NSTIM;
paradigm.param.duration = duration;
paradigm.param.snapBefore = snapBefore;
paradigm.param.snapAfter = snapAfter;

ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }'; 
ln = ln + 1;
paradigm.lines{ln} = 'lpt pressuretrig { Port 0; Bit 5; Toggle 0; Value 0; }'; 
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', randomJit);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', randomJit+snapBefore+duration+snapAfter);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 pressuretrig Value 1', randomJit+snapBefore);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 pressuretrig Value 0', randomJit+snapBefore+duration);      % start imaging

paradigm.param.randomJit = randomJit;
paradigm.filename = 'oip_pressureinjection.m';
paradigm.name = 'pressureinjection';
paradigm.desc = 'Pressure Injection - 2/10/2006';
paradigm.nframes = randomJit+snapBefore+duration+snapAfter+5;
global EXPERIMENT;
