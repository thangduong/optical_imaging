function M = estAffineIter2(im1,im2,numIters,M)
%
% function M = estAffineIter2(im1,im2,numIters,Minitial)
%
% Each iteration warps the images according to the previous
% estimate, and estimates the residual motion.

% Incrementally estimate the correct transform
for iter=1:numIters
   imWarp2=warpAffine2(im2,M);
   deltaM=estAffine2(im1,imWarp2);
   M=deltaM*M;
   
   %img(abs(im1-warpaffine2(im2, M)));
   
end

return;