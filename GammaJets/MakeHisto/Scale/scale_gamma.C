#define scale_gamma_cxx
#include "scale_gamma.h"
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
      scale_gamma t(argv[1], argv[2]);
      t.Loop();
    }
  return 0;
}

using namespace std;

void scale_gamma::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
        evt_wgt = IDSF*nvsf*kFactor;
        nvertex->Fill(nvtx,evt_wgt);
        Photon_pt->Fill(photon_pt,evt_wgt);
        Photon_eta->Fill(photon_eta,evt_wgt);
        Photon_phi->Fill(photon_phi,evt_wgt);
        Photon_energy->Fill(photon_energy,evt_wgt);
        MET_pt->Fill(met,evt_wgt);
        MET_pt_JetEnUp->Fill(met_JetEnUp,evt_wgt);
        MET_pt_JetEnDown->Fill(met_JetEnDown,evt_wgt);
        MET_pt_JetResUp->Fill(met_JetResUp,evt_wgt);
        MET_pt_JetResDown->Fill(met_JetResDown,evt_wgt);
        MET_pt_UnclusteredEnUp->Fill(met_UnclusteredEnUp,evt_wgt);
        MET_pt_UnclusteredEnDown->Fill(met_UnclusteredEnDown,evt_wgt);
        MET_phi->Fill(met_phi,evt_wgt);
        CorrMET_pt->Fill(corrmet,evt_wgt);
	CorrMET_pt_JetEnUp->Fill(corrmet_JetEnUp,evt_wgt);
        CorrMET_pt_JetEnDown->Fill(corrmet_JetEnDown,evt_wgt);
        CorrMET_pt_JetResUp->Fill(corrmet_JetResUp,evt_wgt);
        CorrMET_pt_JetResDown->Fill(corrmet_JetResDown,evt_wgt);
        CorrMET_pt_UnclusteredEnUp->Fill(corrmet_UnclusteredEnUp,evt_wgt);
        CorrMET_pt_UnclusteredEnDown->Fill(corrmet_UnclusteredEnDown,evt_wgt);
        CorrMET_phi->Fill(corrmet_phi,evt_wgt);
        uPara->Fill(uparallel+photon_pt,evt_wgt);
        uPara_JetEnUp->Fill(uparallel_JetEnUp+photon_pt,evt_wgt);
        uPara_JetEnDown->Fill(uparallel_JetEnDown+photon_pt,evt_wgt);
        uPara_JetResUp->Fill(uparallel_JetResUp+photon_pt,evt_wgt);
        uPara_JetResDown->Fill(uparallel_JetResDown+photon_pt,evt_wgt);
        uPara_UnclusteredEnUp->Fill(uparallel_UnclusteredEnUp+photon_pt,evt_wgt);
        uPara_UnclusteredEnDown->Fill(uparallel_UnclusteredEnDown+photon_pt,evt_wgt);
        uPerp->Fill(uperpendicular,evt_wgt);
        uPerp_JetEnUp->Fill(uperpendicular_JetEnUp,evt_wgt);
        uPerp_JetEnDown->Fill(uperpendicular_JetEnDown,evt_wgt);
        uPerp_JetResUp->Fill(uperpendicular_JetResUp,evt_wgt);
        uPerp_JetResDown->Fill(uperpendicular_JetResDown,evt_wgt);
        uPerp_UnclusteredEnUp->Fill(uperpendicular_UnclusteredEnUp,evt_wgt);
        uPerp_UnclusteredEnDown->Fill(uperpendicular_UnclusteredEnDown,evt_wgt);
        Jet_pt->Fill(jet_pt,evt_wgt);
        Jet_eta->Fill(jet_eta,evt_wgt);
        Jet_phi->Fill(jet_phi,evt_wgt);
        if(photon_pt > 50 && photon_pt <= 60) upara50->Fill(uparallel/photon_pt,evt_wgt);
        else if(photon_pt > 60 && photon_pt <= 80) upara60->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 80 && photon_pt <= 90) upara80->Fill(uparallel/photon_pt,evt_wgt);
        else if(photon_pt > 90 && photon_pt <= 100) upara90->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 100 && photon_pt <= 110) upara100->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 110 && photon_pt <= 130) upara110->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 130 && photon_pt <= 150) upara130->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 150 && photon_pt <= 175) upara150->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 175 && photon_pt <= 200) upara175->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 200 && photon_pt <= 225) upara200->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 225 && photon_pt <= 250) upara225->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 250 && photon_pt <= 275) upara250->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 275 && photon_pt <= 305) upara275->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 305 && photon_pt <= 335) upara305->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 335 && photon_pt <= 365) upara335->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 365 && photon_pt <= 400) upara365->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 400 && photon_pt <= 440) upara400->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 440 && photon_pt <= 500) upara440->Fill(uparallel/photon_pt,evt_wgt);
	else if(photon_pt > 500) upara500->Fill(uparallel/photon_pt,evt_wgt);
   }
}

