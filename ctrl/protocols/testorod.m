paramlist = genparamlist([0 1],[0 90],.1,[2],1,5,15,2);
paramlist = onegratingnull(paramlist);                  % add the null condition
(5+5+15+2)*length(paramlist)/(60)
