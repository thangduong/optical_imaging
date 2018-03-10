function pos = find_pt_between(array, value);
%array = acv;
%value = .5;

% first position is 0

valueAbove = min(find(array >= value));
valueBelow = max(find(array <= value));

if (valueAbove == valueBelow)
    pos = valueAbove - 1;
else
	% there is a point between that is equal
	p = polyfit([array(valueBelow) array(valueAbove)],[0 1], 1);
	pos = valueBelow + polyval(p,value) - 1;
end