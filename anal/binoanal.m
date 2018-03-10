for i=1:length(bphasedata)
    disp(['analyzing ' num2str(i)]);
    bphasedata{i} = frontsub(bphasedata{i}(:,:,2:end-1));
end
d1 = normalize(bphasedata{1})-normalize(bphasedata{2});
d2 = normalize(bphasedata{1})-normalize(bphasedata{3});
d3 = normalize(bphasedata{1})-normalize(bphasedata{4});