% SMSYNCSTART   Starts SMSYNC
%
%
function smstart(filename);

global CONNECTIONS;
if (isfield(CONNECTIONS, 'smsyncCon'))
    sendsmsyncline(['go']);
else
    disp('no connection to smsync');
end
