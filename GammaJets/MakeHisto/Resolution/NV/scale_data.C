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
        if (nJet == 0) continue;
        photon_ptbin = std::max(1, std::min(histo->GetNbinsX(), histo->GetXaxis()->FindBin(photon_pt)));
        if(photon_pt > 500) photon_ptbin = std::max(1, std::min(histo->GetNbinsX(), histo->GetXaxis()->FindBin(510)));
        responseCorr = histo->GetBinContent(photon_ptbin);
        wgt = wgt*(1.0/responseCorr);
        if(nvtx > 1 && nvtx <= 6) { upara2->Fill(uparallel+photon_pt,wgt); uperp2->Fill(uperpendicular,wgt); }
        else if(nvtx > 6 && nvtx <= 10) { upara6->Fill(uparallel+photon_pt,wgt); uperp6->Fill(uperpendicular,wgt); }
        else if(nvtx > 10 && nvtx <= 14) { upara10->Fill(uparallel+photon_pt,wgt); uperp10->Fill(uperpendicular,wgt); }
        else if(nvtx > 14 && nvtx <= 18) { upara14->Fill(uparallel+photon_pt,wgt); uperp14->Fill(uperpendicular,wgt); }
        else if(nvtx > 18 && nvtx <= 22) { upara18->Fill(uparallel+photon_pt,wgt); uperp18->Fill(uperpendicular,wgt); }
        else if(nvtx > 22 && nvtx <= 26) { upara22->Fill(uparallel+photon_pt,wgt); uperp22->Fill(uperpendicular,wgt); }
        else if(nvtx > 26 && nvtx <= 30) { upara26->Fill(uparallel+photon_pt,wgt); uperp26->Fill(uperpendicular,wgt); }
        else if(nvtx > 30 && nvtx <= 34) { upara30->Fill(uparallel+photon_pt,wgt); uperp30->Fill(uperpendicular,wgt); }
        else if(nvtx > 34 && nvtx <= 38) { upara34->Fill(uparallel+photon_pt,wgt); uperp34->Fill(uperpendicular,wgt); }
        else if(nvtx > 38 && nvtx <= 42) { upara38->Fill(uparallel+photon_pt,wgt); uperp38->Fill(uperpendicular,wgt); }
        else if(nvtx > 42 && nvtx <= 46) { upara42->Fill(uparallel+photon_pt,wgt); uperp42->Fill(uperpendicular,wgt); }
        else if(nvtx > 46 && nvtx <= 50) { upara46->Fill(uparallel+photon_pt,wgt); uperp46->Fill(uperpendicular,wgt); }
        else if(nvtx > 50 && nvtx <= 54) { upara50->Fill(uparallel+photon_pt,wgt); uperp50->Fill(uperpendicular,wgt); }
        else if(nvtx > 54 && nvtx <= 58) { upara54->Fill(uparallel+photon_pt,wgt); uperp54->Fill(uperpendicular,wgt); }
        else if(nvtx > 58) { upara58->Fill(uparallel+photon_pt,wgt); uperp58->Fill(uperpendicular,wgt); }

   }
}

void scale_data::BookHistos(const char* file2){
        fileName = new TFile(file2, "RECREATE");
        fileName->cd();

	char name[100];

        sprintf(name, "upara2");
        upara2 = new TH1F (name, "upara2", 300, -80., 80.);

        sprintf(name, "upara6");
        upara6 = new TH1F (name, "upara6", 300, -80., 80.);

        sprintf(name, "upara10");
        upara10 = new TH1F (name, "upara10", 300, -80., 80.);

        sprintf(name, "upara14");
        upara14 = new TH1F (name, "upara14", 300, -80., 80.);

        sprintf(name, "upara18");
        upara18 = new TH1F (name, "upara18", 300, -80., 80.);

        sprintf(name, "upara22");
        upara22 = new TH1F (name, "upara22", 300, -80., 80.);

        sprintf(name, "upara26");
        upara26 = new TH1F (name, "upara26", 300, -80., 80.);

        sprintf(name, "upara30");
        upara30 = new TH1F (name, "upara30", 300, -80., 80.);

        sprintf(name, "upara34");
        upara34 = new TH1F (name, "upara34", 300, -80., 80.);

        sprintf(name, "upara38");
        upara38 = new TH1F (name, "upara38", 300, -80., 80.);

        sprintf(name, "upara42");
        upara42 = new TH1F (name, "upara42", 300, -80., 80.);

        sprintf(name, "upara46");
        upara46 = new TH1F (name, "upara46", 300, -80., 80.);

        sprintf(name, "upara50");
        upara50 = new TH1F (name, "upara50", 300, -80., 80.);

        sprintf(name, "upara54");
        upara54 = new TH1F (name, "upara54", 300, -80., 80.);

        sprintf(name, "upara58");
        upara58 = new TH1F (name, "upara58", 300, -80., 80.);

        sprintf(name, "uperp2");
        uperp2 = new TH1F (name, "uperp2", 300, -80., 80.);

        sprintf(name, "uperp6");
        uperp6 = new TH1F (name, "uperp6", 300, -80., 80.);

        sprintf(name, "uperp10");
        uperp10 = new TH1F (name, "uperp10", 300, -80., 80.);

        sprintf(name, "uperp14");
        uperp14 = new TH1F (name, "uperp14", 300, -80., 80.);

        sprintf(name, "uperp18");
        uperp18 = new TH1F (name, "uperp18", 300, -80., 80.);

        sprintf(name, "uperp22");
        uperp22 = new TH1F (name, "uperp22", 300, -80., 80.);

        sprintf(name, "uperp26");
        uperp26 = new TH1F (name, "uperp26", 300, -80., 80.);

        sprintf(name, "uperp30");
        uperp30 = new TH1F (name, "uperp30", 300, -80., 80.);

        sprintf(name, "uperp34");
        uperp34 = new TH1F (name, "uperp34", 300, -80., 80.);

        sprintf(name, "uperp38");
        uperp38 = new TH1F (name, "uperp38", 300, -80., 80.);

        sprintf(name, "uperp42");
        uperp42 = new TH1F (name, "uperp42", 300, -80., 80.);

        sprintf(name, "uperp46");
        uperp46 = new TH1F (name, "uperp46", 300, -80., 80.);

        sprintf(name, "uperp50");
        uperp50 = new TH1F (name, "uperp50", 300, -80., 80.);

        sprintf(name, "uperp54");
        uperp54 = new TH1F (name, "uperp54", 300, -80., 80.);

        sprintf(name, "uperp58");
        uperp58 = new TH1F (name, "uperp58", 300, -80., 80.);
}
