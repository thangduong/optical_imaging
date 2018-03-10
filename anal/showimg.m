% SHOWIMG   Shows an image
function img = showimg(filename);
fns = size(filename);
if (prod(fns)~=length(filename))
    if (size(filename,3)==3)
        M = 1;
        
		correctIm(:,:,1) = fliplr(flipud(squeeze(filename(:,:,1))'));
		correctIm(:,:,2) = fliplr(flipud(squeeze(filename(:,:,2))'));
		correctIm(:,:,3) = fliplr(flipud(squeeze(filename(:,:,3))'));
        correctIm = normalize(correctIm);
		CCDDiam = 4.1;      % in mm
		Mag = 0.9;     % 50mm image and 55 mm objective
		mm = round(256/(CCDDiam/Mag));
		correctIm(8:10,5:(5+mm),1)=M;
		correctIm(8:10,5:(5+mm),2)=M;
		correctIm(8:10,5:(5+mm),3)=M;
		image(correctIm); %colormap(gray);
		%	image(correctIm*64); %colormap(gray);
		axis equal; axis off;        
		img = filename;
    else
		M = max(max(filename));
		%	figure; 
		correctIm = fliplr(flipud(filename'));
		CCDDiam = 4.1;      % in mm
		Mag = 0.9;     % 50mm image and 55 mm objective
		mm = round(256/(CCDDiam/Mag));
		correctIm(8:10,5:(5+mm))=M;
		%imagesc(correctIm); %colormap(gray);
			image(correctIm*64); %colormap(gray);
		axis equal; axis off;        
		img = filename;
    end
else
    filename
	img = loadimg(filename);
	M = max(max(img.image));
	%img.image(5:(5+64),250:252)=M;
	figure; correctIm = fliplr(flipud(img.image'));
	CCDDiam = 4.1;      % in mm
	Mag = 0.9;     % 50mm image and 55 mm objective
	mm = round(256/(CCDDiam/Mag));
	correctIm(8:10,5:(5+mm))=M;
	imagesc(correctIm); %colormap(gray);
	title(filename);
	axis equal; axis off;
end