void scale_gamma::BookHistos(const char* file2){
        fileName = new TFile(file2, "RECREATE");
        fileName->cd();

	char name[100];

        sprintf(name, "nvertex");
        nvertex = new TH1F (name,"nvertex", 80, 0, 80);
	nvertex->Sumw2();

        sprintf(name, "Photon_pt");
        Photon_pt = new TH1F (name,"gamma pt", 40, 50, 850);
        Photon_pt->Sumw2();

        sprintf(name, "Photon_eta");
        Photon_eta = new TH1F (name,"gamma eta", 40, -1.5, 1.5);
        Photon_eta->Sumw2();

        sprintf(name, "Photon_phi");
        Photon_phi = new TH1F (name,"gamma phi", 40, -M_PI, M_PI);
        Photon_phi->Sumw2();

        sprintf(name, "Photon_energy");
        Photon_energy = new TH1F (name,"gamma energy", 40, 50, 1050);
        Photon_energy->Sumw2();

        sprintf(name, "MET_pt");
	Float_t binb[] = {0,10,20,30,40,50,65,80,100,125,150,200,300};
        Int_t  binnum = 12;
        MET_pt = new TH1F (name,"MET pt", binnum, binb);
        MET_pt->Sumw2();

        sprintf(name, "MET_pt_JetEnUp");
        MET_pt_JetEnUp = new TH1F (name,"MET pt JetEnUP", binnum, binb);
        MET_pt_JetEnUp->Sumw2();

        sprintf(name, "MET_pt_JetEnDown");
        MET_pt_JetEnDown = new TH1F (name,"MET pt JetEnDown", binnum, binb);
        MET_pt_JetEnDown->Sumw2();

        sprintf(name, "MET_pt_JetResUp");
        MET_pt_JetResUp = new TH1F (name,"MET pt JetResUP", binnum, binb);
        MET_pt_JetResUp->Sumw2();

        sprintf(name, "MET_pt_JetResDown");
        MET_pt_JetResDown = new TH1F (name,"MET pt JetResDown", binnum, binb);
        MET_pt_JetResDown->Sumw2();

        sprintf(name, "MET_pt_UnclusteredEnUp");
        MET_pt_UnclusteredEnUp = new TH1F (name,"MET pt UnclusteredEnUp", binnum, binb);
        MET_pt_UnclusteredEnUp->Sumw2();

        sprintf(name, "MET_pt_UnclusteredEnDown");
        MET_pt_UnclusteredEnDown = new TH1F (name,"MET pt UnclusteredEnDown", binnum, binb);
        MET_pt_UnclusteredEnDown->Sumw2();

	sprintf(name, "CorrMET_pt_JetEnUp");
        CorrMET_pt_JetEnUp = new TH1F (name,"CorrMET pt JetEnUP", binnum, binb);
        CorrMET_pt_JetEnUp->Sumw2();

        sprintf(name, "CorrMET_pt_JetEnDown");
        CorrMET_pt_JetEnDown = new TH1F (name,"CorrMET pt JetEnDown", binnum, binb);
        CorrMET_pt_JetEnDown->Sumw2();

        sprintf(name, "CorrMET_pt_JetResUp");
        CorrMET_pt_JetResUp = new TH1F (name,"CorrMET pt JetResUP", binnum, binb);
        CorrMET_pt_JetResUp->Sumw2();

        sprintf(name, "CorrMET_pt_JetResDown");
        CorrMET_pt_JetResDown = new TH1F (name,"CorrMET pt JetResDown", binnum, binb);
        CorrMET_pt_JetResDown->Sumw2();

        sprintf(name, "CorrMET_pt_UnclusteredEnUp");
        CorrMET_pt_UnclusteredEnUp = new TH1F (name,"CorrMET pt UnclusteredEnUp", binnum, binb);
        CorrMET_pt_UnclusteredEnUp->Sumw2();

        sprintf(name, "CorrMET_pt_UnclusteredEnDown");
        CorrMET_pt_UnclusteredEnDown = new TH1F (name,"CorrMET pt UnclusteredEnDown", binnum, binb);
        CorrMET_pt_UnclusteredEnDown->Sumw2();
	
        sprintf(name, "MET_phi");
        MET_phi = new TH1F (name,"MET phi", 40, -M_PI, M_PI);
        MET_phi->Sumw2();

        sprintf(name, "CorrMET_pt");
        CorrMET_pt = new TH1F (name,"corrected MET pt", binnum, binb);
        CorrMET_pt->Sumw2();

        sprintf(name, "CorrMET_phi");
        CorrMET_phi = new TH1F (name,"corrected MET phi", 40, -M_PI, M_PI);
        CorrMET_phi->Sumw2();

        sprintf(name, "uPara");
        uPara = new TH1F (name,"uPara", 40, -200, 200);
        uPara->Sumw2();

        sprintf(name, "uPara_JetEnUp");
        uPara_JetEnUp = new TH1F (name,"uPara JetEnUp", 40, -200, 200);
        uPara_JetEnUp->Sumw2();

        sprintf(name, "uPara_JetEnDown");
        uPara_JetEnDown = new TH1F (name,"uPara JetEnDown", 40, -200, 200);
        uPara_JetEnDown->Sumw2();

        sprintf(name, "uPara_JetResUp");
        uPara_JetResUp = new TH1F (name,"uPara JetResUp", 40, -200, 200);
        uPara_JetResUp->Sumw2();

        sprintf(name, "uPara_JetResDown");
        uPara_JetResDown = new TH1F (name,"uPara JetResDown", 40, -200, 200);
        uPara_JetResDown->Sumw2();

        sprintf(name, "uPara_UnclusteredEnUp");
        uPara_UnclusteredEnUp = new TH1F (name,"uPara UnclusteredEnUp", 40, -200, 200);
        uPara_UnclusteredEnUp->Sumw2();

        sprintf(name, "uPara_UnclusteredEnDown");
        uPara_UnclusteredEnDown = new TH1F (name,"uPara UnclusteredEnDown", 40, -200, 200);
        uPara_UnclusteredEnDown->Sumw2();

        sprintf(name, "uPerp");
        uPerp = new TH1F (name,"uperp", 40, -200, 200);
        uPerp->Sumw2();

        sprintf(name, "uPerp_JetEnUp");
        uPerp_JetEnUp = new TH1F (name,"uPerp JetEnUp", 40, -200, 200);
        uPerp_JetEnUp->Sumw2();
        
        sprintf(name, "uPerp_JetEnDown");
        uPerp_JetEnDown = new TH1F (name,"uPerp JetEnDown", 40, -200, 200);
        uPerp_JetEnDown->Sumw2();
        
        sprintf(name, "uPerp_JetResUp");
        uPerp_JetResUp = new TH1F (name,"uPerp JetResUp", 40, -200, 200);
        uPerp_JetResUp->Sumw2();

        sprintf(name, "uPerp_JetResDown");
        uPerp_JetResDown = new TH1F (name,"uPerp JetResDown", 40, -200, 200);
        uPerp_JetResDown->Sumw2();

        sprintf(name, "uPerp_UnclusteredEnUp");
        uPerp_UnclusteredEnUp = new TH1F (name,"uPerp UnclusteredEnUp", 40, -200, 200);
        uPerp_UnclusteredEnUp->Sumw2();

        sprintf(name, "uPerp_UnclusteredEnDown");
        uPerp_UnclusteredEnDown = new TH1F (name,"uPerp UnclusteredEnDown", 40, -200, 200);
        uPerp_UnclusteredEnDown->Sumw2();

        sprintf(name, "Jet_pt");
        Jet_pt = new TH1F (name,"jet pt", 40, 40, 2000);
        Jet_pt->Sumw2();

        sprintf(name, "Jet_eta");
        Jet_eta = new TH1F (name,"jet eta", 40, -2.5, 2.5);
        Jet_eta->Sumw2();

        sprintf(name, "Jet_phi");
        Jet_phi = new TH1F (name,"jet phi", 40, -M_PI, M_PI);
        Jet_phi->Sumw2();

	sprintf(name, "upara50");
	upara50 = new TH1F (name, "upara50", 200, -2.7, 0.7);
	upara50->Sumw2();

        sprintf(name, "upara60");
        upara60 = new TH1F (name, "upara60", 200, -2.7, 0.7);
	upara60->Sumw2();

        sprintf(name, "upara80");
        upara80 = new TH1F (name, "upara80", 200, -2.6, 0.6);
	upara80->Sumw2();

        sprintf(name, "upara90");
        upara90 = new TH1F (name, "upara90", 150, -2.4, 0.4);	
	upara90->Sumw2();

	sprintf(name, "upara100");
	upara100 = new TH1F (name, "upara100", 150, -2.2, 0.2);
	upara100->Sumw2();

	sprintf(name, "upara110");
	upara110 = new TH1F (name, "upara110", 150, -2.2, 0.2);
	upara110->Sumw2();

	sprintf(name, "upara130");
	upara130 = new TH1F (name, "upara130", 150, -1.9, -0.1);
	upara130->Sumw2();

	sprintf(name, "upara150");
	upara150 = new TH1F (name, "upara150", 150, -1.7, -0.3);
	upara150->Sumw2();

	sprintf(name, "upara175");
	upara175 = new TH1F (name, "upara175", 150, -1.6, -0.4);
	upara175->Sumw2();

	sprintf(name, "upara200");
	upara200 = new TH1F (name, "upara200", 150, -1.6, -0.4);
	upara200->Sumw2();

	sprintf(name, "upara225");
	upara225 = new TH1F (name, "upara225", 150, -1.6, -0.4);
	upara225->Sumw2();

	sprintf(name, "upara250");
	upara250 = new TH1F (name, "upara250", 100, -1.6, -0.4);
	upara250->Sumw2();

	sprintf(name, "upara275");
	upara275 = new TH1F (name, "upara275", 100, -1.5, -0.5);
	upara275->Sumw2();

	sprintf(name, "upara305");
	upara305 = new TH1F (name, "upara305", 100, -1.4, -0.6);
	upara305->Sumw2();

	sprintf(name, "upara335");
	upara335 = new TH1F (name, "upara335", 100, -1.4, -0.6);
	upara335->Sumw2();

	sprintf(name, "upara365");
	upara365 = new TH1F (name, "upara365", 100, -1.3, -0.7);
	upara365->Sumw2();

	sprintf(name, "upara400");
	upara400 = new TH1F (name, "upara400", 100, -1.4, -0.6);
	upara400->Sumw2();

	sprintf(name, "upara440");
	upara440 = new TH1F (name, "upara440", 100, -1.3, -0.7);
	upara440->Sumw2();

	sprintf(name, "upara500");
	upara500 = new TH1F (name, "upara500", 100, -1.3, -0.7);
	upara500->Sumw2();
}
