#include "../../remoll/include/remolltypes.hh"

using RNode  = ROOT::RDF::RNode;
using namespace ROOT::VecOps;
using rvec_i = const RVec<int> &;

using namespace TMath;
/*
struct remollBeamTarget_t {
  double x, y, z;
  double dx, dy, dz;
  double th, ph;
};
*/
void SlimRootfile(RNode df, std::string_view rootname);

/***GoodEventsMoller
 * slim the moller remoll root files: only save primary electron events reaches the main detector
 * @df: remoll root files dataframe
 * @nr: 1=only generate one hit root files
 * 	2=only generate two hits root files
 * 	3=both 1 and 
***/
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

RNode GenMollerDF(RNode df){

   auto primary_hit = "hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2)";
 
   auto selected_df = df.Define("prm_e",primary_hit).Define("main","hit.det==28").Define("sieve","hit.det==60").Define("gem","hit.det==30")
	            .Define("gem_1","hit.z>=19279.5 && hit.z<=19280.5").Define("gem_2","hit.z>=19779.5 && hit.z<=19780.5")
		    .Define("gem_3","hit.z>=20193.5 && hit.z<=20194.5").Define("gem_4","hit.z>=20693.5 && hit.z<=20694.5")
		    .Define("good_ev","Sum(prm_e && main)").Define("trid","hit.trid[prm_e && main]").Filter("good_ev>0");

   return selected_df; 
}

/***GoodEventsGeneral
 * slim the ep or other one primary electron scattering remoll root files: only save primary electron events that reach the main detector
 * @df: remoll root files dataframe
***/
RNode GenEpDF(RNode df){

   auto primary_hit = "hit.pid==11 && hit.mtrid==0 && hit.trid==1";
 
   auto selected_df = df.Define("prm_e",primary_hit).Define("main","hit.det==28").Define("sieve","hit.det==60").Define("gem","hit.det==30")
	            .Define("gem_1","hit.z>=19279.5 && hit.z<=19280.5").Define("gem_2","hit.z>=19779.5 && hit.z<=19780.5")
		    .Define("gem_3","hit.z>=20193.5 && hit.z<=20194.5").Define("gem_4","hit.z>=20693.5 && hit.z<=20694.5")
		    .Define("good_ev","Sum(prm_e && main)").Define("trid","hit.trid[prm_e && main]").Filter("good_ev>0");
  
   return selected_df;
}

/***SlimRootfile
 * @df: dataframe with primary electrons cut applied
 * @rootname: name for the generated slim root file
 * For each event, the slimed root file will save the hit information as for detectors: main, sieve, gem, tg, bm
***/
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
	  .Define("bm_th","bm.th").Define("bm_ph","bm.ph").Define("beamE","ev.beamp");

     df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","main_trid","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p","sieve_trid",
        "gem_r","gem_ph","gem_x","gem_y","gem_p","gem_z","gem_trid",
        "tg_th","tg_p","tg_ph","tg_vz","tg_vx","tg_vy","tg_trid","tg_pid","rate",
	"bm_x","bm_y","bm_z","bm_dx","bm_dy","bm_dz","bm_th","bm_ph","beamE"});

     return;
}

