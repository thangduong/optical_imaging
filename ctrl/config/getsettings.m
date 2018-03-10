function settings = getsettings;

settings.ncapIP = '192.168.2.165:22';
settings.nstimIP = '192.168.2.2:21';
settings.smsyncIP = '127.0.0.1:19';

%settings.ncapIP = '';%'192.168.0.165:22';
%settings.nstimIP = '127.0.0.1:21';
%settings.smsyncIP = '';%'127.0.0.1:22';
settings.ncap_data = 'i:\';
settings.nstim_data = 's:\';
settings.smsync_data = 'c:\temp';
settings.server_data = 's:\';   % this is where data gets backed up
settings.cache_dir = 'c:\temp';