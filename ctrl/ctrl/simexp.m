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
prepexp;

if (~exist('nreps') || (length(nreps)==0))
    nreps = 1;
end

clear paradigm;
% set up image capturing stuff
sendcapline(['datadir ' EXPERIMENT.currentExp]);
expFilePath = [EXPERIMENT.currentExpDir filesep EXPERIMENT.currentExp];
for rep = 1:nreps
    sendcapline(['streamlpt ' EXPERIMENT.currentExp '.' num2str(rep)]);
    
	[cparadigm] = feval(['oip_' protocol], varargin{:});
    cparadigm.startTime = datestr(now);
    paradigm{rep} = cparadigm;

	
	% save stimulation file
	stimFilename = [expFilePath '.stim'];
	fd = fopen(stimFilename, 'wb');
	sendstimline('reset');                  % reset old stimulation
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
	
	% stimulate, but first, wait for all the commands to be processed
    nstimping;
	disp(['simulating for ' num2str(cparadigm.nframes) ' frames']);
	sendstimline(['simulate ' num2str(cparadigm.nframes) ' ' EXPERIMENT.currentExp '.rep' num2str(rep)]);
    
    timeToWait = 1+cparadigm.nframes / NSTIM.framerate;
    disp(['it will take ' num2str(timeToWait) ' seconds to finish this rep ']);
    pause(timeToWait);
    while (nstimisstimulating)
        disp('.');
        pause(1);
    end
    paradigm{rep}.endTime = datestr(now);
    
    sendcapline('stopstream');
end
backuprun;
EXPERIMENT.exp = EXPERIMENT.exp+1;