% SOCKREAD	Reads data from a connected socket
%
%   DATA = SOCKREAD(SOCKET, NUMBYTES) reads NUMBYTES bytes of data from opened socket
%   identified by SOCKET.  Return value is an array of bytes DATA.  This function blocks
%   and doesn't return until NUMBYTES bytes have been received.
%
% See also INITWINSOCK, SOCKCONNECT, SOCKWRITE.
%