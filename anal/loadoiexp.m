%function loadoiexp(

ddir = ['F:\oidata\rb381'];
expname = ['rb381x0402'];
expdir = [ddir '\' expname];

expdescfile = [expdir '\' expname '.desc'];
load(expdescfile,'-mat');

plist = {};
ncond = 0;
for rep=1:length(paradigm)
    for con=1:length(paradigm{rep})
        p = paradigm{rep};
        if (length(paradigm{rep})>1)
            p = paradigm{rep}{con};
        end
        on = ncond+1;
        for nc=1:length(plist)
            if (structcompare(plist{nc}.param,p.param))
                on = nc;
            end
        end
        curFile = [expdir filesep sprintf('%s.%d.%04d.csf', expname, rep, con-1)];
        curData = csfload(curFile,[],[],[],1);        
        if (on==(ncond+1))
            plist{on} = p;
            plist{on}.data = curData.frames;
            ncond = ncond+1;
        else
            plist{on}.data = addmovie(plist{on}.data,curData.frames);
        end
    end
end