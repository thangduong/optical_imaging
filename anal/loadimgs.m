function res = loadimgs(a,b);

for i=a:b
    f = sprintf('%04d.img', i-a+1);
    v = loadimg(f);
    res(:,:,i-a+1)=v.image;
end