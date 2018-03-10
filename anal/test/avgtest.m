dirName = 'C:\data\qt383x0131\imaging_data\';
dataFiles = dir([dirName '*.csf']);

a = csfload([dirName dataFiles(1).name],[],[],[1 200],1);
img = a.frames;
for i=2:length(dataFiles)
    fn = [dirName dataFiles(i).name];
    a = csfload(fn,[],[],[1 200],1);
    img = img + a.frames;
end

img = img(:,:,2:end-1);
for i=2:size(img,3), img(:,:,i) = img(:,:,i)-img(:,:,1); end;
img = img(:,:,2:end);
img = normalize(img);
for i=1:size(img,3), image(img(:,:,i)*64); title(num2str(i/6.75-5)); pause(.1); end;
%for i=1:231, imagesc(img(:,:,i)-img(:,:,2)); colormap(bone); title(num2str(i/6.75)); pause(.1); end;
return

img2 = img(50:100,50:100,:);
img2 = normalize(img2);
for i=1:size(img2,3), image(img2(:,:,i)*64); title(num2str(i/6.75-5)); pause(.1); end;
