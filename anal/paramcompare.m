% PARAMCOMPARE     Compares 2 structures and return 0 for equal, 1 for not equal
%
%   EQUAL = PARAMCOMPARE(S1, S2) 
%
function equal = paramcompare(s1, s2)

fn = fieldnames(s1);
fn2 = fieldnames(s2);
equal = 0;
if (length(fn) == length(fn2)) 
    equal = 1;
	for i=1:length(fn)
        if (strcmp(fn{i},fn2{i}))
            if (strcmpi(fn{i},'randomJit')==0)
                if (getfield(s1,fn{i})==getfield(s2,fn{i}))
                else
                    equal = 0;
                    break;
                end
            end
        else
            equal = 0;
            break;
        end
	end
end