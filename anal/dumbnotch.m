% DUMBNOTCH     A dumb notch filter
%
%   result = dumbnotch(x, startfreq, endfreq)
function result = dumbnotch(x, startfreq, endfreq)

SR = 108/16;
freq = linspace(-SR/2, SR/2, length(x)+1);
freq = freq(1:end-1);
zeroidx = find((abs(freq)>startfreq)&(abs(freq)<endfreq));
f = fftshift(fft(x));
fb = f;
f(zeroidx) = 0;
% subplot(2,1,1);
% plot(freq, abs(fb), freq, abs(f));
% subplot(2,1,2);
result = real(ifft(fftshift(f)));