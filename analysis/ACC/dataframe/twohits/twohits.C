#include "twohits.h"
void twohits(){
   ROOT::EnableImplicitMT();

   //auto fileName = "/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_*.root";
   //auto treeName = "T";
   //ROOT::RDataFrame d(treeName, fileName);

   TChain chain("T");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_1.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_2.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_3.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_4.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_5.root");
 
   ROOT::RDataFrame d(chain);

   GoodEvents(d, 3);
}
