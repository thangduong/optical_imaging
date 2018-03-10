a = ordata{1};
a = normalize(clip(a,2));
figure(1);
i0=30; 
for i=i0:2:90, 
    subplot(8,8,i-i0+1); 
    showimg(a(:,:,i)*64); 
    axis off; 
    title(time(i));
end;

figure(2);
subplot(2,3,1);
showimg(normalize(clip(ordata{1}(:,:,55),1))*64);
subplot(2,3,2);
showimg(normalize(clip(ordata{2}(:,:,55),1))*64);
subplot(2,3,3);
showimg(normalize(clip(ordata{3}(:,:,55),1))*64);
subplot(2,3,4);
showimg(ordata{3}(:,:,50));
x = 187;
y = 102;
plot(time,squeeze(ordata{1}(x,y,:)),...
    time,squeeze(ordata{2}(x,y,:)),...
    time,squeeze(ordata{3}(x,y,:)));
subplot(2,3,5);
x = 140;
y = 57;
plot(time,squeeze(ordata{1}(x,y,:)),...
    time,squeeze(ordata{2}(x,y,:)),...
    time,squeeze(ordata{3}(x,y,:)));
subplot(2,3,6);
x = 121;
y = 226;
plot(time,squeeze(ordata{1}(x,y,:)),...
    time,squeeze(ordata{2}(x,y,:)),...
    time,squeeze(ordata{3}(x,y,:)));

oldA = a;
a = normalize(a)*255;
for i=1:size(a,3)
    A = squeeze(a(:,:,i));
    txt = num2str(time(i));
    A = drawtext(A, [0 230], txt(1:5));
    M = max(max(squeeze(A)));
    A = fliplr(flipud(squeeze(A')));
	CCDDiam = 4.1;      % in mm
	Mag = 0.9;     % 50mm image and 55 mm objective
	mm = round(256/(CCDDiam/Mag));
	A(8:10,5:(5+mm))=M;
    a(:,:,i) = A;
end
m = mat2mov(a/255);
mov2avi(m,'rb381x0302.c0.avi',5);