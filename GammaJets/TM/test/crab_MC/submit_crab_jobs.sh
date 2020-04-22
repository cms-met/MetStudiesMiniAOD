#!/bin/sh
count="1"

while [ $count -lt 27 ] 
do

echo count $count

#sed -n "${count}p" < MC_input.txt
line=$(sed -n "${count}p" < MC_input.txt)
#echo "$line"
#echo $line | awk -F'/' '{print $2}'
dataset=$(echo $line | awk '{print $2}')
echo "$dataset"
name=$(echo $line | awk -F'/' '{print $2}')
echo "$name"
#echo $name | awk -F'_' '{print $1}'
req=$(echo $line | awk '{print $1}')
echo "$req"

cat>crab3_${req}.py<<EOF
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = '$name'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.allowUndistributedCMSSW = True
config.JobType.maxJobRuntimeMin = 300
config.JobType.numCores = 4
config.JobType.maxMemoryMB = 9000
config.JobType.psetName = '/afs/cern.ch/work/p/pdas/METstudies/performance/CMSSW_10_2_15/src/TreeMaker/TM/test/treemaker_cfg_mc2018.py'
config.JobType.pluginName = 'Analysis'
config.JobType.outputFiles = ['histo.root']
config.JobType.inputFiles = ['Autumn18_V19_MC.db']

config.Data.inputDataset = '$dataset'
config.Data.unitsPerJob = 1
config.Data.splitting = 'FileBased'
config.Data.outLFNDirBase = '/store/user/pdas/'

config.Site.storageSite = 'T2_IN_TIFR'

EOF

crab submit -c crab3_${req}.py

count=$[$count+1]
done


exit 0
