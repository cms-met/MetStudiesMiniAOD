from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'EGamma2018Av2'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.allowUndistributedCMSSW = True
config.JobType.maxJobRuntimeMin = 300
config.JobType.numCores = 4
config.JobType.maxMemoryMB = 9000
config.JobType.psetName = '/afs/cern.ch/work/p/pdas/METstudies/performance/CMSSW_10_2_15/src/TreeMaker/TM/test/treemaker_cfg_data2018.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['histo.root']
config.JobType.inputFiles = ['Autumn18_RunABCD_V19_DATA.db']

config.Data.inputDataset = '/EGamma/Run2018A-17Sep2018-v2/MINIAOD'
config.Data.unitsPerJob = 1
config.Data.splitting = 'FileBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
config.Data.outLFNDirBase = '/store/user/pdas/'

config.Site.storageSite = 'T2_IN_TIFR'

