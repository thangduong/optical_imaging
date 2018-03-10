% GENPARAMLIST  Generates a list of parameters for use with "runexpvrep"
%
%      GENPARAMLIST([param1list],[param2list],[param3list],...)
%
%
%		paramlist = genparamlist([2],[0 90 180 270],.1,2,1,2,2,2,5);
%		paramlist = onegratingnull(paramlist);                  % add the null condition
%		runexpvrep('onegrating', 5, paramlist);%
%
function paramlist = genparamlist(varargin);
idx = ones(1,length(varargin));
num = 1;
for i=1:length(varargin)
    if (length(varargin{i})>0)
        num = num * length(varargin{i});
    end
end
for i=1:num
    for p=1:length(varargin)
        if (length(varargin{p})>0)
            paramlist{i}{p} = varargin{p}(idx(p));
        else
            paramlist{i}{p} = [];
        end
    end
    for j = length(idx):-1:1;
        idx(j) = idx(j)+1;
        if (idx(j)<= length(varargin{j}))
            break;
        else
            idx(j) = 1;
        end
    end
end

