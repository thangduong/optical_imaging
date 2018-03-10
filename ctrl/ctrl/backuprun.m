% BACKUPRUN Copies data in current run to the server
%
function backuprun;

global EXPERIMENT;
global IMAGING;
global SETTINGS;
global CONNECTIONS;
global NSTIM;

fprintf(1,'moving configuration data to server...');
expFilePath = [EXPERIMENT.currentExpDir];
disp(SETTINGS.server_data);
serverFolder = [SETTINGS.server_data filesep EXPERIMENT.currentExp];
mkdir(SETTINGS.server_data, EXPERIMENT.currentExp);
disp(['moving from ' expFilePath ' to ' serverFolder]);
%movefile(expFilePath, serverFolder,'f');

% copy imaging data over
fprintf(1,'moving imaging data to server...');
mkdir([SETTINGS.server_data filesep EXPERIMENT.currentExp], 'imaging_data');
movefile([SETTINGS.ncap_data filesep EXPERIMENT.currentExp filesep '*.*'], [serverFolder filesep 'imaging_data'],'f');
disp('done!');

% TODO: copy sync data from smsync over!
fprintf(1,'moving smsync...');
movefile([SETTINGS.smsync_data filesep EXPERIMENT.currentExp '.*.sync'], serverFolder,'f');
disp('done!');

% TODO: copy stimulation sync over
fprintf(1, 'moving stimulation sync data to server...');
disp('NOTE: do this after experiment! NEVIS computer is not shared!');

