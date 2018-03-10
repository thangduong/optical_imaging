% RUNEXP    Runs an optical imaging experiment
%
%   RUNEXP(PROTOCOL, NREPS, PARAMS) runs experiment of protocol specified by
%   PROTOCOL for NREPS times.
%
% EXAMPLE
%   runexp('mseq', 5);
%
function runexpvrep(protocol, nreps, paramlist, filtpos);

global EXPERIMENT;
global IMAGING;
global SETTINGS;
global CONNECTIONS;
global NSTIM;
global currentFilename;
global initFilename;
global paradigm;
global cparadigm;
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

paradigm={};
% set up image capturing stuff
sendcapline(['datadir ' EXPERIMENT.currentExp]);
expFilePath = [EXPERIMENT.currentExpDir filesep EXPERIMENT.currentExp];
smsyncgo;
smsyncstop;
pause(.5);

shuttervalue = 1;
for rep = 1:nreps
    repdata{rep}.perm = randperm(length(paramlist));
    sendcapline('stopstream');
    sendcapline(['streamlpt ' EXPERIMENT.currentExp '.' num2str(rep)]);
    for subrep = 1:length(repdata{rep}.perm)
        
        disp(sprintf('at rep %d condition %d', rep, subrep));
        ((paramlist{repdata{rep}.perm(subrep)}))
		sendstimline('reset');
        smsyncstart([EXPERIMENT.currentExp filesep EXPERIMENT.currentExp '.' num2str(rep) '.' num2str(subrep-1)]);

        pl = paramlist{repdata{rep}.perm(subrep)};
        if (pl{5}<0)                % THIS IS A HACK!
            pl{5} = 0;
            shuttervalue = 0;
        else
            shuttervalue = 1;
        end
%		[cparadigm] = feval(['oip_' protocol], paramlist{repdata{rep}.perm(subrep)});
		[cparadigm] = feval(['oip_' protocol], pl);

        cparadigm.startTime = datestr(now);
        cparadigm.smsyncFilename = [EXPERIMENT.currentExp '.' num2str(rep)];
        cparadigm.filterpos = filtpos(repdata{rep}.perm(subrep));
        sendcapline(['filter ' num2str(cparadigm.filterpos)]);
        sleep(.5);
        paradigm{rep}{subrep} = cparadigm;
		% save stimulation file
		stimFilename = [expFilePath '.stim'];
		fd = fopen(stimFilename, 'wb');
		for i=1:length(cparadigm.lines)
            fprintf(fd, '%s\r\n', cparadigm.lines{i});
            sendstimline(cparadigm.lines{i});
		end
		fclose(fd);
        		
		% save all the structures
		save([expFilePath '.desc'], 'EXPERIMENT', 'IMAGING', 'paradigm', 'cparadigm', 'rep', 'SETTINGS', 'NSTIM', 'paramlist', 'repdata');
		
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
        nstimping;
        
        if (shuttervalue)
            sendcapline('shutter 1');
        else
            sendcapline('shutter 0');
        end
		disp(['stimulating for ' num2str(cparadigm.nframes) ' frames']);
		sendstimline(['stimulate ' num2str(cparadigm.nframes) ' ' EXPERIMENT.currentExp '.rep' num2str(rep)]);
        
        timeToWait = 1+cparadigm.nframes / NSTIM.framerate;
        disp(['it will take ' num2str(timeToWait) ' seconds to finish this rep ']);
        pause(timeToWait);
        while (nstimisstimulating)
            disp('.');
            pause(.1);
        end
        paradigm{rep}{subrep}.endTime = datestr(now);
        
        smsyncstop;
        if (shuttervalue)
            sendcapline('shutter 0');
        end
    end
%    pause(.5);
    sendcapline('stopstream');
end

%smsyncoff;
EXPERIMENT.exp = EXPERIMENT.exp+1;
EXPERIMENT.running = 0;
save([SETTINGS.cache_dir filesep currentFilename]);
backuprun;
