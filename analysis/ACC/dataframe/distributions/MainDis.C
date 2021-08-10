#include "MainDis.h"

void MainDis(){

   auto stpw = new TStopwatch();
   stpw->Start();
   ::Info("", "New analysis method via using RDataFrame is starting:");

   //ROOT::EnableImplicitMT();
   auto fileName = Form("/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_H1_moller_p%d_newfield1.root",pass);
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
		      .Define("good_hit","Sum(primary_hit==1 && main==1)").Define("trid","hit.trid[primary_hit==1 && main==1]").Filter("good_hit==1");

   std::string_view rootname;
   if(ismoller) rootname=Form("moller_small_p%d.root",pass);
   else rootname=Form("C12el_small_p%d.root",pass);

   GenSmallRootfile(selected_d,rootname);

   std::cout <<"1:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   ROOT::RDataFrame newdf("T",rootname);




}
