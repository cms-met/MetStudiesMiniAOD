### Making ntuples
Ntuplizer for the gamma+jets studies is located in the `TM` folder, which creates a tree with necessary branches for photon, jet and lepton identification.

Three configuration files are used: `test/treemaker_cfg_mc2018.py`, `test/treemaker_cfg_data2018.py` and `test/treemaker_cfg_data2018_prompt.py` depending on type of dataset.

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

svn export https://github.com/pallabidas/MetStudiesMiniAOD/trunk/GammaJets

scram b -j 8
```

### Making selected events tree

The folder `PostProc` folder contains the necessary scripts for post-processing data and MC ntuples and calculating the variables for Type 1 corrected PF MET.

Changes can be made in the script to run on other MET flavors like RAW and PUPPI.

The first step to making the selected events trees (`mettree`) is to create the pileup or number of vertices weights for MC.

These are kept inside the `PostProc/PileUp` folder.

Note: the official recipe for pileup histogram is given here https://twiki.cern.ch/twiki/bin/viewauth/CMS/PileupJSONFileforData which is used to produce the `MyDataPileupHistogram2018.root` file.

After creating the weights, proceed to the next step for event selection.

For signal gamma+jets samples a separate weight from k-factor is to be undertaken, thus the script is slightly different.

Following command is used to compile and run:

```
g++ -g  -Wno-deprecated ana.C -o out.exe  -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs`
./out.exe ntuple_files.list output.root 
```
The `ntuples_files.list` should contain the full path to the ntuple files, sample wise.

### Making histograms

Scripts for making histograms from the `mettree` branches are kept inside `MakeHisto` folder.

Separate scripts are required for data, gamma+jets signal MC and other MC samples due to different weights.

Compilation commands, in case of data for example, are as follows:

```
g++ -Wno-deprecated scale_data.C -o dummy.exe  -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs`
./dummy.exe output.root histo.root
```

#### Calculating scale and resolution

The scale and resolution from data are calculated using `Mean` and `RMS` methods implemented in ROOT.

Before making histograms for the resolution, the response histograms are needed for correction.

Thus, `make_response_histo.C` should be run before moving onto the `MakeHisto/Resolution` folder from `MakeHisto/Scale`.

The step is included in the `script_findmean.sh` executable.

After creating the response hitogram the `scale_data.C` script inside `Resolution` folder is to be compiled to obtain the resolution histograms, `script_findrms.sh` script produces the resolution numbers.

`NV` and `QT` folder refer to number of vertices and photon transverse momentum respectively, which are used as x-axis for two sets of resolution plots.

### Making plots

The `Plot` folder contains the necessary scripts for making the different plots: data/MC agreements, scale and resolutions for data.

`stack_plotter_met.C` will produce the stack plots for MET transverse momentum distributions.

`graph_scale_comparison.C`, `graph_reso_comparison.C` and `graph_nvtx_reso_comparison.C` compare MET scale and resolutions for different eras of data-taking, they can be adapted to plot different flavors of MET as well.

These scripts are run simply using `root -l` command.

Examples of the input .txt files to the different scripts are provided.

These should necessarily be the outputs from the previous step.
