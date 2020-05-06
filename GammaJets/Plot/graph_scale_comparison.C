{
  TCanvas *c1 =new TCanvas("c1", " ", 0, 0, 700, 800);

  c1->Range(0,0,1,1);
  c1->SetFillColor(0);
  c1->SetBorderMode(0);
  c1->SetBorderSize(2);
  c1->SetFrameBorderMode(0);
  c1->Draw();

  TLine *line = new TLine(0, 1., 500, 1.);
  line->SetLineColor(kBlack);
  line->SetLineWidth(1.);
  line->SetLineStyle(3);

  ifstream f1, f2, f3, f4;

  f1.open("scale_data_EGamma_2018A.txt");
  f2.open("scale_data_EGamma_2018B.txt");
  f3.open("scale_data_EGamma_2018C.txt");
  f4.open("scale_data_EGamma_2018D.txt");
  string s1;
  float yvalue1, yerr1;
  Float_t bins[] = { 50, 60, 80, 90, 100, 110, 130, 150, 175, 200, 225, 250, 275, 305, 335, 365, 400, 440, 500, 600 };
  Int_t  binnum = 19;
  TH1F* h1 = new TH1F("h1","h1", binnum, bins);
  TH1F* h2 = new TH1F("h2","h2", binnum, bins);
  TH1F* h3 = new TH1F("h3","h3", binnum, bins);
  TH1F* h4 = new TH1F("h4","h4", binnum, bins);

  for(int i = 0; i < binnum; i++){
    f1>>s1>>yvalue1>>yerr1;
    h1->SetBinContent(i+1, yvalue1); h1->SetBinError(i+1, yerr1);
    f2>>s1>>yvalue1>>yerr1;
    h2->SetBinContent(i+1, yvalue1); h2->SetBinError(i+1, yerr1);
    f3>>s1>>yvalue1>>yerr1;
    h3->SetBinContent(i+1, yvalue1); h3->SetBinError(i+1, yerr1);
    f4>>s1>>yvalue1>>yerr1;
    h4->SetBinContent(i+1, yvalue1); h4->SetBinError(i+1, yerr1);
  }

  TGraphErrors* gr1 = new TGraphErrors(h1);
  TGraphErrors* gr2 = new TGraphErrors(h2);
  TGraphErrors* gr3 = new TGraphErrors(h3);
  TGraphErrors* gr4 = new TGraphErrors(h4);

  gr1->SetTitle("");
  gr1->SetMarkerStyle(8);
  gr1->SetMarkerSize(0.8);
  gr1->SetMarkerColor(kRed);
  gr1->SetLineColor(kRed);
  gr1->SetLineWidth(2);

  gr1->GetXaxis()->SetTitle("q_{T} [GeV]");
  gr1->GetXaxis()->SetRangeUser(0, 500);
  gr1->GetXaxis()->SetTitleSize(0.04);

  gr1->GetYaxis()->SetTitle("- <u_{||}>/<q_{T}>");
  gr1->GetYaxis()->SetRangeUser(0.85, 1.15);
  gr1->GetYaxis()->SetTitleSize(0.04);
  gr1->GetYaxis()->SetTitleOffset(1.2);

  gr2->SetMarkerStyle(8);
  gr2->SetMarkerSize(0.8);
  gr2->SetMarkerColor(kBlue);
  gr2->SetLineColor(kBlue);
  gr2->SetLineWidth(2);

  gr3->SetMarkerStyle(8);
  gr3->SetMarkerSize(0.8);
  gr3->SetMarkerColor(kGreen+1);
  gr3->SetLineColor(kGreen+1);
  gr3->SetLineWidth(2);

  gr4->SetMarkerStyle(8);
  gr4->SetMarkerSize(0.8);
  gr4->SetMarkerColor(kViolet+1);
  gr4->SetLineColor(kViolet+1);
  gr4->SetLineWidth(2);

  gr1->Draw("apz");
  gr2->Draw("pez same");
  gr3->Draw("pez same");
  gr4->Draw("pez same");

  line->Draw("same");

  TLegend *legend1 = new TLegend(0.2, 0.6, 0.4, 0.85);
  legend1->SetTextFont(42);
  legend1->SetLineColor(0);
  legend1->SetTextSize(0.04);
  legend1->SetFillColor(0);
  legend1->AddEntry(gr1, "2018A", "lp");
  legend1->AddEntry(gr2, "2018B", "lp");
  legend1->AddEntry(gr3, "2018C", "lp");
  legend1->AddEntry(gr4, "2018D", "lp");
  legend1->Draw("same");

  TLatex *t2a = new TLatex(0.5,0.9," #bf{CMS} #it{Preliminary}          59.7 fb^{-1} (13 TeV, 2018) ");
  t2a->SetNDC();
  t2a->SetTextFont(42);
  t2a->SetTextSize(0.04);
  t2a->SetTextAlign(20);
  t2a->Draw("same");

}
