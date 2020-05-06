{
  ifstream f1;
  f1.open("scale_data_EGamma_2018.txt");
  string s;
  float yvalue, yerr;
  Float_t bins[] = { 50, 60, 80, 90, 100, 110, 130, 150, 175, 200, 225, 250, 275, 305, 335, 365, 400, 440, 500, 600 };
  Int_t  binnum = 19;
  TH1F* h1 = new TH1F("h1","h1", binnum, bins);

  for(int i = 0; i < binnum; i++){
    f1>>s>>yvalue>>yerr;
    h1->SetBinContent(i+1, yvalue); h1->SetBinError(i+1, yerr);
  }

  TFile *MyFile = new TFile("response_2018.root","NEW");
  h1->Write();
  MyFile->cd();
  MyFile->Write();
  delete h1; delete  MyFile; 
}
