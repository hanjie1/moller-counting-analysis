using RNode = ROOT::RDF::RNode;
using namespace TMath;

double r[7]={650,690,735,790,900,1060,1160};     // radius for the 6 rings
double ph[7][5];
double xx[7][7][5];   // x[ring][sec][C,T,O,T]
double yy[7][7][5];

void SetXYPhi(){
    for(int ii=0; ii<7; ii++){  // ring loop
      double tmpr=r[ii];
      for(int jj=0; jj<7; jj++){  // phi loop
	for(int kk=0; kk<5; kk++){ // close, transition, open
	  double tmp_ph = -Pi()/28.0 + 2*kk*Pi()/28.0 + jj*2*Pi()/7.0;
	  if(tmp_ph>Pi()) tmp_ph=tmp_ph-2*Pi();
	  ph[jj][kk]=tmp_ph;
	  xx[ii][jj][kk]=tmpr*cos(tmp_ph);
	  yy[ii][jj][kk]=tmpr*sin(tmp_ph);
//cout<<ph[jj][kk]<<"  ";
	}
//cout<<endl;
      }
    } 
    return;
} 

void GenSmallRootfile(RNode df,std::string_view rootname){
  auto df_small = df.Define("main_r","hit.r[maindet_hit][0]").Define("main_ph","hit.ph[maindet_hit][0]").Define("main_x","hit.x[maindet_hit][0]").Define("main_y","hit.y[maindet_hit][0]")
		    .Define("main_p","hit.p[maindet_hit][0]")
     		    .Define("tg_th","trid[0]==1?part.th[0]:part.th[1]").Define("tg_ph","trid[0]==1?part.ph[0]:part.ph[1]").Define("tg_p","trid[0]==1?part.p[0]:part.p[1]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","tg_th","tg_ph","tg_p","rate"}); 
  return;
}

void CheckTWOhits(RNode df){
      auto multihit_d = df.Filter("good_hit==2");    // there are two moller primary electrons at main det

      // check the two electrons distribution
      auto multihit_count=multihit_d.Count();
      if(*multihit_count>0) {
          cout<<"There are "<<*multihit_count<<" events have 2 primary electrons at main detector"<<endl;

          TCanvas *c1= new TCanvas("c1");
          auto multihit_xy = multihit_d.Define("hitx","hit.x[maindet_hit]").Define("hity","hit.y[maindet_hit]")
                                     .Histo2D({"hxy_multihit","y vs. x at main det",200,-1200,1200,200,-1200,1200},"hitx","hity","rate");
          multihit_xy->DrawCopy("COLZ");
          c1->SaveAs("plots/twohit_main_xy.png");
      }

      return;
}
