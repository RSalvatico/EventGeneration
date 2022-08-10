from CRABAPI.RawCommand import crabCommand
from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config
config = Configuration()

runningEra = 2 # 0 = 2016, 1 = 2017, 2 = 2018

config.section_('General')
config.General.transferOutputs = True
config.General.workArea = 'crab_projects'
config.section_('JobType')
config.JobType.pluginName = 'PrivateMC'

config.JobType.allowUndistributedCMSSW = True

config.section_('Data')

if runningEra == 0:
    config.General.requestName = 'N2toC1W_GENSIM_2016'
    config.JobType.psetName = 'Configuration/GenProduction/python/'
    config.JobType.outputFiles = ['N2toC1W_GENSIM_2016.root']
    config.Data.outputPrimaryDataset = 'N2toC1W_GENSIM_2016'

if runningEra == 1:
    config.General.requestName = 'N2toC1W_GENSIM_2017'
    config.JobType.psetName = ''
    config.JobType.outputFiles = ['N2toC1W_GENSIM_2017.root']
    config.Data.outputPrimaryDataset = 'N2toC1W_GENSIM_2017'

if runningEra == 2:
    config.General.requestName = 'N2toC1W_GENSIM_2018'
    config.JobType.psetName = 'cmssw_config/N2toC1W_GENSIM_2018_cfg.py'
    config.JobType.outputFiles = ['N2toC1W_GENSIM_2018.root']
    config.Data.outputPrimaryDataset = 'N2toC1W_GENSIM_2018'

config.Data.splitting = 'EventBased' # Can only be set to EventBased if pluginName = PrivateMC
config.Data.unitsPerJob = 8
NJOBS = 10000
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = True

if runningEra == 0:
    config.Data.outputDatasetTag = 'N2toC1W_2016_v1'
if runningEra == 1:
    config.Data.outputDatasetTag = 'N2toC1W_2017_v1'
if runningEra == 2:
    config.Data.outputDatasetTag = 'N2toC1W_2018_v1'

config.section_('Site')
config.Site.storageSite = 'T2_IT_Legnaro'
