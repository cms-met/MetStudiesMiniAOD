Ntuplizer for the gamma+jets studies is located in the TM folder, which creates a tree with necessary branches for photon, jet and lepton identification.

Three configuration files are used: test/treemaker_cfg_mc2018.py, test/treemaker_cfg_data2018.py and test/treemaker_cfg_data2018_prompt.py depending on type of dataset.

The framework uses JEC implemented using the .db files from here: https://github.com/cms-jet/JECDatabase/tree/master/SQLiteFiles which are updated for checking the performance of MET reconstruction algorithms.

Analysis based on the 2018 data recommendations here: https://twiki.cern.ch/twiki/bin/viewauth/CMS/PdmVAnalysisSummaryTable.


To succesfully compile the ntuplizer code following steps are needed:
```
cmsrel CMSSW_10_2_15

cd CMSSW_10_2_15/src/

cmsenv

git cms-init

git cms-merge-topic cms-egamma:EgammaPostRecoTools

scram b -j 8

git cms-addpkg EgammaAnalysis/ElectronTools

rm EgammaAnalysis/ElectronTools/data -rf

git clone git@github.com:cms-egamma/EgammaAnalysis-ElectronTools.git EgammaAnalysis/ElectronTools/data

cd EgammaAnalysis/ElectronTools/data

git checkout ScalesSmearing2018_Dev

cd -

git cms-merge-topic cms-egamma:EgammaPostRecoTools_dev

git cms-addpkg RecoMET/METFilters

git cms-addpkg PhysicsTools/PatAlgos

git cms-addpkg PhysicsTools/PatUtils

git cms-addpkg CommonTools/Utils

git clone https://github.com/pallabidas/MetStudiesMiniAOD.git

scram b -j 8
```
