#ifndef scale_mc_h
#define scale_mc_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TBranch.h>
#include <TMinuit.h>
#include <TRandom.h>
#include <string>
#include <iostream>
#include <fstream>
#include <TMath.h>
#include <stdio.h>
#include <TString.h>
#include <TH1F.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TH2F.h>
#include <TH1I.h>
#include <TSystemFile.h>
#include <TSystemDirectory.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TList.h>
#include <Riostream.h>
#include <TGraphAsymmErrors.h>
#include <TMap.h>
#include <vector>
#include <TTree.h>
#ifdef __MAKECINT__
#pragma link C++ class vector<std::vector<int> >+;
#pragma link C++ class vector<std::vector<std::string> >+;
#pragma link C++ class vector<std::vector<float> >+;
#pragma link C++ class vector<std::vector<bool> >+;
#pragma extra_include "vector";
#endif

using namespace std;

// Header file for the classes stored in the TTree if any.

class scale_mc {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile *fileName;
   TH1F *nvertex, *Photon_pt_unp, *Photon_pt, *Photon_eta, *Photon_phi, *Photon_energy, *MET_pt, *MET_phi, *CorrMET_pt, *CorrMET_phi, *Jet_pt, *Jet_eta, *Jet_phi, *uPara, *uPara_JetEnUp, *uPara_JetEnDown, *uPara_JetResUp, *uPara_JetResDown, *uPara_UnclusteredEnUp, *uPara_UnclusteredEnDown, *uPerp, *uPerp_JetEnUp, *uPerp_JetEnDown, *uPerp_JetResUp, *uPerp_JetResDown, *uPerp_UnclusteredEnUp, *uPerp_UnclusteredEnDown, *upara50, *upara60, *upara80, *upara90, *upara100, *upara110, *upara130, *upara150, *upara175, *upara200, *upara225, *upara250, *upara275, *upara305, *upara335, *upara365, *upara400, *upara440, *upara500, *MET_pt_JetEnUp, *MET_pt_JetEnDown, *MET_pt_JetResUp, *MET_pt_JetResDown, *MET_pt_UnclusteredEnUp, *MET_pt_UnclusteredEnDown, *CorrMET_pt_JetEnUp, *CorrMET_pt_JetEnDown, *CorrMET_pt_JetResUp, *CorrMET_pt_JetResDown, *CorrMET_pt_UnclusteredEnUp, *CorrMET_pt_UnclusteredEnDown;
   Float_t evt_wgt;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         uparallel;
   Float_t         uparallel_JetEnUp;
   Float_t         uparallel_JetEnDown;
   Float_t         uparallel_JetResUp;
   Float_t         uparallel_JetResDown;
   Float_t         uparallel_UnclusteredEnUp;
   Float_t         uparallel_UnclusteredEnDown;
   Float_t         uperpendicular;
   Float_t         uperpendicular_JetEnUp;
   Float_t         uperpendicular_JetEnDown;
   Float_t         uperpendicular_JetResUp;
   Float_t         uperpendicular_JetResDown;
   Float_t         uperpendicular_UnclusteredEnUp;
   Float_t         uperpendicular_UnclusteredEnDown;
   Float_t         photon_pt;
   Float_t         photon_eta;
   Float_t         photon_phi;
   Float_t         photon_energy;
   Float_t         met;
   Float_t         met_JetEnUp;
   Float_t         met_JetEnDown;
   Float_t         met_JetResUp;
   Float_t         met_JetResDown;
   Float_t         met_UnclusteredEnUp;
   Float_t         met_UnclusteredEnDown;
   Float_t         met_phi;
   Float_t         corrmet;
   Float_t         corrmet_JetEnUp;
   Float_t         corrmet_JetEnDown;
   Float_t         corrmet_JetResUp;
   Float_t         corrmet_JetResDown;
   Float_t         corrmet_UnclusteredEnUp;
   Float_t         corrmet_UnclusteredEnDown;
   Float_t         corrmet_phi;
   Float_t         pusf;
   Float_t         nvsf;
   Float_t         wgtA;
   Float_t         wgtB;
   Float_t         wgtC;
   Float_t         wgtD;
   Int_t           nvtx;
   Int_t           nJet;
   Float_t         jet_pt;
   Float_t         jet_eta;
   Float_t         jet_phi;
   Float_t         IDSF;
   Char_t          fail;

