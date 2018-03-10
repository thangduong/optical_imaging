% SMSYNCSTART   Starts SMSYNC
%
%
function smstart(filename);

global CONNECTIONS;
if (isfield(CONNECTIONS, 'smsyncCon'))
    sendsmsyncline(['cap ' filename]);
else
    disp('no connection to smsync');
end
