#define PUinfo_cxx
#include "PUinfo.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

int main(int argc, char *argv[])
{
  
  if(argc > 1)
    { 
      PUinfo t(argv[1], argv[2]);
      t.Loop();
    }
  return 0;
}

using namespace std;
void PUinfo::Loop()
{
	if (fChain == 0) return;
	
	Long64_t nentries = fChain->GetEntriesFast();
	
	Long64_t nbytes = 0, nb = 0;

        string photon1("HLT_Photon30_R9Id90_HE10_IsoM_v"), photon2("HLT_Photon50_R9Id90_HE10_IsoM_v"), photon3("HLT_Photon75_R9Id90_HE10_IsoM_v"), photon4("HLT_Photon90_R9Id90_HE10_IsoM_v"), photon5("HLT_Photon120_R9Id90_HE10_IsoM_v"), photon6("HLT_Photon165_R9Id90_HE10_IsoM_v");
        size_t found1, found2, found3, found4, found5, found6;
        bool tr30, tr50, tr75, tr90, tr120, tr165;
        int ps30, ps50, ps75, ps90, ps120, ps165, prescale;

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;

        	tr30 = false; tr50 = false; tr75 = false; tr90 = false; tr120 = false; tr165 = false;
        	ps30 = 0; ps50 = 0; ps75 = 0; ps90 = 0; ps120 = 0; ps165 = 0; prescale = 0;

        	for(unsigned int t = 0; t < all_ifTriggerpassed->size(); t++){
        	        found1 = (*all_triggernames)[t].find(photon1);
        	        found2 = (*all_triggernames)[t].find(photon2);
        	        found3 = (*all_triggernames)[t].find(photon3);
        	        found4 = (*all_triggernames)[t].find(photon4);
        	        found5 = (*all_triggernames)[t].find(photon5);
        	        found6 = (*all_triggernames)[t].find(photon6);
        	        if(found1 != string::npos){ tr30 = (*all_ifTriggerpassed)[t]; ps30 = (*all_triggerprescales)[t];}
        	        if(found2 != string::npos){ tr50 = (*all_ifTriggerpassed)[t]; ps50 = (*all_triggerprescales)[t];}
        	        if(found3 != string::npos){ tr75 = (*all_ifTriggerpassed)[t]; ps75 = (*all_triggerprescales)[t];}
        	        if(found4 != string::npos){ tr90 = (*all_ifTriggerpassed)[t]; ps90 = (*all_triggerprescales)[t];}
        	        if(found5 != string::npos){ tr120 = (*all_ifTriggerpassed)[t]; ps120 = (*all_triggerprescales)[t];}
        	        if(found6 != string::npos){ tr165 = (*all_ifTriggerpassed)[t]; ps165 = (*all_triggerprescales)[t];}
        	}
        	
        	if(Photon_n > 0){
        	        TLorentzVector* q = (TLorentzVector*) (*Photon_4Momentum_corr)[0];
        	        if(q->Pt() < 80 && tr50) prescale = ps50;
        	        else if(q->Pt() >= 80 && q->Pt() < 95 && tr75) prescale = ps75;
        	        else if(q->Pt() >= 95 && q->Pt() < 130 && tr90) prescale = ps90;
        	        else if(q->Pt() >= 130 && q->Pt() < 175 && tr120) prescale = ps120;
        	        else if(q->Pt() >= 175 && tr165) prescale = ps165;
        	        else prescale = 0;
        	}
        	
        	float nVert = 0; 
        	for(int i = 0; i < Vertex_n; i++){
        	        TVector3* vtx = (TVector3*) (*Vertex_position)[i];
        	        if(!(*Vertex_isFake)[i] && (*Vertex_ndof)[i] > 4 && abs(vtx->z()) <= 24. && abs((*Vertex_d0)[i]) <= 2.) nVert++;
        	}
        	nVertices->Fill(nVert,prescale);
	}
}

void PUinfo::BookHistos(const char* file2){
  fileName = new TFile(file2, "RECREATE");
  fileName->cd();
  char name[100];

        sprintf(name, "nVertices");
        nVertices = new TH1F (name,"nVertices", 100, 0, 100);
        nVertices->GetXaxis()->SetTitle("N_{vertex}");

}
