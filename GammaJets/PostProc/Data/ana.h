#ifndef ana_h
#define ana_h

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
#ifdef __MAKECINT__
#pragma link C++ class vector<std::vector<int> >+;
#pragma link C++ class vector<std::vector<std::string> >+;
#pragma link C++ class vector<std::vector<float> >+;
#pragma link C++ class vector<std::vector<bool> >+;
#pragma extra_include "vector";
#endif

using namespace std;

class ana {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Files and histograms

   TFile *fileName;
   TTree *mettree;
   Float_t uparallel, uperpendicular, met, met_phi, corrmet, corrmet_phi, corrupara, corruperp, wgt, jet_pt, jet_eta, jet_phi, photon_pt, photon_eta, photon_phi, photon_energy;
   Bool_t fail;
   Int_t nvtx, nJet;

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<string>  *all_triggernames;
   vector<int>     *all_triggerprescales;
   vector<bool>    *all_ifTriggerpassed;
   UInt_t          RunNumber;
   ULong64_t       EventNumber;
   UInt_t          LumiNumber;
   UInt_t          BXNumber;
   Int_t           Event_n;
   Int_t           Vertex_n;
   vector<float>   *Vertex_chi2;
   vector<float>   *Vertex_d0;
   vector<int>     *Vertex_tracksize;
   vector<int>     *Vertex_ndof;
   vector<bool>    *Vertex_isFake;
   TClonesArray    *Vertex_position;
   Int_t           Muon_n;
   TClonesArray    *Muon_4Momentum;
   vector<bool>    *Muon_isLooseMuon;
   vector<float>   *Muon_idPreselection;
   Int_t           Photon_n;
   vector<float>   *Photon_HoverE;
   vector<float>   *Photon_sigmaIetaIeta;
   vector<float>   *Photon_chargedHadronIso;
   vector<float>   *Photon_neutralHadronIso;
   vector<float>   *Photon_photonIso;
   TClonesArray    *Photon_4Momentum;
   TClonesArray    *Photon_4Momentum_corr;
   TClonesArray    *Photon_Vposition;
   vector<float>   *Photon_r9;
   vector<bool>    *Photon_hasPixelSeed;
   vector<bool>    *Photon_passElectronVeto;
   vector<float>   *Photon_hOVERe;
   vector<float>   *Photon_full5x5_r9;
   vector<float>   *Photon_full5x5_sigmaIetaIeta;
   vector<float>   *Photon_full5x5_e5x5;
   vector<float>   *Photon_scEta;
   vector<float>   *Photon_scEnergy;
   Int_t           Electron_n;
   TClonesArray    *Electron_4Momentum;
   vector<float>   *Electron_idPreselection;
   Float_t         rho;
   vector<float>   *PFMetPt;
   vector<float>   *PFMetPx;
   vector<float>   *PFMetPy;
   vector<float>   *PFMetPhi;
   vector<float>   *RawMetPt;
   vector<float>   *RawMetPx;
   vector<float>   *RawMetPy;
   vector<float>   *RawMetPhi;
   vector<float>   *RawChsMetPt;
   vector<float>   *RawChsMetPx;
   vector<float>   *RawChsMetPy;
   vector<float>   *RawChsMetPhi;
   vector<float>   *RawTrkMetPt;
   vector<float>   *RawTrkMetPx;
   vector<float>   *RawTrkMetPy;
   vector<float>   *RawTrkMetPhi;
   vector<float>   *PuppiMetPt;
   vector<float>   *PuppiMetPx;
   vector<float>   *PuppiMetPy;
   vector<float>   *PuppiMetPhi;
   vector<float>   *PuppiMetcorPt;
   vector<float>   *PuppiMetcorPx;
   vector<float>   *PuppiMetcorPy;
   vector<float>   *PuppiMetcorPhi;
   vector<bool>    *filter_goodVertices;
   vector<bool>    *filter_globaltighthalo2016;
   vector<bool>    *filter_globalsupertighthalo2016;
   vector<bool>    *filter_hbher2t;
   vector<bool>    *filter_hbheiso;
   vector<bool>    *filter_ecaltp;
   vector<bool>    *filter_ecalsc;
   vector<bool>    *filter_badPFMuon;
   vector<bool>    *filter_ecalBadCalib;
   Int_t           PFJet_n;
   TClonesArray    *PFJet_4Momentum;
   TClonesArray    *UcPFJet_4Momentum;
   TClonesArray    *PFJet_Vposition;
   vector<float>   *PFJet_CEMF;
   vector<float>   *PFJet_NEMF;
   vector<float>   *PFJet_CHF;
   vector<float>   *PFJet_NHF;
   vector<float>   *PFJet_MUF;
   vector<int>     *PFJet_NumNeutralParticles;
   vector<int>     *PFJet_CHM;
   vector<int>     *PFJet_NumConst;
   vector<int>     *PFJet_jecUncer;
   vector<int>     *PFJet_jecCorr;

