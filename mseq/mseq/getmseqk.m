% GETMSEQK  Get cross correlation between two m-sequence seeds
%
%   K = GETMSEQK(ORDER, SEED1, SEED2) returns the cross correlation
%   function of the two sequences generated by SEED1 and SEED2.  This is
%   done by doing a fast m-transform with SEED2 on the sequence generated
%   by SEED1.
%
% See also GENMSEQ, FASTM.
%
function k = getmseqk(order, seed1, seed2)

seq1 = [int32(0) genmseq(order, seed1, 2)];
k = fastm(order, seed2, seq1);