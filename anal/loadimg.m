% LOADIMG   Loads an .IMG file from NCAP
%
%   IMG = LOADIMG(FILENAME) loads an .IMG file from NCAP and returns 
%   a structure in IMG.  IMG contains 4 fields:
%       width       Width of the image in pixels
%       height      Height of the image in pixels
%       bpp         # of bits per pixel
%       image       Actual image data (converted to double)
%   .IMG file format consists of a header followed by the image data.
%   The header contains 3 DWORD fields: width, height, and bpp (in that
%   order).
%
%   See also LOADCSF.
%
function img = loadimg(filename);

fid = fopen(filename, 'rb');
info = fread(fid, 3, 'uint32');
data = fread(fid, info(1)*info(2), 'uint16');
img = struct('width', info(1), 'height', info(2), 'bpp', info(3), 'image', reshape(data, [info(1) info(2)]));
fclose(fid);
