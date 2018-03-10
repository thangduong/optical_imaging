% OIP_ONEGRATING   A single grating stimulation
%
%   To parameters:
%       EYE, OR, SF, TF, contrast, 
%       OFFSET, TAIL, DURATION (in seconds), BPHASE, JitMax, CX, CY, W, H
%       
%       EYE: 0 = left, 1 = right, 2 = binoc same patch, 3 = binoc with bphase difference
%       OR: orientation in degrees (negative orientation means bi-directional)
%       SF: spatial frequency in cycles per degrees
%       TF: temporal frequency in cycles per sec
%       OFFSET: period before stimulation
%       TAIL: period after stimulation
%       DURATION: period of stimulation
%       BP: binocular phase
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
    sf = .1;
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

if ((length(varargin)>8) & (length(varargin{9})~=0))
    bphase = varargin{9};
else
    bphase = 0;
end
if ((length(varargin)>9) & (length(varargin{10})~=0))
    jitMax = varargin{10}*NSTIM.framerate;
else
    jitMax = 5*NSTIM.framerate;
end

if ((length(varargin)>10) & (length(varargin{11})~=0))
    cx = varargin{11};
else
    cx = NSTIM.mode.width/4;
end
if ((length(varargin)>11) & (length(varargin{12})~=0))
    cy = varargin{12};
else
    cy = NSTIM.mode.height/2;
end
if ((length(varargin)>12) & (length(varargin{13})~=0))
    w = varargin{13};%*NSTIM.framerate;
else
    w = NSTIM.mode.width/2;
end
if ((length(varargin)>13) & (length(varargin{14})~=0))
    h = varargin{14};
else
    h = NSTIM.mode.height;
end

paradigm.param.eye = eye;
paradigm.param.orientation = orientation;
paradigm.param.sf = sf;
paradigm.param.tf = tf;
paradigm.param.offset = offset;
paradigm.param.tail = tail;
paradigm.NSTIM = NSTIM;
paradigm.varargin = varargin;
paradigm.param.contrast = contrast;
paradigm.param.spatialPhase = 0;
paradigm.param.bphase = bphase;
paradigm.param.pos = [cx cy w h];
OFFSET = eye * NSTIM.mode.width/2;
ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }'; 
ln = ln+1;
bidir = 0;
if (orientation < 0)
    orientation = -orientation;
    bidir = 2;
end
randomJit = round(rand*jitMax);
if (contrast > 0)
	if ((eye == 0) | (eye == 1))
        paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
            'spatialfrequency %0.2f_cpd; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; spatialphase 0; alpha 255; shape 0; bidir %d }'],...
            cx + OFFSET, cy, w, h,...
            paradigm.param.sf, tf, orientation, round(contrast*127), bidir);
	%        NSTIM.mode.width/4 + OFFSET, NSTIM.mode.height/2, NSTIM.mode.width/2, NSTIM.mode.height,...
	%        paradigm.param.sf, tf, orientation, round(contrast*127));
	else
		if (eye == 2)
			paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
                'spatialfrequency %0.2f_cpd; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; spatialphase 0;  alpha 255; shape 0; bidir %d }'],...
                NSTIM.mode.width/2, cx,...%NSTIM.mode.height/2
                NSTIM.mode.width, h,...%NSTIM.mode.height,...
                paradigm.param.sf, tf, orientation, round(contrast*127), bidir);
        else
            if (eye == 3)
				paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
                    'spatialfrequency %0.2f_cpd; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; spatialphase 0; alpha 255; shape 0; bidir %d }'],...
                    cx, cy, w, h,...
                    paradigm.param.sf, tf, orientation, round(contrast*127), bidir);            
                ln = ln + 1;
				paradigm.lines{ln} = sprintf(['patch grating stimpatchr { centerx %d; centery %d; width %d; height %d; '...
                    'spatialfrequency %0.2f_cpd; temporalfrequency %0.2f; textureorientation %d; spatialphase %0.2f; contrast %0.2f; alpha 255; shape 0; bidir %d }'],...
                    NSTIM.mode.width/2 + cx, cy, w, h,...
                    paradigm.param.sf, tf, orientation, bphase, round(contrast*127), bidir);
            end
        end
	end
    ln = ln+1;
	paradigm.lines{ln} = sprintf('fsequence stimpatch %d %d', offset+randomJit, offset+randomJit+duration);
	ln = ln + 1;
	if (eye == 3)
		paradigm.lines{ln} = sprintf('fsequence stimpatchr %d %d', offset+randomJit, offset+randomJit+duration);
		ln = ln + 1;
	end
end
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', randomJit);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', randomJit+offset+duration+tail);      % stop imaging
ln = ln + 1;
paradigm.param.randomJit = randomJit;
paradigm.filename = 'oip_onegrat.m';
paradigm.name = 'onegrat';
paradigm.desc = 'Single grating - 8/29/2006 v6: v4 has correct binocular phase stimuation for bidirectional. v5 has variable height for eye mode=2. v6 has fixed width';
paradigm.nframes = randomJit+offset+duration+tail+5;
global EXPERIMENT;
