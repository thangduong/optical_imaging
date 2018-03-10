function result = processcsf(filename);

result = csfload(filename, [], [], [], 1);

f = result.frames(:,:,2:end-1);
for i=2:size(f,3), f(:,:,i) = (f(:,:,i)-f(:,:,1))./f(:,:,1); end;
result.frames = f(:,:,2:end);