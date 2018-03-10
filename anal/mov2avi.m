function mov2avi(m, aviname, frate)

if (~exist('frate'))
    frate = 5;
end
%aviname = 'c:\qt007x0108.left.minus.right.with.stim.square.avi';
f = avifile(aviname, 'compression', 'none', 'fps', frate);
for i=1:length(m)
    f = addframe(f, m(i));
end
f = close(f);