% STRUCTCOMPARE     Compares 2 structures and return 0 for equal, 1 for not equal
%
%   EQUAL = STRUCTCOMPARE(S1, S2) 
%
function equal = structcompare(s1, s2)

fn = fieldnames(s1);
fn2 = fieldnames(s2);
equal = 0;
if (length(fn) == length(fn2)) 
    equal = 1;
	for i=1:length(fn)
        if (strcmp(fn{i},fn2{i}))
            if (getfield(s1,fn{1})==getfield(s2,fn{1}))
            else
                equal = 0;
                break;
            end
        else
            equal = 0;
            break;
        end
	end
end