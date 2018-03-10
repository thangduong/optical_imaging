function resimg = dumbnotchmovie(inmov, startfreq, stopfreq);

[R,C,t] = size(inmov);
for r=1:R
    for c=1:C
        resimg(r,c,:) = dumbnotch(squeeze(inmov(r,c,:)),startfreq,stopfreq);
    end
    disp(['at row ' num2str(r)]);
end