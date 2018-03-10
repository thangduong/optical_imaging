function f = processcsfdata(result, N);

if (~exist('N'))
    N = 5;
end
f = result(:,:,2:end-1);%result.frames(:,:,2:end-1);
fbaseline = mean(f(:,:,1:N),3);

%for i=1:size(f,3), f(:,:,i) = fliplr(flipud(squeeze((f(:,:,i)-fbaseline)./fbaseline)')); end;
for i=1:size(f,3), f(:,:,i) = squeeze((f(:,:,i)-fbaseline)./fbaseline); end;
%result.frames = f(:,:,2:end);

