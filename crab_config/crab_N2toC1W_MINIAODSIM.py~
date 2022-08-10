from CRABClient.UserUtilities import config
config = config()
 
runningEra = 2 # 0 = 2016, 1 = 2017, 2 = 2018
 
config.section_('General')
config.General.transferOutputs = True
config.General.workArea = 'crab_projects'
config.section_('JobType')
config.JobType.pluginName = 'Analysis'
config.section_('Data')

config.JobType.allowUndistributedCMSSW = True

if runningEra == 0:

    config.JobType.psetName = 'cmssw_config/N2toC1W_MINIAODSIM_2016_cfg.py'
    config.General.requestName = 'N2toC1W_MINIAODSIM_2016'
    config.Data.inputDataset = ''

if runningEra == 1:

    config.JobType.psetName = 'cmssw_config/N2toC1W_MINIAODSIM_2018_cfg.py'
    config.General.requestName = 'N2toC1W_MINIAODSIM_2017'
    config.Data.inputDataset = ''

if runningEra == 2:

    config.JobType.psetName = 'cmssw_config/N2toC1W_MINIAODSIM_2018_cfg.py'
    config.General.requestName = 'N2toC1W_MINIAODSIM_2018'
    config.JobType.maxMemoryMB = 2000
    config.Data.inputDataset = '/N2toC1W_GENSIM_2018/rselvati-N2toC1W_AODSIM_2018_v1-72e9fe4c1715e830e23a1f8f7ca56279/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 2
config.Data.publication = True

if runningEra == 0:

    config.Data.outputDatasetTag = 'N2toC1W_MINIAODSIM_2016_v1'

if runningEra == 1:

    config.Data.outputDatasetTag = 'N2toC1W_MINIAODSIM_2017_v1'

if runningEra == 2:

    config.Data.outputDatasetTag = 'N2toC1W_MINIAODSIM_2018_v1'

config.section_('Site')
config.Site.storageSite = 'T2_IT_Legnaro'
