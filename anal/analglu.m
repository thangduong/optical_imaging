clear;
close all;
cat = 'rb089';
exp = 'rb089x0317';
nrep = 5;
file = ['e:\' cat '\' exp '\' exp '.' num2str(1) '.0000.csf'];
a = csfload(file,[],[],[1:2:484],1);
    c = a.frames;
    c2 = zeros(size(c));
for x=1:256
    for y=1:256
        t = squeeze(c(x,y,:));
        f = fftshift(fft(t));
        f(96:101)=0; f(141:146)=0;
        s = real(ifft(fftshift(f)));
        c2(x,y,:)=s;
    end
    disp(sprintf('%d done', x));
end
a.frames = c2;
for i=2:nrep
    file = ['e:\' cat '\' exp '\'  exp '.' num2str(i) '.0000.csf'];
    b = csfload(file,[],[],[1:2:484],1);
    c = b.frames;
for x=1:256
    for y=1:256
        t = squeeze(c(x,y,:));
        f = fftshift(fft(t));
        f(96:101)=0; f(141:146)=0;
        s = real(ifft(fftshift(f)));
        c2(x,y,:)=s;
    end
    disp(sprintf('%d done', x));
end
    a.frames = a.frames+c2;
    
end
c = processcsfdata(a.frames);
%c = normalize(clip(c,1));
%for i=1:size(c,3), showimg(normalize(c(59:200,50:200,i))); colormap(gray); drawnow;title(num2str((i/(108/32))-10)); pause(.1); end;
%for i=1:size(c,3), showimg(c(:,:,i)); colormap(gray); drawnow;title(num2str((i/(108/32))-10)); pause(.1); end;

