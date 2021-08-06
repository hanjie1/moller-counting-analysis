#include "Acceptance.h"

void Acceptance(){
   auto stpw = new TStopwatch();
   stpw->Start();
   ::Info("", "New analysis method via using RDataFrame is starting:");

   bool check_twohits=false;

   ROOT::EnableImplicitMT();
   auto fileName = "/w/halla-scifs17exp/moller12gev/hanjie/remoll/rootfiles/remoll_H1_moller_p5_newfield1.root";
   auto treeName = "T";
 
   ROOT::RDataFrame d(treeName, fileName);

   // cuts
   auto main_el="hit.det==28 && hit.pid==11 && hit.mtrid==0 && hit.trid==1";   // elastic primary events at main detector
   auto main_moller="hit.det==28 && hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2)";   // moller primary events at maine detector

   // apply cuts and generate new columns
   auto selected_d = d.Define("maindet_hit",main_moller).Define("good_hit","Sum(maindet_hit)").Define("trid","hit.trid[maindet_hit]").Filter("good_hit>0");

   // generate small root file for one hit events
   auto onehit_d = selected_d.Filter("good_hit==1");

   GenSmallRootfile(onehit_d,"small.root");
   ROOT::RDataFrame newdf("T","small.root");
   
   //auto d1=newdf.Display();
   //d1->Print();

   // check two hits events
   if(check_twohits) CheckTWOhits(selected_d);

   // make plots
   SetXYPhi();

   std::cout <<"1:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

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
   TH2D *tg_thph_acc[6][7][4];

   ROOT::RDF::RResultPtr<TH2D> tg_thp_in;
   ROOT::RDF::RResultPtr<TH2D> tg_thp_main[6][7][4];
   TH2D *tg_thp_acc[6][7][4];


   tgth_in = d.Histo1D<Double_t>({"tgth_in","tgth_in",50,0,0.024},"part.th","rate");
   tgph_in = d.Histo1D<Double_t>({"tgph_in","tgph_in",50,-Pi(),Pi()},"part.ph","rate");
   tgp_in = d.Histo1D<Double_t>({"tgp_in","tgp_in",50,0,11000},"part.p","rate");

   tg_thph_in = d.Histo2D<Double_t>({"tg_thph_in","tg_thph_in",50,0,0.024,50,-Pi(),Pi()},"part.th","part.ph","rate");
   tg_thp_in = d.Histo2D<Double_t>({"tg_thp_in","tg_thp_in",50,0,0.024,50,0,11000},"part.th","part.p","rate");

   for(int ii=0; ii<6; ii++){
    for(int jj=0; jj<7; jj++){
     for(int kk=0; kk<4; kk++){
	TString cuts;
        if(jj==3 && kk==2) 
	   cuts = Form("(main_r>%f && main_r<%f) && ((main_ph>%f && main_ph<%f) || (main_ph>%f && main_ph<%f))",r[ii],r[ii+1],ph[jj][kk],Pi(),-Pi(),ph[jj][kk+1]);
	else 
  	   cuts = Form("(main_r>%f && main_r<%f) && (main_ph>%f && main_ph<%f)",r[ii],r[ii+1],ph[jj][kk],ph[jj][kk+1]); 

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
   PlotSecACC( tgth_in, tgth_main, "th");

  std::cout <<"3:  "<< stpw->RealTime() << std::endl;
  stpw->Start();

   PlotSecACC( tgph_in, tgph_main, "ph");

  std::cout <<"4:  "<< stpw->RealTime() << std::endl;
  stpw->Start();

   PlotSecACC( tgp_in, tgp_main, "p");

  std::cout <<"5:  "<< stpw->RealTime() << std::endl;
/*
   TH1D *tgth_acc_r[6];
   TH1D *tgph_acc_r[6];
   TH1D *tgp_acc_r[6];
   
   TH2D *tgthph_acc_r[6];
   TH2D *tgthp_acc_r[6];

   TList *list = new TList;

  list->Add(h1);
  list->Add(h2);
  list->Add(h3);
  TH1F *h = (TH1F*)h1->Clone("h");
  h->Reset();
  h->Merge(list);
  h->Draw();
   
   for

   std::cout <<"3:  "<< stpw->RealTime() << std::endl;
   stpw->Start();

   gStyle->SetOptStat(111101);

   TCanvas *c1 = new TCanvas();
   c1->Divide(4,3);
   for(int ii=0; ii<4; ii++){
	c1->cd(ii+1);
        tgth_acc[5][0][ii]->Draw("hist");
   }

   for(int ii=0; ii<4; ii++){
	c1->cd(ii+5);
        tgph_acc[5][0][ii]->Draw("hist");
   }
   for(int ii=0; ii<4; ii++){
	c1->cd(ii+9);
        tgp_acc[5][0][ii]->Draw("hist");
   }

   c1->Print("plots/accep.pdf[");
*/


}
