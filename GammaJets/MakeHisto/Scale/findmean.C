{
  TFile *fdata1 = TFile::Open("histo_EGamma2018.root");
  TH1F  *h1 = (TH1F*)fdata1->Get("upara50");

  double histomean = h1->GetMean();
  double histomean_err = h1->GetMeanError();

  fstream out;
  out.open("scale_data_EGamma_2018.txt", fstream::in | fstream::out | fstream::app);
  out<<"upara50"<<"\t"<<-histomean<<"\t"<<histomean_err<<endl;
  out.close();
}
