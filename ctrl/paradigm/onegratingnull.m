function result = onegratingnull(inparam);

result = inparam;
result{end+1} = inparam{end};
result{end}{5} = 0;