   // List of branches
   TBranch        *b_uparallel;   //!
   TBranch        *b_uparallel_JetEnUp;   //!
   TBranch        *b_uparallel_JetEnDown;   //!
   TBranch        *b_uparallel_JetResUp;   //!
   TBranch        *b_uparallel_JetResDown;   //!
   TBranch        *b_uparallel_UnclusteredEnUp;   //!
   TBranch        *b_uparallel_UnclusteredEnDown;   //!
   TBranch        *b_uperpendicular;   //!
   TBranch        *b_uperpendicular_JetEnUp;   //!
   TBranch        *b_uperpendicular_JetEnDown;   //!
   TBranch        *b_uperpendicular_JetResUp;   //!
   TBranch        *b_uperpendicular_JetResDown;   //!
   TBranch        *b_uperpendicular_UnclusteredEnUp;   //!
   TBranch        *b_uperpendicular_UnclusteredEnDown;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_energy;   //!
   TBranch        *b_met;   //!
   TBranch        *b_met_JetEnUp;   //!
   TBranch        *b_met_JetEnDown;   //!
   TBranch        *b_met_JetResUp;   //!
   TBranch        *b_met_JetResDown;   //!
   TBranch        *b_met_UnclusteredEnUp;   //!
   TBranch        *b_met_UnclusteredEnDown;   //!
   TBranch        *b_met_phi;   //!
   TBranch        *b_corrmet;   //!
   TBranch        *b_corrmet_JetEnUp;   //!
   TBranch        *b_corrmet_JetEnDown;   //!
   TBranch        *b_corrmet_JetResUp;   //!
   TBranch        *b_corrmet_JetResDown;   //!
   TBranch        *b_corrmet_UnclusteredEnUp;   //!
   TBranch        *b_corrmet_UnclusteredEnDown;   //!
   TBranch        *b_corrmet_phi;   //!
   TBranch        *b_pusf;   //!
   TBranch        *b_nvsf;   //!
   TBranch        *b_wgtA;   //!
   TBranch        *b_wgtB;   //!
   TBranch        *b_wgtC;   //!
   TBranch        *b_wgtD;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_nJet;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_IDSF;   //!
   TBranch        *b_fail;   //!

   scale_mc(const char* file1, const char* file2);
   virtual ~scale_mc();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     BookHistos(const char* file2);
};

#endif

#ifdef scale_mc_cxx
scale_mc::scale_mc(const char* file1, const char* file2) 
{
   BookHistos(file2);
   TChain *chain = new TChain("mettree");
   chain->Add(file1);
   std::cout<<chain->GetEntries()<<std::endl;
   Init(chain);
}

scale_mc::~scale_mc()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();

   fileName->cd();
   fileName->Write();
   delete fileName;
}

