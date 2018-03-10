% NCAPSNAP  snaps an image from ncap
%   [img,filename] = NCAPSNAP(FILENAME)
%
function [img,filename] = ncapsnap(filename);
global SETTINGS;
global EXPERIMENT;
if (~exist('filename') | (length(filename)==0))
    filename = sprintf('%sx%02d%02d', EXPERIMENT.catName, EXPERIMENT.group, EXPERIMENT.exp);
end
sendcapline(['snap ' filename]);
imgFile = [SETTINGS.ncap_data filesep 'images' filesep filename '.img'];
disp(imgFile);
pause(.1);
img = showimg(imgFile);

%img = loadimg(imgFile);
%M = max(max(img.image));
%img.image(5:(5+64),250:252)=M;
%figure; correctIm = fliplr(flipud(img.image'));
%correctIm(8:10,5:(5+64))=M;
%imagesc(correctIm); colormap(gray);
%title(imgFile);
%axis equal; axis off;