using namespace TMath;

void TwoHits(){

   ROOT::EnableImplicitMT();
   auto fileName = "/home/hanjie/moller/optics_analysis/Rootfiles/sieve1/trackhits_moller_pass5_LH2_*";
   auto treeName = "T";

   ROOT::RDataFrame d(treeName, fileName);

   // apply cuts and generate new columns
   auto selected_d = d.Filter("ntrk==2 && ring.r>500");

   ROOT::RDF::RResultPtr<TH1D> ring_r[2];
   ROOT::RDF::RResultPtr<TH1D> ring_ph[2];
   ROOT::RDF::RResultPtr<TH1D> ring_p[2];
   ROOT::RDF::RResultPtr<TH1D> tg_th[2];
   ROOT::RDF::RResultPtr<TH1D> tg_ph[2];
   ROOT::RDF::RResultPtr<TH1D> tg_p[2];

   ring_r[0] = selected_d.Histo1D<Double_t>({"ring_r0","ring_r0",200,0,2000},"ring.r[0]","rate");
   ring_r[1] = selected_d.Histo1D<Double_t>({"ring_r1","ring_r1",200,0,2000},"ring.r[1]","rate");

   ring_ph[0] = selected_d.Histo1D<Double_t>({"ring_ph0","ring_ph0",200,-Pi(),Pi()},"ring.ph[0]","rate");
   ring_ph[1] = selected_d.Histo1D<Double_t>({"ring_ph1","ring_ph1",200,-Pi(),Pi()},"ring.ph[1]","rate");

   ring_p[0] = selected_d.Histo1D<Double_t>({"ring_p0","ring_p0",200,0,11000},"ring.p[0]","rate");
   ring_p[1] = selected_d.Histo1D<Double_t>({"ring_p1","ring_p1",200,0,11000},"ring.p[1]","rate");

   tg_th[0] = selected_d.Histo1D<Double_t>({"tg_th0","tg_th0",200,0,2000},"tg.th[0]","rate");
   tg_th[1] = selected_d.Histo1D<Double_t>({"tg_th1","tg_th1",200,0,2000},"tg.th[1]","rate");

   tg_ph[0] = selected_d.Histo1D<Double_t>({"tg_ph0","tg_ph0",200,-Pi(),Pi()},"tg.ph[0]","rate");
   tg_ph[1] = selected_d.Histo1D<Double_t>({"tg_ph1","tg_ph1",200,-Pi(),Pi()},"tg.ph[1]","rate");

   tg_p[0] = selected_d.Histo1D<Double_t>({"tg_p0","tg_p0",200,0,11000},"tg.p[0]","rate");
   tg_p[1] = selected_d.Histo1D<Double_t>({"tg_p1","tg_p1",200,0,11000},"tg.p[1]","rate");

   TCanvas *c1=new TCanvas("c1","c1",1500,1000);
   c1->Divide(2,2);
   c1->cd(1);
   ring_r[0].GetPtr()->SetLineColor(2);
   ring_r[1].GetPtr()->SetLineColor(4);
   ring_r[0]->Draw("HIST");
   ring_r[1]->Draw("HIST same");

   c1->cd(2);
   ring_ph[0].GetPtr()->SetLineColor(2);
   ring_ph[1].GetPtr()->SetLineColor(4);
   ring_ph[0]->Draw("HIST");
   ring_ph[1]->Draw("HIST same");

   c1->cd(3);
   ring_p[0].GetPtr()->SetLineColor(2);
   ring_p[1].GetPtr()->SetLineColor(4);
   ring_p[0]->Draw("HIST");
   ring_p[1]->Draw("HIST same");

   TCanvas *c2=new TCanvas("c2","c2",1500,1000);
   c2->Divide(2,2);
   c2->cd(1);
   tg_th[0].GetPtr()->SetLineColor(2);
   tg_th[1].GetPtr()->SetLineColor(4);
   tg_th[0]->Draw("HIST");
   tg_th[1]->Draw("HIST same");

   c2->cd(2);
   tg_ph[0].GetPtr()->SetLineColor(2);
   tg_ph[1].GetPtr()->SetLineColor(4);
   tg_ph[0]->Draw("HIST");
   tg_ph[1]->Draw("HIST same");

   c2->cd(3);
   tg_p[0].GetPtr()->SetLineColor(2);
   tg_p[1].GetPtr()->SetLineColor(4);
   tg_p[0]->Draw("HIST");
   tg_p[1]->Draw("HIST same");

}
