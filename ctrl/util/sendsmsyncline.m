function sendstimline(line)

global CONNECTIONS;
if (isfield(CONNECTIONS, 'smsyncCon'))
    sockwrite(CONNECTIONS.smsyncCon, uint8(sprintf('\r\n%s\r\n', line)));
end