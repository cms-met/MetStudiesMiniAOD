for component in upara uperp; do

for i in 50 60 80 90 100 110 130 140 160 180 200 240 320 400; do

cat>test.C<<EOF
{
  TFile *fdata1 = TFile::Open("histo_EGamma2018.root");
  TH1F  *h1 = (TH1F*)fdata1->Get("${component}${i}");

  double historms = h1->GetRMS();
  double historms_err = h1->GetRMSError();

  fstream out;
  out.open("${component}_reso_data_2018.txt", fstream::in | fstream::out | fstream::app);
  out<<"${component}${i}"<<"\t"<<historms<<"\t"<<historms_err<<endl;
  out.close();
}
EOF

root -l -b -q test.C

rm -f test.C

done

done
