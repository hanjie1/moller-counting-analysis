using RNode = ROOT::RDF::RNode;
using namespace TMath;

bool ismoller=false;
int pass=3;

double r[7]={650,690,735,790,900,1060,1160};     // radius for the 6 rings
double ph_1[7];
double ph_2[7];

void SetRPhi(){
    for(int ii=0; ii<7; ii++){  // ring loop
      double tmpr=r[ii];

      double tmp_ph = -Pi()/28.0 + ii*2*Pi()/7.0;
      if(tmp_ph>Pi()) tmp_ph=tmp_ph-2*Pi();
      ph_1[ii]=tmp_ph;

      tmp_ph = ii*2*Pi()/7.0;
      if(tmp_ph>Pi()) tmp_ph=tmp_ph-2*Pi();
      ph_2[ii]=tmp_ph;
    }
    return;
}

void GenSmallRootfile(RNode df,std::string_view rootname){
if(ismoller){
  auto df_small = df.Define("goodtrk","hit.trid==trid[0]")
	  .Define("main_r","hit.r[main && primary_hit][0]").Define("main_ph","hit.ph[main && primary_hit][0]")
          .Define("main_x","hit.x[main && primary_hit][0]").Define("main_y","hit.y[main && primary_hit][0]").Define("main_p","hit.p[main && primary_hit][0]")
          .Define("sieve_r","hit.r[sieve && primary_hit && goodtrk][0]").Define("sieve_ph","hit.ph[sieve && primary_hit && goodtrk][0]")
          .Define("sieve_x","hit.x[sieve && primary_hit && goodtrk][0]").Define("sieve_y","hit.y[sieve && primary_hit && goodtrk][0]").Define("sieve_p","hit.p[sieve && primary_hit && goodtrk][0]")
          .Define("gem_r0","hit.r[gem && primary_hit][0]").Define("gem_ph0","hit.ph[gem && primary_hit][0]").Define("gem_z0","hit.z[gem && primary_hit][0]")
          .Define("gem_x0","hit.x[gem && primary_hit][0]").Define("gem_y0","hit.y[gem && primary_hit][0]").Define("gem_p0","hit.p[gem && primary_hit][0]")
          .Define("gem_r1","hit.r[gem && primary_hit][1]").Define("gem_ph1","hit.ph[gem && primary_hit][1]").Define("gem_z1","hit.z[gem && primary_hit][1]")
          .Define("gem_x1","hit.x[gem && primary_hit][1]").Define("gem_y1","hit.y[gem && primary_hit][1]").Define("gem_p1","hit.p[gem && primary_hit][1]")
          .Define("gem_r2","hit.r[gem && primary_hit][2]").Define("gem_ph2","hit.ph[gem && primary_hit][2]").Define("gem_z2","hit.z[gem && primary_hit][2]")
          .Define("gem_x2","hit.x[gem && primary_hit][2]").Define("gem_y2","hit.y[gem && primary_hit][2]").Define("gem_p2","hit.p[gem && primary_hit][2]")
          .Define("gem_r3","hit.r[gem && primary_hit][3]").Define("gem_ph3","hit.ph[gem && primary_hit][3]").Define("gem_z3","hit.z[gem && primary_hit][3]")
          .Define("gem_x3","hit.x[gem && primary_hit][3]").Define("gem_y3","hit.y[gem && primary_hit][3]").Define("gem_p3","hit.p[gem && primary_hit][3]")
          .Define("tg_th","trid[0]==1?part.th[0]:part.th[1]").Define("tg_ph","trid[0]==1?part.ph[0]:part.ph[1]").Define("tg_p","trid[0]==1?part.p[0]:part.p[1]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p",
	"gem_r0","gem_ph0","gem_x0","gem_y0","gem_p0","gem_z0",
	"gem_r1","gem_ph1","gem_x1","gem_y1","gem_p1","gem_z1",
	"gem_r2","gem_ph2","gem_x2","gem_y2","gem_p2","gem_z2",
	"gem_r3","gem_ph3","gem_x3","gem_y3","gem_p3","gem_z3",
	"tg_th","tg_ph","tg_p","rate"});
}
else{

  auto df_small = df.Define("main_r","hit.r[main && primary_hit][0]").Define("main_ph","hit.ph[main && primary_hit][0]")
          .Define("main_x","hit.x[main && primary_hit][0]").Define("main_y","hit.y[main && primary_hit][0]").Define("main_p","hit.p[main && primary_hit][0]")
          .Define("sieve_r","hit.r[sieve && primary_hit][0]").Define("sieve_ph","hit.ph[sieve && primary_hit][0]")
          .Define("sieve_x","hit.x[sieve && primary_hit][0]").Define("sieve_y","hit.y[sieve && primary_hit][0]").Define("sieve_p","hit.p[sieve && primary_hit][0]")
          .Define("gem_r0","hit.r[gem && primary_hit][0]").Define("gem_ph0","hit.ph[gem && primary_hit][0]").Define("gem_z0","hit.z[gem && primary_hit][0]")
          .Define("gem_x0","hit.x[gem && primary_hit][0]").Define("gem_y0","hit.y[gem && primary_hit][0]").Define("gem_p0","hit.p[gem && primary_hit][0]")
          .Define("gem_r1","hit.r[gem && primary_hit][1]").Define("gem_ph1","hit.ph[gem && primary_hit][1]").Define("gem_z1","hit.z[gem && primary_hit][1]")
          .Define("gem_x1","hit.x[gem && primary_hit][1]").Define("gem_y1","hit.y[gem && primary_hit][1]").Define("gem_p1","hit.p[gem && primary_hit][1]")
          .Define("gem_r2","hit.r[gem && primary_hit][2]").Define("gem_ph2","hit.ph[gem && primary_hit][2]").Define("gem_z2","hit.z[gem && primary_hit][2]")
          .Define("gem_x2","hit.x[gem && primary_hit][2]").Define("gem_y2","hit.y[gem && primary_hit][2]").Define("gem_p2","hit.p[gem && primary_hit][2]")
          .Define("gem_r3","hit.r[gem && primary_hit][3]").Define("gem_ph3","hit.ph[gem && primary_hit][3]").Define("gem_z3","hit.z[gem && primary_hit][3]")
          .Define("gem_x3","hit.x[gem && primary_hit][3]").Define("gem_y3","hit.y[gem && primary_hit][3]").Define("gem_p3","hit.p[gem && primary_hit][3]")
          .Define("tg_th","part.th[0]").Define("tg_ph","part.ph[0]").Define("tg_p","part.p[0]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","sieve_r","sieve_ph","sieve_x","sieve_y","sieve_p",
	"gem_r0","gem_ph0","gem_x0","gem_y0","gem_p0","gem_z0",
	"gem_r1","gem_ph1","gem_x1","gem_y1","gem_p1","gem_z1",
	"gem_r2","gem_ph2","gem_x2","gem_y2","gem_p2","gem_z2",
	"gem_r3","gem_ph3","gem_x3","gem_y3","gem_p3","gem_z3",
	"tg_th","tg_ph","tg_p","rate"});
}
  return;
}

