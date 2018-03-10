%function oieventanal(
global datadir;
exp = 'rb381x0202';
descfile = [datadir '\' exp '.desc'];
desc = load(descfile,'-mat');
variables = {'bphase', 'orientation'};
for v=1:length(variables)
    variableValue{v} = [];
end

for r=1:length(desc.paradigm)
    for c=1:length(desc.paradigm{r})
        if (desc.paradigm{r}{c}.param.contrast > 0)
            for v=1:length(variables)
                variableValue{v} = [variableValue{v} getfield(desc.paradigm{r}{c}.param,variables{v})];            
            end
        end
    end
end

for v=1:length(variables)
    variableValue{v} = unique(variableValue{v});
end

for r=1:length(desc.paradigm)
    for c=1:length(desc.paradigm{r})
        if (desc.paradigm{r}{c}.param.contrast > 0)
            for v=1:length(variables)
                variableValue{v} = [variableValue{v} getfield(desc.paradigm{r}{c}.param,variables{v})];            
            end
        end
    end
end
