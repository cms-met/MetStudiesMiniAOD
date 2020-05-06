#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TH1F.h>

int main(){
TFile *g1 = TFile::Open("QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8.root");
TFile *g2 = TFile::Open("MyDataPileupHistogram2018.root");

TH1D *h1 = (TH1D*)g1->Get("nTrueInteractions");
TH1D *h2 = (TH1D*)g2->Get("pileup");

if (h1->Integral()!=0) h1->Scale(1/h1->Integral());
if (h2->Integral()!=0) h2->Scale(1/h2->Integral());

TH1F *weight = new TH1F("weight","weight",100,0,100);

for(int i = 1; i <= 100; i++){
        float num = h2->GetBinContent(i);
        float den = h1->GetBinContent(i);
        if(den > 0) weight->SetBinContent(i, num/den);
}

TFile* file = TFile::Open("weightFile_PU_QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8.root","RECREATE");
h1->Write();
h2->Write();
weight->Write();
file->Close();
delete weight;
delete file;
}
