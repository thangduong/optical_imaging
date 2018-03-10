datadir = 'i:\';
exp = 'calib08152006x0101';

datadir = [datadir exp '\'];

x = 128;
y = 200;
t = 2:10;
for i=1:256,
    filename = sprintf('%s%s.%d.%04d.csf', datadir,exp,1, i-1);
    a = csfload(filename, [], [], [], 1);
    figure(1);
    subplot(4,5,mod(i,20)+1);
    image(squeeze(a.frames(:,:,10)*64/65536));
%    r = squeeze(a.frames(100:end,:,10));
 %   cv = mean(reshape(r, 1,prod(size(r))));
 %   disp(num2str(cv));
 %   acv(i) = cv;
    r = squeeze(a.frames(x,y,t));
    acv(i) = mean(reshape(r,1,prod(size(r))));
    drawnow;
%    pause(.1);
end

acv = sort(acv);
acv = normalize(acv);

% now generate the lookup table
line = linspace(0,1,256);
for i=1:length(line)
    tableValue(i) = round(analcalib_findpt_between(acv,line(i))*65535/255);
    tableValueIdx(i) = round(analcalib_findpt_between(acv,line(i))) + 1;
end

tableValueI = uint16(tableValue);
f = fopen(['c:\' exp '.lut'], 'wb');
fwrite(f,tableValueI,'uint16');
fwrite(f,tableValueI,'uint16');
fwrite(f,tableValueI,'uint16');
fclose(f);

f = fopen(['c:\' exp '.lut'], 'rb');
resultValue = fread(f,'uint16');
fclose(f);