void PlotSec( ROOT::RDF::RResultPtr<TH2D> h2d, ROOT::RDF::RResultPtr<TH1D> h1d[7], TString var){
     
     TCanvas *c1=new TCanvas("c1");
     c1->Divide(4,2);
     for(int ii=0; ii<7; ii++){
	c1->cd(ii+1);
	h1d[ii]->DrawCopy("hist");
	h1d[ii].GetPtr()->SetTitle(Form("gem %s sec%d;gem_%s[0];;",var.Data(),ii+1,var.Data()));

        Int_t nevent = h1d[ii].GetPtr()->GetEntries();
        Int_t nevent_eff = h1d[ii].GetPtr()->GetEffectiveEntries();

        TLatex tex;
        tex.SetTextSize(0.025);
        tex.DrawLatexNDC(.2,.8,Form("N=%d",nevent));
        tex.DrawLatexNDC(.2,.75,Form("Neff=%d",nevent_eff));
     } 

     c1->cd(8);
     h2d->DrawCopy("colz");
     h2d->SetTitle("sieve y vs x;sieve_x;sieve_y;");

     TString plotname;
     if(ismoller) plotname=Form("plots/moller_dis_gem_%s.pdf",var.Data());
     else plotname=Form("plots/C12el_dis_gem_%s.pdf",var.Data());

     c1->Print(Form("%s",plotname.Data()));
     return;
}
