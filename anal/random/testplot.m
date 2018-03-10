x = 100; y = 128;
plot(linspace(-5,15,146),squeeze(bphasedata{1}(x,y,2:end-1)));
hold on;plot(linspace(-5,15,146),squeeze(bphasedata{2}(x,y,2:end-1)),'r');
hold on;plot(linspace(-5,15,146),squeeze(bphasedata{3}(x,y,2:end-1)),'g');
hold on;plot(linspace(-5,15,146),squeeze(bphasedata{4}(x,y,2:end-1)),'k');
