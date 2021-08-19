using namespace ROOT::VecOps;
using rvec_i = const RVec<int> &;

void test(){
   ROOT::EnableImplicitMT();

   //auto fileName = "/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_test_1.root";
   auto fileName = "/w/halla-scifs17exp/moller12gev/hanjie/remoll_optics/remoll/rootfiles/moller_pass5_LH2_test_2.root";
   auto treeName = "T";
 
   ROOT::RDataFrame d(treeName, fileName);
   bool ismoller=true;
   // cuts
   std::string_view main_el; 
   if(ismoller)
       main_el="hit.det==28 && hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2) && hit.r>500";   // moller primary events at maine detector
   else
       main_el="hit.det==28 && hit.pid==11 && hit.mtrid==0 && hit.trid==1 ";   // elastic primary events at main detector

   // apply cuts and generate new columns
   auto selected_d = d.Define("maindet_hit",main_el).Define("good_hit","Sum(maindet_hit)").Define("trid","hit.trid[maindet_hit]").Filter("good_hit>0");

   auto check_trid = [](rvec_i trid) {
	int newid=1;
	for(int ii=1; ii<trid.size(); ii++){
	  bool found=false;
	  int jj=0;
	  for(jj=0; jj<ii; jj++){
	     if(trid[jj]==trid[ii])
		 break;
	  }
 	  if(jj==ii)newid++;
	}

	return newid;
   };
   auto newdf = selected_d.Define("ntrk",check_trid, {"trid"});
   auto twohits = newdf.Filter("ntrk==2");
   auto onehit = newdf.Filter("ntrk==1");

   cout<<*twohits.Count()<<endl;
   cout<<*onehit.Count()<<endl;

/*
   auto onehit_d = selected_d.Filter("good_hit==1");

   auto d1=selected_d.Display({"hit.r","hit.det","maindet_hit","good_hit","trid"},295);
   d1->Print();
*/
}
