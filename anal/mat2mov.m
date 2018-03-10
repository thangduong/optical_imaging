function m = mat2mov(mat);
%mat = a;

for i=1:255
    cm255(i,:) = [i i i]/255;
end
for i=1:size(mat,3)
    im = squeeze(mat(:,:,i));
    im = round(im*254)+1;
    m(i) = im2frame(im, cm255);
end