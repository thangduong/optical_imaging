function outval = matchsize(inval, sz);

insz = size(inval);
inval = reshape(inval, [1 prod(insz)]);
if (prod(sz)>prod(insz))
    outval = [inval zeros(1,prod(sz)-prod(insz))];
else
    outval = inval(1:prod(sz));
end
outval = reshape(outval, sz);