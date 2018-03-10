% OIP_TMS   rTMS stimulation
%
%   Parameters:
%       OFFSET, NPULSES, DELTA, TAIL, RANDOMJIT
%
%   OFFSET = offset before stimulation
%   NPULSES = number of pulses to stimulate
%   DELTA = time between pulse in seconds
%   TAIL = capturing time after stimulation
%   Hook camera to bit 4, pressure injection to bit 5
function [paradigm] = oip_tms(varargin);

global NSTIM;

if (length(varargin)>0)
if (length(varargin{1})>1)
    varargin = varargin{1};
end
end


if ((length(varargin)>0) & (length(varargin{1})~=0))
    offset = varargin{1} * NSTIM.framerate;
else
    offset = NSTIM.framerate;
end
offset = round(offset);

if ((length(varargin)>1) & (length(varargin{2})~=0))
    npulses = varargin{2};
else
    npulses = 100;
end
npulses = round(npulses);

if ((length(varargin)>2) & (length(varargin{3})~=0))
    delta = varargin{3} * NSTIM.framerate;
else
    delta = .25 * NSTIM.framerate;
end
delta = round(delta);

if ((length(varargin)>3) & (length(varargin{4})~=0))
    tail = varargin{4} * NSTIM.framerate;
else
    tail = NSTIM.framerate;
end
tail = round(tail);

if ((length(varargin)>4) & (length(varargin{5})~=0))
    randomJit = varargin{5} * NSTIM.framerate;
else
    randomJit = NSTIM.framerate;
end
randomJit = round(rand*randomJit);
randomJit

paradigm.NSTIM = NSTIM;
paradigm.param.offset = offset;
paradigm.param.npulses = npulses;
paradigm.param.delta = delta;
paradigm.param.randomJit = randomJit;
paradigm.param.tail = tail;
duration = npulses * delta;

ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }'; 
ln = ln + 1;
paradigm.lines{ln} = 'lpt pressuretrig { Port 0; Bit 5; Toggle 0; Value 0; }'; 
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', randomJit);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', randomJit+offset+duration+tail);      % start imaging
ln = ln + 1;
for i=1:npulses
	paradigm.lines{ln} = sprintf('sequence %d 2 pressuretrig Value 1', randomJit+offset+delta*(i-1));      % start imaging
	ln = ln + 1;
	paradigm.lines{ln} = sprintf('sequence %d 2 pressuretrig Value 0', randomJit+offset+delta*(i-1)+1);      % start imaging
	ln = ln + 1;
end
%paradigm.lines{ln} = sprintf('sequence %d 2 pressuretrig Value 0', randomJit+offset+duration);      % start imaging

paradigm.param.randomJit = randomJit;
paradigm.filename = 'oip_tms.m';
paradigm.name = 'rTMS';
paradigm.desc = 'rTMS - 9/28/2006';
paradigm.nframes = randomJit+offset+duration+tail+5;
global EXPERIMENT;
