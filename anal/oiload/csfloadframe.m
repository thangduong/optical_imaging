function [frame, pretime, posttime, success] = csfloadframe(fid, header);


try
	pretime = fread(fid, 1, 'uint64');
	frame = reshape(fread(fid, header.frame_size/2,'uint16'), header.frame_size/(header.height*2), header.height);
	posttime = fread(fid, 1, 'uint64');
    success = 1;
catch
    success = 0;
end
