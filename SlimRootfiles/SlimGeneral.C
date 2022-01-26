#include "SlimGeneral.h"

using namespace std;
void SlimGeneral(TString infile, TString outfile, bool isMoller){

/*** SlimGeneral
 * generate slimed rootfiles for the primary moller electrons
 * can generate the rootfile for one track events, or two track events
 * cuts only for moller events
 * @filename: input remoll root files
 * @rootname: output root file name
 * @treename: input remoll tree name
 * @isMoller: True=moller
 * 	      Flase=not moller
 * @nr: 1=only generate one hit root file
 * 	2=only generate two hits root file
 * 	3=both 1 and 2
***/

   ROOT::EnableImplicitMT();

   //auto fileName = "/w/halla-scifs17exp/moller12gev/hanjie/remoll_optics/remoll/rootfiles/moller_pass5_LH2_*";
   
   //bool isMoller=false;
   //TString rootname ="c12_optics1_dsc_ep_pass4";
   auto fileName = Form("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/%s_*",infile.Data());
   auto treeName = "T";
   ROOT::RDataFrame d(treeName, fileName);

   //TChain chain("T");
   //chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_1.root");
   //chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_2.root");
   //chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_3.root");
   //chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_4.root");
   //chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_5.root");
 
   //ROOT::RDataFrame d(chain);

   if(isMoller){
     int nr=1;   // 1; only generate one hit root file; 2: only generate two hit file; 3: both 1 and 2
     GoodEventsMoller(d, nr, outfile);
/*
     switch(nr){
	case 1:
	  gSystem->Exec(Form("mv onehit.root rootfiles/%s_onehit.root",outfile.Data()));
	  break;
	case 2:
	  gSystem->Exec(Form("mv twohits.root rootfiles/%s_twohits.root",outfile.Data()));
	  break;
	case 3:
	  gSystem->Exec(Form("mv onehit.root rootfiles/%s_onehit.root",outfile.Data()));
	  gSystem->Exec(Form("mv twohits.root rootfiles/%s_twohits.root",outfile.Data()));
     }
*/
   }
   else{
     GoodEventsGeneral(d, outfile);
//     gSystem->Exec(Form("mv general.root rootfiles/%s_slim.root",outfile.Data()));
   }
   

}
