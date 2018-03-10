paramlist = genparamlist([0 1],[0:45:330],[.1 .2 .4 .8],[2 4 8 16],[.25 .5 1],2,4,4);
paramlist = onegratingnull(paramlist);                  % add the null condition
(8)*length(paramlist)/(60*60)
