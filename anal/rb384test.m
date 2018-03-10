experiment = 'rb384x0103';
left = [];
right = [];
ddir = ['c:\temp\' experiment '\'];
load([ddir experiment '.desc'],'-mat');
nrep = 8;%length(paradigm);
ncond = length(paradigm{1});
bphase = [];
bphasedata = {[],[],[],[]};
%ordata = {[],[],[],[]};
or = [0,90,180,270];
ordata = {};
for i=1:length(or)
    ordata{end+1} = [];
end
tf = [2 8];
tfdata = {[],[]};
for rep=1:nrep
    for cond=1:ncond
        if (paradigm{rep}{cond}.varargin{5}==0)
            % blank condition
            continue;
        end
        curFile = ['e:\' experiment '\' sprintf('%s.%d.%04d.csf', experiment, rep, cond-1)];
        curData = csfload(curFile,[],[],[],1);
        if (length(paradigm{rep}{cond}.varargin)>8)
            bpp = find(paradigm{rep}{cond}.varargin{9} == bphase);
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