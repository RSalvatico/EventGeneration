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

    config.JobType.inputFiles = ['N2toC1W_MixingModule_2016.py'] #Import correct mixing module file
    config.JobType.psetName = 'cmssw_config/N2C1_DRPREMIX_2016_cfg.py'
    config.General.requestName = 'N2toC1W_DRPREMIX_2016'
    config.Data.inputDataset = ''

if runningEra == 1:

    config.JobType.inputFiles = ['N2toC1W_MixingModule_2017.py'] #Import correct mixing module file
    config.JobType.psetName = 'cmssw_config/N2C1_DRPREMIX_2018_cfg.py'
    config.General.requestName = 'N2toC1W_DRPREMIX_2017'
    config.Data.inputDataset = ''

if runningEra == 2:

    config.JobType.inputFiles = ['N2toC1W_MixingModule_2018.py'] #Import correct mixing module file
    config.JobType.psetName = 'cmssw_config/N2C1_DRPREMIX_2018_cfg.py'
    config.JobType.maxMemoryMB = 3000
    config.General.requestName = 'N2toC1W_DRPREMIX_2018_v2'
    config.Data.inputDataset = '/N2toC1W_GENSIM_2018/rselvati-N2toC1W_2018_v1-146b202c4f841623ae37599a96cb6ee8/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = True

if runningEra == 0:

    config.Data.outputDatasetTag = 'N2toC1W_DRPREMIX_2016_v1'

if runningEra == 1:

    config.Data.outputDatasetTag = 'N2toC1W_DRPREMIX_2017_v1'

if runningEra == 2:

    config.Data.outputDatasetTag = 'N2toC1W_DRPREMIX_2018_v2'

config.section_('Site')
config.Site.storageSite = 'T2_IT_Legnaro'
