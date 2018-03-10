% SMSYNCSTART   Starts SMSYNC
%
%
function smsyncoff(filename);

global CONNECTIONS;
if (isfield(CONNECTIONS, 'smsyncCon'))
    sendsmsyncline(['stop']);
else
    disp('no connection to smsync');
end
