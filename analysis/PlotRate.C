void PlotRate(){
     TChain *Tmoller = new TChain("T");
     Tmoller->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_H1_moller_p5_newfield*");

     TChain *T1 = new TChain("T");
     T1->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p1_*");

     TChain *T2 = new TChain("T");
     T2->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p2_*");

     TChain *T3 = new TChain("T");
     T3->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p3_*");

     TChain *T4 = new TChain("T");
     T4->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p4_*");

     TChain *T5 = new TChain("T");
     T5->Add("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p5_*");

     TH1F *hr_moller = new TH1F("hr_moller","moller events r distribution",400,500,1300);
     TH1F *hr_p1 = new TH1F("hr_p1","elastic p1 events r distribution",400,500,1300);
     TH1F *hr_p2 = new TH1F("hr_p2","elastic p2 events r distribution",400,500,1300);
     TH1F *hr_p3 = new TH1F("hr_p3","elastic p3 events r distribution",400,500,1300);
     TH1F *hr_p4 = new TH1F("hr_p4","elastic p4 events r distribution",400,500,1300);
     TH1F *hr_p5 = new TH1F("hr_p5","elastic p5 events r distribution",400,500,1300);

     TString CUT1="ring.r>300";

     TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
     //Tmoller->Draw("ring.r>>hr_moller",Form("rate*(%s)",CUT1.Data()),"HIST");
     //hr_moller->SetLineColor(1);
     
     T1->Draw("ring.r>>hr_p1",Form("rate*(%s)",CUT1.Data()),"HIST");
     hr_p1->SetLineColor(2);
     hr_p1->SetLineWidth(2);
     hr_p1->SetTitle("r at main detector;ring.r;");

     T2->Draw("ring.r>>hr_p2",Form("rate*(%s)",CUT1.Data()),"HIST SAME");
     hr_p2->SetLineColor(4);
     hr_p2->SetLineWidth(2);
     hr_p2->SetTitle("rate vs. ring.r (10uA);ring.r;rate;");


     T3->Draw("ring.r>>hr_p3",Form("rate*(%s)",CUT1.Data()),"HIST SAME");
     hr_p3->SetLineColor(6);
     hr_p3->SetLineWidth(2);

     T4->Draw("ring.r>>hr_p4",Form("rate*(%s)",CUT1.Data()),"HIST SAME");
     hr_p4->SetLineColor(8);
     hr_p4->SetLineWidth(2);

     T5->Draw("ring.r>>hr_p5",Form("rate*(%s)",CUT1.Data()),"HIST SAME");
     hr_p5->SetLineColor(9);
     hr_p5->SetLineWidth(2);

     TLegend *leg=new TLegend(0.2,0.6,0.35,0.8);
     //leg->AddEntry(hr_moller,"moller","L");
     leg->AddEntry(hr_p1,"pass 1","L");
     leg->AddEntry(hr_p2,"pass 2","L");
     leg->AddEntry(hr_p3,"pass 3","L");
     leg->AddEntry(hr_p4,"pass 4","L");
     leg->AddEntry(hr_p5,"pass 5","L");
     leg->Draw();


     double rMin[7][3]={
      { 640.0,  640.0,  640.0},
      { 680.0,  680.0,  680.0},
      { 750.0,  750.0,  750.0},
      { 855.0,  847.5,  825.0},
      { 935.0,  920.0,  875.0},
      {1075.0, 1080.0, 1090.0},
      {1200.0, 1200.0, 1200.0}
    };
    double rMax[7][3]={
      { 680.0,  680.0,  680.0},
      { 750.0,  750.0,  750.0},
      { 855.0,  847.5,  825.0},
      { 935.0,  920.0,  875.0},
      {1075.0, 1060.0, 1055.0},
      {1190.0, 1190.0, 1190.0},
      {1500.0, 1500.0, 1500.0}
    };

     c1->Update();
     TLine *l1_min = new TLine(rMin[0][2],0,rMin[0][2],60e6);
     TLine *l2_min = new TLine(rMin[1][2],0,rMin[1][2],60e6);
     TLine *l3_min = new TLine(rMin[2][2],0,rMin[2][2],60e6);
     TLine *l4_min = new TLine(rMin[3][2],0,rMin[3][2],60e6);
     TLine *l5_min = new TLine(rMin[4][2],0,rMin[4][2],60e6);
     TLine *l6_min = new TLine(rMin[5][2],0,rMin[5][2],60e6);
     TLine *l7_min = new TLine(rMin[6][2],0,rMin[6][2],60e6);

     l1_min->SetLineColor(15);
     l1_min->SetLineStyle(9);
     l1_min->Draw();

     l2_min->SetLineColor(15);
     l2_min->SetLineStyle(9);
     l2_min->Draw();

     l3_min->SetLineColor(15);
     l3_min->SetLineStyle(9);
     l3_min->Draw();

     l4_min->SetLineColor(15);
     l4_min->SetLineStyle(9);
     l4_min->Draw();

     l5_min->SetLineColor(15);
     l5_min->SetLineStyle(9);
     l5_min->Draw();

     l6_min->SetLineColor(15);
     l6_min->SetLineStyle(9);
     l6_min->Draw();

     l7_min->SetLineColor(15);
     l7_min->SetLineStyle(9);
     l7_min->Draw();
}
