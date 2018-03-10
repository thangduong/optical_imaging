function mo = dumbfilter(mi, N)

if (~exist('N'))
    N=1;
end
[r c] = size(mi);

if (N==1)
    A = [1 1 1;1 2 1; 1 1 1]; 
    mask = A/sum(sum(A));
else
    if (N==2)
        A = [1 1 1 1 1;1 2 2 2 1; 1 2 4 2 1; 1 2 2 2 1; 1 1 1 1 1]; 
        mask = A/sum(sum(A));
    else
        if (N==3)
            A = [1 1 1 1 1 1 1;1 2 2 2 2 2 1; 1 2 4 4 4 2 1; 1 2 4 16 4 2 1; 1 2 4 4 4 2 1; 1 2 2 2 2 2 1; 1 1 1 1 1 1 1]; 
            mask = A/sum(sum(A));
        end
    end
end

for i=(1+N):(r-N)
    for j=(1+N):(c-N)
        if (N<3)
            q = mi((i-N):(i+N),(j-N):(j+N)) .* mask;
        else
            q = mi((i-N):(i+N),(j-N):(j+N));
        end
        q = reshape(q, prod(size(q)),1);
        mo(i-N,j-N)=mean(q);
    end
end