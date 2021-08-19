using namespace TMath;

void TwoHits(){

   TChain *T=new TChain("T");
   T->Add("/home/hanjie/moller/optics_analysis/Rootfiles/trackhits_remoll_test_allSD.root");


   TString twotrk="ntrk==2 && ring.r[0]>500 && abs(ring.ph[0]-ring.ph[1])>0.001";
   //TString twotrk="ntrk==2 && ring.r[0]>500";

   TH1D* ring_r[2];
   TH2D* ring_ph;
   TH1D* ring_p[2];
   TH1D* tg_th[2];
   TH2D* tg_ph;
   TH1D* tg_p[2];

   ring_r[0]=new TH1D("ring_r0","ring_r0",200,500,1500);
   ring_r[1]=new TH1D("ring_r1","ring_r1",200,500,1500);

   ring_p[0]=new TH1D("ring_p0","ring_p0",200,0,11000);
   ring_p[1]=new TH1D("ring_p1","ring_p1",200,0,11000);

   tg_th[0]=new TH1D("tg_th0","tg_th0",200,0,0.025);
   tg_th[1]=new TH1D("tg_th1","tg_th1",200,0,0.025);

   tg_p[0]=new TH1D("tg_p0","tg_p0",200,0,11000);
   tg_p[1]=new TH1D("tg_p1","tg_p1",200,0,11000);

   TH1D *ring_r_onehit = new TH1D("ring_r_onehit","ring_r_onehit",200,500,1500);   
   TH1D *ring_p_onehit = new TH1D("ring_p_onehit","ring_p_onehit",200,0,11000);   
   TH1D *tg_th_onehit=new TH1D("tg_th_onehit","tg_th_onehit",200,0,0.025);
   TH1D *tg_p_onehit=new TH1D("tg_p_onehit","tg_p_onehit",200,0,11000);


   TCanvas *c1=new TCanvas("c1","c1",1500,1000);
   c1->Divide(2,2);
   c1->cd(1);
   T->Draw("ring.r[0]>>ring_r0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("ring.r[1]>>ring_r1",Form("rate*(%s)",twotrk.Data()));
   ring_r[0]->SetLineColor(2);
   ring_r[1]->SetLineColor(4);
   ring_r[0]->Draw("HIST");
   ring_r[1]->Draw("HIST same");
   ring_r[0]->SetTitle("two trks ring.r;ring.r;;"); 

   Double_t nhit1 = ring_r[0]->Integral();
   Double_t nhit2 = ring_r[1]->Integral();

   TLatex tex;
   tex.SetTextSize(0.03);
   tex.DrawLatexNDC(.2,.8,Form("N0=%e",nhit1));
   tex.DrawLatexNDC(.2,.75,Form("N1=%e",nhit2));
   
   TLegend *leg1 = new TLegend(0.6,0.7,0.75,0.85);
   leg1->AddEntry(ring_r[0],"ring.r[0]","L");
   leg1->AddEntry(ring_r[1],"ring.r[1]","L");
   leg1->Draw();

   c1->cd(2);
   T->Draw("ring.p[0]>>ring_p0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("ring.p[1]>>ring_p1",Form("rate*(%s)",twotrk.Data()));
   ring_p[0]->SetLineColor(2);
   ring_p[1]->SetLineColor(4);
   ring_p[0]->Draw("HIST");
   ring_p[1]->Draw("HIST same");
   ring_p[0]->SetTitle("two trks ring.p;ring.p;;"); 
   
   TLegend *leg2 = new TLegend(0.6,0.7,0.75,0.85);
   leg2->AddEntry(ring_p[0],"ring.p[0]","L");
   leg2->AddEntry(ring_p[1],"ring.p[1]","L");
   leg2->Draw();

   c1->cd(3);
   T->Draw("ring.r>>ring_r_onehit","rate*(ntrk==1 && ring.r>500)");
   ring_r_onehit->SetTitle("one trk ring.r;ring.r;;"); 

   Double_t nhit3 = ring_r_onehit->Integral();

   TLatex tex1;
   tex1.SetTextSize(0.03);
   tex1.DrawLatexNDC(.2,.8,Form("N=%e",nhit3));

   c1->cd(4);
   T->Draw("ring.p>>ring_p_onehit","rate*(ntrk==1 && ring.r>500)");
   ring_p_onehit->SetTitle("one trk ring.p;ring.p;;"); 


   TCanvas *c2=new TCanvas("c2","c2",1500,1000);
   c2->Divide(2,2);
   c2->cd(1);
   T->Draw("tg.th[0]>>tg_th0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("tg.th[1]>>tg_th1",Form("rate*(%s)",twotrk.Data()));
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
   T->Draw("tg.p[0]>>tg_p0",Form("rate*(%s)",twotrk.Data()));
   T->Draw("tg.p[1]>>tg_p1",Form("rate*(%s)",twotrk.Data()));
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
   T->Draw("tg.th>>tg_th_onehit","rate*(ntrk==1 && ring.r>500)");
   tg_th_onehit->SetTitle("one tthk tg.th;tg.th;;"); 

   c2->cd(4);
   T->Draw("tg.p>>tg_p_onehit","rate*(ntrk==1 && ring.r>500)");
   tg_p_onehit->SetTitle("one trk tg.p;tg.p;;"); 

   TCanvas *c3=new TCanvas("c3","c3",1500,1000);
   c3->Divide(2,1);
   ring_ph=new TH2D("ring_ph","ring_ph",100,-Pi(),Pi(),100,-Pi(),Pi());
   tg_ph=new TH2D("tg_ph","tg_ph",100,-Pi(),Pi(),100,-Pi(),Pi());

   c3->cd(1);
   T->Draw("ring.ph[1]:ring.ph[0]>>ring_ph",Form("rate*(%s)",twotrk.Data()),"COLZ");
   ring_ph->SetTitle("two trks ring ph;ring.ph[0];ring.ph[1];");

   c3->cd(2);
   T->Draw("tg.ph[1]:tg.ph[0]>>tg_ph",Form("rate*(%s)",twotrk.Data()),"COLZ");
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

     if(ii==3) T->Draw(Form("fmod(sieve.ph+2*Pi(),2*Pi())>>sieve_ph%d",ii),Form("rate*(%s)",twotrk.Data()),"HIST");
     else T->Draw(Form("sieve.ph>>sieve_ph%d",ii),Form("rate*(%s)",twotrk.Data()),"HIST");
   }

   c4->cd(8);
   TH2D *sieve_ph2d = new TH2D("sieve_ph2d","sieve_ph2d",200,-100,100,200,-100,100);
   T->Draw("sieve.y:sieve.x>>sieve_ph2d",Form("rate*(%s)",twotrk.Data()),"COLZ");

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

     if(ii==3) T->Draw(Form("fmod(sieve.ph+2*Pi(),2*Pi())>>sieve1_ph%d",ii),"rate*(ring.r>500)","HIST");
     else T->Draw(Form("sieve.ph>>sieve1_ph%d",ii),"rate*(ring.r>500)","HIST");
   }

   c5->cd(8);
   TH2D *sieve1_ph2d = new TH2D("sieve1_ph2d","sieve1_ph2d",200,-100,100,200,-100,100);
   T->Draw("sieve.y:sieve.x>>sieve1_ph2d","rate*(ring.r>500)","COLZ");


}
