#define ana_cxx
#include "ana.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "LepGood.h"
#include "XYMETCorrection.h"

std::pair<double,double> upara_uperp(double metx, double mety, double qx, double qy, double qt){
	double uX = - metx - qx;
	double uY = - mety - qy;
	double upara = (uX*qx + uY*qy)/qt;
	double uperp = (uX*qy - uY*qx)/qt;
	return {upara, uperp};
}

int main(int argc, char *argv[])
{

  if(argc > 1)
    {
      ana t(argv[1], argv[2]);
      t.Loop();
    }
  return 0;
}

using namespace std;

void ana::Loop()
{
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
        Long64_t nbytes = 0, nb = 0;
        string photon1("HLT_Photon30_R9Id90_HE10_IsoM_v"), photon2("HLT_Photon50_R9Id90_HE10_IsoM_v"), photon3("HLT_Photon75_R9Id90_HE10_IsoM_v"), photon4("HLT_Photon90_R9Id90_HE10_IsoM_v"), photon5("HLT_Photon120_R9Id90_HE10_IsoM_v"), photon6("HLT_Photon165_R9Id90_HE10_IsoM_v");
        size_t found1, found2, found3, found4, found5, found6;
        double upara, uperp, uX, uY, chIso_corrected, neIso_corrected, phIso_corrected, JEC_unc, jPt_up, jPt_down, genpt, kfactor, gammaSF; 
	int bin1, bin2, nJet40;
        vector<int> tight_photon; vector<bool> clean_jet;
        vector<LepGood> veto_collection, LepGood_coll; LepGood loose_lepton, loose_photon;
        bool tr30, tr50, tr75, tr90, tr120, tr165, pass;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
        upara = 0; uperp = 0; uX = 0; uY = 0; chIso_corrected = 0.0; neIso_corrected = 0.0; phIso_corrected = 0.0;
        tight_photon.clear(); clean_jet.clear();
        LepGood_coll.clear(); veto_collection.clear(); nJet40 = 0; nvtx = 0;
        tr30 = false; tr50 = false; tr75 = false; tr90 = false; tr120 = false; tr165 = false; pass = false;
	jet_pt = -9999; jet_eta = -9999; fail = false;
	bin1 = std::max(1, std::min(g2->GetNbinsX(), g2->GetXaxis()->FindBin((int)trueInteractions)));
        pusf = g2->GetBinContent(bin1);
//Trigger
	for(unsigned int t = 0; t < all_ifTriggerpassed->size(); t++){
                found1 = (*all_triggernames)[t].find(photon1);
                found2 = (*all_triggernames)[t].find(photon2);
                found3 = (*all_triggernames)[t].find(photon3);
                found4 = (*all_triggernames)[t].find(photon4);
                found5 = (*all_triggernames)[t].find(photon5);
                found6 = (*all_triggernames)[t].find(photon6);
                if(found1 != string::npos){ tr30 = (*all_ifTriggerpassed)[t]; }
                if(found2 != string::npos){ tr50 = (*all_ifTriggerpassed)[t]; }
                if(found3 != string::npos){ tr75 = (*all_ifTriggerpassed)[t]; }
                if(found4 != string::npos){ tr90 = (*all_ifTriggerpassed)[t]; }
                if(found5 != string::npos){ tr120 = (*all_ifTriggerpassed)[t]; }
                if(found6 != string::npos){ tr165 = (*all_ifTriggerpassed)[t]; }
        }
//Choose tight photons with Summer17 v2 id: https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2#Working_points_for_94X_and_later
        for(int i = 0; i < Photon_n; i++){
                TLorentzVector* q = (TLorentzVector*) (*Photon_4Momentum_corr)[i];
                if(abs(q->Eta()) < 1.0){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0112, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0668, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.1113, 0.0);
                }
                else if(abs(q->Eta()) < 1.479){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0108, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.1054, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.0953, 0.0);
                }
                else if(abs(q->Eta()) < 2.0){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0106, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0786, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.0619, 0.0);
                }
                else if(abs(q->Eta()) < 2.2){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.01002, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0233, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.0837, 0.0);
                }
                else if(abs(q->Eta()) < 2.3){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0098, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0078, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.1070, 0.0);
                }
                else if(abs(q->Eta()) < 2.4){
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0089, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0028, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.1212, 0.0);
                }
                else {
                        chIso_corrected = max((*Photon_chargedHadronIso)[i] - rho*0.0087, 0.0);
                        neIso_corrected = max((*Photon_neutralHadronIso)[i] - rho*0.0137, 0.0);
                        phIso_corrected = max((*Photon_photonIso)[i] - rho*0.1466, 0.0);
                }
                if(q->Pt() > 30 && abs(q->Eta()) < 1.479 && (*Photon_HoverE)[i] < 0.02148 && (*Photon_sigmaIetaIeta)[i] < 0.00996 && chIso_corrected < 0.65 && neIso_corrected < 0.317 + 0.01512*q->Pt() + 0.00002259*q->Pt()*q->Pt() && phIso_corrected < 2.044 + 0.004017*q->Pt()) tight_photon.push_back(i);
                if(q->Pt() > 30 && abs(q->Eta()) > 1.479 && abs(q->Eta()) < 2.5 && (*Photon_HoverE)[i] < 0.0321 && (*Photon_sigmaIetaIeta)[i] < 0.0271 && chIso_corrected < 0.517 && neIso_corrected < 2.716 + 0.0117*q->Pt() + 0.000023*q->Pt()*q->Pt() && phIso_corrected < 3.032 + 0.0037*q->Pt()) tight_photon.push_back(i);
        }