Int_t scale_mc::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t scale_mc::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void scale_mc::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("uparallel", &uparallel, &b_uparallel);
   fChain->SetBranchAddress("uparallel_JetEnUp", &uparallel_JetEnUp, &b_uparallel_JetEnUp);
   fChain->SetBranchAddress("uparallel_JetEnDown", &uparallel_JetEnDown, &b_uparallel_JetEnDown);
   fChain->SetBranchAddress("uparallel_JetResUp", &uparallel_JetResUp, &b_uparallel_JetResUp);
   fChain->SetBranchAddress("uparallel_JetResDown", &uparallel_JetResDown, &b_uparallel_JetResDown);
   fChain->SetBranchAddress("uparallel_UnclusteredEnUp", &uparallel_UnclusteredEnUp, &b_uparallel_UnclusteredEnUp);
   fChain->SetBranchAddress("uparallel_UnclusteredEnDown", &uparallel_UnclusteredEnDown, &b_uparallel_UnclusteredEnDown);
   fChain->SetBranchAddress("uperpendicular", &uperpendicular, &b_uperpendicular);
   fChain->SetBranchAddress("uperpendicular_JetEnUp", &uperpendicular_JetEnUp, &b_uperpendicular_JetEnUp);
   fChain->SetBranchAddress("uperpendicular_JetEnDown", &uperpendicular_JetEnDown, &b_uperpendicular_JetEnDown);
   fChain->SetBranchAddress("uperpendicular_JetResUp", &uperpendicular_JetResUp, &b_uperpendicular_JetResUp);
   fChain->SetBranchAddress("uperpendicular_JetResDown", &uperpendicular_JetResDown, &b_uperpendicular_JetResDown);
   fChain->SetBranchAddress("uperpendicular_UnclusteredEnUp", &uperpendicular_UnclusteredEnUp, &b_uperpendicular_UnclusteredEnUp);
   fChain->SetBranchAddress("uperpendicular_UnclusteredEnDown", &uperpendicular_UnclusteredEnDown, &b_uperpendicular_UnclusteredEnDown);
   fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
   fChain->SetBranchAddress("photon_eta", &photon_eta, &b_photon_eta);
   fChain->SetBranchAddress("photon_phi", &photon_phi, &b_photon_phi);
   fChain->SetBranchAddress("photon_energy", &photon_energy, &b_photon_energy);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("met_JetEnUp", &met_JetEnUp, &b_met_JetEnUp);
   fChain->SetBranchAddress("met_JetEnDown", &met_JetEnDown, &b_met_JetEnDown);
   fChain->SetBranchAddress("met_JetResUp", &met_JetResUp, &b_met_JetResUp);
   fChain->SetBranchAddress("met_JetResDown", &met_JetResDown, &b_met_JetResDown);
   fChain->SetBranchAddress("met_UnclusteredEnUp", &met_UnclusteredEnUp, &b_met_UnclusteredEnUp);
   fChain->SetBranchAddress("met_UnclusteredEnDown", &met_UnclusteredEnDown, &b_met_UnclusteredEnDown);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   fChain->SetBranchAddress("corrmet", &corrmet, &b_corrmet);
   fChain->SetBranchAddress("corrmet_JetEnUp", &corrmet_JetEnUp, &b_corrmet_JetEnUp);
   fChain->SetBranchAddress("corrmet_JetEnDown", &corrmet_JetEnDown, &b_corrmet_JetEnDown);
   fChain->SetBranchAddress("corrmet_JetResUp", &corrmet_JetResUp, &b_corrmet_JetResUp);
   fChain->SetBranchAddress("corrmet_JetResDown", &corrmet_JetResDown, &b_corrmet_JetResDown);
   fChain->SetBranchAddress("corrmet_UnclusteredEnUp", &corrmet_UnclusteredEnUp, &b_corrmet_UnclusteredEnUp);
   fChain->SetBranchAddress("corrmet_UnclusteredEnDown", &corrmet_UnclusteredEnDown, &b_corrmet_UnclusteredEnDown);
   fChain->SetBranchAddress("corrmet_phi", &corrmet_phi, &b_corrmet_phi);
   fChain->SetBranchAddress("pusf", &pusf, &b_pusf);
   fChain->SetBranchAddress("nvsf", &nvsf, &b_nvsf);
   fChain->SetBranchAddress("wgtA", &wgtA, &b_wgtA);
   fChain->SetBranchAddress("wgtB", &wgtB, &b_wgtB);
   fChain->SetBranchAddress("wgtC", &wgtC, &b_wgtC);
   fChain->SetBranchAddress("wgtD", &wgtD, &b_wgtD);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("IDSF", &IDSF, &b_IDSF);
   fChain->SetBranchAddress("fail", &fail, &b_fail);
   Notify();
}

Bool_t scale_mc::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void scale_mc::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t scale_mc::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef scale_mc_cxx
