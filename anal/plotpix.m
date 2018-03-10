function h=plotpix(d,y,x);

figure; 
frate = 6.8029;
pretime = 4.89;
t = ((1:size(d{1},3))/(frate)) - pretime; % assume 5 second precap
[a,b]=min(abs(t-5))
color = ['r','g','b','c','m','y','k'];

for i=1:length(d)
    hold on;
    h{i} = plot(t,squeeze(d{i}(x,y,:)),color(mod(i-1,length(color))+1));
end
title(num2str([x,y]));

xlabel('time (s)');
ylabel('dL/L');
