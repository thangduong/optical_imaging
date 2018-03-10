experiment = 'rb381x0302';
left = [];
right = [];
ddir = ['F:\oidata\rb381\' experiment '\'];
load([ddir experiment '.desc'],'-mat');
nrep = length(paradigm);
ncond = length(paradigm{1});
bphase = [0 90 180 270];
bphasedata = {[],[],[],[]};
%ordata = {[],[],[],[]};
or = [];
ordata = {};
for i=1:length(or)
    ordata{end+1} = [];
end
t = 1:140;
tf = [];
tfdata = {};
for rep=1:nrep
    for cond=1:ncond
        if (paradigm{rep}{cond}.varargin{5}==0)
            % blank condition
            continue;
        end
        curFile = [ddir '\' sprintf('%s.%d.%04d.csf', experiment, rep, cond-1)];
        curData = csfload(curFile,[],[],[],1);
        curData.frames = curData.frames(:,:,t);
        ((paradigm{rep}{cond}.param))
        if (paradigm{rep}{cond}.param.contrast == 0)
            continue;
        end
        if (isfield(paradigm{rep}{cond}.param,'bphase'))    

            bpp = find(paradigm{rep}{cond}.param.bphase == bphase);
            disp(['bprec = ' num2str(paradigm{rep}{cond}.param.bphase) 'bpp = ' num2str(bpp) ' bphase = ' num2str(bphase(bpp))]);
            if (length(bpp)>0)
                bphasedata{bpp} = addmovie(bphasedata{bpp},curData.frames);
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>3)
            bpp = find(paradigm{rep}{cond}.varargin{4} == tf);
            if (length(bpp)>0)
                tfdata{bpp} = addmovie(tfdata{bpp},curData.frames);
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>1)
            bpp = find(paradigm{rep}{cond}.varargin{2} == or);
            if (length(bpp)>0)
                ordata{bpp} = addmovie(ordata{bpp},curData.frames);
            end
        end
        if (paradigm{rep}{cond}.varargin{1}==0)
            left = addmovie(left,curData.frames);
        else
            right = addmovie(right,curData.frames);
        end
    end
end