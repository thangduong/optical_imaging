function sendstimline(line)

global CONNECTIONS;
sockwrite(CONNECTIONS.nstimCon, uint8(sprintf('\r\n%s\r\n', line)));