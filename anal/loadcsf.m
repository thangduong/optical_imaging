% LOADCSF   Loads a CSF file into memory
%
%   DATA = LOADCSF(FILENAME, OPTION, [START], [END]);
%
%   Valid values for OPTION are:
%       0       Load just the header information
%       1       Load the header information and count the number of frames
%       2       Load from frame number [START] to frame number [END]
%       3       Load the whole file (not recomended)
%
