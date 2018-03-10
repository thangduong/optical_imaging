% OIP_MSEQ      Optical Imaging Paradigm MSEQUENCE
%
%
function line = oip_mseq;

order = 8;
seed = 207;
nframes = 30;
width = 640;
height = 480;
nx = 2;
ny = 2;
nor = 2;
ori = [0 90];
neye = 2;

ms = double(genmseq(order, seed, 1));

i = 1;

line{i} = sprintf('viewport left { x 0; y 0; width %d; height %d }', width/2, height);
i = i + 1;
line{i} = sprintf('viewport right { x %d; y 0; width %d; height %d }', width/2, width/2, height);
i = i + 1;

patchWidth = (width/2)/nx;
patchHeight = (height)/ny;
patchNum = 0;
for or=1:nor
    alpha = floor(255/or);
	for eye=1:neye
		for y=1:ny
            for x=1:nx
                patchNum = patchNum + 1;
                if (eye == 1)
                    line{i} = sprintf('patch grating p%d { centerx %d; centery %d; width %d; height %d; shape 0; viewport left; temporalfrequency 4 ; bidir 1; blitangle %d; blitangle2 %d; alpha %d }', patchNum, (x-.5-(nx/2))*patchWidth, (y-.5-(ny/2))*patchHeight, patchWidth, patchHeight, ori(or), ori(or), alpha);
                else
                    line{i} = sprintf('patch grating p%d { centerx %d; centery %d; width %d; height %d; shape 0; viewport right; temporalfrequency 4 ; bidir 1; blitangle %d; blitangle2 %d; alpha %d }', patchNum, (x-.5-(nx/2))*patchWidth, (y-.5-(ny/2))*patchHeight, patchWidth, patchHeight, ori(or), ori(or), alpha);
                end
                i = i + 1;
            end
		end
	end
end

displacement = ceil(length(ms)/patchNum);
prev = zeros(1,patchNum);
for patch=1:patchNum
    curline =  sprintf('fsequence p%d ', patch);
    for elt=1:length(ms)
        idx = mod(elt + patch*displacement-1, length(ms))+1;
        if (ms(idx) ~= prev(patch))
            curline = [curline num2str(nframes*elt) ' '];
            prev(patch) = ms(idx);
        end
    end
    line{i} = curline;
    i = i + 1;
end



paradigm.filename = 'oip_mseq.m';
paradigm.name = 'mseq';
paradigm.order = order;
paradigm.seed = seed;

global EXPERIMENT;
