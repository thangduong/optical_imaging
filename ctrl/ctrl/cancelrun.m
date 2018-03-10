function cancelrun;

% back the data up
backuprun;

% now clear the state of everything!
if (nstimisstimulating)
    disp('still stimulating! forcing stop');
    % TODO: stop stim
end

% stop capturing
sendcapline('stopstream');
