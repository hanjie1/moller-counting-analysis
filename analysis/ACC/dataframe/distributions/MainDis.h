using RNode = ROOT::RDF::RNode;
using namespace TMath;

bool ismoller=true;
int pass=5;

double r[7]={650,690,735,790,900,1060,1160};     // radius for the 6 rings
double ph_1[7][5];
double ph_2[7][6];
double ph[7];

void SetXYPhi(){
    for(int ii=0; ii<7; ii++){  // ring loop
      double tmpr=r[ii];
      for(int jj=0; jj<7; jj++){  // phi loop
        for(int kk=0; kk<5; kk++){ // close, transition, open
          double tmp_ph = -Pi()/28.0 + 2*kk*Pi()/28.0 + jj*2*Pi()/7.0;
          if(tmp_ph>Pi()) tmp_ph=tmp_ph-2*Pi();
          ph[jj][kk]=tmp_ph;
//if(ii==0)cout<<ph[jj][kk]<<"  ";
        }
//if(ii==0)cout<<endl;
      }
    }
    return;
}



void GenSmallRootfile(RNode df,std::string_view rootname){
if(ismoller){
  auto df_small = df.Define("main_r","hit.r[main && primary_hit]").Define("main_ph","hit.ph[main && primary_hit]")
          .Define("main_x","hit.x[main && primary_hit]").Define("main_y","hit.y[main && primary_hit]").Define("main_p","hit.p[main && primary_hit]")
          .Define("sieve_r","hit.r[sieve && primary_hit]").Define("sieve_ph","hit.ph[sieve && primary_hit]")
          .Define("sieve_x","hit.x[sieve && primary_hit]").Define("sieve_y","hit.y[sieve && primary_hit]").Define("sieve_p","hit.p[sieve && primary_hit]")
          .Define("gem_r","hit.r[gem && primary_hit]").Define("gem_ph","hit.ph[gem && primary_hit]").Define("gem_z","hit.z[gem && primary_hit]")
          .Define("gem_x","hit.x[gem && primary_hit]").Define("gem_y","hit.y[gem && primary_hit]").Define("gem_p","hit.p[gem && primary_hit]")
          .Define("tg_th","trid[0]==1?part.th[0]:part.th[1]").Define("tg_ph","trid[0]==1?part.ph[0]:part.ph[1]").Define("tg_p","trid[0]==1?part.p[0]:part.p[1]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p","gem_r","gem_ph","gem_x","gem_y","gem_p",
		                  "gem_z","tg_th","tg_ph","tg_p","rate"});
}
else{

  auto df_small = df.Define("main_r","hit.r[main && primary_hit]").Define("main_ph","hit.ph[main && primary_hit]")
          .Define("main_x","hit.x[main && primary_hit]").Define("main_y","hit.y[main && primary_hit]").Define("main_p","hit.p[main && primary_hit]")
          .Define("sieve_r","hit.r[sieve && primary_hit]").Define("sieve_ph","hit.ph[sieve && primary_hit]")
          .Define("sieve_x","hit.x[sieve && primary_hit]").Define("sieve_y","hit.y[sieve && primary_hit]").Define("sieve_p","hit.p[sieve && primary_hit]")
          .Define("gem_r","hit.r[gem && primary_hit]").Define("gem_ph","hit.ph[gem && primary_hit]").Define("gem_z","hit.z[gem && primary_hit]")
          .Define("gem_x","hit.x[gem && primary_hit]").Define("gem_y","hit.y[gem && primary_hit]").Define("gem_p","hit.p[gem && primary_hit]")
          .Define("tg_th","part.th[0]").Define("tg_ph","part.ph[0]").Define("tg_p","part.p[0]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p","gem_r","gem_ph","gem_x","gem_y","gem_p",
		                  "gem_z","tg_th","tg_ph","tg_p","rate"});
}
  return;
}
