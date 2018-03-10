% SOCKCONNECT	Connects to a host using WinSock
%
%	SOCKET = SOCKCONNECT(HOST) connects to HOST where HOST is a string
%   of the form <ADDRESS>:<PORT> and <ADDRESS> is either the host name or
%   the host IP.  <PORT> of course is the port number.  The connection made
%   is via TCP/IP, and the resulting socket is returned as SOCKET.
%   SOCKET is 0xFFFFFFFF if there's an error.  SOCKET is just a 32-bit unsigned
%   integer.
%
%
% Example:
%   initwinsock;
%   sock = sockconnect('neurovision.berkeley.edu:80');
%
% See also INITWINSOCK.