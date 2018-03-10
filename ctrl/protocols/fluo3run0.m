% first version of bphase is just 2 phases
paramlist = genparamlist([3],[0 90 180 270],.1,2,1,2,2,2,5);
paramlist = onegratingnull(paramlist);                  % add the null condition
35*length(paramlist)/(60*60)
