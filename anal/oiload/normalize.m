function n = normalize(v);

s = size(v);
n = reshape(v, 1, prod(s));
n = n - min(n);
n = n / max(n);
n = reshape(n, s);