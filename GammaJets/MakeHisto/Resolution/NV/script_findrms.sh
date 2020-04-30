for component in upara uperp; do

for i in 2 6 10 14 18 22 26 30 34 38 42 46 50 54 58; do

cat>test.C<<EOF
{
  TFile *fdata1 = TFile::Open("histo_EGamma2018.root");
  TH1F  *h1 = (TH1F*)fdata1->Get("${component}${i}");

  double historms = h1->GetRMS();
  double historms_err = h1->GetRMSError();

  fstream out;
  out.open("nvtx_${component}_reso_data_2018.txt", fstream::in | fstream::out | fstream::app);
  out<<"${component}${i}"<<"\t"<<historms<<"\t"<<historms_err<<endl;
  out.close();
}
EOF

root -l -b -q test.C

rm -f test.C

done

done
