function stat = nstimping(time);

global CONNECTIONS;
if ((~exist('time')) | (length(time) == 0))
    time = 30*60;
end

nstimflush;

sendstimline('ping');
fprintf(1,'PING:');

while ((double(sockpendingdata(CONNECTIONS.nstimCon)) == 0) & (time > 0))
    pause(.5);
    time = time - 1;
    fprintf(1,'.');
end

if (double(sockpendingdata(CONNECTIONS.nstimCon)) == 5)
	data = [];
	currentByte = 1;
	while (currentByte ~= 0)
        currentByte = sockread(CONNECTIONS.nstimCon, 1);
        data(end+1) = currentByte;
	end
	data = data(1:(end-1));
	
	
	disp([data '!']);
else
    stat = 0;
end