   // List of branches
   TBranch        *b_all_triggernames;   //!
   TBranch        *b_all_triggerprescales;   //!
   TBranch        *b_all_ifTriggerpassed;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_LumiNumber;   //!
   TBranch        *b_BXNumber;   //!
   TBranch        *b_Event_n;   //!
   TBranch        *b_Vertex_n;   //!
   TBranch        *b_Vertex_chi2;   //!
   TBranch        *b_Vertex_d0;   //!
   TBranch        *b_Vertex_tracksize;   //!
   TBranch        *b_Vertex_ndof;   //!
   TBranch        *b_Vertex_isFake;   //!
   TBranch        *b_Vertex_position;   //!
   TBranch        *b_Muon_n;   //!
   TBranch        *b_Muon_4Momentum;   //!
   TBranch        *b_Muon_isLooseMuon;   //!
   TBranch        *b_Muon_idPreselection;   //!
   TBranch        *b_Photon_n;   //!
   TBranch        *b_Photon_HoverE;   //!
   TBranch        *b_Photon_sigmaIetaIeta;   //!
   TBranch        *b_Photon_chargedHadronIso;   //!
   TBranch        *b_Photon_neutralHadronIso;   //!
   TBranch        *b_Photon_photonIso;   //!
   TBranch        *b_Photon_4Momentum;   //!
   TBranch        *b_Photon_4Momentum_corr;   //!
   TBranch        *b_Photon_Vposition;   //!
   TBranch        *b_Photon_r9;   //!
   TBranch        *b_Photon_hasPixelSeed;   //!
   TBranch        *b_Photon_passElectronVeto;   //!
   TBranch        *b_Photon_hOVERe;   //!
   TBranch        *b_Photon_full5x5_r9;   //!
   TBranch        *b_Photon_full5x5_sigmaIetaIeta;   //!
   TBranch        *b_Photon_full5x5_e5x5;   //!
   TBranch        *b_Photon_scEta;   //!
   TBranch        *b_Photon_scEnergy;   //!
   TBranch        *b_Electron_n;   //!
   TBranch        *b_Electron_4Momentum;   //!
   TBranch        *b_Electron_idPreselection;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_PFMetPt;   //!
   TBranch        *b_PFMetPx;   //!
   TBranch        *b_PFMetPy;   //!
   TBranch        *b_PFMetPhi;   //!
   TBranch        *b_RawMetPt;   //!
   TBranch        *b_RawMetPx;   //!
   TBranch        *b_RawMetPy;   //!
   TBranch        *b_RawMetPhi;   //!
   TBranch        *b_RawChsMetPt;   //!
   TBranch        *b_RawChsMetPx;   //!
   TBranch        *b_RawChsMetPy;   //!
   TBranch        *b_RawChsMetPhi;   //!
   TBranch        *b_RawTrkMetPt;   //!
   TBranch        *b_RawTrkMetPx;   //!
   TBranch        *b_RawTrkMetPy;   //!
   TBranch        *b_RawTrkMetPhi;   //!
   TBranch        *b_PuppiMetPt;   //!
   TBranch        *b_PuppiMetPx;   //!
   TBranch        *b_PuppiMetPy;   //!
   TBranch        *b_PuppiMetPhi;   //!
   TBranch        *b_PuppiMetcorPt;   //!
   TBranch        *b_PuppiMetcorPx;   //!
   TBranch        *b_PuppiMetcorPy;   //!
   TBranch        *b_PuppiMetcorPhi;   //!
   TBranch        *b_filter_goodVertices;   //!
   TBranch        *b_filter_globaltighthalo2016;   //!
   TBranch        *b_filter_globalsupertighthalo2016;   //!
   TBranch        *b_filter_hbher2t;   //!
   TBranch        *b_filter_hbheiso;   //!
   TBranch        *b_filter_ecaltp;   //!
   TBranch        *b_filter_ecalsc;   //!
   TBranch        *b_filter_badPFMuon;   //!
   TBranch        *b_filter_ecalBadCalib;   //!
   TBranch        *b_PFJet_n;   //!
   TBranch        *b_PFJet_4Momentum;   //!
   TBranch        *b_UcPFJet_4Momentum;   //!
   TBranch        *b_PFJet_Vposition;   //!
   TBranch        *b_PFJet_CEMF;   //!
   TBranch        *b_PFJet_NEMF;   //!
   TBranch        *b_PFJet_CHF;   //!
   TBranch        *b_PFJet_NHF;   //!
   TBranch        *b_PFJet_MUF;   //!
   TBranch        *b_PFJet_NumNeutralParticles;   //!
   TBranch        *b_PFJet_CHM;   //!
   TBranch        *b_PFJet_NumConst;   //!
   TBranch        *b_PFJet_jecUncer;   //!
   TBranch        *b_PFJet_jecCorr;   //!