/***SlimOneTrkRootfile
 * @df: dataframe with primary electrons cut applied and one track filter applied
 * @rootname: name for the generated slim root file
 * For each event, the slimed root file will save the hit information as for detectors: main, sieve, gem, tg, bm (all single variable not vectors)
***/
void SlimOneTrkRootfile(RNode df, std::string_view rootname){

     auto df_small = df.Define("main_trid","hit.trid[main && prm_e][0]")
          .Define("main_r","hit.r[main && prm_e][0]").Define("main_ph","hit.ph[main && prm_e][0]")
          .Define("main_x","hit.x[main && prm_e][0]").Define("main_y","hit.y[main && prm_e][0]")
	  .Define("main_px","hit.px[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("main_py","hit.py[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("main_pz","hit.pz[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
          .Define("sieve_trid","hit.trid[sieve && prm_e && hit.trid==main_trid][0]")
          .Define("sieve_r","hit.r[sieve && prm_e && hit.trid==main_trid][0]").Define("sieve_ph","hit.ph[sieve && prm_e && hit.trid==main_trid][0]")
          .Define("sieve_x","hit.x[sieve && prm_e && hit.trid==main_trid][0]").Define("sieve_y","hit.y[sieve && prm_e && hit.trid==main_trid][0]")
 	  .Define("sieve_px","hit.px[sieve && prm_e && hit.trid==main_trid][0]").Define("sieve_py","hit.py[sieve && prm_e && hit.trid==main_trid][0]")
	  .Define("sieve_pz","hit.pz[sieve && prm_e && hit.trid==main_trid][0]")
	  .Define("gem1_trid","hit.trid[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
          .Define("gem1_r","hit.r[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem1_ph","hit.ph[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem1_x","hit.x[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem1_y","hit.y[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem1_px","hit.px[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem1_py","hit.py[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem1_pz","hit.pz[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem2_trid","hit.trid[gem && prm_e && gem_2 && hit.trid==main_trid][0]")
          .Define("gem2_r","hit.r[gem && prm_e && gem_2 && hit.trid==main_trid][0]").Define("gem2_ph","hit.ph[gem && prm_e && gem_2 && hit.trid==main_trid][0]")
	  .Define("gem2_x","hit.x[gem && prm_e && gem_2 && hit.trid==main_trid][0]").Define("gem2_y","hit.y[gem && prm_e && gem_2 && hit.trid==main_trid][0]")
	  .Define("gem2_px","hit.px[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem2_py","hit.py[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem2_pz","hit.pz[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem3_trid","hit.trid[gem && prm_e && gem_3 && hit.trid==main_trid][0]")
          .Define("gem3_r","hit.r[gem && prm_e && gem_3 && hit.trid==main_trid][0]").Define("gem3_ph","hit.ph[gem && prm_e && gem_3 && hit.trid==main_trid][0]")
	  .Define("gem3_x","hit.x[gem && prm_e && gem_3 && hit.trid==main_trid][0]").Define("gem3_y","hit.y[gem && prm_e && gem_3 && hit.trid==main_trid][0]")
	  .Define("gem3_px","hit.px[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem3_py","hit.py[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem3_pz","hit.pz[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem4_trid","hit.trid[gem && prm_e && gem_4 && hit.trid==main_trid][0]")
          .Define("gem4_r","hit.r[gem && prm_e && gem_4 && hit.trid==main_trid][0]").Define("gem4_ph","hit.ph[gem && prm_e && gem_4 && hit.trid==main_trid][0]")
	  .Define("gem4_x","hit.x[gem && prm_e && gem_4 && hit.trid==main_trid][0]").Define("gem4_y","hit.y[gem && prm_e && gem_4 && hit.trid==main_trid][0]")
	  .Define("gem4_px","hit.px[gem && prm_e && gem_1 && hit.trid==main_trid][0]").Define("gem4_py","hit.py[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
	  .Define("gem4_pz","hit.pz[gem && prm_e && gem_1 && hit.trid==main_trid][0]")
          .Define("tg_th","part.th[part.trid==main_trid][0]").Define("tg_ph","part.ph[part.trid==main_trid][0]").Define("tg_p","part.p[part.trid==main_trid][0]")
	  .Define("tg_vx","part.vx[part.trid==main_trid][0]").Define("tg_vy","part.vy[part.trid==main_trid][0]").Define("tg_vz","part.vz[part.trid==main_trid][0]")
	  .Define("tg_trid","part.trid[part.trid==main_trid][0]").Define("tg_pid","part.pid[part.trid==main_trid][0]")
	  .Define("bm_x","bm.x").Define("bm_y","bm.y").Define("bm_z","bm.z").Define("bm_dx","bm.dx").Define("bm_dy","bm.dy").Define("bm_dz","bm.dz")
	  .Define("bm_th","bm.th").Define("bm_ph","bm.ph").Define("beamE","ev.beamp");

     df_small.Snapshot("newT",rootname,{"main_r","main_ph","main_x","main_y","main_px","main_py","main_pz","main_trid",
	"sieve_r","sieve_ph","sieve_x","sieve_y","sieve_px","sieve_py","sieve_pz","sieve_trid",
        "gem1_r","gem1_ph","gem1_x","gem1_y","gem1_px","gem1_py","gem1_pz","gem1_trid",
        "gem2_r","gem2_ph","gem2_x","gem2_y","gem2_px","gem2_py","gem2_pz","gem2_trid",
        "gem3_r","gem3_ph","gem3_x","gem3_y","gem3_px","gem3_py","gem3_pz","gem3_trid",
        "gem4_r","gem4_ph","gem4_x","gem4_y","gem4_px","gem4_py","gem4_pz","gem4_trid",
        "tg_th","tg_p","tg_ph","tg_vz","tg_vx","tg_vy","tg_trid","tg_pid","rate",
	"bm_x","bm_y","bm_z","bm_dx","bm_dy","bm_dz","bm_th","bm_ph","beamE"});
 
//     auto d2=df_small.Display({"main_r","main_trid","sieve_trid","sieve_r","tg_trid","gem1_trid"},10);
//     d2->Print();
     return;

}


