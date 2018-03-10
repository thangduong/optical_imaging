function sendcapline(line)

global CONNECTIONS;
if (~isfield(CONNECTIONS, 'ncapCon') | (length(CONNECTIONS.ncapCon)==0))
    disp('sendcapline WARNING:  connection not established yet');
else
    sockwrite(CONNECTIONS.ncapCon, uint8(sprintf('\r\n%s\r\n', line)));
end