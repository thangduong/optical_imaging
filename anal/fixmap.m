function mo = fixmap(mi, N)

if (~exist('N'))
    N=1;
end
[r c] = size(mi);

for i=(1+N):(r-N)
    for j=(1+N):(c-N)
        q = mi((i-N):(i+N),(j-N):(j+N));
        q = reshape(q, prod(size(q)),1);
        mo(i-N,j-N)=median(q);
    end
end