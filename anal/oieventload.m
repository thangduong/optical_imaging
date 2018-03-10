global datadir;
exp = 'rb381x0202';
descfile = [datadir '\' exp '.desc'];
desc = load(descfile,'-mat');
nullMean = [];
nullSquare = [];
nullCount = 0;
paramList = {};
paramData = {};
paramSquare = {};
paramCount = {};
for r=1:length(desc.paradigm)
    for c=1:length(desc.paradigm{r})
        datafile = [datadir '\rb381x0202.' num2str(r) '.' sprintf('%04d',c-1) '.csf'];
        data = csfload(datafile,[],[],[],1);
        data.frames = data.frames(:,:,2:end-2);
        if (desc.paradigm{r}{c}.param.contrast > 0)
            foundIt = 0;
            for p=1:length(paramList)
                if (paramcompare(paramList{p},desc.paradigm{r}{c}.param))
                    paramData{p} = paramData{p} + data.frames;
                    paramCount{p} = paramCount{p}+1;
                    paramSquare{p} = paramSquare{p} + data.frames.^2;
                    foundIt = 1;
                    break;
                end
            end
            if (~foundIt)
                paramList{end+1} = desc.paradigm{r}{c}.param;
                paramData{end+1} = data.frames;
                paramSquare{end+1} = data.frames.^2;
                paramCount{end+1} = 1;
            end
        else
            if (length(nullMean)==0) 
                nullMean = data.frames;
                nullSquare = data.frames.^2;
            else
                nullMean = nullMean + data.frames;
                nullSquare = nullSquare + data.frames.^2;
            end
            nullCount = nullCount + 1;
        end
    end
end
