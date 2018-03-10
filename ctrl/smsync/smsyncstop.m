% SMSYNCSTOP    Stops SMSYNC
%
%
function smsyncstop(filename);

global CONNECTIONS;
if (isfield(CONNECTIONS, 'smsyncCon'))
    sendsmsyncline(['stopcap']);
else
    disp('no connection to smsync');
end
