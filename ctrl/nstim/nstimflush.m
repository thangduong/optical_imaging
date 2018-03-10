function sendstimline

global CONNECTIONS;
nbytes = sockpendingdata(CONNECTIONS.nstimCon);
if (nbytes > 0)
    CONNECTIONS.nstimflush = sockread(CONNECTIONS.nstimCon, nbytes);
else
    CONNECTIONS.nstimflush = [];
end
