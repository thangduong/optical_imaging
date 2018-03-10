% PIX2DEG    Convert from # of pixels to degree of visual angle
%
%    DEG = PIX2DEG(PIX, [NSTIM, XORY])
%
function deg = pix2deg(pix, NSTIM, xory)

if ((~exist('xory')) | (length(xory)==0))
    xory = 0;       % 0 for x, 1 for y
end

if ((exist('NSTIM')~=1) | (length(NSTIM)==0))
    global NSTIM;
end

if (xory==0)
    deg = ((pix/NSTIM.cfg.mode.width)*NSTIM.cfg.monitorWidth)/NSTIM.cfg.monitorDistanceAway;
else
    deg = ((pix/NSTIM.cfg.mode.width)*NSTIM.cfg.monitorHeight)/NSTIM.cfg.monitorDistanceAway;
end

deg = 2*atan(deg/2);
