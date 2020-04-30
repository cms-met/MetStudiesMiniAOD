#ifndef PUinfo_h
#define PUinfo_h

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

class PUinfo {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   TFile *fileName;
   TH1F *nVertices, *nTrueInteractions, *nPUInteractions;

   vector<string>  *all_triggernames;
   vector<int>     *all_triggerprescales;
   vector<bool>    *all_ifTriggerpassed;
   Int_t           Event_n;
   Int_t           ootnpuVertices;
   Int_t           npuVertices;
   Int_t           npuVerticesm1;
   Int_t           npuVerticesp1;
   Float_t         trueInteractions;
   Int_t           Vertex_n;
   vector<float>   *Vertex_chi2;
   vector<float>   *Vertex_d0;
   vector<int>     *Vertex_tracksize;
   vector<int>     *Vertex_ndof;
   vector<bool>    *Vertex_isFake;
   TClonesArray    *Vertex_position;
   Int_t           Photon_n;
   TClonesArray    *Photon_4Momentum;
   TClonesArray    *Photon_4Momentum_corr;

   TBranch        *b_all_triggernames;   //!
   TBranch        *b_all_triggerprescales;   //!
   TBranch        *b_all_ifTriggerpassed;   //!
   TBranch        *b_ootnpuVertices;   //!
   TBranch        *b_npuVertices;   //!
   TBranch        *b_npuVerticesm1;   //!
   TBranch        *b_npuVerticesp1;   //!
   TBranch        *b_trueInteractions;   //!
   TBranch        *b_Vertex_n;   //!
   TBranch        *b_Vertex_chi2;   //!
   TBranch        *b_Vertex_d0;   //!
   TBranch        *b_Vertex_tracksize;   //!
   TBranch        *b_Vertex_ndof;   //!
   TBranch        *b_Vertex_isFake;   //!
   TBranch        *b_Vertex_position;   //!
   TBranch        *b_Photon_n;   //!
   TBranch        *b_Photon_4Momentum;   //!
   TBranch        *b_Photon_4Momentum_corr;   //!

   PUinfo(string fileToOpen, const char* file2);
   virtual ~PUinfo();
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

#ifdef PUinfo_cxx
PUinfo::PUinfo(string fileToOpen, const char* file2)
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

  //TString path = "/home/pdas/t3store2/Summer16_validation/";
  //TString fullpath = (path+dir1);

  //TSystemDirectory sourceDir("hi",fullpath);
  //TList* fileList = sourceDir.GetListOfFiles();
  //TIter next(fileList);
  //TSystemFile* filename;
  //int fileNumber = 0;
  //int maxFiles = -1;
  //while ((filename = (TSystemFile*)next()) && fileNumber >  maxFiles){
  //  if(fileNumber > 1)
  //    {
  //      TString  FullPathInputFile = (fullpath+filename->GetName());
  //      std::cout<<FullPathInputFile<<std::endl;
  //      chain->Add(FullPathInputFile);
  //      std::cout<<chain->GetEntries()<<std::endl;
  //    }
  //  fileNumber++;
  //}//loop over while

   Init(chain);
}

PUinfo::~PUinfo()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
   fileName->cd();
   fileName->Write();
   fileName->Close();
}

Int_t PUinfo::GetEntry(Long64_t entry)
{
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PUinfo::LoadTree(Long64_t entry)
{
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}
void PUinfo::Init(TTree *tree)
{

   all_triggernames = 0;
   all_triggerprescales = 0;
   all_ifTriggerpassed = 0;
   Vertex_chi2 = 0;
   Vertex_d0 = 0;
   Vertex_tracksize = 0;
   Vertex_ndof = 0;
   Vertex_isFake = 0;
   Vertex_position = 0;
   Photon_4Momentum = 0;
   Photon_4Momentum_corr = 0;

   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("all_triggernames", &all_triggernames, &b_all_triggernames);
   fChain->SetBranchAddress("all_triggerprescales", &all_triggerprescales, &b_all_triggerprescales);
   fChain->SetBranchAddress("all_ifTriggerpassed", &all_ifTriggerpassed, &b_all_ifTriggerpassed);
   fChain->SetBranchAddress("ootnpuVertices", &ootnpuVertices, &b_ootnpuVertices);
   fChain->SetBranchAddress("npuVertices", &npuVertices, &b_npuVertices);
   fChain->SetBranchAddress("npuVerticesm1", &npuVerticesm1, &b_npuVerticesm1);
   fChain->SetBranchAddress("npuVerticesp1", &npuVerticesp1, &b_npuVerticesp1);
   fChain->SetBranchAddress("trueInteractions", &trueInteractions, &b_trueInteractions);
   fChain->SetBranchAddress("Vertex_n", &Vertex_n, &b_Vertex_n);
   fChain->SetBranchAddress("Vertex_chi2", &Vertex_chi2, &b_Vertex_chi2);
   fChain->SetBranchAddress("Vertex_d0", &Vertex_d0, &b_Vertex_d0);
   fChain->SetBranchAddress("Vertex_tracksize", &Vertex_tracksize, &b_Vertex_tracksize);
   fChain->SetBranchAddress("Vertex_ndof", &Vertex_ndof, &b_Vertex_ndof);
   fChain->SetBranchAddress("Vertex_isFake", &Vertex_isFake, &b_Vertex_isFake);
   fChain->SetBranchAddress("Vertex_position", &Vertex_position, &b_Vertex_position);
   fChain->SetBranchAddress("Photon_n", &Photon_n, &b_Photon_n);
   fChain->SetBranchAddress("Photon_4Momentum", &Photon_4Momentum, &b_Photon_4Momentum);
   fChain->SetBranchAddress("Photon_4Momentum_corr", &Photon_4Momentum_corr, &b_Photon_4Momentum_corr);

   Notify();
}

Bool_t PUinfo::Notify()
{
   return kTRUE;
}

void PUinfo::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PUinfo::Cut(Long64_t entry)
{ 
   return 1;
}
#endif // #ifdef PUinfo_cxx

