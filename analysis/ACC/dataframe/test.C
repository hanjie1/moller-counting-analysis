#include "/w/halla-scshelf2102/moller12gev/hanjie/remoll/include/remolltypes.hh"

void test(){
   //auto fileName = "/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_C12_elastic_p3test_1.root";
   auto fileName = "/w/halla-scshelf2102/moller12gev/hanjie/remoll/rootfiles/moller_pass5_LH2_1.root";
   auto treeName = "T";
 
   ROOT::RDataFrame d(treeName, fileName);

   auto n_cut = [](const std::vector<remollGenericDetectorHit_t> &hit) { return hit[0].det==30; };
   auto nentries = d.Filter(n_cut, {"hit"});

   //auto goodele_main="hit.det==28 && hit.pid==11 && hit.mtrid==0 && hit.trid==1";
   //auto selected_d = d.Define("maindet_hit",goodele_main).Define("good_hit","Sum(maindet_hit)").Filter("good_hit>0");

   //auto hitdet = selected_d.Histo1D("part.th");

//   auto c1 = new TCanvas();
//   hitdet->DrawCopy();
//   auto d1=selected_d.Display({"part.th","hit.r","hit.det","maindet_hit","good_hit"},3);
 //  d1->Print();
cout<<"================================================="<<endl;
   //auto d2=d.Display({"part.th","hit.r","hit.det","maindet_hit","good_hit"},3);
   auto d2=d.Display({"part.th","hit.r","hit.det"},3);
   d2->Print();

//auto colNames = d.GetColumnNames();
// Print columns' names
//for (auto &&colName : colNames) std::cout << colName << std::endl;


}
