#include "Acceptance.h"

void Acceptance(){

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

   ROOT::RDF::RResultPtr<TH1D> tgth_in[6][7][4];
   ROOT::RDF::RResultPtr<TH1D> tgth_main[6][7][4];
   TH1D *tgth_acc[6][7][4];

   for(int ii=0; ii<6; ii++){
    for(int jj=0; jj<7; jj++){
     for(int kk=0; kk<4; kk++){
	tgth_in[ii][jj][kk] = d.Histo1D<Double_t>({Form("tgth_in_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgth_in_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024},"part.th","rate");
	if(jj==3 && kk==2)
	 tgth_main[ii][jj][kk] = newdf.Filter(Form("main_r>%f && main_r<%f && ((main_ph>%f && main_ph<%f) || (main_ph>%f && main_ph<%f))",r[ii],r[ii+1],ph[jj][kk],Pi(),-Pi(),ph[jj][kk+1]))
				.Histo1D<Double_t>({Form("tgth_acc_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgth_acc_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024},"tg_th","rate");
	else tgth_main[ii][jj][kk] = newdf.Filter(Form("main_r>%f && main_r<%f && main_ph>%f && main_ph<%f",r[ii],r[ii+1],ph[jj][kk],ph[jj][kk+1]))
				.Histo1D<Double_t>({Form("tgth_acc_r%ds%dp%d",ii+1,jj+1,kk+1),Form("tgth_acc_r%ds%dp%d",ii+1,jj+1,kk+1),50,0,0.024},"tg_th","rate");
	
	tgth_acc[ii][jj][kk] = (TH1D *)tgth_main[ii][jj][kk].GetPtr()->Clone();
	tgth_acc[ii][jj][kk]->Divide(tgth_in[ii][jj][kk].GetPtr());	
     }
    }
   }

   TCanvas *c1 = new TCanvas();
   c1->Divide(2,2);
   for(int ii=0; ii<4; ii++){
	c1->cd(ii+1);
        tgth_acc[5][0][ii]->Draw("hist");
   }

// = d.Histo1D();

 
/*   double r[7]={650,690,735,790,900,1060,1160};

   auto ring_th = new THIF[6];
   auto ring_ph = new THIF[6];
   auto ring_p = new THIF[6];

   for(int ii=0; ii<7; ii++){
      auto c1=new TCanvas();
      c1->Divide(4,1);
      
   }
*/
 //  auto hitdet = selected_d.Histo1D("tgth");

   //auto c1 = new TCanvas();
   //hitdet->DrawCopy();
   //auto d1=selected_d.Display({"part.th","hit.r","hit.det","maindet_hit","good_hit","trid","tgth"},7);
   //auto d1=d.Display({"part.th","hit.r","hit.det"},7);
   //d1->Print();
   
   //auto d1=check_d.Display({"part.th","hit.r","hit.det","maindet_hit","good_hit","trid"},7);
   //auto d1=d.Display({"part.th","hit.r","hit.det"},7);
   //d1->Print();

   //auto colType = selected_d.GetColumnType("trid");
// Print column type
   //std::cout << "Column " << colType << " has type " << colType << std::endl;

//auto colNames = d.GetColumnNames();
// Print columns' names
//for (auto &&colName : colNames) std::cout << colName << std::endl;


}
