using namespace TMath;

void PlotGEM(){

     auto fileName = "twohits.root";
     auto treeName = "T";
     ROOT::RDataFrame d(treeName, fileName);

     auto newdf = d.Define("sec1","sieve_ph>Pi()/14.0 && sieve_ph<6*Pi()/28.").Define("found","Sum(sec1)").Filter("found==1")
		   .Define("sieve_x1","sieve_x[sec1]").Define("sieve_y1","sieve_y[sec1]").Define("newtrid","sieve_trid[sec1]")
		   .Define("opssec1","sieve_trid==(3-newtrid[0])").Define("sieve_x2","sieve_x[opssec1]").Define("sieve_y2","sieve_y[opssec1]")
		   .Define("sec1_gem","gem_trid==newtrid[0] && gem_z==19279.500").Define("gem_x1","gem_x[sec1_gem]")
		   .Define("gem_y1","gem_y[sec1_gem]").Define("opssec_gem","gem_trid==(3-newtrid[0]) && gem_z==19279.500")
		   .Define("gem_x2","gem_x[opssec_gem]").Define("gem_y2","gem_y[opssec_gem]");

   //auto d1=newdf.Display({"sec1","found","sieve_ph","sieve_trid","newtrid","gem_z","sec1_gem","gem_x1","gem_x2"},5);
   //auto d1=newdf.Display({"sec1","found","sieve_ph","sieve_trid","gem_z"},5);
   //d1->Print();

   auto hgem_xy1 = newdf.Histo2D({"gem_xy1","y vs x at gem1",1100,-1100,1100,1100,-1100,1100},"gem_x1","gem_y1","rate");
   auto hgem_xy2 = newdf.Histo2D({"gem_xy2","y vs x at gem1",1100,-1100,1100,1100,-1100,1100},"gem_x2","gem_y2","rate");

   auto hsieve_xy1 = newdf.Histo2D({"sieve_xy1","y vs x at sieve",200,-100,100,200,-100,100},"sieve_x1","sieve_y1","rate");
   auto hsieve_xy2 = newdf.Histo2D({"sieve_xy2","y vs x at sieve",200,-100,100,200,-100,100},"sieve_x2","sieve_y2","rate");


     double x[7][5], y[7][5];

     double delta=2*Pi()/14.0;
     double r1=540;
     double r2=1130;

     TGraph *gsec[7];
     TMultiGraph *mg=new TMultiGraph();

     for(int ii=0; ii<7; ii++){

	double start=ii*2*Pi()/7.0;

        x[ii][0] = r1*cos(start);
	y[ii][0] = r1*sin(start);

        x[ii][1] = r2*cos(start);
	y[ii][1] = r2*sin(start);

        x[ii][2] = r2*cos(start+delta);
	y[ii][2] = r2*sin(start+delta);

        x[ii][3] = r1*cos(start+delta);
	y[ii][3] = r1*sin(start+delta);

        x[ii][4] = r1*cos(start);
	y[ii][4] = r1*sin(start);

	gsec[ii] = new TGraph(5,x[ii],y[ii]);
	gsec[ii]->SetLineColor(2);
	mg->Add(gsec[ii]);
     }

     //hgem_xy1->SetMarkerColor(1);
     //hgem_xy2->SetMarkerColor(4);

     TCanvas *c1=new TCanvas("c1","c1",1500,1500);
     c1->Divide(2,1);
     c1->cd(1);
     mg->Draw("APl");
     hgem_xy1->DrawCopy("colz same");
     hgem_xy2->DrawCopy("colz same");
     mg->SetTitle("gem first plane;gem_x;gem_y;");

     c1->cd(2);
     hsieve_xy1->DrawCopy("COLZ");
     hsieve_xy2->DrawCopy("COLZ same");



}
