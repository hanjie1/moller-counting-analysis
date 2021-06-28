using namespace TMath;
void PlotFF_el(){
  // Physical Constants      
  double a = 1.65;                            // well parameter [fm]

  //double FF = (1.0 - (q2*a*a)/9.0)*exp(-(q2*a*a)/4.0);        // Form Factor

   TF1 *fa1 = new TF1("fa1",Form("pow((1.0 - (x*%f*%f)/9.0)*exp(-(x*%f*%f)/4.0),2)",a,a,a,a),0,12);

   TCanvas *c1=new TCanvas("c1","c1",300,1000);
   fa1->Draw();
   gPad->SetLogy();
   
   fa1->GetYaxis()->SetRangeUser(1e-7,1);
  



}
