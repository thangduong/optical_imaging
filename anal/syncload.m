% SYNCLOAD  Loads a synchronization file
%
%   RESULT = SYNCLOAD(FILENAME) loads a synchronization file FILENAME.
%
%
function result = syncload(filename);
%filename = 'c:\temp\junka.sync';

fp = fopen(filename, 'rb');

hdr.magic = char(fread(fp, 4, 'char')');
hdr.samplingRate = fread(fp, 1, 'uint32');
hdr.lowChan = fread(fp, 1, 'uint16');
hdr.highChan = fread(fp, 1, 'uint16');
hdr.bytesToSkip = fread(fp, 1, 'uint32');
hdr.threshold = fread(fp, 1, 'float');
junk = fread(fp, hdr.bytesToSkip, 'char');

data = fread(fp, 'uint32');
times = bitand(data,2^28-1);
values = bitand(data,2^28) > 0;
chan = bitshift(bitand(data,2^29 + 2^30 + 2^31),-29);
result.header = hdr;
result.data = data;
result.times = times;
result.values = values;
result.chan = chan;
fclose(fp);