//Event selection
//Choose photon in barrel, add met filter requirements
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/MissingETOptionalFiltersRun2#2018_data
        if(tight_photon.size() == 1 && (*filter_goodVertices)[0] && (*filter_globalsupertighthalo2016)[0] && (*filter_hbher2t)[0] && (*filter_hbheiso)[0] && (*filter_ecaltp)[0] && (*filter_ecalBadCalib)[0] && (*filter_badPFMuon)[0]){
                for(int i = 0; i < Vertex_n; i++){
                        TVector3* vtx = (TVector3*) (*Vertex_position)[i];
                        if(!(*Vertex_isFake)[i] && (*Vertex_ndof)[i] > 4 && abs(vtx->z()) <= 24. && abs((*Vertex_d0)[i]) <= 2.) nvtx++;
                }
                for(int i = 0; i < Muon_n; i++){
                        TLorentzVector* mu = (TLorentzVector*) (*Muon_4Momentum)[i];
                        if((*Muon_idPreselection)[i] > 0.5){
                                loose_lepton.momentum = mu;
                                LepGood_coll.push_back(loose_lepton);
                        }
                }
                for(int i = 0; i < Electron_n; i++){
                        TLorentzVector* ele = (TLorentzVector*) (*Electron_4Momentum)[i];
                        int fail_ele = 0;
                        for (unsigned int k = 0; k < LepGood_coll.size(); k++){
                                if( (*LepGood_coll[k].momentum).DeltaR(*ele) < 0.05 ) fail_ele++;
                        }
                        if((*Electron_idPreselection)[i] > 0.5 && fail_ele == 0){
                                loose_lepton.momentum = ele;
                                LepGood_coll.push_back(loose_lepton);
                        }
                }
                for(int i = 0; i < PFJet_n; i++){
			TLorentzVector* j = (TLorentzVector*) (*PFJet_4Momentum)[i];
			JEC_unc = (*PFJet_jecUncer)[i];
			jPt_up = (j->Pt())*(1+JEC_unc); // up variation
			jPt_down = (j->Pt())*(1-JEC_unc); // down variation
			if((j->Pt() > 40) && (abs(j->Eta()) <= 2.4) && ((*PFJet_NHF)[i] < 0.90) && ((*PFJet_NEMF)[i] < 0.90) && ((*PFJet_NumConst)[i] > 1) && ((*PFJet_CHF)[i] > 0) && ((*PFJet_CHM)[i] > 0)){
				clean_jet.push_back((bool) true);
			}
			else clean_jet.push_back((bool) false); 
                }
//Select events using trigger
                TLorentzVector* q = (TLorentzVector*) (*Photon_4Momentum_corr)[tight_photon[0]];
                if(q->Pt() < 80 && tr50) pass = true;
                else if(q->Pt() >= 80 && q->Pt() < 95 && tr75) pass = true;
                else if(q->Pt() >= 95 && q->Pt() < 130 && tr90) pass = true;
                else if(q->Pt() >= 130 && q->Pt() < 175 && tr120) pass = true;
                else if(q->Pt() >= 175 && tr165) pass = true;
                for(int i = 0; i < PFJet_n; i++){
                        if(clean_jet[i]) nJet40++;
                }
                nJet = nJet40;
                if(PFJet_n > 0) {
                        TLorentzVector* jet = (TLorentzVector*) (*PFJet_4Momentum)[0];
                        if(q->DeltaR(*jet) < 0.5) fail = true;
                }
//Addtional quality criteria for photon, lepton veto
                if(pass && LepGood_coll.size() == 0 && q->Pt() > 50 && abs(q->Eta()) < 1.44 && (*Photon_r9)[tight_photon[0]] > 0.9 && (*Photon_r9)[tight_photon[0]] < 1.0 && !(*Photon_hasPixelSeed)[tight_photon[0]] && (*Photon_passElectronVeto)[tight_photon[0]]){
                        if(Gen_Photon_n > 0){ TLorentzVector* mc = (TLorentzVector*) (*Gen_Photon_4Momentum)[0]; genpt = mc->Pt();}
                        else genpt = 0;
                        if(kfactorfunction->Eval(genpt) > 0.) kfactor = kfactorfunction->Eval(genpt);
                        else kfactor = 1.;
			kFactor = kfactor; 
                        int etabin = std::max(1, std::min(h2->GetNbinsX(), h2->GetXaxis()->FindBin((*Photon_scEta)[0])));
                        int ptbin = std::max(1, std::min(h2->GetNbinsY(), h2->GetYaxis()->FindBin(q->Pt())));
                        gammaSF = h2->GetBinContent(etabin,ptbin);
                        uparallel = upara_uperp((*PFMetPx)[0], (*PFMetPy)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_JetEnUp = upara_uperp((*PFMetPx_JetEnUp)[0], (*PFMetPy_JetEnUp)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_JetEnDown = upara_uperp((*PFMetPx_JetEnDown)[0], (*PFMetPy_JetEnDown)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_JetResUp = upara_uperp((*PFMetPx_JetResUp)[0], (*PFMetPy_JetResUp)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_JetResDown = upara_uperp((*PFMetPx_JetResDown)[0], (*PFMetPy_JetResDown)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_UnclusteredEnUp = upara_uperp((*PFMetPx_UnclusteredEnUp)[0], (*PFMetPy_UnclusteredEnUp)[0], q->Px(), q->Py(), q->Pt()).first;
			uparallel_UnclusteredEnDown = upara_uperp((*PFMetPx_UnclusteredEnDown)[0], (*PFMetPy_UnclusteredEnDown)[0], q->Px(), q->Py(), q->Pt()).first;
			uperpendicular = upara_uperp((*PFMetPx)[0], (*PFMetPy)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_JetEnUp = upara_uperp((*PFMetPx_JetEnUp)[0], (*PFMetPy_JetEnUp)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_JetEnDown = upara_uperp((*PFMetPx_JetEnDown)[0], (*PFMetPy_JetEnDown)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_JetResUp = upara_uperp((*PFMetPx_JetResUp)[0], (*PFMetPy_JetResUp)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_JetResDown = upara_uperp((*PFMetPx_JetResDown)[0], (*PFMetPy_JetResDown)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_UnclusteredEnUp = upara_uperp((*PFMetPx_UnclusteredEnUp)[0], (*PFMetPy_UnclusteredEnUp)[0], q->Px(), q->Py(), q->Pt()).second;
                        uperpendicular_UnclusteredEnDown = upara_uperp((*PFMetPx_UnclusteredEnDown)[0], (*PFMetPy_UnclusteredEnDown)[0], q->Px(), q->Py(), q->Pt()).second;
                        photon_pt = q->Pt();
                        photon_eta = q->Eta();
                        photon_phi = q->Phi();
                        photon_energy = q->E();
                        met = (*PFMetPt)[0];
			met_JetEnUp = (*PFMetPt_JetEnUp)[0];
			met_JetEnDown = (*PFMetPt_JetEnDown)[0];
			met_JetResUp = (*PFMetPt_JetResUp)[0];
			met_JetResDown = (*PFMetPt_JetResDown)[0];
			met_UnclusteredEnUp = (*PFMetPt_UnclusteredEnUp)[0];
			met_UnclusteredEnDown = (*PFMetPt_UnclusteredEnDown)[0];
			met_phi = (*PFMetPhi)[0];
			corrmet = METXYCorr_Met_MetPhi(met, met_phi, RunNumber, 2018, true, Vertex_n).first;
                        corrmet_JetEnUp = METXYCorr_Met_MetPhi((*PFMetPt_JetEnUp)[0], (*PFMetPhi_JetEnUp)[0], RunNumber, 2018, true, Vertex_n).first;
                        corrmet_JetEnDown = METXYCorr_Met_MetPhi((*PFMetPt_JetEnDown)[0], (*PFMetPhi_JetEnDown)[0], RunNumber, 2018, true, Vertex_n).first;
                        corrmet_JetResUp = METXYCorr_Met_MetPhi((*PFMetPt_JetResUp)[0], (*PFMetPhi_JetResUp)[0], RunNumber, 2018, true, Vertex_n).first;
                        corrmet_JetResDown = METXYCorr_Met_MetPhi((*PFMetPt_JetResDown)[0], (*PFMetPhi_JetResDown)[0], RunNumber, 2018, true, Vertex_n).first;
                        corrmet_UnclusteredEnUp = METXYCorr_Met_MetPhi((*PFMetPt_UnclusteredEnUp)[0], (*PFMetPhi_UnclusteredEnUp)[0], RunNumber, 2018, true, Vertex_n).first;
                        corrmet_UnclusteredEnDown = METXYCorr_Met_MetPhi((*PFMetPt_UnclusteredEnDown)[0], (*PFMetPhi_UnclusteredEnDown)[0], RunNumber, 2018, true, Vertex_n).first;
			corrmet_phi = METXYCorr_Met_MetPhi(met, met_phi, RunNumber, 2018, true, Vertex_n).second;
			bin2 = std::max(1, std::min(g4->GetNbinsX(), g4->GetXaxis()->FindBin(nvtx)));
			nvsf = g4->GetBinContent(bin2);
			wgtA = gammaSF*(g6->GetBinContent(bin2));
                        wgtB = gammaSF*(g8->GetBinContent(bin2));
                        wgtC = gammaSF*(g10->GetBinContent(bin2));
                        wgtD = gammaSF*(g12->GetBinContent(bin2));
                        for(int i = 0; i < PFJet_n; i++){
                                if(clean_jet[i]){
                                	TLorentzVector* recjet = (TLorentzVector*) (*PFJet_4Momentum)[i];
                                	jet_pt = recjet->Pt();
                                	jet_eta = recjet->Eta();
					jet_phi = recjet->Phi();
                                	break;
                                }
                        }
			IDSF = gammaSF;
                        mettree->Fill();
                }
	} 
   }
}

void ana::BookHistos(const char* file2){
        fileName = new TFile(file2, "RECREATE");
        fileName->cd();
        char name[100];

        mettree = new TTree("mettree", "selected events");
        mettree->Branch("uparallel",&uparallel,"uparallel/F");
        mettree->Branch("uparallel_JetEnUp",&uparallel_JetEnUp,"uparallel_JetEnUp/F");
	mettree->Branch("uparallel_JetEnDown",&uparallel_JetEnDown,"uparallel_JetEnDown/F");
        mettree->Branch("uparallel_JetResUp",&uparallel_JetResUp,"uparallel_JetResUp/F");
        mettree->Branch("uparallel_JetResDown",&uparallel_JetResDown,"uparallel_JetResDown/F");
        mettree->Branch("uparallel_UnclusteredEnUp",&uparallel_UnclusteredEnUp,"uparallel_UnclusteredEnUp/F");
        mettree->Branch("uparallel_UnclusteredEnDown",&uparallel_UnclusteredEnDown,"uparallel_UnclusteredEnDown/F");
        mettree->Branch("uperpendicular",&uperpendicular,"uperpendicular/F");
        mettree->Branch("uperpendicular_JetEnUp",&uperpendicular_JetEnUp,"uperpendicular_JetEnUp/F");
        mettree->Branch("uperpendicular_JetEnDown",&uperpendicular_JetEnDown,"uperpendicular_JetEnDown/F");
        mettree->Branch("uperpendicular_JetResUp",&uperpendicular_JetResUp,"uperpendicular_JetResUp/F");
        mettree->Branch("uperpendicular_JetResDown",&uperpendicular_JetResDown,"uperpendicular_JetResDown/F");
        mettree->Branch("uperpendicular_UnclusteredEnUp",&uperpendicular_UnclusteredEnUp,"uperpendicular_UnclusteredEnUp/F");
        mettree->Branch("uperpendicular_UnclusteredEnDown",&uperpendicular_UnclusteredEnDown,"uperpendicular_UnclusteredEnDown/F");
        mettree->Branch("photon_pt",&photon_pt,"photon_pt/F");
	mettree->Branch("photon_eta",&photon_eta,"photon_eta/F");
        mettree->Branch("photon_phi",&photon_phi,"photon_phi/F");
        mettree->Branch("photon_energy",&photon_energy,"photon_energy/F");
        mettree->Branch("met",&met,"met/F");
        mettree->Branch("met_JetEnUp",&met_JetEnUp,"met_JetEnUp/F");
        mettree->Branch("met_JetEnDown",&met_JetEnDown,"met_JetEnDown/F");
        mettree->Branch("met_JetResUp",&met_JetResUp,"met_JetResUp/F");
        mettree->Branch("met_JetResDown",&met_JetResDown,"met_JetResDown/F");
        mettree->Branch("met_UnclusteredEnUp",&met_UnclusteredEnUp,"met_UnclusteredEnUp/F");
        mettree->Branch("met_UnclusteredEnDown",&met_UnclusteredEnDown,"met_UnclusteredEnDown/F");
        mettree->Branch("met_phi",&met_phi,"met_phi/F");
        mettree->Branch("corrmet",&corrmet,"corrmet/F");
        mettree->Branch("corrmet_JetEnUp",&corrmet_JetEnUp,"corrmet_JetEnUp/F");
        mettree->Branch("corrmet_JetEnDown",&corrmet_JetEnDown,"corrmet_JetEnDown/F");
        mettree->Branch("corrmet_JetResUp",&corrmet_JetResUp,"corrmet_JetResUp/F");
        mettree->Branch("corrmet_JetResDown",&corrmet_JetResDown,"corrmet_JetResDown/F");
        mettree->Branch("corrmet_UnclusteredEnUp",&corrmet_UnclusteredEnUp,"corrmet_UnclusteredEnUp/F");
        mettree->Branch("corrmet_UnclusteredEnDown",&corrmet_UnclusteredEnDown,"corrmet_UnclusteredEnDown/F");
        mettree->Branch("corrmet_phi",&corrmet_phi,"corrmet_phi/F");
        mettree->Branch("pusf",&pusf,"pusf/F");
	mettree->Branch("nvsf",&nvsf,"nvsf/F");
        mettree->Branch("wgtA",&wgtA,"wgtA/F");
        mettree->Branch("wgtB",&wgtB,"wgtB/F");
        mettree->Branch("wgtC",&wgtC,"wgtC/F");
        mettree->Branch("wgtD",&wgtD,"wgtD/F");
	mettree->Branch("nvtx",&nvtx,"nvtx/I");
	mettree->Branch("nJet", &nJet, "nJet/I");
        mettree->Branch("jet_pt",&jet_pt,"jet_pt/F");
        mettree->Branch("jet_eta",&jet_eta,"jet_eta/F");
        mettree->Branch("jet_phi",&jet_phi,"jet_phi/F");
	mettree->Branch("IDSF",&IDSF,"IDSF/F");
	mettree->Branch("kFactor",&kFactor,"kFactor/F");
        mettree->Branch("fail",&fail,"fail/B");
}
