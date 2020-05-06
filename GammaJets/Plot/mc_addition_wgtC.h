#include <iostream>
#include <fstream>
#include <set>
#include<TFile.h>
#include<TTree.h>
#include<TH1.h>
#include<TH2.h>
#include<THStack.h>
#include<TGraphErrors.h>
#include<TGraphAsymmErrors.h>
#include<TCanvas.h>
#include<TFrame.h>
#include<TLegend.h>
#include<vector>
#include<iostream>
#include<TMath.h>
#include<TROOT.h>
#include<TInterpreter.h>
#include<TStyle.h>
#include<TChain.h>
#include<TString.h>
#include<TPaveStats.h>
#include<TPad.h>
#include<TLatex.h>
#include "TEfficiency.h"
#include "TAxis.h"

TH1F* mc_addition(double lumi, const char* variable){

  double w1 = (lumi) * (19000./9371355.);
  TFile *f1 = TFile::Open("wgtC/histo_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hGJets40 = (TH1F*)f1->Get(variable);
  hGJets40->SetBinContent(hGJets40->GetNbinsX(), hGJets40->GetBinContent(hGJets40->GetNbinsX())+hGJets40->GetBinContent(hGJets40->GetNbinsX()+1));
  hGJets40->Scale(w1);

  double w2 = (lumi) * (8300./9798176.);
  TFile *f2 = TFile::Open("wgtC/histo_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hGJets100 = (TH1F*)f2->Get(variable);
  hGJets100->SetBinContent(hGJets100->GetNbinsX(), hGJets100->GetBinContent(hGJets100->GetNbinsX())+hGJets100->GetBinContent(hGJets100->GetNbinsX()+1));
  hGJets100->Scale(w2);

  double w3 = (lumi) * (2200./19062809.);
  TFile *f3 = TFile::Open("wgtC/histo_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hGJets200 = (TH1F*)f3->Get(variable);
  hGJets200->SetBinContent(hGJets200->GetNbinsX(), hGJets200->GetBinContent(hGJets200->GetNbinsX())+hGJets200->GetBinContent(hGJets200->GetNbinsX()+1));
  hGJets200->Scale(w3);

  double w4 = (lumi) * (260./4655985.);
  TFile *f4 = TFile::Open("wgtC/histo_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hGJets400 = (TH1F*)f4->Get(variable);
  hGJets400->SetBinContent(hGJets400->GetNbinsX(), hGJets400->GetBinContent(hGJets400->GetNbinsX())+hGJets400->GetBinContent(hGJets400->GetNbinsX()+1));
  hGJets400->Scale(w4);

  double w5 = (lumi) * (84./4981121.);
  TFile *f5 = TFile::Open("wgtC/histo_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hGJets600 = (TH1F*)f5->Get(variable);
  hGJets600->SetBinContent(hGJets600->GetNbinsX(), hGJets600->GetBinContent(hGJets600->GetNbinsX())+hGJets600->GetBinContent(hGJets600->GetNbinsX()+1));
  hGJets600->Scale(w5);

  hGJets40->Add(hGJets100); hGJets40->Add(hGJets200); hGJets40->Add(hGJets400); hGJets40->Add(hGJets600);

  double w6 = (lumi) * (27849880./93972378.);
  TFile *f6 = TFile::Open("wgtC/histo_QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8_part1.root");
  TFile *f6_2 = TFile::Open("wgtC/histo_QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8_part2.root");
  TH1F *hQCD100 = (TH1F*)f6->Get(variable);
  TH1F *hQCD100_2 = (TH1F*)f6_2->Get(variable);
  hQCD100->Add(hQCD100_2);
  hQCD100->SetBinContent(hQCD100->GetNbinsX(), hQCD100->GetBinContent(hQCD100->GetNbinsX())+hQCD100->GetBinContent(hQCD100->GetNbinsX()+1));
  hQCD100->Scale(w6);
 
  double w7 = (lumi) * (1716997./54289442.);
  TFile *f7 = TFile::Open("wgtC/histo_QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hQCD200 = (TH1F*)f7->Get(variable);
  hQCD200->SetBinContent(hQCD200->GetNbinsX(), hQCD200->GetBinContent(hQCD200->GetNbinsX())+hQCD200->GetBinContent(hQCD200->GetNbinsX()+1));
  hQCD200->Scale(w7);

  double w8 = (lumi) * (351302./54661579.);
  TFile *f8 = TFile::Open("wgtC/histo_QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hQCD300 = (TH1F*)f8->Get(variable);
  hQCD300->SetBinContent(hQCD300->GetNbinsX(), hQCD300->GetBinContent(hQCD300->GetNbinsX())+hQCD300->GetBinContent(hQCD300->GetNbinsX()+1));
  hQCD300->Scale(w8);
  
  double w9 = (lumi) * (31630./55152960.);
  TFile *f9 = TFile::Open("wgtC/histo_QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8_part1.root");
  TFile *f9_2 = TFile::Open("wgtC/histo_QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8_part2.root");
  TH1F *hQCD500 = (TH1F*)f9->Get(variable);
  TH1F *hQCD500_2 = (TH1F*)f9_2->Get(variable);
  hQCD500->Add(hQCD500_2);
  hQCD500->SetBinContent(hQCD500->GetNbinsX(), hQCD500->GetBinContent(hQCD500->GetNbinsX())+hQCD500->GetBinContent(hQCD500->GetNbinsX()+1));
  hQCD500->Scale(w9);
  
  double w10 = (lumi) * (6802./48158738.);
  TFile *f10 = TFile::Open("wgtC/histo_QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8_part1.root");
  TFile *f10_2 = TFile::Open("wgtC/histo_QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8_part2.root");
  TH1F *hQCD700 = (TH1F*)f10->Get(variable);
  TH1F *hQCD700_2 = (TH1F*)f10_2->Get(variable);
  hQCD700->Add(hQCD700_2);
  hQCD700->SetBinContent(hQCD700->GetNbinsX(), hQCD700->GetBinContent(hQCD700->GetNbinsX())+hQCD700->GetBinContent(hQCD700->GetNbinsX()+1));
  hQCD700->Scale(w10);
  
  double w11 = (lumi) * (1206./15466225.);
  TFile *f11 = TFile::Open("wgtC/histo_QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hQCD1000 = (TH1F*)f11->Get(variable);
  hQCD1000->SetBinContent(hQCD1000->GetNbinsX(), hQCD1000->GetBinContent(hQCD1000->GetNbinsX())+hQCD1000->GetBinContent(hQCD1000->GetNbinsX()+1));
  hQCD1000->Scale(w11);
  
  double w12 = (lumi) * (98.71/10955087.);
  TFile *f12 = TFile::Open("wgtC/histo_QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hQCD1500 = (TH1F*)f12->Get(variable);
  hQCD1500->SetBinContent(hQCD1500->GetNbinsX(), hQCD1500->GetBinContent(hQCD1500->GetNbinsX())+hQCD1500->GetBinContent(hQCD1500->GetNbinsX()+1));
  hQCD1500->Scale(w12);
  
  double w13 = (lumi) * (20.2/5475677.);
  TFile *f13 = TFile::Open("wgtC/histo_QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hQCD2000 = (TH1F*)f13->Get(variable);
  hQCD2000->SetBinContent(hQCD2000->GetNbinsX(), hQCD2000->GetBinContent(hQCD2000->GetNbinsX())+hQCD2000->GetBinContent(hQCD2000->GetNbinsX()+1));
  hQCD2000->Scale(w13);

  hQCD100->Add(hQCD200); hQCD100->Add(hQCD300); hQCD100->Add(hQCD500); hQCD100->Add(hQCD700);
  hQCD100->Add(hQCD1000); hQCD100->Add(hQCD1500); hQCD100->Add(hQCD2000);

  double w14 = (lumi) * (1319*1.21/28084244.);
  TFile *f14 = TFile::Open("wgtC/histo_WJetsToLNu_HT-70To100_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets70 = (TH1F*)f14->Get(variable);
  hWJets70->SetBinContent(hWJets70->GetNbinsX(), hWJets70->GetBinContent(hWJets70->GetNbinsX())+hWJets70->GetBinContent(hWJets70->GetNbinsX()+1));
  hWJets70->Scale(w14);

  double w15 = (lumi) * (1395*1.17/35862893.);
  TFile *f15 = TFile::Open("wgtC/histo_WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets100 = (TH1F*)f15->Get(variable);
  hWJets100->SetBinContent(hWJets100->GetNbinsX(), hWJets100->GetBinContent(hWJets100->GetNbinsX())+hWJets100->GetBinContent(hWJets100->GetNbinsX()+1));
  hWJets100->Scale(w15);

  double w16 = (lumi) * (408.7*1.17/25468933.);
  TFile *f16 = TFile::Open("wgtC/histo_WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets200 = (TH1F*)f16->Get(variable);
  hWJets200->SetBinContent(hWJets200->GetNbinsX(), hWJets200->GetBinContent(hWJets200->GetNbinsX())+hWJets200->GetBinContent(hWJets200->GetNbinsX()+1));
  hWJets200->Scale(w16);

  double w17 = (lumi) * (57.52*1.17/5932701.);
  TFile *f17 = TFile::Open("wgtC/histo_WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets400 = (TH1F*)f17->Get(variable);
  hWJets400->SetBinContent(hWJets400->GetNbinsX(), hWJets400->GetBinContent(hWJets400->GetNbinsX())+hWJets400->GetBinContent(hWJets400->GetNbinsX()+1));
  hWJets400->Scale(w17);
 
  double w18 = (lumi) * (12.78*1.17/19771294.);
  TFile *f18 =TFile::Open("wgtC/histo_WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets600 = (TH1F*)f18->Get(variable);
  hWJets600->SetBinContent(hWJets600->GetNbinsX(), hWJets600->GetBinContent(hWJets600->GetNbinsX())+hWJets600->GetBinContent(hWJets600->GetNbinsX()+1));
  hWJets600->Scale(w18);

  double w19 = (lumi) * (5.246*1.17/8402687.);
  TFile *f19 = TFile::Open("wgtC/histo_WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets800 = (TH1F*)f19->Get(variable);
  hWJets800->SetBinContent(hWJets800->GetNbinsX(), hWJets800->GetBinContent(hWJets800->GetNbinsX())+hWJets800->GetBinContent(hWJets800->GetNbinsX()+1));
  hWJets800->Scale(w19);
 
  double w20 = (lumi) * (1.071*1.17/7633949.);
  TFile *f20 = TFile::Open("wgtC/histo_WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets1200 = (TH1F*)f20->Get(variable);
  hWJets1200->SetBinContent(hWJets1200->GetNbinsX(), hWJets1200->GetBinContent(hWJets1200->GetNbinsX())+hWJets1200->GetBinContent(hWJets1200->GetNbinsX()+1));
  hWJets1200->Scale(w20);

  double w21 = (lumi) * (0.00819*1.17/3273980.);
  TFile *f21 = TFile::Open("wgtC/histo_WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root");
  TH1F *hWJets2500 = (TH1F*)f21->Get(variable);
  hWJets2500->SetBinContent(hWJets2500->GetNbinsX(), hWJets2500->GetBinContent(hWJets2500->GetNbinsX())+hWJets2500->GetBinContent(hWJets2500->GetNbinsX()+1));
  hWJets2500->Scale(w21);

  hWJets70->Add(hWJets100); hWJets70->Add(hWJets200); hWJets70->Add(hWJets400); hWJets70->Add(hWJets600);
  hWJets70->Add(hWJets800); hWJets70->Add(hWJets1200); hWJets70->Add(hWJets2500);

  double w22 = (lumi) * (489./5059865.);
  TFile *f22 = TFile::Open("wgtC/histo_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
  TH1F *hWGToLNuG = (TH1F*)f22->Get(variable);
  hWGToLNuG->SetBinContent(hWGToLNuG->GetNbinsX(), hWGToLNuG->GetBinContent(hWGToLNuG->GetNbinsX())+hWGToLNuG->GetBinContent(hWGToLNuG->GetNbinsX()+1));
  hWGToLNuG->Scale(w22);

  double w23 = (lumi) * (117.864/14372682.);
  TFile *f23 = TFile::Open("wgtC/histo_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
  TH1F *hZGTo2LG = (TH1F*)f23->Get(variable);
  hZGTo2LG->SetBinContent(hZGTo2LG->GetNbinsX(), hZGTo2LG->GetBinContent(hZGTo2LG->GetNbinsX())+hZGTo2LG->GetBinContent(hZGTo2LG->GetNbinsX()+1));
  hZGTo2LG->Scale(w23);

  double w24 = (lumi) * (28.05/2009042.);
  TFile *f24 = TFile::Open("wgtC/histo_ZGTo2NuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root");
  TH1F *hZGTo2NuG = (TH1F*)f24->Get(variable);
  hZGTo2NuG->SetBinContent(hZGTo2NuG->GetNbinsX(), hZGTo2NuG->GetBinContent(hZGTo2NuG->GetNbinsX())+hZGTo2NuG->GetBinContent(hZGTo2NuG->GetNbinsX()+1));
  hZGTo2NuG->Scale(w24);

  double w25 = (lumi) * (2.967/1109000.);
  TFile *f25 = TFile::Open("wgtC/histo_TGJets_TuneCP5_13TeV_amcatnlo_madspin_pythia8.root");
  TH1F *hTGJets = (TH1F*)f25->Get(variable);
  hTGJets->SetBinContent(hTGJets->GetNbinsX(), hTGJets->GetBinContent(hTGJets->GetNbinsX())+hTGJets->GetBinContent(hTGJets->GetNbinsX()+1));
  hTGJets->Scale(w25);

  double w26 = (lumi) * (4.322/4691915.);
  TFile *f26 = TFile::Open("wgtC/histo_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8.root");
  TH1F *hTTGJets = (TH1F*)f26->Get(variable);
  hTTGJets->SetBinContent(hTTGJets->GetNbinsX(), hTTGJets->GetBinContent(hTTGJets->GetNbinsX())+hTTGJets->GetBinContent(hTTGJets->GetNbinsX()+1));
  hTTGJets->Scale(w26);

  hWGToLNuG->Add(hZGTo2LG); hWGToLNuG->Add(hZGTo2NuG); hWGToLNuG->Add(hTGJets); hWGToLNuG->Add(hTTGJets); hWGToLNuG->Add(hWJets70);

  hGJets40->Add(hQCD100); hGJets40->Add(hWJets70); hGJets40->Add(hWGToLNuG);

  return hGJets40;
}
