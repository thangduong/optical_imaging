mseq = a.frames(:,:,25:303);
% hacks analysis of bms
[w,h,t] = size(mseq);

order = 6;
seed = 33;
k = ceil(size(mseq,3)/(2^order - 1));
for x=1:w,
    for y=1:h
        data = squeeze(mseq(x,y,:));
        xi = linspace(0,1,length(data));
        xo = linspace(0,1,(2^order - 1)*k);
        datao = interp1(xi,data,xo);
        [fm,ffm] = fixfastm(order, fastm(order, seed, [zeros(1,k) datao]));
        out(x,y,:) = ffm;
    end
    disp(num2str(x));
end