function [header, success] = csfloadheader(fid);

try
	header.magic = fread(fid, 1, 'uint32');
	header.version = fread(fid, 1, 'uint32');
	header.width = fread(fid, 1, 'uint32');
	header.height = fread(fid, 1, 'uint32');
	header.ebpp = fread(fid, 1, 'uint32');
	header.bpp = fread(fid, 1, 'uint32');
	header.pixeltype = fread(fid, 1, 'uint32');
	header.xbin = fread(fid, 1, 'uint32');
	header.ybin = fread(fid, 1, 'uint32');
	header.frame_size = fread(fid, 1, 'uint32');
	header.timestamp_freq = fread(fid, 1, 'uint64');
	header.expected_fps = fread(fid, 1, 'double');
	header.ccdinfo.desc = char(fread(fid, 512, 'char'));
	header.ccdinfo.desc = header.ccdinfo.desc(1:min(find(header.ccdinfo.desc==0)))';
	header.ccdinfo.well_size = fread(fid, 1, 'uint32');
	header.ccdinfo.adc_speed = fread(fid, 1, 'uint32');
	header.bytes_to_skip = fread(fid, 1, 'uint32') + 4;
	header.junk = char(fread(fid, header.bytes_to_skip, 'char'));
	success = 1;
catch
    header = [];
    success = 0;
end