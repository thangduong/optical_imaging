function [mode, data] = nstimgetframerate;

global CONNECTIONS;

nstimflush;

sendstimline('dispmode');

data = [];
currentByte = 1;
while (currentByte ~= 0)
    currentByte = sockread(CONNECTIONS.nstimCon, 1);
    data(end+1) = currentByte;
end
data = char(data);
[t,r] = strtok(data, ',');
mode.width = str2num(t);
[t,r] = strtok(r(2:end), ',');
mode.height = str2num(t);
[t,r] = strtok(r(2:end), ',');
mode.framerate = str2num(t);
[t,r] = strtok(r(2:end), ',');
mode.format = str2num(t);