   ana(string fileToOpen, const char* file2);
   virtual ~ana();
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

#ifdef ana_cxx
ana::ana(string fileToOpen, const char* file2) 
{
  
  BookHistos(file2);
  TChain *chain = new TChain("demo/tree");
  ifstream file;
  file.open(fileToOpen.c_str(), ifstream::in );
  char filename[2000];
  while (true) {
    file >> filename;
    if( file.eof() ) break;
        chain->Add(filename);
        cout<<"Added "<<filename<<endl;
  }//loop over while
   Init(chain);
}

ana::~ana()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
   fileName->cd();
   fileName->Write();
   fileName->Close();
}

Int_t ana::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ana::LoadTree(Long64_t entry)
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

void ana::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   all_triggernames = 0;
   all_triggerprescales = 0;
   all_ifTriggerpassed = 0;
   Vertex_chi2 = 0;
   Vertex_d0 = 0;
   Vertex_tracksize = 0;
   Vertex_ndof = 0;
   Vertex_isFake = 0;
   Vertex_position = 0;
   Muon_4Momentum = 0;
   Muon_isLooseMuon = 0;
   Muon_idPreselection = 0;
   Photon_HoverE = 0;
   Photon_sigmaIetaIeta = 0;
   Photon_chargedHadronIso = 0;
   Photon_neutralHadronIso = 0;
   Photon_photonIso = 0;
   Photon_4Momentum = 0;
   Photon_4Momentum_corr = 0;
   Photon_Vposition = 0;
   Photon_r9 = 0;
   Photon_hasPixelSeed = 0;
   Photon_passElectronVeto = 0;
   Photon_hOVERe = 0;
   Photon_full5x5_r9 = 0;
   Photon_full5x5_sigmaIetaIeta = 0;
   Photon_full5x5_e5x5 = 0;
   Photon_scEta = 0;
   Photon_scEnergy = 0;
   Electron_4Momentum = 0;
   Electron_idPreselection = 0;
   PFMetPt = 0;
   PFMetPx = 0;
   PFMetPy = 0;
   PFMetPhi = 0;
   RawMetPt = 0;
   RawMetPx = 0;
   RawMetPy = 0;
   RawMetPhi = 0;
   RawChsMetPt = 0;
   RawChsMetPx = 0;
   RawChsMetPy = 0;
   RawChsMetPhi = 0;
   RawTrkMetPt = 0;
   RawTrkMetPx = 0;
   RawTrkMetPy = 0;
   RawTrkMetPhi = 0;
   PuppiMetPt = 0;
   PuppiMetPx = 0;
   PuppiMetPy = 0;
   PuppiMetPhi = 0;
   PuppiMetcorPt = 0;
   PuppiMetcorPx = 0;
   PuppiMetcorPy = 0;
   PuppiMetcorPhi = 0;
   filter_goodVertices = 0;
   filter_globaltighthalo2016 = 0;
   filter_globalsupertighthalo2016 = 0;
   filter_hbher2t = 0;
   filter_hbheiso = 0;
   filter_ecaltp = 0;
   filter_ecalsc = 0;
   filter_badPFMuon = 0;
   filter_ecalBadCalib = 0;
   PFJet_4Momentum = 0;
   UcPFJet_4Momentum = 0;
   PFJet_Vposition = 0;
   PFJet_CEMF = 0;
   PFJet_NEMF = 0;
   PFJet_CHF = 0;
   PFJet_NHF = 0;
   PFJet_MUF = 0;
   PFJet_NumNeutralParticles = 0;
   PFJet_CHM = 0;
   PFJet_NumConst = 0;
   PFJet_jecUncer = 0;
   PFJet_jecCorr = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("all_triggernames", &all_triggernames, &b_all_triggernames);
   fChain->SetBranchAddress("all_triggerprescales", &all_triggerprescales, &b_all_triggerprescales);
   fChain->SetBranchAddress("all_ifTriggerpassed", &all_ifTriggerpassed, &b_all_ifTriggerpassed);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("LumiNumber", &LumiNumber, &b_LumiNumber);
   fChain->SetBranchAddress("BXNumber", &BXNumber, &b_BXNumber);
   fChain->SetBranchAddress("Event_n", &Event_n, &b_Event_n);
   fChain->SetBranchAddress("Vertex_n", &Vertex_n, &b_Vertex_n);
   fChain->SetBranchAddress("Vertex_chi2", &Vertex_chi2, &b_Vertex_chi2);
   fChain->SetBranchAddress("Vertex_d0", &Vertex_d0, &b_Vertex_d0);
   fChain->SetBranchAddress("Vertex_tracksize", &Vertex_tracksize, &b_Vertex_tracksize);
   fChain->SetBranchAddress("Vertex_ndof", &Vertex_ndof, &b_Vertex_ndof);
   fChain->SetBranchAddress("Vertex_isFake", &Vertex_isFake, &b_Vertex_isFake);
   fChain->SetBranchAddress("Vertex_position", &Vertex_position, &b_Vertex_position);
   fChain->SetBranchAddress("Muon_n", &Muon_n, &b_Muon_n);
   fChain->SetBranchAddress("Muon_4Momentum", &Muon_4Momentum, &b_Muon_4Momentum);
   fChain->SetBranchAddress("Muon_isLooseMuon", &Muon_isLooseMuon, &b_Muon_isLooseMuon);
   fChain->SetBranchAddress("Muon_idPreselection", &Muon_idPreselection, &b_Muon_idPreselection);
   fChain->SetBranchAddress("Photon_n", &Photon_n, &b_Photon_n);
   fChain->SetBranchAddress("Photon_HoverE", &Photon_HoverE, &b_Photon_HoverE);
   fChain->SetBranchAddress("Photon_sigmaIetaIeta", &Photon_sigmaIetaIeta, &b_Photon_sigmaIetaIeta);
   fChain->SetBranchAddress("Photon_chargedHadronIso", &Photon_chargedHadronIso, &b_Photon_chargedHadronIso);
   fChain->SetBranchAddress("Photon_neutralHadronIso", &Photon_neutralHadronIso, &b_Photon_neutralHadronIso);
   fChain->SetBranchAddress("Photon_photonIso", &Photon_photonIso, &b_Photon_photonIso);
   fChain->SetBranchAddress("Photon_4Momentum", &Photon_4Momentum, &b_Photon_4Momentum);
   fChain->SetBranchAddress("Photon_4Momentum_corr", &Photon_4Momentum_corr, &b_Photon_4Momentum_corr);
   fChain->SetBranchAddress("Photon_Vposition", &Photon_Vposition, &b_Photon_Vposition);
   fChain->SetBranchAddress("Photon_r9", &Photon_r9, &b_Photon_r9);
   fChain->SetBranchAddress("Photon_hasPixelSeed", &Photon_hasPixelSeed, &b_Photon_hasPixelSeed);
   fChain->SetBranchAddress("Photon_passElectronVeto", &Photon_passElectronVeto, &b_Photon_passElectronVeto);
   fChain->SetBranchAddress("Photon_hOVERe", &Photon_hOVERe, &b_Photon_hOVERe);
   fChain->SetBranchAddress("Photon_full5x5_r9", &Photon_full5x5_r9, &b_Photon_full5x5_r9);
   fChain->SetBranchAddress("Photon_full5x5_sigmaIetaIeta", &Photon_full5x5_sigmaIetaIeta, &b_Photon_full5x5_sigmaIetaIeta);
   fChain->SetBranchAddress("Photon_full5x5_e5x5", &Photon_full5x5_e5x5, &b_Photon_full5x5_e5x5);
   fChain->SetBranchAddress("Photon_scEta", &Photon_scEta, &b_Photon_scEta);
   fChain->SetBranchAddress("Photon_scEnergy", &Photon_scEnergy, &b_Photon_scEnergy);
   fChain->SetBranchAddress("Electron_n", &Electron_n, &b_Electron_n);
   fChain->SetBranchAddress("Electron_4Momentum", &Electron_4Momentum, &b_Electron_4Momentum);
   fChain->SetBranchAddress("Electron_idPreselection", &Electron_idPreselection, &b_Electron_idPreselection);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("PFMetPt", &PFMetPt, &b_PFMetPt);
   fChain->SetBranchAddress("PFMetPx", &PFMetPx, &b_PFMetPx);
   fChain->SetBranchAddress("PFMetPy", &PFMetPy, &b_PFMetPy);
   fChain->SetBranchAddress("PFMetPhi", &PFMetPhi, &b_PFMetPhi);
   fChain->SetBranchAddress("RawMetPt", &RawMetPt, &b_RawMetPt);
   fChain->SetBranchAddress("RawMetPx", &RawMetPx, &b_RawMetPx);
   fChain->SetBranchAddress("RawMetPy", &RawMetPy, &b_RawMetPy);
   fChain->SetBranchAddress("RawMetPhi", &RawMetPhi, &b_RawMetPhi);
   fChain->SetBranchAddress("RawChsMetPt", &RawChsMetPt, &b_RawChsMetPt);
   fChain->SetBranchAddress("RawChsMetPx", &RawChsMetPx, &b_RawChsMetPx);
   fChain->SetBranchAddress("RawChsMetPy", &RawChsMetPy, &b_RawChsMetPy);
   fChain->SetBranchAddress("RawChsMetPhi", &RawChsMetPhi, &b_RawChsMetPhi);
   fChain->SetBranchAddress("RawTrkMetPt", &RawTrkMetPt, &b_RawTrkMetPt);
   fChain->SetBranchAddress("RawTrkMetPx", &RawTrkMetPx, &b_RawTrkMetPx);
   fChain->SetBranchAddress("RawTrkMetPy", &RawTrkMetPy, &b_RawTrkMetPy);
   fChain->SetBranchAddress("RawTrkMetPhi", &RawTrkMetPhi, &b_RawTrkMetPhi);
   fChain->SetBranchAddress("PuppiMetPt", &PuppiMetPt, &b_PuppiMetPt);
   fChain->SetBranchAddress("PuppiMetPx", &PuppiMetPx, &b_PuppiMetPx);
   fChain->SetBranchAddress("PuppiMetPy", &PuppiMetPy, &b_PuppiMetPy);
   fChain->SetBranchAddress("PuppiMetPhi", &PuppiMetPhi, &b_PuppiMetPhi);
   fChain->SetBranchAddress("PuppiMetcorPt", &PuppiMetcorPt, &b_PuppiMetcorPt);
   fChain->SetBranchAddress("PuppiMetcorPx", &PuppiMetcorPx, &b_PuppiMetcorPx);
   fChain->SetBranchAddress("PuppiMetcorPy", &PuppiMetcorPy, &b_PuppiMetcorPy);
   fChain->SetBranchAddress("PuppiMetcorPhi", &PuppiMetcorPhi, &b_PuppiMetcorPhi);
   fChain->SetBranchAddress("filter_goodVertices", &filter_goodVertices, &b_filter_goodVertices);
   fChain->SetBranchAddress("filter_globaltighthalo2016", &filter_globaltighthalo2016, &b_filter_globaltighthalo2016);
   fChain->SetBranchAddress("filter_globalsupertighthalo2016", &filter_globalsupertighthalo2016, &b_filter_globalsupertighthalo2016);
   fChain->SetBranchAddress("filter_hbher2t", &filter_hbher2t, &b_filter_hbher2t);
   fChain->SetBranchAddress("filter_hbheiso", &filter_hbheiso, &b_filter_hbheiso);
   fChain->SetBranchAddress("filter_ecaltp", &filter_ecaltp, &b_filter_ecaltp);
   fChain->SetBranchAddress("filter_ecalsc", &filter_ecalsc, &b_filter_ecalsc);
   fChain->SetBranchAddress("filter_badPFMuon", &filter_badPFMuon, &b_filter_badPFMuon);
   fChain->SetBranchAddress("filter_ecalBadCalib", &filter_ecalBadCalib, &b_filter_ecalBadCalib);
   fChain->SetBranchAddress("PFJet_n", &PFJet_n, &b_PFJet_n);
   fChain->SetBranchAddress("PFJet_4Momentum", &PFJet_4Momentum, &b_PFJet_4Momentum);
   fChain->SetBranchAddress("UcPFJet_4Momentum", &UcPFJet_4Momentum, &b_UcPFJet_4Momentum);
   fChain->SetBranchAddress("PFJet_Vposition", &PFJet_Vposition, &b_PFJet_Vposition);
   fChain->SetBranchAddress("PFJet_CEMF", &PFJet_CEMF, &b_PFJet_CEMF);
   fChain->SetBranchAddress("PFJet_NEMF", &PFJet_NEMF, &b_PFJet_NEMF);
   fChain->SetBranchAddress("PFJet_CHF", &PFJet_CHF, &b_PFJet_CHF);
   fChain->SetBranchAddress("PFJet_NHF", &PFJet_NHF, &b_PFJet_NHF);
   fChain->SetBranchAddress("PFJet_MUF", &PFJet_MUF, &b_PFJet_MUF);
   fChain->SetBranchAddress("PFJet_NumNeutralParticles", &PFJet_NumNeutralParticles, &b_PFJet_NumNeutralParticles);
   fChain->SetBranchAddress("PFJet_CHM", &PFJet_CHM, &b_PFJet_CHM);
   fChain->SetBranchAddress("PFJet_NumConst", &PFJet_NumConst, &b_PFJet_NumConst);
   fChain->SetBranchAddress("PFJet_jecUncer", &PFJet_jecUncer, &b_PFJet_jecUncer);
   fChain->SetBranchAddress("PFJet_jecCorr", &PFJet_jecCorr, &b_PFJet_jecCorr);
   Notify();
}

Bool_t ana::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ana::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ana::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ana_cxx
