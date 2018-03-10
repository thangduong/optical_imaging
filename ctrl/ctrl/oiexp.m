% OIEXP     Set up an Optical Imaging experiment
%
%   OIEXP   Starts an optical imaging experiment.  This function reloads
%   data from an experiment in progress (an experiment is one cat) or asks
%   the user for new data to start a new experiment.  All data from 
%   intermediate stages are stored in the c:\temp directory, so make sure 
%   it exists.
%
%   NOTE: this function will create several global variables describing
%   parameters of the experiment: SETTINGS, EXPERIMENT, CONNECTIONS,
%   IMAGING.
%   ADDITIONAL NOTE: this function will clear the workspace before doing
%   its thing.  
%
% EXAMPLE
%
%   % to run a typical optical imaging experiment
%   oiexp;           % start up experiment, enter cat name, etc.
%   runexp('protocol1');
%   runexp('protocol2');
%
clear;
global SETTINGS;
global EXPERIMENT;
global CONNECTIONS;
global IMAGING;
global NSTIM;
global NCAP;
global currentFilename;
global initFilename;

initFilename = ['init.mat'];
currentFilename = ['current.mat'];
SETTINGS = getsettings;

continueExp = 0;

if (exist([SETTINGS.cache_dir filesep currentFilename], 'file'))
    yesno = lower(input('Experiment in progress.  Continue? [y/n] ', 's'));
    while (~(strcmpi(yesno, 'y') | strcmpi(yesno, 'n')))
        yesno = lower(input('Experiment in progress.  Continue? [y/n] ', 's'));    
    end
    if (strcmpi(yesno, 'y'))
        load([SETTINGS.cache_dir filesep currentFilename]);
        if (EXPERIMENT.running)
            disp('an experiment was running before it got interrupted');
        end
        continueExp = 1;
        CONNECTIONS.nstimCon = 0;
        CONNECTIONS.ncapCon = 0;
        CONNECTIONS.smsyncCon = 0;
    end
end

if (continueExp == 0)
	EXPERIMENT.catName = input('What is the cat name? ', 's');
    EXPERIMENT.catWeight = input('What is the cat weight? ', 's');
    EXPERIMENT.catSex = input('What is the cat sex? ', 's');
	EXPERIMENT.startTime = fix(clock);
	EXPERIMENT.initFilename = initFilename;
	EXPERIMENT.currentFilename = currentFilename;
    EXPERIMENT.group = 1;
    EXPERIMENT.exp = 1;
    EXPERIMENT.running = 0;
    EXPERIMENT.currentExp = '';
	save([SETTINGS.cache_dir filesep initFilename]);
	save([SETTINGS.cache_dir filesep currentFilename]);
end

disp(['NSTIM location: ' SETTINGS.nstimIP]);
disp(['NCAP location: ' SETTINGS.ncapIP]);

connectall;

IMAGING.sumLength = 16;