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
***/

   //ROOT::EnableImplicitMT();

   //auto fileName = "/w/halla-scifs17exp/moller12gev/hanjie/remoll_optics/remoll/rootfiles/moller_pass5_LH2_*";
   
   //bool isMoller=false;
   //TString rootname ="c12_optics1_dsc_ep_pass4";
   //auto fileName = Form("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/%s*",infile.Data());
   //auto treeName = "T";
   //ROOT::RDataFrame d(treeName, fileName);

   TChain chain("T");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_1.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_2.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_3.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_4.root");
   chain.Add("/lustre19/expphy/volatile/halla/moller12gev/hanjie/remoll_rootfiles/moller_pass5_LH2_5.root");
 
   ROOT::RDataFrame d(chain);

   if(isMoller){
     int nr=1;   // 1; only generate one hit root file; 2: only generate two hit file;
     auto d_new=GenMollerDF(d);
     auto d_moller = d_new.Define("ntrk",check_trid, {"trid"});

     switch(nr){
	case 1:
           auto onehit_d = d_moller.Filter("ntrk==1");
           auto rootname1=Form("rootfiles/%s_onehit.root",outfile.Data());
	   SlimOneTrkRootfile(onehit_d,rootname1);
	   break;
     } 
   }
   else{
     auto d_new=GenEpDF(d);

     auto rootname=Form("rootfiles/%s_slim.root",outfile.Data());
     SlimOneTrkRootfile(d_new,rootname);
   }
   

}
