% cocktail correction
ordata = ordata2;
%for i=1:length(ordata)
%    ordata{i} = ordata{i}(50:200,:,2:end-1);
%end
cocktail = ordata{1}+ordata{2}+ordata{3}+ordata{4}+ordata{5}+ordata{6}+ordata{7}+ordata{8};
cocktail = cocktail/8;
for i=1:length(ordata), ordata{i} = (ordata{i}-cocktail)./(cocktail+1); end;

for i=1:length(ordata)
b{i} = ordata{i};
%b{i} = b{i}(:,:,2:end-1);
b{i} = clip(sum(b{i}(:,:,(end-5):end),3),1);
end

for i=1:8, 
    subplot(2,4,i); 
    showimg(b{i}); 
    colormap(gray); 
    title(num2str(or(i))); 
    v{i} = normalize(b{i});
end;

for i=1:size(v{1},1)
    for j=1:size(v{1},2)
        vl = [];
        for o=1:8
            vl = [vl v{o}(i,j)];
        end
        [val idx] = min([vl]);
        mymap(i,j) = or(idx);
    end
end