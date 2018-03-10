% NSTIMINIT     Gets initializes the global variable NSTIM
%
%   NSTIMINIT   this function basically loads parameters (framerate,xres,yres,etc.)
%   from nstim computer and saves to to the global NSTIM variable.
%
function nstiminit;

global NSTIM;

NSTIM.mode = nstimgetmode;
NSTIM.framerate = nstimgetframerate;
NSTIM.cfg = stimcfg;

disp(['INITNSTIM']);
disp(['NSTIM: width = ' num2str(NSTIM.mode.width)]);
disp(['NSTIM: height = ' num2str(NSTIM.mode.height)]);
disp(['NSTIM: framerate = ' num2str(NSTIM.framerate)]);