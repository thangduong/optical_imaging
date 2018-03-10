% SOCKWRITE 	Writes data from a connected socket
%
%   SOCKWRITE(SOCKET, NUMBYTES) writes NUMBYTES bytes of data to opened socket
%   identified by SOCKET.  This function blocks and doesn't return until NUMBYTES 
%   bytes have been written.
%
% See also INITWINSOCK, SOCKCONNECT, SOCKREAD.
%