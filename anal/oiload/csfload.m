% CSFLOAD   Loads a CSF (camera stream file)
%
%      csf = csfload(filename, roix, roiy, roit, verbose)
%   ROIX = pixesl in X
%   ROIY = pixels in Y
%
function csf = loadcsf(filename, roix, roiy, roit, verbose);

if (~exist('verbose') | (length(verbose)==0))
    verbose = 0;
end
%filename = 'T:\qt007\qt007x0101.0000.csf'

% first, read the header

fid = fopen(filename, 'rb');

[csf.header, success] = csfloadheader(fid);
nframes = csfestimatelength(fid, csf.header);
if (~exist('roix') | (length(roix)==0))
    roix = 1:csf.header.width;
end
if (~exist('roiy') | (length(roiy)==0))
    roiy = 1:csf.header.height;
end
if (~exist('roit') | (length(roit)==0))
    roit = [0:nframes];
end
%nframes
%csf.header
%nframes
%csf.frames = zeros(csf.header.frame_size/(csf.header.height*2), csf.header.height, nframes);
csf.frames = zeros(length(roix), length(roiy), min(nframes,length(roit)));%min(nframes,roit(2)-roit(1)));
csf.pretimes = zeros(1,nframes);
csf.posttimes = zeros(1,nframes);

if (verbose)
    fprintf(1, '%s', ['loading frames from : ' filename ' : ']);
    statMark = .1;
end

strFrme = 1;
for frame = 1:nframes;
%     if ((frame >= roit(1)) & (frame <= roit(2)))
%         [cframe csf.pretimes(frame) csf.posttimes(frame)] = csfloadframe(fid, csf.header);
%         csf.frames(:,:,frame-roit(1)+1) = cframe(roix, roiy);
%     else
%         csfloadframe(fid, csf.header);
%         if (frame > roit(2))
%             break;
%         end
%     end
    if (length(find(frame==roit))>0) %(frame >= roit(1)) & (frame <= roit(2)))
        [cframe csf.pretimes(frame) csf.posttimes(frame)] = csfloadframe(fid, csf.header);
        csf.frames(:,:,strFrme) = cframe(roix, roiy);
        strFrme = strFrme+1;
    else
        csfloadframe(fid, csf.header);
        if (frame > roit(end))
            break;
        end
    end
    
    if (verbose)
        if (frame > statMark * nframes)
            statMark = statMark + .1;
            fprintf(1, '.');
        end
    end
end

if (verbose)
    disp('done!');
end

csf.pretimes = csf.pretimes / 3579545;
csf.posttimes = csf.posttimes / 3579545;
fclose(fid);