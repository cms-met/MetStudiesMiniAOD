#define scale_data_cxx
#include "scale_data.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{
  
  if(argc > 1)
    { 
      scale_data t(argv[1], argv[2]);
      t.Loop();
    }
  return 0;
}

using namespace std;

void scale_data::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   int photon_ptbin; double responseCorr;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
        if(nJet == 0) continue;
        photon_ptbin = std::max(1, std::min(histo->GetNbinsX(), histo->GetXaxis()->FindBin(photon_pt)));
	if(photon_pt > 500) photon_ptbin = std::max(1, std::min(histo->GetNbinsX(), histo->GetXaxis()->FindBin(510)));
	responseCorr = histo->GetBinContent(photon_ptbin);
	wgt = wgt*(1.0/responseCorr);
        if(photon_pt > 50 && photon_pt <= 60) { upara50->Fill(uparallel+photon_pt,wgt); uperp50->Fill(uperpendicular,wgt); }
        else if(photon_pt > 60 && photon_pt <= 80) { upara60->Fill(uparallel+photon_pt,wgt); uperp60->Fill(uperpendicular,wgt); }
        else if(photon_pt > 80 && photon_pt <= 90) { upara80->Fill(uparallel+photon_pt,wgt); uperp80->Fill(uperpendicular,wgt); }
        else if(photon_pt > 90 && photon_pt <= 100) { upara90->Fill(uparallel+photon_pt,wgt); uperp90->Fill(uperpendicular,wgt); }
        else if(photon_pt > 100 && photon_pt <= 110) { upara100->Fill(uparallel+photon_pt,wgt); uperp100->Fill(uperpendicular,wgt); }
	else if(photon_pt > 110 && photon_pt <= 130) { upara110->Fill(uparallel+photon_pt,wgt); uperp110->Fill(uperpendicular,wgt); }
	else if(photon_pt > 130 && photon_pt <= 140) { upara130->Fill(uparallel+photon_pt,wgt); uperp130->Fill(uperpendicular,wgt); }
        else if(photon_pt > 140 && photon_pt <= 160) { upara140->Fill(uparallel+photon_pt,wgt); uperp140->Fill(uperpendicular,wgt); }
	else if(photon_pt > 160 && photon_pt <= 180) { upara160->Fill(uparallel+photon_pt,wgt); uperp160->Fill(uperpendicular,wgt); }
        else if(photon_pt > 180 && photon_pt <= 200) { upara180->Fill(uparallel+photon_pt,wgt); uperp180->Fill(uperpendicular,wgt); }
        else if(photon_pt > 200 && photon_pt <= 240) { upara200->Fill(uparallel+photon_pt,wgt); uperp200->Fill(uperpendicular,wgt); }
        else if(photon_pt > 240 && photon_pt <= 320) { upara240->Fill(uparallel+photon_pt,wgt); uperp240->Fill(uperpendicular,wgt); }
        else if(photon_pt > 320 && photon_pt <= 400) { upara320->Fill(uparallel+photon_pt,wgt); uperp320->Fill(uperpendicular,wgt); }
        else if(photon_pt > 400) { upara400->Fill(uparallel+photon_pt,wgt); uperp400->Fill(uperpendicular,wgt); }

   }
}

void scale_data::BookHistos(const char* file2){
        fileName = new TFile(file2, "RECREATE");
        fileName->cd();

	char name[100];

        sprintf(name, "upara50");
        upara50 = new TH1F (name, "upara50", 300, -80., 80.);

        sprintf(name, "upara60");
        upara60 = new TH1F (name, "upara60", 300, -80., 80.);

        sprintf(name, "upara80");
        upara80 = new TH1F (name, "upara80", 300, -80., 80.);

        sprintf(name, "upara90");
        upara90 = new TH1F (name, "upara90", 300, -80., 80.);

        sprintf(name, "upara100");
        upara100 = new TH1F (name, "upara100", 300, -80., 80.);

        sprintf(name, "upara110");
        upara110 = new TH1F (name, "upara110", 300, -80., 80.);

        sprintf(name, "upara130");
        upara130 = new TH1F (name, "upara130", 300, -80., 80.);

        sprintf(name, "upara140");
        upara140 = new TH1F (name, "upara140", 300, -80., 80.);

        sprintf(name, "upara160");
        upara160 = new TH1F (name, "upara160", 300, -80., 80.);

        sprintf(name, "upara180");
        upara180 = new TH1F (name, "upara180", 300, -80., 80.);

        sprintf(name, "upara200");
        upara200 = new TH1F (name, "upara200", 300, -80., 80.);

        sprintf(name, "upara240");
        upara240 = new TH1F (name, "upara240", 300, -80., 80.);

        sprintf(name, "upara320");
        upara320 = new TH1F (name, "upara320", 300, -80., 80.);

        sprintf(name, "upara400");
        upara400 = new TH1F (name, "upara400", 300, -80., 80.);

        sprintf(name, "uperp50");
        uperp50 = new TH1F (name, "uperp50", 300, -80., 80.);

        sprintf(name, "uperp60");
        uperp60 = new TH1F (name, "uperp60", 300, -80., 80.);

        sprintf(name, "uperp80");
        uperp80 = new TH1F (name, "uperp80", 300, -80., 80.);

        sprintf(name, "uperp90");
        uperp90 = new TH1F (name, "uperp90", 300, -80., 80.);

        sprintf(name, "uperp100");
        uperp100 = new TH1F (name, "uperp100", 300, -80., 80.);

        sprintf(name, "uperp110");
        uperp110 = new TH1F (name, "uperp110", 300, -80., 80.);

        sprintf(name, "uperp130");
        uperp130 = new TH1F (name, "uperp130", 300, -80., 80.);

        sprintf(name, "uperp140");
        uperp140 = new TH1F (name, "uperp140", 300, -80., 80.);

        sprintf(name, "uperp160");
        uperp160 = new TH1F (name, "uperp160", 300, -80., 80.);

        sprintf(name, "uperp180");
        uperp180 = new TH1F (name, "uperp180", 300, -80., 80.);

        sprintf(name, "uperp200");
        uperp200 = new TH1F (name, "uperp200", 300, -80., 80.);

        sprintf(name, "uperp240");
        uperp240 = new TH1F (name, "uperp240", 300, -80., 80.);

        sprintf(name, "uperp320");
        uperp320 = new TH1F (name, "uperp320", 300, -80., 80.);

        sprintf(name, "uperp400");
        uperp400 = new TH1F (name, "uperp400", 300, -80., 80.);
}
