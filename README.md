# EventGeneration

This is a basic set of instructions to generate events starting from a certain CMS central MC production, whose steps one can track down on McM. Some more thorough material can be found here:

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookGenIntro


## Generate config files

Event generation steps can be split in several ways. I always find it a good idea to follow what was done for a certain campaign on McM, both in terms of splitting and of choice of the CMSSW release to use. Here's an example for producing signal events following the central production of the 2018 N2C1 dataset:

[/SMS-N2C1-higgsino_TuneCP2_13TeV-madgraphMLM-pythia8/RunIIAutumn18NanoAODv7-Nano02Apr2020_GridpackScan_102X_upgrade2018_realistic_v21-v1/NANOAODSIM](https://cmsweb.cern.ch/das/request?input=dataset%3D%2FSMS-N2C1-higgsino_TuneCP2_13TeV-madgraphMLM-pythia8%2FRunIIAutumn18NanoAODv7-Nano02Apr2020_GridpackScan_102X_upgrade2018_realistic_v21-v1%2FNANOAODSIM&instance=prod/global)

So, to begin with, go on

https://cms-pdmv.cern.ch/mcm/requests?page=0&shown=127

and choose the input option "Output Dataset". This requires the exact dataset name as displayed on DAS. If we click on the "Show chained requests" symbol on the right of the `Dataset name`, we'll be prompted to a page with several `PrepIds`, corresponding to the various campaigns. One of those corresponds to the specific dataset we are looking at (usually just check the version number). On the right of the same page, we'll see the `Chain` of processes that were involved in the creation of that dataset. Let's click on the first one (typically labeled *GS* as in GenSim). This will take us to a page where we'll see a few options under `Actions`. If we click on "Get setup command", we'll see exactly what was done to generate events for the desired process.

In [this specific case](https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_setup/SUS-RunIIFall18GS-00002), we'll see that we have to set up a local repo with CMSSW_10_2_7, and then to get a Pythia fragment with
```
curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIFall18GS-00002 --retry 3 --create-dirs -o Configuration/GenProduction/python/SUS-RunIIFall18GS-00002-fragment.py
```
After compiling, we can use the cmsDriver command to get the proper cmsRun config file. In the case of the N2toC1W generation, I did:

### GENSIM
```
cmsDriver.py Configuration/GenProduction/python/SUS-RunIIFall18GS-00002-fragment.py --python_filename SUS-RunIIFall18GS-00002_1_cfg.py --eventcontent RAWSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM --fileout file:SUS-RunIIFall18GS-00002.root --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --customise_commands "process.source.numberEventsInLuminosityBlock = cms.untracked.uint32(200)" --step GEN,SIM --geometry DB:Extended --era Run2_2018 --no_exec --mc -n 1
```
`--python_filename` will determine the name of your config file. Once we have this, it's usually a good idea to run it locally before starting a larger production on CRAB (see the CRAB section). Note that it's also a good idea to submit jobs on CRAB with the `publication` option disabled the first time, as it's not trivial to delete files that you've saved on some T2.

Once we're happy of what we've got, we can proceed with the next steps in a similar manner to what we've done for GenSim. Here are example cmsDriver commands to produce config files, which in this repo can be found under `cmssw_config`.

### DIGI-RAW-PREMIX
```
cmsDriver.py  --python_filename SUS-RunIIAutumn18DRPremix-00026_1_cfg.py --eventcontent PREMIXRAW --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --fileout file:SUS-RunIIAutumn18DRPremix-00026_0.root --pileup_input "dbs:/Neutrino_E-10_gun/RunIISummer17PrePremix-PUAutumn18_102X_upgrade2018_realistic_v15-v1/GEN-SIM-DIGI-RAW" --conditions 102X_upgrade2018_realistic_v15 --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:@relval2018 --procModifiers premix_stage2 --geometry DB:Extended --filein "dbs:/SMS-N2C1-higgsino_TuneCP2_13TeV-madgraphMLM-pythia8/RunIIFall18GS-GridpackScan_102X_upgrade2018_realistic_v11-v1/GEN-SIM" --datamix PreMix --era Run2_2018 --no_exec --mc -n 1
```

### AODSIM
```
cmsDriver.py  --python_filename SUS-RunIIAutumn18DRPremix-00026_2_cfg.py --eventcontent AODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier AODSIM --fileout file:SUS-RunIIAutumn18DRPremix-00026.root --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --procModifiers premix_stage2 --filein file:SUS-RunIIAutumn18DRPremix-00026_0.root --era Run2_2018 --runUnscheduled --no_exec --mc -n 1
```

### MINIAODSIM
```
cmsDriver.py  --python_filename SUS-RunIIAutumn18MiniAOD-00026_1_cfg.py --eventcontent MINIAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier MINIAODSIM --fileout file:SUS-RunIIAutumn18MiniAOD-00026.root --conditions 102X_upgrade2018_realistic_v15 --step PAT --geometry DB:Extended --filein "dbs:/SMS-N2C1-higgsino_TuneCP2_13TeV-madgraphMLM-pythia8/RunIIAutumn18DRPremix-GridpackScan_102X_upgrade2018_realistic_v15-v1/AODSIM" --era Run2_2018 --runUnscheduled --no_exec --mc -n 1
```

### NANOAODSIM
```
cmsDriver.py  --python_filename N2toC1W_NANOAODSIM_2018_cfg.py --eventcontent NANOAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAODSIM --customise_commands="process.add_(cms.Service('InitRootHandlers', EnableIMT = cms.untracked.bool(False)))" --fileout file:N2toC1W_NANOAODSIM_2018.root --conditions 102X_upgrade2018_realistic_v21 --step NANO --filein "dbs:/SMS-N2C1-higgsino_TuneCP2_13TeV-madgraphMLM-pythia8/RunIIAutumn18MiniAOD-GridpackScan_102X_upgrade2018_realistic_v15-v1/MINIAODSIM" --era Run2_2018,run2_nanoAOD_102Xv1 --no_exec --mc -n 1
```

A few important NOTES:

- the PREMIX step uses a neutrino gun sample for the simulation of pileup. Pratically, this will add a **very** long python list to your config, which might slow it down when you're editing it. What I usually do in order to deal with this problem only once is that I move that list in a separate python file (called `N2C1_MixingModule_2018.py` in this repo) and I import it in the config file;

- the CMSSW release used for the NANOAOD has changed from that used in the previous step. Therefore, it's necessary to move to CMSSW_12_2_22 for this step;

- the option `--customise_commands="process.add_(cms.Service('InitRootHandlers', EnableIMT = cms.untracked.bool(False)))"` is required in the NANOAODSIM production if the desired result are flat ntuples. Otherwise, one will get EDM-style events;

- following [this set of instructions](https://github.com/dmwm/CRABServer/issues/5600#issuecomment-733783280%20and%20https://twiki.cern.ch/twiki/bin/viewauth/CMS/NanoAODProduction), one currently has to add `fakeNameForCrab =cms.untracked.bool(True),` in the `NanoAODOutputModule customization` of the NANOAOD config file, in order to run it on CRAB smoothly.


## CRAB config files

CRAB servers are useful to run a "mass event production". Example configs can be found in this repo under `crab_config`. There is a config per each simulation step. After sourcing the CRAB3 environment with
```
source /cvmfs/cms.cern.ch/crab3/crab.sh
```
and initializing the grid token, one can submit jobs with:
```
crab submit -c crab_config/the_desired_config.py
```
The type of job splitting, required RAM etc might have to be adjusted according to the needs. For example, it is a good idea to request at least ~3GB of memory when running the PREMIX step, otherwise your jobs might fail for the rest of eternity. If what you ask for is not enough, you can adjust your request based on the actual RAM consumption by adding the flag `--maxMemory=4000` to the `crab resubmit` command. The unit is in MB. Note that most of the sites offer up to 2500 MB, some up to 3000 and only few up to 4000 MB (and if you don't specify it, CRAB will ask for 2000 MB). So, if you need lots of RAM, your jobs might spend more time in *idle*, but will eventually run.

If the option `Data.publication = true`, the final output will be published on the chosen site. You can find a link to DAS by doing
```
crab status -d crab_projects/your_crab_output_directory/
```
Remember that the output files do not end up in `prod/global`, but in `prod/phys03`. To find them with *dasgoclient*, do:
```
dasgoclient -query="file dataset=/dataset_name instance=prod/phys03"
```

Note that the output file for one simulation step will have to be the input file for the following step, of course.