void test() {
   TH1F *h = new TH1F("h","test",30,-3,3);
   h->FillRandom("gaus",10000);
   h->Draw();
   TText t;
   t.SetTextSize(0.02);
   t.SetTextAlign(22);
   Double_t yt = - h->GetMaximum()/15.;   
   for (Int_t i=1;i<=30;i++) t.DrawText(h->GetBinCenter(i),yt,Form("%d",i%10));

}
