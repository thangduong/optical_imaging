% CLIP  Clips the data to increase contrast around a fixed range
%
%   RESULT = CLIP(DATA, NUMSTD)
function result = clip(d, nstd);

drs = reshape(d,1,prod(size(d)));
m = mean(drs);
s = std(drs);
LT = m -nstd*s;
HT = m +nstd*s;
d(find(d<LT))=LT;
d(find(d>HT))=HT;
result = d;