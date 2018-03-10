% OIP_SINGLEMSEQ    Single patch m-sequence
%
%   To parameters:
%       EYE, OR, SF, TF, contrast, BASE_PERIOD (in sec), ORDER, SEED, OFFSETTIME (in
%       sec), TAILTIME (in sec)
%       
%       EYE: 0 = left, 1 = right
%       OR: orientation in degrees
%       SF: spatial frequency in cycles per degrees
%       TF: temporal frequency in cycles per sec
%       BASE_PERIOD: in seconds
%       ORDER, SEED: m-sequence (if not given, it will assume)
%       OFFSETTIME: offset time (time at the beginning to image without
%       stimulating)
%
%
function [paradigm] = oip_singlemseq(varargin);

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
    contrast = 50;
end
if ((length(varargin)>5) & (length(varargin{6})~=0))
    basePeriod = floor(varargin{6}*NSTIM.framerate);
else
    basePeriod = 75;
end
if ((length(varargin)>6) & (length(varargin{7})>0))
    order = varargin{7};
else
    order = 5;
end
if ((length(varargin)>7) & (length(varargin{8})>0))
    seed = varargin{8};
else
    seedList = double(findmseqseed(order));
    randSeed = round(rand*(length(seedList)-1))+1;
    seed = seedList(randSeed);
end
if ((length(varargin)>8) & (length(varargin{9})>0))
    offsetTime = floor(varargin{9}*NSTIM.framerate);
else
    offsetTime = 75*5;
end
if ((length(varargin)>9) & (length(varargin{10})>0))
    tailTime = floor(varargin{10}*NSTIM.framerate);
else
    tailTime = 75*5;
end

paradigm.param.eye = eye;
paradigm.param.orientation = orientation;
paradigm.param.sf = sf;
paradigm.param.tf = tf;
paradigm.param.basePeriod = basePeriod;
paradigm.param.seed = seed;
paradigm.param.order = order;
paradigm.param.offsetTime = offsetTime;
paradigm.param.tailTime = tailTime;
paradigm.NSTIM = NSTIM;
paradigm.varargin = varargin;
paradigm.contrast = contrast;
paradigm.param.sf_pixPerCycle = round(deg2pix(1)/sf);
OFFSET = eye * NSTIM.mode.width/2;
ln = 1;
paradigm.lines{ln} = 'lpt cameratrig { Port 0; Bit 4; Toggle 0; Value 0; }'; 
ln = ln+1;
if (eye == 3)
	paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
        'spatialfrequency %d; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; alpha 255; shape 0 }'],...
        NSTIM.mode.width/2, NSTIM.mode.height/2, NSTIM.mode.width, NSTIM.mode.height,...
        paradigm.param.sf_pixPerCycle, tf, orientation, contrast);
else
    paradigm.lines{ln} = sprintf(['patch grating stimpatch { centerx %d; centery %d; width %d; height %d; '...
        'spatialfrequency %d; temporalfrequency %0.2f; textureorientation %d; contrast %0.2f; alpha 255; shape 0 }'],...
        NSTIM.mode.width/4 + OFFSET, NSTIM.mode.height/2, NSTIM.mode.width/2, NSTIM.mode.height,...
        paradigm.param.sf_pixPerCycle, tf, orientation, contrast);
end
ln = ln+1;
paradigm.param.mseq = [genmseq(order, seed, 1) 0];
fsequenceLine = ['fsequence stimpatch'];
curFrame = offsetTime;
stim = 0;
for i=1:length(paradigm.param.mseq)
    if (stim == 0)
        if (paradigm.param.mseq(i) == 1)
            fsequenceLine = [fsequenceLine ' ' num2str(curFrame)];
            stim = 1;
        end
    else
        if (paradigm.param.mseq(i) == 0)
            fsequenceLine = [fsequenceLine ' ' num2str(curFrame)];
            stim = 0;
        end        
    end
    curFrame = curFrame + basePeriod;
end
paradigm.lines{ln} = fsequenceLine;
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 1', 0);      % start imaging
ln = ln + 1;
paradigm.lines{ln} = sprintf('sequence %d 2 cameratrig Value 0', curFrame + tailTime);      % start imaging
ln = ln + 1;
paradigm.filename = 'oip_singlemseq.m';
paradigm.name = 'singlemseq';
paradigm.desc = 'Single condition m-sequence - 2/10/2006';
paradigm.nframes = curFrame + tailTime + 5;
global EXPERIMENT;
