#include "include/GenRoottypes.h"

void MakePlots(){

     TString filename;
     cout<<"Which root file?    ";
     cin>>filename;

     TFile *f = new TFile(Form("Rootfiles/trackhits_%s.root",filename.Data()));

     TTree *T = (TTree*) f->Get("T");
/*
     vector<detHit> *sieve=0;
     vector<detHit> *ring=0;
     vector<detHit> *gem_f1=0;
     vector<detHit> *gem_f2=0;
     vector<detHit> *gem_b1=0;
     vector<detHit> *gem_b2=0;
     vector<tgPart> *tg=0;

     int ntrk;
     double rate;

     T->SetBranchAddress("sieve", &sieve);
     T->SetBranchAddress("ring", &ring);
     T->SetBranchAddress("gem_f1", &gem_f1);
     T->SetBranchAddress("gem_f2", &gem_f2);
     T->SetBranchAddress("gem_b1", &gem_b1);
     T->SetBranchAddress("gem_b2", &gem_b2);
     T->SetBranchAddress("tg", &tg);
     T->SetBranchAddress("rate", &rate);
     T->SetBranchAddress("ntrk", &ntrk);
*/
     TCut nodump = "sieve.r>35.4";
     
     TH2F *hxy_ring = new TH2F("hxy_ring","y vs. x distribution at the main detector",500,-1500,1500,500,-1500,1500);
     TH2F *hthr_ring = new TH2F("hthr_ring","r vs. theta distribution at the main detector",500,0,0.022,500,500,1500);
     TH2F *hxy_sieve = new TH2F("hxy_sieve","y vs. x distribution at the sieve",150,-150,150,150,-150,150);
     TH2F *hthr_sieve = new TH2F("hthr_sieve","r vs. theta distribution at the sieve",500,0,0.022,150,0,150);

     TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
     c1->Divide(2,2);
     c1->cd(1);   
     T->Draw("sieve.y:sieve.x>>hxy_sieve","rate","COLZ");
     hxy_sieve->GetXaxis()->SetTitle("x"); 
     hxy_sieve->GetYaxis()->SetTitle("y"); 
     hxy_sieve->SetTitle("y vs x at sieve (no cut)");

     c1->cd(2);
     T->Draw("ring.y:ring.x>>hxy_ring",nodump*"rate","COLZ"); 
     hxy_ring->GetXaxis()->SetTitle("x"); 
     hxy_ring->GetYaxis()->SetTitle("y"); 
     hxy_ring->SetTitle("y vs x at ring (sieve.r>35.4)");

     c1->cd(3);
     T->Draw("sieve.r:tg.th>>hthr_sieve",nodump*"rate","COLZ"); 
     hthr_sieve->GetXaxis()->SetTitle("tg.th"); 
     hthr_sieve->GetYaxis()->SetTitle("r"); 
     hthr_sieve->SetTitle("r vs th at sieve (sieve.r>35.4)");

     c1->cd(4);
     T->Draw("ring.r:tg.th>>hthr_ring",nodump*"rate","COLZ"); 
     hthr_ring->GetXaxis()->SetTitle("tg.th"); 
     hthr_ring->GetYaxis()->SetTitle("r"); 
     hthr_ring->SetTitle("r vs th at ring (sieve.r>35.4)");

     TH2F *hxy_gemf1 = new TH2F("hxy_gemf1","y vs. x distribution at the GEM f1",500,-1500,1500,500,-1500,1500);
     TH2F *hthr_gemf1 = new TH2F("hthr_gemf1","r vs. theta distribution at the GEM f1",500,0,0.022,500,500,1500);
     TH2F *hxy_gemf2 = new TH2F("hxy_gemf2","y vs. x distribution at the GEM f2",500,-1500,1500,500,-1500,1500);
     TH2F *hthr_gemf2 = new TH2F("hthr_gemf2","r vs. theta distribution at the GEM f2",500,0,0.022,500,500,1500);
     TH2F *hxy_gemb1 = new TH2F("hxy_gemb1","y vs. x distribution at the GEM b1",500,-1500,1500,500,-1500,1500);
     TH2F *hthr_gemb1 = new TH2F("hthr_gemb1","r vs. theta distribution at the GEM b1",500,0,0.022,500,500,1500);
     TH2F *hxy_gemb2 = new TH2F("hxy_gemb2","y vs. x distribution at the GEM b2",500,-1500,1500,500,-1500,1500);
     TH2F *hthr_gemb2 = new TH2F("hthr_gemb2","r vs. theta distribution at the GEM b2",500,0,0.022,500,500,1500);

     TCanvas *c2 = new TCanvas("c2","c2",1500,1500);
     c2->Divide(2,4);
     c2->cd(1);
     T->Draw("gem_f1.y:gem_f1.x>>hxy_gemf1",nodump*"rate","COLZ"); 
     hxy_gemf1->GetXaxis()->SetTitle("x"); 
     hxy_gemf1->GetYaxis()->SetTitle("y"); 
     hxy_gemf1->SetTitle("y vs x at gem_f1 (sieve.r>35.4)");

     c2->cd(2);
     T->Draw("gem_f1.r:tg.th>>hthr_gemf1",nodump*"rate","COLZ"); 
     hthr_gemf1->GetXaxis()->SetTitle("tg.th"); 
     hthr_gemf1->GetYaxis()->SetTitle("r"); 
     hthr_gemf1->SetTitle("r vs th at gem_f1 (sieve.r>35.4)");

     c2->cd(3);
     T->Draw("gem_f2.y:gem_f2.x>>hxy_gemf2",nodump*"rate","COLZ"); 
     hxy_gemf2->GetXaxis()->SetTitle("x"); 
     hxy_gemf2->GetYaxis()->SetTitle("y"); 
     hxy_gemf2->SetTitle("y vs x at gem_f2 (sieve.r>35.4)");

     c2->cd(4);
     T->Draw("gem_f2.r:tg.th>>hthr_gemf2",nodump*"rate","COLZ"); 
     hthr_gemf2->GetXaxis()->SetTitle("tg.th"); 
     hthr_gemf2->GetYaxis()->SetTitle("r"); 
     hthr_gemf2->SetTitle("r vs th at gem_f2 (sieve.r>35.4)");

     c2->cd(5);
     T->Draw("gem_b1.y:gem_b1.x>>hxy_gemb1",nodump*"rate","COLZ"); 
     hxy_gemb1->GetXaxis()->SetTitle("x"); 
     hxy_gemb1->GetYaxis()->SetTitle("y"); 
     hxy_gemb1->SetTitle("y vs x at gem_b1 (sieve.r>35.4)");

     c2->cd(6);
     T->Draw("gem_b1.r:tg.th>>hthr_gemb1",nodump*"rate","COLZ"); 
     hthr_gemb1->GetXaxis()->SetTitle("tg.th"); 
     hthr_gemb1->GetYaxis()->SetTitle("r"); 
     hthr_gemb1->SetTitle("r vs th at gem_b1 (sieve.r>35.4)");

     c2->cd(7);
     T->Draw("gem_b2.y:gem_b2.x>>hxy_gemb2",nodump*"rate","COLZ"); 
     hxy_gemb2->GetXaxis()->SetTitle("x"); 
     hxy_gemb2->GetYaxis()->SetTitle("y"); 
     hxy_gemb2->SetTitle("y vs x at gem_b2 (sieve.r>35.4)");

     c2->cd(8);
     T->Draw("gem_b2.r:tg.th>>hthr_gemb2",nodump*"rate","COLZ"); 
     hthr_gemb2->GetXaxis()->SetTitle("tg.th"); 
     hthr_gemb2->GetYaxis()->SetTitle("r"); 
     hthr_gemb2->SetTitle("r vs th at gem_b2 (sieve.r>35.4)");

     TH2F *hrprime_th_ring = new TH2F("hrprime_th_ring","r' vs. th distribution at the main detector",500,0,0.025,500,0.0,0.08);
     TCanvas *c3 = new TCanvas("c3","c3",1500,1500);
     c3->Divide(2,1);
     c3->cd(1);
     hthr_ring->Draw("COLZ");
     c3->cd(2);
     T->Draw("sqrt(ring.px*ring.px+ring.py*ring.py)/ring.pz:tg.th>>hrprime_th_ring",nodump*"rate","COLZ");
     hrprime_th_ring->GetXaxis()->SetTitle("tg.th"); 
     hrprime_th_ring->GetYaxis()->SetTitle("r'"); 
     hrprime_th_ring->SetTitle("r' vs th at ring (sieve.r>35.4)");




     


}
