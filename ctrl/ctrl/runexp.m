% RUNEXP    Runs an optical imaging experiment
%
%   RUNEXP(PROTOCOL, NREPS, PARAMS) runs experiment of protocol specified by
%   PROTOCOL for NREPS times.
%
% EXAMPLE
%   runexp('mseq', 5);
%
function runexp(protocol, nreps, varargin);

global EXPERIMENT;
global IMAGING;
global SETTINGS;
global CONNECTIONS;
global NSTIM;
global currentFilename;
global initFilename;
save([SETTINGS.cache_dir filesep currentFilename]);
if (EXPERIMENT.running)
    disp('there is an experiment running.  please see EXPERIMENT global and do something about it!');
    return;
end;
EXPERIMENT.running = 1;
prepexp;
if (~exist('nreps') | (length(nreps)==0))
    nreps = 1;
end

clear paradigm;
% set up image capturing stuff
sendcapline(['datadir ' EXPERIMENT.currentExp]);
expFilePath = [EXPERIMENT.currentExpDir filesep EXPERIMENT.currentExp];
smsyncgo;
smsyncstop;
pause(.5);
for rep = 1:nreps
	sendstimline('reset');
    sendcapline('stopstream');
    sendcapline(['streamlpt ' EXPERIMENT.currentExp '.' num2str(rep)]);
    smsyncstart([EXPERIMENT.currentExp filesep EXPERIMENT.currentExp '.' num2str(rep)]);
    
	[cparadigm] = feval(['oip_' protocol], varargin{:});
    cparadigm.startTime = datestr(now);
    cparadigm.smsyncFilename = [EXPERIMENT.currentExp '.' num2str(rep)];
    paradigm{rep} = cparadigm;
	
	% save stimulation file
	stimFilename = [expFilePath '.stim'];
	fd = fopen(stimFilename, 'wb');
	for i=1:length(cparadigm.lines)
        fprintf(fd, '%s\r\n', cparadigm.lines{i});
        sendstimline(cparadigm.lines{i});
	end
	fclose(fd);
	
	% save all the structures
	save([expFilePath '.desc'], 'EXPERIMENT', 'IMAGING', 'paradigm', 'cparadigm', 'rep', 'SETTINGS', 'NSTIM', 'varargin');
	
    % send additional commands to ncap
    if (isfield(cparadigm, 'ncapCmds'))
        for i=1:length(cparadigm.ncapCmds)
            sendcapline(cparadigm.ncapCmds{i});
        end
    end
    
	% set up smsync stuff
    % TODO: write this code!
    sendsmsyncline(['cap ' cparadigm.smsyncFilename]);
	
	% stimulate, but first, wait for all the commands to be processed
    sendcapline('shutter 1');
    nstimping;
    pause(.1);
	disp(['stimulating for ' num2str(cparadigm.nframes) ' frames']);
	sendstimline(['stimulate ' num2str(cparadigm.nframes) ' ' EXPERIMENT.currentExp '.rep' num2str(rep)]);
    
    timeToWait = 1+cparadigm.nframes / NSTIM.framerate;
    disp(['it will take ' num2str(timeToWait) ' seconds to finish this rep ']);
    pause(timeToWait);
    while (nstimisstimulating)
        disp('.');
        pause(1);
    end
    paradigm{rep}.endTime = datestr(now);
    
    pause(2);
    sendcapline('stopstream');
    smsyncstop;
    sendcapline('shutter 0');
end
EXPERIMENT.exp = EXPERIMENT.exp+1;
EXPERIMENT.running = 0;
save([SETTINGS.cache_dir filesep currentFilename]);
backuprun;
%smsyncoff;