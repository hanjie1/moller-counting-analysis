#include "MainDis.h"

void MainDis(){

   auto stpw = new TStopwatch();
   stpw->Start();
   ::Info("", "New analysis method via using RDataFrame is starting:");

   ROOT::EnableImplicitMT();
   auto fileName = Form("/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_C12_elastic_p%dtest_*",pass);
   //auto fileName = Form("/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_H1_moller_p%d_newfield*",pass);
   auto treeName = "T";

   ROOT::RDataFrame d(treeName, fileName);

   // cuts
   std::string_view prm_el;
   if(ismoller){
       prm_el="hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2)";   // moller primary events at maine detector
   }
   else{
       prm_el="hit.pid==11 && hit.mtrid==0 && hit.trid==1";   // elastic primary events at main detector
   }

   auto selected_d = d.Define("primary_hit",prm_el).Define("main","hit.det==28").Define("sieve","hit.det==600").Define("gem","hit.det==30")
		      .Define("good_hit","Sum(primary_hit==1 && main==1)").Define("trid","hit.trid[primary_hit && main]").Filter("good_hit==1");

   std::string_view rootname;
   if(ismoller) rootname=Form("moller_small_p%d.root",pass);
   else rootname=Form("C12el_small_p%d.root",pass);

   GenSmallRootfile(selected_d,rootname);

   std::cout <<"1:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   ROOT::RDataFrame newdf("T",rootname);

   SetRPhi();

   ROOT::RDF::RResultPtr<TH1D> gem_r[7];     // r
   ROOT::RDF::RResultPtr<TH1D> gem_rp[7];    // r'
   ROOT::RDF::RResultPtr<TH1D> gem_ph[7];    // phi
   ROOT::RDF::RResultPtr<TH1D> gem_php[7];   // phi'

   ROOT::RDF::RResultPtr<TH2D> sieve_xy;     // r

   auto cutdf1 = newdf.Filter(Form("sieve_r>20 && main_r>%f && tg_p>1000",r[0]));

   sieve_xy = cutdf1.Histo2D<Double_t>({"sieve_xy","y vs. x at sieve",200,-120,120,200,-120,120},"sieve_x","sieve_y","rate");

   for(int ii=0; ii<7; ii++){
        TString cuts;
        if(ii==3)
           cuts = Form("(main_ph>%f && main_ph<=%f) || (main_ph>=%f && main_ph<=%f)",ph_1[ii],Pi(),-Pi(),ph_1[ii+1]);
        else if(ii==6)
           cuts = Form("main_ph>%f && main_ph<=%f",ph_1[ii],ph_1[0]);
	else
           cuts = Form("main_ph>%f && main_ph<=%f",ph_1[ii],ph_1[ii+1]);

        auto sec_df = cutdf1.Filter(cuts.Data());;
 
	gem_r[ii]=sec_df.Histo1D<Double_t>({Form("gem_r_s%d",ii+1),Form("gem_r_s%d",ii+1),500,600,1100},"gem_r0","rate");
	gem_ph[ii]=sec_df.Histo1D<Double_t>({Form("gem_ph_s%d",ii+1),Form("gem_ph_s%d",ii+1),100,-Pi(),Pi()},"gem_ph0","rate");

	gem_rp[ii]=sec_df.Define("gemrp","(gem_r1-gem_r0)/(gem_z1-gem_z0)")
			.Histo1D<Double_t>({Form("gem_r'_s%d",ii+1),Form("gem_r'_s%d",ii+1),500,0,0.1},"gemrp","rate");
	gem_php[ii]=sec_df.Define("gemphp","(gem_ph1-gem_ph0)/(gem_z1-gem_z0)")
			.Histo1D<Double_t>({Form("gem_ph'_s%d",ii+1),Form("gem_ph'_s%d",ii+1),500,-2e-5,2e-5},"gemphp","rate");

   }

   PlotSec(sieve_xy, gem_r,"r");  
   PlotSec(sieve_xy, gem_ph,"ph");  
   PlotSec(sieve_xy, gem_rp,"rp");  
   PlotSec(sieve_xy, gem_php,"php");  

   std::cout <<"3:  "<< stpw->RealTime() << std::endl;
}
