using RNode  = ROOT::RDF::RNode;
using namespace ROOT::VecOps;
using rvec_i = const RVec<int> &;

using namespace TMath;

struct remollBeamTarget_t {
  double x, y, z;
  double dx, dy, dz;
  double th, ph;
};

void SlimRootfile(RNode df, std::string_view rootname);

void GoodEvents(RNode df, int nr){   // nr=1: only generate one hit root files, n=2: only generate two hits root files, n=3: generate both cases' rootfiles

   auto primary_hit = "hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2)";
 
   auto selected_df = df.Define("prm_e",primary_hit).Define("main","hit.det==28").Define("sieve","hit.det==60").Define("gem","hit.det==30")
		    .Define("good_ev","Sum(prm_e && main)").Define("trid","hit.trid[prm_e && main]").Filter("good_ev>0");

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

   auto newdf = selected_df.Define("ntrk",check_trid, {"trid"});
   auto twohits_d = newdf.Filter("ntrk==2");
   auto onehit_d = newdf.Filter("ntrk==1");

   cout<<"Two tracks:  "<<*twohits_d.Count()<<endl;
   cout<<"One tracks:  "<<*onehit_d.Count()<<endl;

   switch(nr){
	case 1: 
	  SlimRootfile(onehit_d,"onehit.root"); 
	  break;
	case 2:
	  SlimRootfile(twohits_d,"twohits.root"); 
	  break;

	case 3:
	  SlimRootfile(onehit_d,"onehit.root"); 
	  SlimRootfile(twohits_d,"twohits.root"); 
	  break;
   } 
  
   return;

}

void SlimRootfile(RNode df, std::string_view rootname){
     auto df_small = df.Define("main_trid","hit.trid[main && prm_e]")
          .Define("main_r","hit.r[main && prm_e]").Define("main_ph","hit.ph[main && prm_e]")
          .Define("main_x","hit.x[main && prm_e]").Define("main_y","hit.y[main && prm_e]").Define("main_p","hit.p[main && prm_e]")
          .Define("sieve_r","hit.r[sieve && prm_e]").Define("sieve_ph","hit.ph[sieve && prm_e]").Define("sieve_trid","hit.trid[sieve && prm_e]")
          .Define("sieve_x","hit.x[sieve && prm_e]").Define("sieve_y","hit.y[sieve && prm_e]").Define("sieve_p","hit.p[sieve && prm_e]")
          .Define("gem_r","hit.r[gem && prm_e]").Define("gem_ph","hit.ph[gem && prm_e]").Define("gem_z","hit.z[gem && prm_e]").Define("gem_trid","hit.trid[gem && prm_e]")
          .Define("gem_x","hit.x[gem && prm_e]").Define("gem_y","hit.y[gem && prm_e]").Define("gem_p","hit.p[gem && prm_e]")
          .Define("tg_th","part.th").Define("tg_ph","part.ph").Define("tg_p","part.p").Define("tg_vx","part.vx").Define("tg_vy","part.vy").Define("tg_vz","part.vz")
	  .Define("tg_trid","part.trid").Define("tg_pid","part.pid")
	  .Define("bm_x","bm.x").Define("bm_y","bm.y").Define("bm_z","bm.z").Define("bm_dx","bm.dx").Define("bm_dy","bm.dy").Define("bm_dz","bm.dz")
	  .Define("bm_th","bm.th").Define("bm_ph","bm.ph");


     df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","main_trid","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p","sieve_trid",
        "gem_r","gem_ph","gem_x","gem_y","gem_p","gem_z","gem_trid",
        "tg_th","tg_p","tg_ph","tg_vz","tg_vx","tg_vy","tg_trid","tg_pid","rate",
	"bm_x","bm_y","bm_z","bm_dx","bm_dy","bm_dz","bm_th","bm_ph"});

     return;
}

