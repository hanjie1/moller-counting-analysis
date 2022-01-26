using namespace TMath;

void PlotTwoHits(){

   TChain *T=new TChain("T");
   T->Add("twohits.root");

   TChain *T1=new TChain("T");
   T1->Add("onehit.root");

   TString twotrk="main_r[0]>500 && main_r[1]>500 && (main_trid[0]!=main_trid[1])";

   TH1D* main_r[2];
   TH2D* main_ph;
   TH1D* main_p[2];
   TH1D* tg_th[2];
   TH2D* tg_ph;
   TH1D* tg_p[2];

   main_r[0]=new TH1D("main_r0","main_r0",200,500,1500);
   main_r[1]=new TH1D("main_r1","main_r1",200,500,1500);

   main_p[0]=new TH1D("main_p0","main_p0",200,0,11000);
   main_p[1]=new TH1D("main_p1","main_p1",200,0,11000);

   tg_th[0]=new TH1D("tg_th0","tg_th0",200,0,0.025);
   tg_th[1]=new TH1D("tg_th1","tg_th1",200,0,0.025);

   tg_p[0]=new TH1D("tg_p0","tg_p0",200,0,11000);
   tg_p[1]=new TH1D("tg_p1","tg_p1",200,0,11000);

   TH1D *main_r_onehit = new TH1D("main_r_onehit","main_r_onehit",200,500,1500);   
   TH1D *main_p_onehit = new TH1D("main_p_onehit","main_p_onehit",200,0,11000);   
   TH1D *tg_th_onehit=new TH1D("tg_th_onehit","tg_th_onehit",200,0,0.025);
   TH1D *tg_p_onehit=new TH1D("tg_p_onehit","tg_p_onehit",200,0,11000);


   TCanvas *c1=new TCanvas("c1","c1",1500,1000);
   c1->Divide(2,2);
   c1->cd(1);
   T->Draw("main_r[0]>>main_r0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("main_r[1]>>main_r1",Form("rate*(%s)",twotrk.Data()));
   main_r[0]->SetLineColor(2);
   main_r[1]->SetLineColor(4);
   main_r[0]->Draw("HIST");
   main_r[1]->Draw("HIST same");
   main_r[0]->SetTitle("two trks main.r;main.r;;"); 

   Double_t nhit1 = main_r[0]->Integral();
   Double_t nhit2 = main_r[1]->Integral();

   TLatex tex;
   tex.SetTextSize(0.03);
   tex.DrawLatexNDC(.2,.8,Form("N0=%e",nhit1));
   tex.DrawLatexNDC(.2,.75,Form("N1=%e",nhit2));
   
   TLegend *leg1 = new TLegend(0.6,0.7,0.75,0.85);
   leg1->AddEntry(main_r[0],"main.r[0]","L");
   leg1->AddEntry(main_r[1],"main.r[1]","L");
   leg1->Draw();

   c1->cd(2);
   T->Draw("main_p[0]>>main_p0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("main_p[1]>>main_p1",Form("rate*(%s)",twotrk.Data()));
   main_p[0]->SetLineColor(2);
   main_p[1]->SetLineColor(4);
   main_p[0]->Draw("HIST");
   main_p[1]->Draw("HIST same");
   main_p[0]->SetTitle("two trks main.p;main.p;;"); 
   
   TLegend *leg2 = new TLegend(0.6,0.7,0.75,0.85);
   leg2->AddEntry(main_p[0],"main.p[0]","L");
   leg2->AddEntry(main_p[1],"main.p[1]","L");
   leg2->Draw();

   c1->cd(3);
   T1->Draw("main_r[0]>>main_r_onehit","rate*(main_r[0]>500)","hist");
   main_r_onehit->SetTitle("one trk main.r;main.r;;"); 

   Double_t nhit3 = main_r_onehit->Integral();

   TLatex tex1;
   tex1.SetTextSize(0.03);
   tex1.DrawLatexNDC(.2,.8,Form("N=%e",nhit3));

   c1->cd(4);
   T1->Draw("main_p[0]>>main_p_onehit","rate*(main_r[0]>500)","hist");
   main_p_onehit->SetTitle("one trk main.p;main.p;;"); 


   TCanvas *c2=new TCanvas("c2","c2",1500,1000);
   c2->Divide(2,2);
   c2->cd(1);
   T->Draw("tg_th[0]>>tg_th0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("tg_th[1]>>tg_th1",Form("rate*(%s)",twotrk.Data()));
   tg_th[0]->SetLineColor(2);
   tg_th[1]->SetLineColor(4);
   tg_th[0]->Draw("HIST");
   tg_th[1]->Draw("HIST same");
   tg_th[0]->SetTitle("two trks tg.th;tg.th;;"); 
   
   TLegend *leg3 = new TLegend(0.6,0.7,0.75,0.85);
   leg3->AddEntry(tg_th[0],"tg.th[0]","L");
   leg3->AddEntry(tg_th[1],"tg.th[1]","L");
   leg3->Draw();

   c2->cd(2);
   T->Draw("tg_p[0]>>tg_p0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("tg_p[1]>>tg_p1",Form("rate*(%s)",twotrk.Data()));
   tg_p[0]->SetLineColor(2);
   tg_p[1]->SetLineColor(4);
   tg_p[0]->Draw("HIST");
   tg_p[1]->Draw("HIST same");
   tg_p[0]->SetTitle("two trks tg.p;tg.p;;"); 
   
   TLegend *leg4 = new TLegend(0.6,0.7,0.75,0.85);
   leg4->AddEntry(tg_p[0],"tg.p[0]","L");
   leg4->AddEntry(tg_p[1],"tg.p[1]","L");
   leg4->Draw();

   c2->cd(3);
   T1->Draw("tg_th>>tg_th_onehit","rate*(main_r[0]>500 && (tg_trid==main_trid[0]))","hist");
   tg_th_onehit->SetTitle("one trk tg.th;tg.th;;"); 

   c2->cd(4);
   T1->Draw("tg_p>>tg_p_onehit","rate*(main_r[0]>500 && (tg_trid==main_trid[0]))","hist");
   tg_p_onehit->SetTitle("one trk tg.p;tg.p;;"); 

   TCanvas *c3=new TCanvas("c3","c3",1500,1000);
   c3->Divide(2,1);
   main_ph=new TH2D("main_ph","main_ph",100,-Pi(),Pi(),100,-Pi(),Pi());
   tg_ph=new TH2D("tg_ph","tg_ph",100,-Pi(),Pi(),100,-Pi(),Pi());

   c3->cd(1);
   T->Draw("main_ph[1]:main_ph[0]>>main_ph",Form("rate*(%s)",twotrk.Data()),"COLZ");
   main_ph->SetTitle("two trks main ph;main.ph[0];main.ph[1];");

   c3->cd(2);
   T->Draw("tg_ph[1]:tg_ph[0]>>tg_ph",Form("rate*(%s)",twotrk.Data()),"COLZ");
   tg_ph->SetTitle("two trks tg ph;tg.ph[0];tg.ph[1];");

   TCanvas *c4=new TCanvas("c4","c4",1500,1000);
   c4->Divide(4,2);

   TH1D *sieve_ph[7];
   for(int ii=0; ii<7; ii++){
     c4->cd(ii+1);
     double ph_lo = -Pi()/28.0 + ii*2*Pi()/7.0;
     double ph_hi = -Pi()/28.0 + (ii+1)*2*Pi()/7.0;
     if(ph_lo>Pi() && ii!=3) ph_lo=ph_lo-2*Pi();
     if(ph_hi>Pi() && ii!=3) ph_hi=ph_hi-2*Pi();

     sieve_ph[ii] = new TH1D(Form("sieve_ph%d",ii),Form("sieve_ph%d",ii),50,ph_lo,ph_hi);

     if(ii==3) T->Draw(Form("fmod(sieve_ph+2*Pi(),2*Pi())>>sieve_ph%d",ii),Form("rate*(%s)",twotrk.Data()),"HIST");
     else T->Draw(Form("sieve_ph>>sieve_ph%d",ii),Form("rate*(%s)",twotrk.Data()),"HIST");
   }

   c4->cd(8);
   TH2D *sieve_ph2d = new TH2D("sieve_ph2d","sieve_ph2d",200,-100,100,200,-100,100);
   T->Draw("sieve_y:sieve_x>>sieve_ph2d",Form("rate*(%s)",twotrk.Data()),"COLZ");

   TCanvas *c5=new TCanvas("c5","c5",1500,1000);
   c5->Divide(4,2);

   TH1D *sieve1_ph[7];
   for(int ii=0; ii<7; ii++){
     c5->cd(ii+1);
     double ph_lo = -Pi()/28.0 + ii*2*Pi()/7.0;
     double ph_hi = -Pi()/28.0 + (ii+1)*2*Pi()/7.0;
     if(ph_lo>Pi() && ii!=3) ph_lo=ph_lo-2*Pi();
     if(ph_hi>Pi() && ii!=3) ph_hi=ph_hi-2*Pi();

     sieve1_ph[ii] = new TH1D(Form("sieve1_ph%d",ii),Form("sieve1_ph%d",ii),50,ph_lo,ph_hi);

     if(ii==3) T1->Draw(Form("fmod(sieve_ph+2*Pi(),2*Pi())>>sieve1_ph%d",ii),"rate*(main_r[0]>500 && (sieve_trid==main_trid[0]))","HIST");
     else T1->Draw(Form("sieve_ph>>sieve1_ph%d",ii),"rate*(main_r[0]>500 && (sieve_trid==main_trid[0]))","HIST");
   }

   c5->cd(8);
   TH2D *sieve1_ph2d = new TH2D("sieve1_ph2d","sieve1_ph2d",200,-100,100,200,-100,100);
   T1->Draw("sieve_y:sieve_x>>sieve1_ph2d","rate*(main_r[0]>500 && (sieve_trid==main_trid[0]))","COLZ");


}
