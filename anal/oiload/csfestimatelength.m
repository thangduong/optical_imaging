% CSFESTIMATELENGTH Estimate length of a CSF file in terms of # of frames
%
%
function nframes = csfestimatelength(fid, header);

oldpos = ftell(fid);

fseek(fid, 0, 1);
filesize = ftell(fid);

fseek(fid, oldpos, -1);

datasize = filesize - header.bytes_to_skip - 580; % 580 is the size of the header
bytesperframe = header.frame_size + 16;             % 8 pretime and 8 posttime stamp
nframes = floor(datasize / bytesperframe);
