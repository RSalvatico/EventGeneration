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

    config.JobType.psetName = 'cmssw_config/N2toC1W_AODSIM_2016_cfg.py'
    config.General.requestName = 'N2toC1W_AODSIM_2016'
    config.Data.inputDataset = ''

if runningEra == 1:

    config.JobType.psetName = 'cmssw_config/N2toC1W_AODSIM_2018_cfg.py'
    config.General.requestName = 'N2toC1W_AODSIM_2017'
    config.Data.inputDataset = ''

if runningEra == 2:

    config.JobType.psetName = 'cmssw_config/N2toC1W_AODSIM_2018_cfg.py'
    config.JobType.maxMemoryMB = 2500
    config.General.requestName = 'N2toC1W_AODSIM_2018'
    config.Data.inputDataset = '/N2toC1W_GENSIM_2018/rselvati-N2toC1W_DRPREMIX_2018_v2-561697a7e1ccc674784d5e0d3e6ef789/USER' #v2 has all jobs succeeded

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = True

if runningEra == 0:

    config.Data.outputDatasetTag = 'N2toC1W_AODSIM_2016_v1'

if runningEra == 1:

    config.Data.outputDatasetTag = 'N2toC1W_AODSIM_2017_v1'

if runningEra == 2:

    config.Data.outputDatasetTag = 'N2toC1W_AODSIM_2018_v1'

config.section_('Site')
config.Site.storageSite = 'T2_IT_Legnaro'
