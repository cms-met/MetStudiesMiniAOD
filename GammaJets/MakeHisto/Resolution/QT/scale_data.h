#ifndef scale_data_h
#define scale_data_h

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

class scale_data {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TFile *fileName;
   TH1F *upara50, *upara60, *upara80, *upara90, *upara100, *upara110, *upara130, *upara140, *upara160, *upara180, *upara200, *upara240, *upara320, *upara400;
   TH1F *uperp50, *uperp60, *uperp80, *uperp90, *uperp100, *uperp110, *uperp130, *uperp140, *uperp160, *uperp180, *uperp200, *uperp240, *uperp320, *uperp400;

// Response correction
   TFile *f = TFile::Open("response_2018.root");
   TH1F *histo = (TH1F*)f->Get("h1");

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         uparallel;
   Float_t         uperpendicular;
   Float_t         photon_pt;
   Float_t         met;
   Float_t         wgt;
   Int_t           nvtx;
   Int_t           nJet;

   // List of branches
   TBranch        *b_uparallel;   //!
   TBranch        *b_uperpendicular;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_met;   //!
   TBranch        *b_wgt;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_nJet;   //!

   scale_data(const char* file1, const char* file2);
   virtual ~scale_data();
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

#ifdef scale_data_cxx
scale_data::scale_data(const char* file1, const char* file2) 
{
   BookHistos(file2);
   TChain *chain = new TChain("mettree");
   chain->Add(file1);
   std::cout<<chain->GetEntries()<<std::endl;
   Init(chain);
}

scale_data::~scale_data()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();

   fileName->cd();
   fileName->Write();
   delete fileName;
}

Int_t scale_data::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t scale_data::LoadTree(Long64_t entry)
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

void scale_data::Init(TTree *tree)
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
   fChain->SetBranchAddress("uperpendicular", &uperpendicular, &b_uperpendicular);
   fChain->SetBranchAddress("photon_pt", &photon_pt, &b_photon_pt);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("wgt", &wgt, &b_wgt);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("nJet", &nJet, &b_nJet);
   Notify();
}

Bool_t scale_data::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void scale_data::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t scale_data::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef scale_data_cxx
