function [stimulating, data] = nstimisstimulating;

global CONNECTIONS;

nstimflush;

sendstimline('simulating');

data = [];
currentByte = 1;
while (currentByte ~= 0)
    currentByte = sockread(CONNECTIONS.nstimCon, 1);
    data(end+1) = currentByte;
end
data = char(data);
%disp(char(data));
stimulating = str2num(data);