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
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
        nvertex->Fill(nvtx,wgt);
        Photon_pt_unp->Fill(photon_pt);
        Photon_pt->Fill(photon_pt,wgt);
	Photon_eta->Fill(photon_eta,wgt);
	Photon_phi->Fill(photon_phi,wgt);
        Photon_energy->Fill(photon_energy,wgt);
	MET_pt->Fill(met,wgt);
        MET_phi->Fill(met_phi,wgt);
        CorrMET_pt->Fill(corrmet,wgt);
        CorrMET_phi->Fill(corrmet_phi,wgt);
	uPara->Fill(uparallel+photon_pt,wgt);
	uPerp->Fill(uperpendicular,wgt);
	Jet_pt->Fill(jet_pt,wgt);
	Jet_eta->Fill(jet_eta,wgt);
        Jet_phi->Fill(jet_phi,wgt);
	if(photon_pt > 50 && photon_pt <= 60) upara50->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 60 && photon_pt <= 70) upara60->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 70 && photon_pt <= 80) upara70->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 80 && photon_pt <= 90) upara80->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 90 && photon_pt <= 100) upara90->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 100 && photon_pt <= 110) upara100->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 110 && photon_pt <= 130) upara110->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 130 && photon_pt <= 150) upara130->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 150 && photon_pt <= 175) upara150->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 175 && photon_pt <= 200) upara175->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 200 && photon_pt <= 225) upara200->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 225 && photon_pt <= 250) upara225->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 250 && photon_pt <= 275) upara250->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 275 && photon_pt <= 305) upara275->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 305 && photon_pt <= 335) upara305->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 335 && photon_pt <= 365) upara335->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 365 && photon_pt <= 400) upara365->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 400 && photon_pt <= 440) upara400->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 440 && photon_pt <= 500) upara440->Fill(uparallel/photon_pt,wgt);
	else if(photon_pt > 500) upara500->Fill(uparallel/photon_pt,wgt);

//For XY-corrected MET
	if(photon_pt > 50 && photon_pt <= 60) corrupara50->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 60 && photon_pt <= 70) corrupara60->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 70 && photon_pt <= 80) corrupara70->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 80 && photon_pt <= 90) corrupara80->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 90 && photon_pt <= 100) corrupara90->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 100 && photon_pt <= 110) corrupara100->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 110 && photon_pt <= 130) corrupara110->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 130 && photon_pt <= 150) corrupara130->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 150 && photon_pt <= 175) corrupara150->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 175 && photon_pt <= 200) corrupara175->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 200 && photon_pt <= 225) corrupara200->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 225 && photon_pt <= 250) corrupara225->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 250 && photon_pt <= 275) corrupara250->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 275 && photon_pt <= 305) corrupara275->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 305 && photon_pt <= 335) corrupara305->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 335 && photon_pt <= 365) corrupara335->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 365 && photon_pt <= 400) corrupara365->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 400 && photon_pt <= 440) corrupara400->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 440 && photon_pt <= 500) corrupara440->Fill(corrupara/photon_pt,wgt);
	else if(photon_pt > 500) corrupara500->Fill(corrupara/photon_pt,wgt);
	}
   }
}

void scale_data::BookHistos(const char* file2){
        fileName = new TFile(file2, "RECREATE");
        fileName->cd();

	char name[100];

        sprintf(name, "nvertex");
	nvertex = new TH1F (name,"nvertex", 80, 0, 80);
	nvertex->Sumw2();

        sprintf(name, "Photon_pt_unp");
        Photon_pt_unp = new TH1F (name,"gamma pt unprescaled", 40, 50, 850);
	Photon_pt_unp->Sumw2();

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
	Float_t binb[] = { 0,10,20,30,40,50,65,80,100,125,150,200,300 };
	Int_t  binnum = 12;
        MET_pt = new TH1F (name,"MET pt", binnum, binb);
        MET_pt->Sumw2();

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

	sprintf(name, "uPerp");
	uPerp = new TH1F (name,"uperp", 40, -200, 200);
	uPerp->Sumw2();

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

	sprintf(name, "upara70");
        upara70 = new TH1F (name, "upara70", 200, -2.7, 0.7);
        upara70->Sumw2();

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

	sprintf(name, "corrupara50");
	corrupara50 = new TH1F (name, "corrupara50", 200, -2.7, 0.7);
	corrupara50->Sumw2();

	sprintf(name, "corrupara60");
	corrupara60 = new TH1F (name, "corrupara60", 200, -2.7, 0.7);
	corrupara60->Sumw2();

	sprintf(name, "corrupara70");
	corrupara70 = new TH1F (name, "corrupara70", 200, -2.7, 0.7);
	corrupara70->Sumw2();

	sprintf(name, "corrupara80");
	corrupara80 = new TH1F (name, "corrupara80", 200, -2.6, 0.6);
	corrupara80->Sumw2();

	sprintf(name, "corrupara90");
	corrupara90 = new TH1F (name, "corrupara90", 150, -2.4, 0.4);
	corrupara90->Sumw2();

	sprintf(name, "corrupara100");
	corrupara100 = new TH1F (name, "corrupara100", 150, -2.2, 0.2);
	corrupara100->Sumw2();

	sprintf(name, "corrupara110");
	corrupara110 = new TH1F (name, "corrupara110", 150, -2.2, 0.2);
	corrupara110->Sumw2();

	sprintf(name, "corrupara130");
	corrupara130 = new TH1F (name, "corrupara130", 150, -1.9, -0.1);
	corrupara130->Sumw2();

	sprintf(name, "corrupara150");
	corrupara150 = new TH1F (name, "corrupara150", 150, -1.7, -0.3);
	corrupara150->Sumw2();

	sprintf(name, "corrupara175");
	corrupara175 = new TH1F (name, "corrupara175", 150, -1.6, -0.4);
	corrupara175->Sumw2();

	sprintf(name, "corrupara200");
	corrupara200 = new TH1F (name, "corrupara200", 150, -1.6, -0.4);
	corrupara200->Sumw2();

	sprintf(name, "corrupara225");
	corrupara225 = new TH1F (name, "corrupara225", 150, -1.6, -0.4);
	corrupara225->Sumw2();

	sprintf(name, "corrupara250");
	corrupara250 = new TH1F (name, "corrupara250", 100, -1.6, -0.4);
	corrupara250->Sumw2();

	sprintf(name, "corrupara275");
	corrupara275 = new TH1F (name, "corrupara275", 100, -1.5, -0.5);
	corrupara275->Sumw2();

	sprintf(name, "corrupara305");
	corrupara305 = new TH1F (name, "corrupara305", 100, -1.4, -0.6);
	corrupara305->Sumw2();

	sprintf(name, "corrupara335");
	corrupara335 = new TH1F (name, "corrupara335", 100, -1.4, -0.6);
	corrupara335->Sumw2();

	sprintf(name, "corrupara365");
	corrupara365 = new TH1F (name, "corrupara365", 100, -1.3, -0.7);
	corrupara365->Sumw2();

	sprintf(name, "corrupara400");
	corrupara400 = new TH1F (name, "corrupara400", 100, -1.4, -0.6);
	corrupara400->Sumw2();

	sprintf(name, "corrupara440");
	corrupara440 = new TH1F (name, "corrupara440", 100, -1.3, -0.7);
	corrupara440->Sumw2();

	sprintf(name, "corrupara500");
	corrupara500 = new TH1F (name, "corrupara500", 100, -1.3, -0.7);
	corrupara500->Sumw2();
}
