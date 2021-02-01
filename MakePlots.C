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

}
