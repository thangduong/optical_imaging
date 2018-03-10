initwinsock;

global CONNECTIONS;

if ((~isfield(CONNECTIONS, 'nstimCon')) | ((CONNECTIONS.nstimCon ==0) | (CONNECTIONS.nstimCon == (2^32-1))))
	fprintf(1, 'connecting to nstim (%s)...', SETTINGS.nstimIP);
    if (isfield(SETTINGS, 'nstimIP') & (length(SETTINGS.nstimIP)>0))
		CONNECTIONS.nstimCon = sockconnect(SETTINGS.nstimIP);
		if (CONNECTIONS.nstimCon==(2^32-1))
		disp('FAILED');
		else
		disp('SUCCESSFUL');
		nstiminit;
		end
    else
        disp('IP is not valid?');
    end
end

if ((~isfield(CONNECTIONS, 'ncapCon')) | ((CONNECTIONS.ncapCon ==0) | (CONNECTIONS.ncapCon == (2^32-1))))
	fprintf(1, 'connecting to ncap (%s)...', SETTINGS.ncapIP);
    if (isfield(SETTINGS, 'ncapIP') & (length(SETTINGS.ncapIP)>0))
		CONNECTIONS.ncapCon = sockconnect(SETTINGS.ncapIP);
		if (CONNECTIONS.ncapCon==(2^32-1))
            disp('FAILED');
		else
            disp('SUCCESSFUL');
		end
    else
        disp('IP is not valid?');
    end
end


if ((~isfield(CONNECTIONS, 'smsyncCon')) | ((CONNECTIONS.smsyncCon ==0) | (CONNECTIONS.smsyncCon == (2^32-1))))
	fprintf(1, 'connecting to smsync (%s)...', SETTINGS.smsyncIP);
    if (isfield(SETTINGS, 'smsyncIP') & (length(SETTINGS.smsyncIP)>0))
		CONNECTIONS.smsyncCon = sockconnect(SETTINGS.smsyncIP);
		if (CONNECTIONS.smsyncCon==(2^32-1))
            disp('FAILED');
		else
            disp('SUCCESSFUL');
		end
    else
        disp('IP is not valid?');
    end
end