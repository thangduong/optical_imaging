% NOTE: this code actually does CX but it's called CY because of copy and paste
experiment = 'rb089x0108';
%left = [];
%right = [];
ddir = ['e:\rb089\' experiment '\'];
load([ddir experiment '.desc'],'-mat');
nrep = length(paradigm);
ncond = length(paradigm{1});
t = 1:(6*(1+3+5));
tf = [];
or = [-90 -180];
bphase = [];
eye = [0 1];
eyedata = {};
eyecount = {};

cy = [450   510   570   630   690   750   810];
cycount = {};
cydata = {};
szv = [60 120];
for ev=1:length(eye)
    cydata{ev} = {};
    cycount{ev} = {};
for sz =1:length(szv)
    cydata{ev}{sz} = {};
    cycount{ev}{sz} = {};
	for i=1:length(cy)
        cydata{ev}{sz}{end+1} = [];
        cycount{ev}{sz}{end+1} = [];
	end
end
end
for i=1:length(eye)
    eyedata{end+1} = [];
    eyecount{end+1} = 0;
end
bphasedata = {};
bphasecount = {};
for i=1:length(bphase)
    bphasedata{end+1} = [];
    bphasecount{end+1} = 0;
end
ordata = {};
orcount = {};
for i=1:length(or)
    ordata{end+1} = [];
    orcount{end+1} = 0;
end
tfdata = {};
tfcount = {};
for i=1:length(tf)
    tfdata{end+1} = [];
    tfcount{end+1} = 0;
end
for rep=1:3
    for cond=1:ncond
        if (paradigm{rep}{cond}.varargin{5}==0)
            % blank condition
            continue;
        end
        curFile = [ddir '\' sprintf('%s.%d.%04d.csf', experiment, rep, cond-1)];
        curData = csfload(curFile,[],[],[],1);
        curData.frames = curData.frames(:,:,t);
        if (paradigm{rep}{cond}.param.contrast == 0)
            continue;
        end
        disp(['eye = ' num2str(paradigm{rep}{cond}.param.eye) ...
                ' bprec = ' num2str(paradigm{rep}{cond}.param.bphase) ...
                ' tf = ' num2str(paradigm{rep}{cond}.param.tf) ...
                ' sf = ' num2str(paradigm{rep}{cond}.param.sf) ...
                ' contrast = ' num2str(paradigm{rep}{cond}.param.contrast) ...
                ' orientation = ' num2str(paradigm{rep}{cond}.param.orientation)]);
        if (isfield(paradigm{rep}{cond}.param,'bphase')&(paradigm{rep}{cond}.param.eye==3))    
            bpp = find(paradigm{rep}{cond}.param.bphase == bphase);
            if (length(bpp)>0)
                bphasedata{bpp} = addmovie(bphasedata{bpp},curData.frames);
                bphasecount{bpp} = bphasecount{bpp} + 1; 
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>3)
            bpp = find(paradigm{rep}{cond}.varargin{4} == tf);
            if (length(bpp)>0)
                tfdata{bpp} = addmovie(tfdata{bpp},curData.frames);
                tfcount{bpp} = tfcount{bpp} + 1; 
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>1)
            bpp = find(paradigm{rep}{cond}.varargin{1} == eye);
            if (length(bpp)>0)
                eyedata{bpp} = addmovie(eyedata{bpp},curData.frames);
                eyecount{bpp} = eyecount{bpp} + 1; 
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>1)
            bpp = find(paradigm{rep}{cond}.varargin{2} == or);
            if (length(bpp)>0)
                ordata{bpp} = addmovie(ordata{bpp},curData.frames);
                orcount{bpp} = orcount{bpp} + 1; 
            end
        end
        if (length(paradigm{rep}{cond}.varargin)>11)
            bpp = find(paradigm{rep}{cond}.varargin{12} == cy);
            enum = find(paradigm{rep}{cond}.varargin{1} == eye);
            sz = find(paradigm{rep}{cond}.varargin{14} == szv);
            if ((length(bpp)>0)&(length(enum)>0)&(length(sz)>0))
                cydata{enum}{sz}{bpp} = addmovie(cydata{enum}{sz}{bpp},curData.frames);
                cycount{enum}{sz}{bpp} = cycount{enum}{sz}{bpp} + 1; 
            end
        end
%        if (paradigm{rep}{cond}.varargin{1}==0)
%            left = addmovie(left,curData.frames);
%        else
%            right = addmovie(right,curData.frames);
%        end
    end
end