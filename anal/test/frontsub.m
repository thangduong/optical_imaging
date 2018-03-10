function f = frontsub(img);

f = img;
for i=2:size(f,3), f(:,:,i) = (f(:,:,i)-f(:,:,1))./f(:,:,1); end;
f = f(:,:,2:end);