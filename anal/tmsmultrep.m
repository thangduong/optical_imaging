% this is red, 4sec stimulation
 datafiles = {...
            'E:\rb098\rb098x0113\rb098x0113.1.0000.csf', 'E:\rb098\rb098x0113\rb098x0113.2.0000.csf',...
             'E:\rb098\rb098x0112\rb098x0112.4.0000.csf','E:\rb098\rb098x0112\rb098x0112.3.0000.csf',...
             'E:\rb098\rb098x0112\rb098x0112.2.0000.csf','E:\rb098\rb098x0112\rb098x0112.1.0000.csf',...
             'E:\rb098\rb098x0111\rb098x0111.1.0000.csf','E:\rb098\rb098x0111\rb098x0111.2.0000.csf',...
             'E:\rb098\rb098x0111\rb098x0111.3.0000.csf','E:\rb098\rb098x0111\rb098x0111.4.0000.csf'
     };
% datafiles = {...
%      'E:\rb098\rb098x0115\rb098x0115.1.0000.csf','E:\rb098\rb098x0115\rb098x0115.2.0000.csf',...
%  };
%4Hz,4s
% datafiles = {...
%  'E:\rb097\rb097x0110\rb097x0110.1.0000.csf',...
%  'E:\rb097\rb097x0110\rb097x0110.2.0000.csf',...
%  'E:\rb097\rb097x0110\rb097x0110.3.0000.csf',...
%  'E:\rb097\rb097x0110\rb097x0110.4.0000.csf',...
%  'E:\rb097\rb097x0110\rb097x0110.5.0000.csf',...
%  'E:\rb097\rb097x0110\rb097x0110.6.0000.csf',...
% };

%8Hz,4s
%  datafiles = {...
%   'E:\rb097\rb097x0111\rb097x0111.1.0000.csf',...
%   'E:\rb097\rb097x0111\rb097x0111.2.0000.csf',...
%   'E:\rb097\rb097x0111\rb097x0111.3.0000.csf',...
% };

% green -- cool data
%  datafiles = {...
%   'E:\rb097\rb097x0113\rb097x0113.1.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.2.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.3.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.4.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.5.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.6.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.7.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.8.0000.csf',...
%   'E:\rb097\rb097x0113\rb097x0113.9.0000.csf',...
% };
%  datafiles = {...
%   'E:\rb097\rb097x0114\rb097x0114.1.0000.csf',...
%   'E:\rb097\rb097x0114\rb097x0114.2.0000.csf',...
%   'E:\rb097\rb097x0114\rb097x0114.3.0000.csf',...
%   'E:\rb097\rb097x0114\rb097x0114.4.0000.csf',...
%   'E:\rb097\rb097x0114\rb097x0114.5.0000.csf',...
%   'E:\rb097\rb097x0114\rb097x0114.6.0000.csf',...
% %  'E:\rb097\rb097x0114\rb097x0114.7.0000.csf',...      tms overheated
% };
 datafiles = {...
  'E:\rb097\rb097x0115\rb097x0115.1.0000.csf',...
}
tms_plot_single_rep = 0;   
if (~exist('repData'))
    repData = [];
end
for i=(length(repData)+1):length(datafiles)
    datafile = datafiles{i};
    tmssinglerep;
    repData{i} = -squeeze(mean(mean(b,1),2));
    repImgData{i} = b;
    clear a; 
    clear b;
end
for i=1:length(repData)
    if (i==1)
        result = repData{i};
%        imgResult = repImgData{i};
    else
        result = result + repData{i};
%        imgResult = imgResult + repImgData{i};
    end
end
result = result / length(repData);
%imgResult = imgResult / length(repData);
subplot(2,1,1);
c = ['r','g','b','c','m','y','k'];
for i=1:length(repData)
%    subplot(length(repData)+1,1,i);
    plot(t,repData{i},c(mod(i,length(c))+1));
    axis tight;
    hold on;
end
%subplot(length(repData)+1,1,length(repData)+1);
subplot(2,1,2);
plot(t,result);
axis tight;