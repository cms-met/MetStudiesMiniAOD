TGraphAsymmErrors *JESerror(TH1F *Background, TH1F *Backgrounddown, TH1F *Backgroundup, TH1F * hdata){
    
  TH1F *den1 = (TH1F *) Background->Clone ("bkgden1");
  TH1F *den2 = (TH1F *) Background->Clone ("bkgden2");
	
  const Int_t nvar = 41;
  Double_t x[nvar];
  Double_t y[nvar];
  Double_t exl[nvar];
  Double_t eyl[nvar];
  Double_t exh[nvar];
  Double_t eyh[nvar];
  Double_t x1[nvar];
  Double_t y1[nvar];
  Double_t exl1[nvar];
  Double_t eyl1[nvar];
  Double_t exh1[nvar];
  Double_t eyh1[nvar];

  TH1F *ratiop = (TH1F *) Background->Clone ("backgroundratiop");
  TH1F *ratiom = (TH1F *) Background->Clone ("backgroundratiom");

  double  ymax = 2.;

  for (int km = 0; km <= Background->GetNbinsX (); km++){
    double conte1 =
      sqrt (Background->GetBinError (km) * Background->GetBinError (km) + (Background->GetBinContent (km) - Backgroundup->GetBinContent (km)) * (Background->GetBinContent (km) - Backgroundup->GetBinContent (km)));
    double conte2 =
      sqrt (Background->GetBinError (km) * Background->GetBinError (km) + (Background->GetBinContent (km) - Backgrounddown->GetBinContent (km)) * (Background->GetBinContent (km) - Backgrounddown->GetBinContent (km)));

    den1->SetBinContent (km, Background->GetBinContent (km) + conte1);
    den2->SetBinContent (km, Background->GetBinContent (km) - conte2);
    ymax = Background->GetBinContent(km) + conte1;
    x1[km] = Background->GetBinCenter (km);
    y1[km] = Background->GetBinContent (km);
    exl1[km] = Background->GetBinWidth (km) / 2;
    exh1[km] = Background->GetBinWidth (km) / 2;
    eyl1[km] = conte2;
    eyh1[km] = conte1;
  }

  ratiop->Divide (den1);
  ratiom->Divide (den2);
  
  TH1F *ratio = (TH1F *) hdata->Clone ("ratiodata");
  ratio->Divide (Background);

  for (int km = 0; km <= ratio->GetNbinsX (); km++){
    if (ratio->GetBinContent (km) > ymax)
      ymax = ratio->GetBinContent (km) + ratio->GetBinError (km);
    x[km] = ratio->GetBinCenter (km);
    y[km] = 1;	
    exl[km] = ratio->GetBinWidth (km) / 2;
    exh[km] = ratio->GetBinWidth (km) / 2;


    if (ratiop->GetBinContent (km) != 0)
      eyh[km] = (1. / ratiop->GetBinContent (km) - 1)*ratio->GetBinContent (km);
    else
      eyh[km] = 0;

    if (ratiom->GetBinContent (km) != 0)
      eyl[km] = (1 - 1. / ratiom->GetBinContent (km))*ratio->GetBinContent (km);
    else
      eyl[km] = 0;
  

  }

  TGraphAsymmErrors *err = new TGraphAsymmErrors (nvar, x, y, exl, exh, eyl, eyh);

  return err;
}
