void PlotKin(){

     TChain *Tmoller = new TChain("T");
     Tmoller->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_H1_moller_p5_newfield*");

     TChain *T1 = new TChain("T");
     T1->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p1_*");

     TChain *T2 = new TChain("T");
     T2->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p2_*");
     
     TChain *T3 = new TChain("T");
     T3->Add("../Rootfiles/sieve1/trackhits_remoll_C12_elastic_p3_allSD*");

     TChain *T4 = new TChain("T");
     T4->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p4_*");

     TChain *T5 = new TChain("T");
     T5->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p5_*");

     TH2F *hpth_moller = new TH2F("hpth_moller","E' vs. theta moller distribution",100,0.1,1.8,100,0,12);
     TH2F *hpth_p1 = new TH2F("hpth_p1","E' vs. theta elastic pass 1 distribution",100,0.1,1.8,100,0,12);
     TH2F *hpth_p2 = new TH2F("hpth_p2","E' vs. theta elastic pass 2 distribution",100,0.1,1.8,100,0,12);
     TH2F *hpth_p3 = new TH2F("hpth_p3","E' vs. theta elastic pass 3 distribution",100,0.1,1.8,100,0,12);
     TH2F *hpth_p4 = new TH2F("hpth_p4","E' vs. theta elastic pass 4 distribution",100,0.1,1.8,100,0,12);
     TH2F *hpth_p5 = new TH2F("hpth_p5","E' vs. theta elastic pass 5 distribution",100,0.1,1.8,100,0,12);

     TString COL = "(sieve.r>25)";

     TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
     Tmoller->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_moller",Form("rate*%s",COL.Data()));
     hpth_moller->SetMarkerColor(4);
     hpth_moller->SetTitle("E' vs. theta;theta;E';");
     
     T1->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_p1",Form("rate*%s",COL.Data()),"same");
     hpth_p1->SetMarkerColor(3);

     T2->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_p2",Form("rate*%s",COL.Data()),"same");
     hpth_p2->SetMarkerColor(6);

     T3->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_p3",Form("rate*%s",COL.Data()),"same");
     hpth_p3->SetMarkerColor(46);

     T4->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_p4",Form("rate*%s",COL.Data()),"same");
     hpth_p4->SetMarkerColor(40);

     T5->Draw("tg.p/1000:tg.th/TMath::Pi()*180.>>hpth_p5",Form("rate*%s",COL.Data()),"same");
     hpth_p5->SetMarkerColor(2);

     TLatex lex;
     lex.SetTextSize(0.03);
     lex.DrawLatex(1.4,11,"pass5");
     lex.DrawLatex(1.4,8.8,"pass4");
     lex.DrawLatex(1.4,6.6,"pass3");
     lex.DrawLatex(1.4,4.4,"pass2");
     lex.DrawLatex(1.4,2.2,"pass1");
}
