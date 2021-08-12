#include "Acceptance.h"

void Acceptance(){
   auto stpw = new TStopwatch();
   stpw->Start();
   ::Info("", "New analysis method via using RDataFrame is starting:");

   bool check_twohits=false;

   ROOT::EnableImplicitMT();
   auto fileName = Form("/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_H1_moller_p%d_newfield*",pass);
   auto treeName = "T";
 
   ROOT::RDataFrame d(treeName, fileName);

   // cuts
   std::string_view main_el; 
   if(ismoller)
       main_el="hit.det==28 && hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2)";   // moller primary events at maine detector
   else
       main_el="hit.det==28 && hit.pid==11 && hit.mtrid==0 && hit.trid==1";   // elastic primary events at main detector

   // apply cuts and generate new columns
   auto selected_d = d.Define("maindet_hit",main_el).Define("good_hit","Sum(maindet_hit)").Define("trid","hit.trid[maindet_hit]").Filter("good_hit>0");
   std::cout <<"1:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   // generate small root file for one hit events
   auto onehit_d = selected_d.Filter("good_hit==1");

   std::string_view rootname;
   if(ismoller) rootname=Form("moller_small_p%d.root",pass);
   else rootname=Form("C12el_small_p%d.root",pass);
   
   GenSmallRootfile(onehit_d,rootname);

   std::cout <<"11:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   ROOT::RDataFrame newdf("T",rootname);
   
   //auto d1=newdf.Display();
   //d1->Print();

   // check two hits events
   if(check_twohits) CheckTWOhits(selected_d);

   // make plots
   SetXYPhi();

   ROOT::RDF::RResultPtr<TH1D> tgth_in;
   ROOT::RDF::RResultPtr<TH1D> tgth_main[6][7][4];
   TH1D *tgth_acc[6][7][4];

   ROOT::RDF::RResultPtr<TH1D> tgph_in;
   ROOT::RDF::RResultPtr<TH1D> tgph_main[6][7][4];
   TH1D *tgph_acc[6][7][4];

   ROOT::RDF::RResultPtr<TH1D> tgp_in;
   ROOT::RDF::RResultPtr<TH1D> tgp_main[6][7][4];
   TH1D *tgp_acc[6][7][4];

   ROOT::RDF::RResultPtr<TH2D> tg_thph_in;
   ROOT::RDF::RResultPtr<TH2D> tg_thph_main[6][7][4];

   ROOT::RDF::RResultPtr<TH2D> tg_thp_in;
   ROOT::RDF::RResultPtr<TH2D> tg_thp_main[6][7][4];

   TString tg_cuts;
   if(ismoller) tg_cuts="part.p[0]>1000 && part.p[1]>1000";
   else tg_cuts="part.p[0]>1000";

   auto tg_df = d.Filter(tg_cuts.Data());

   tgth_in = tg_df.Histo1D<Double_t>({"tgth_in","tgth_in",50,0,0.024},"part.th","rate");
   tgph_in = tg_df.Histo1D<Double_t>({"tgph_in","tgph_in",50,-Pi(),Pi()},"part.ph","rate");
   tgp_in = tg_df.Histo1D<Double_t>({"tgp_in","tgp_in",50,0,11000},"part.p","rate");

   tg_thph_in = tg_df.Histo2D<Double_t>({"tg_thph_in","tg_thph_in",50,0,0.024,50,-Pi(),Pi()},"part.th","part.ph","rate");
   tg_thp_in = tg_df.Histo2D<Double_t>({"tg_thp_in","tg_thp_in",50,0,0.024,50,0,11000},"part.th","part.p","rate");

   std::cout <<"12:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   for(int ii=0; ii<6; ii++){
    for(int jj=0; jj<7; jj++){
     for(int kk=0; kk<4; kk++){
	TString cuts;
        if(jj==3 && kk==2) 
	   cuts = Form("(main_r>%f && main_r<%f) && ((main_ph>%f && main_ph<=%f) || (main_ph>=%f && main_ph<=%f))",r[ii],r[ii+1],ph[jj][kk],Pi(),-Pi(),ph[jj][kk+1]);
	else 
  	   cuts = Form("(main_r>%f && main_r<%f) && (main_ph>%f && main_ph<=%f)",r[ii],r[ii+1],ph[jj][kk],ph[jj][kk+1]); 

	auto sec_df = newdf.Filter(cuts.Data());

	// target theta acceptance
	tgth_main[ii][jj][kk] = sec_df.Histo1D<Double_t>({Form("tgth_main_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgth_main_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024},"tg_th","rate");
	
	// target phi acceptance
	tgph_main[ii][jj][kk] = sec_df.Histo1D<Double_t>({Form("tgph_main_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgph_main_r%ds%dp%d",ii+1,jj+1,kk+1),50,-Pi(),Pi()},"tg_ph","rate");
	
	// target p acceptance
	tgp_main[ii][jj][kk] = sec_df.Histo1D<Double_t>({Form("tgp_main_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgp_main_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,11000},"tg_p","rate");

	// ph vs. th
	tg_thph_main[ii][jj][kk] = sec_df.Histo2D<Double_t>({Form("tg_thph_main_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tg_thph_main_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024,50,-Pi(),Pi()},
								"tg_th","tg_ph","rate");

	// p vs. th
	tg_thp_main[ii][jj][kk] = sec_df.Histo2D<Double_t>({Form("tg_thp_main_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tg_thp_main_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024,50,0,11000},
								"tg_th","tg_p","rate");
     }
    }
   }


/*
   TH1D *test=new TH1D("test","test",50,0,0.024);
   for(int ii=1; ii<=50; ii++){
	Double_t n_in = tgth_in.GetPtr()->GetBinContent(ii);
	Double_t n_main = tgth_main[5][0][0].GetPtr()->GetBinContent(ii);

	Double_t ratio = 0;
	if(n_in!=0) ratio=n_main/n_in;
	test->SetBinContent(ii,ratio);	
   }

   test->Draw();
*/

   std::cout <<"2:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   // acceptance plots
 
   // sector

   PlotSecACC( tgth_in, tgth_main, "tgth");
   PlotSecACC( tgph_in, tgph_main, "tgph");
   PlotSecACC( tgp_in, tgp_main, "tgp");

   std::cout <<"3:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   // ring

   PlotRingACC(tgth_in, tgth_main, "tgth"); 
   PlotRingACC(tgph_in, tgph_main, "tgph"); 
   PlotRingACC(tgp_in, tgp_main, "tgp"); 

   std::cout <<"4:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   // sector 2d

   PlotSecAcc2D(tg_thph_in, tg_thph_main, "tgth", "tgph");
   PlotSecAcc2D(tg_thp_in, tg_thp_main, "tgth", "tgp");

   PlotRingAcc2D(tg_thph_in, tg_thph_main, "tgth", "tgph");
   PlotRingAcc2D(tg_thp_in, tg_thp_main, "tgth", "tgp");



   std::cout <<"5:  "<< stpw->RealTime() << std::endl;


}
