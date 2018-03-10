%function frames = oiloadall(exp, xroi, yroi, ntime);
exp = 'calibx0113';

datadir = 't:\';
%exp = 'qt007x0107';
if (~exist('ntime') | (length(ntime)==0))
    ntime = 1;
end
if (~exist('xroi') | (length(xroi)==0))
xroi = 1:256;
end
if (~exist('yroi') | (length(yroi)==0))
yroi = 1:256;
end


dirbase = [datadir exp(1:(min(find(exp=='x')-1))) ];
filebase = [datadir exp(1:(min(find(exp=='x')-1))) filesep exp];
filelist = dir([filebase '.*.csf']);

xmlfile = [filebase '.xml'];
rawfile = [filebase '.raw'];
%getnextcond;
%for i=1:26
%    [rep, cond, condtime, numspikes, spikestimes] = getNextCond(rawfile);    
%    disp(num2str(cond));
%end
%return;
[done, listsize, condlist, condTimes] = getcondlist(rawfile);
[junk, uv] = unique(condTimes);
%conditions = double(condlist(uv));
%conditions = double(condlist(1:3:end));
conditions = double(condlist(1:2:end));
conditions = bitshift(conditions, -8);
ncond = length(unique(conditions));
nrepoi = floor(length(filelist)/ncond);
nrepraw = floor(length(conditions)/ncond);
nrep = min(nrepoi, nrepraw);
disp(sprintf('number of conditions = %d number of reps = %d', ncond, nrep));
csf = csfload([filebase sprintf('.%04d.csf',0)],xroi,yroi,1);
%datasize = size(csf.frames(50:150,:,1:2:end));
datasize = size(csf.frames(:,:,1:ntime:end));
%datasize = size(csf.frames(xroi,yroi,1:ntime:end));

for rep = 1:nrep
for cond = 1:ncond
    frames{cond}{rep} = zeros(datasize);
end
end
rep = 1;
for file = 1:min(length(filelist), nrep*ncond)
    csf = csfload([filebase sprintf('.%04d.csf',file-1)],xroi,yroi,1);
%    min(length(frames{conditions(file)}))
%     if (min(length(frames{conditions(file)})) == 0)
%         frames{conditions(file)} = matchsize(csf.frames(:,:,1:2:end), datasize);
%     else
%         frames{conditions(file)} = matchsize(csf.frames(:,:,1:2:end), datasize) + frames{conditions(file)};
%     end
%    if (min(length(frames{conditions(file)})) == 0)
%        frames{conditions(file)} = matchsize(csf.frames(:,:,1:2:end), datasize) + matchsize(csf.frames(:,:,2:2:end), datasize);
%    else
    if (file > (ncond*rep))
        rep = rep + 1;
    end
    for ctime=1:ntime
        frames{conditions(file)}{rep} = matchsize(csf.frames(:, :,ctime:ntime:end), datasize);
%        frames{conditions(file)} = matchsize(csf.frames(xroi, yroi,ctime:ntime:end), datasize);
    end
%        frames{conditions(file)} = matchsize(csf.frames(50:150,:,1:2:end), datasize) + matchsize(csf.frames(50:150,:,2:2:end), datasize) + frames{conditions(file)};
        %    end
end
