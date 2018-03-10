function result = addmovie(src,dst)

result = src;
if (length(result)==0)
    result = dst;
    return;
end
if (size(result,3)<size(dst,3))
    result = result + dst(:,:,1:size(dst,3));
else
    result(:,:,1:size(dst,3)) = result(:,:,1:size(dst,3)) + dst;
end