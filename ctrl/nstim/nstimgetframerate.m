function [frate, data] = nstimgetframerate;

global CONNECTIONS;

nstimflush;

sendstimline('framerate');

data = [];
currentByte = 1;
while (currentByte ~= 0)
    currentByte = sockread(CONNECTIONS.nstimCon, 1);
    data(end+1) = currentByte;
end
data = char(data);
%disp(char(data));
frate = str2num(data);