if (~exist('tms_plot_single_rep'))
    tms_plot_single_rep = 1;
end
nskip = 3;
nmax = (108/16)*(15+200);
%roix = 115:146;%88:232;  % the red area
%roiy = 108:136;%76:255;
roix = 88:232; % the whole brain
roiy = 76:255;
%roix = 123:199;  % the blue area
%roiy = 183:238;
a = csfload(datafile,roix,roiy,[1:nskip:nmax],1);
b = processcsfdata(a.frames, 15*5);
%plot(squeeze(sum(sum(b,1),2)));
t = 1:size(b,3);
t = nskip*t/(108/16);
t = t - 15;
if (tms_plot_single_rep)
    plot(t,-squeeze(mean(mean(b,1),2)));
end