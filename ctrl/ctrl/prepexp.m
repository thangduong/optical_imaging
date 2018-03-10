%warning off MATLAB:MKDIR:DirectoryExists

EXPERIMENT.currentExp = sprintf('%sx%02d%02d', EXPERIMENT.catName, EXPERIMENT.group, EXPERIMENT.exp);
disp(['preparing to run an experiment ' EXPERIMENT.currentExp]);
EXPERIMENT.currentExpDir = [SETTINGS.cache_dir filesep EXPERIMENT.currentExp];
[a,b] = mkdir(SETTINGS.cache_dir,EXPERIMENT.currentExp);