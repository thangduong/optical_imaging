% DEG2PIX    Convert from deg of visual angle to # of pixels
%
%    PIX = DEG2PIX(DEG, [NSTIM, XORY])
%
function pix = deg2pix(deg, NSTIM, xory)

if ((~exist('xory')) | (length(xory)==0))
    xory = 0;       % 0 for x, 1 for y
end

if ((exist('NSTIM')~=1) | (length(NSTIM)==0))
    global NSTIM;
end


if (xory==0)
    pix = (2*tan(pi*deg/(2*180))*NSTIM.cfg.monitorDistanceAway/NSTIM.cfg.monitorWidth)*NSTIM.cfg.mode.width;
else
    pix = (2*tan(pi*deg/(2*180))*NSTIM.cfg.monitorDistanceAway/NSTIM.cfg.monitorHeight)*NSTIM.cfg.mode.height;
end
