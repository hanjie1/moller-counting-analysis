using RNode = ROOT::RDF::RNode;
using namespace TMath;

bool ismoller=false;
int pass=3;

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
//if(ii==0)cout<<ph[jj][kk]<<"  ";
	}
//if(ii==0)cout<<endl;
      }
    } 
    return;
} 

void GenSmallRootfile(RNode df,std::string_view rootname){
if(ismoller){
  auto df_small = df.Define("main_r","hit.r[maindet_hit][0]").Define("main_ph","hit.ph[maindet_hit][0]").Define("main_x","hit.x[maindet_hit][0]").Define("main_y","hit.y[maindet_hit][0]")
		    .Define("main_p","hit.p[maindet_hit][0]")
     		    .Define("tg_th","trid[0]==1?part.th[0]:part.th[1]").Define("tg_ph","trid[0]==1?part.ph[0]:part.ph[1]").Define("tg_p","trid[0]==1?part.p[0]:part.p[1]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","tg_th","tg_ph","tg_p","rate"}); 
}
else{
  auto df_small = df.Define("main_r","hit.r[maindet_hit][0]").Define("main_ph","hit.ph[maindet_hit][0]").Define("main_x","hit.x[maindet_hit][0]").Define("main_y","hit.y[maindet_hit][0]")
		    .Define("main_p","hit.p[maindet_hit][0]")
     		    .Define("tg_th","part.th[0]").Define("tg_ph","part.ph[0]").Define("tg_p","part.p[0]");

  df_small.Snapshot("T",rootname,{"main_r","main_ph","main_x","main_y","main_p","tg_th","tg_ph","tg_p","rate"}); 
}
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

void PlotSecACC( ROOT::RDF::RResultPtr<TH1D> h1d_in, ROOT::RDF::RResultPtr<TH1D> h1d_main[6][7][4], TString filename){
   TH1D *h1d_acc[6][7][4];

   for(int ii=0; ii<6; ii++){
    for(int jj=0; jj<7; jj++){
     for(int kk=0; kk<4; kk++){
        h1d_acc[ii][jj][kk] = (TH1D *)h1d_main[ii][jj][kk].GetPtr()->Clone();
        h1d_acc[ii][jj][kk]->Divide(h1d_in.GetPtr());
     }
    }
   }

   gStyle->SetOptStat(111101);
   
   for(int ii=0; ii<6; ii++){
     TCanvas *c1=new TCanvas("c1");
     c1->Divide(4,4);
     for(int jj=0; jj<4; jj++){  // sec
      for(int kk=0; kk<4; kk++){  // part
	c1->cd(jj*4+kk+1);
	h1d_acc[ii][jj][kk]->Draw("hist");
	h1d_acc[ii][jj][kk]->SetTitle(Form("acc_r%ds%dp%d;%s;acc;",ii+1,jj+1,kk+1,filename.Data()));
	
	Int_t nevent = h1d_main[ii][jj][kk].GetPtr()->GetEntries();
	Int_t nevent_eff = h1d_main[ii][jj][kk].GetPtr()->GetEffectiveEntries();

	TLatex tex;
   	tex.SetTextSize(0.025);
        tex.DrawLatexNDC(.2,.8,Form("N=%d",nevent));
        tex.DrawLatexNDC(.2,.75,Form("Neff=%d",nevent_eff));
      }
     }
 
     TCanvas *c2=new TCanvas("c2");
     c2->Divide(4,3);
     for(int jj=4; jj<7; jj++){  // sec
      for(int kk=0; kk<4; kk++){  // part
	c2->cd((jj-4)*4+kk+1);
	h1d_acc[ii][jj][kk]->Draw("hist");
	h1d_acc[ii][jj][kk]->SetTitle(Form("acc_r%ds%dp%d;%s;acc;",ii+1,jj+1,kk+1,filename.Data()));

	Int_t nevent = h1d_main[ii][jj][kk].GetPtr()->GetEntries();
	Int_t nevent_eff = h1d_main[ii][jj][kk].GetPtr()->GetEffectiveEntries();

	TLatex tex;
   	tex.SetTextSize(0.025);
        tex.DrawLatexNDC(.2,.8,Form("N=%d",nevent));
        tex.DrawLatexNDC(.2,.75,Form("Neff=%d",nevent_eff));
      }
     }

     TString pdfname;
     if(ismoller)
        pdfname=Form("plots/moller_%d_sec_acc_r%d_%s.pdf",pass,ii+1,filename.Data());
     else 
        pdfname=Form("plots/C12el_%d_sec_acc_r%d_%s.pdf",pass,ii+1,filename.Data());

     c1->Print(Form("%s[",pdfname.Data()));
     c1->Print(pdfname);
     c2->Print(pdfname);
     c2->Print(Form("%s]",pdfname.Data()));
  
     delete c1;
     delete c2; 
   }

   return;
}

void PlotRingACC( ROOT::RDF::RResultPtr<TH1D> h1d_in, ROOT::RDF::RResultPtr<TH1D> h1d_main[6][7][4], TString filename){
   TH1D *hacc_r[6];
   TH1D *hacc_total;
   TH1D *hmain_r[6];
   TH1D *hmain_total;
   
   TList *list = new TList;
   for(int ii=0; ii<6; ii++){

      TList *list_r = new TList;

      for(int jj=0; jj<7; jj++){
         for(int kk=0; kk<4; kk++){

	    list->Add(h1d_main[ii][jj][kk].GetPtr());	
	    list_r->Add(h1d_main[ii][jj][kk].GetPtr());	
         }
      }

      hmain_r[ii]=(TH1D *)h1d_main[ii][0][0].GetPtr()->Clone(Form("hmain_r%d",ii+1));
      hmain_r[ii]->Reset();
      hmain_r[ii]->Merge(list_r); 

      hacc_r[ii]=(TH1D *)hmain_r[ii]->Clone(Form("hacc_r%d",ii+1));
      hacc_r[ii]->Divide(h1d_in.GetPtr());
      delete list_r;
   }

   hmain_total=(TH1D *)h1d_main[0][0][0].GetPtr()->Clone("hmain_total");
   hmain_total->Reset();
   hmain_total->Merge(list); 

   hacc_total=(TH1D *)hmain_total->Clone("hacc_total");
   hacc_total->Divide(h1d_in.GetPtr());

   gStyle->SetOptStat(111101);

   TCanvas *c1= new TCanvas("c1");
   c1->Divide(3,2);
   for(int ii=0; ii<6; ii++){
       c1->cd(ii+1);
       hacc_r[ii]->Draw("hist");
       hacc_r[ii]->SetTitle(Form("r%d;%s;acc;",ii+1,filename.Data()));

       Int_t nevent = hmain_r[ii]->GetEntries();
       Int_t nevent_eff = hmain_r[ii]->GetEffectiveEntries();

       TLatex tex;
       tex.SetTextSize(0.025);
       tex.DrawLatexNDC(.2,.8,Form("N=%d",nevent));
       tex.DrawLatexNDC(.2,.75,Form("Neff=%d",nevent_eff));
   } 

   TCanvas *c2= new TCanvas("c2");
   hacc_total->Draw("hist");
   hacc_total->SetTitle(Form("%s acceptance;%s;acc;",filename.Data(),filename.Data())); 

   Int_t nevent = hmain_total->GetEntries();
   Int_t nevent_eff = hmain_total->GetEffectiveEntries();

   TLatex tex;
   tex.SetTextSize(0.025);
   tex.DrawLatexNDC(.2,.8,Form("N=%d",nevent));
   tex.DrawLatexNDC(.2,.75,Form("Neff=%d",nevent_eff));

   TString pdfname;
   if(ismoller)
      pdfname=Form("plots/moller_%d_ring_acc_%s.pdf",pass,filename.Data());
   else 
      pdfname=Form("plots/C12el_%d_ring_acc_%s.pdf",pass,filename.Data());

     c1->Print(Form("%s[",pdfname.Data()));
     c1->Print(pdfname);
     c2->Print(pdfname);
     c2->Print(Form("%s]",pdfname.Data()));

   return;
}     

void PlotSecAcc2D(ROOT::RDF::RResultPtr<TH2D> h2d_in, ROOT::RDF::RResultPtr<TH2D> h2d_main[6][7][4], TString xname, TString yname){
   TH2D *h2d_acc[6][7][4];

   for(int ii=0; ii<6; ii++){
    for(int jj=0; jj<7; jj++){
     for(int kk=0; kk<4; kk++){
        h2d_acc[ii][jj][kk] = (TH2D *)h2d_main[ii][jj][kk].GetPtr()->Clone();
        h2d_acc[ii][jj][kk]->Divide(h2d_in.GetPtr());
     }
    }
   }

   gStyle->SetOptStat(0);
   
   for(int ii=0; ii<6; ii++){
     TCanvas *c1=new TCanvas("c1");
     c1->Divide(4,4);
     for(int jj=0; jj<4; jj++){  // sec
      for(int kk=0; kk<4; kk++){  // part
	c1->cd(jj*4+kk+1);
	h2d_acc[ii][jj][kk]->Draw("colz");
	h2d_acc[ii][jj][kk]->SetTitle(Form("acc_r%ds%dp%d;%s;%s;",ii+1,jj+1,kk+1,xname.Data(),yname.Data()));
      }
     }
 
     TCanvas *c2=new TCanvas("c2");
     c2->Divide(4,3);
     for(int jj=4; jj<7; jj++){  // sec
      for(int kk=0; kk<4; kk++){  // part
	c2->cd((jj-4)*4+kk+1);
	h2d_acc[ii][jj][kk]->Draw("colz");
	h2d_acc[ii][jj][kk]->SetTitle(Form("acc_r%ds%dp%d;%s;%s;",ii+1,jj+1,kk+1,xname.Data(),yname.Data()));
      }
     }

     TString pdfname;
     if(ismoller)
        pdfname=Form("plots/moller_%d_sec_acc2d_r%d_%s_%s.pdf",pass,ii+1,xname.Data(),yname.Data());
     else 
        pdfname=Form("plots/C12el_%d_sec_acc2d_r%d_%s_%s.pdf",pass,ii+1,xname.Data(),yname.Data());

     c1->Print(Form("%s[",pdfname.Data()));
     c1->Print(pdfname);
     c2->Print(pdfname);
     c2->Print(Form("%s]",pdfname.Data()));
  
     delete c1;
     delete c2; 
   }

   return;
}


void PlotRingAcc2D( ROOT::RDF::RResultPtr<TH2D> h2d_in, ROOT::RDF::RResultPtr<TH2D> h2d_main[6][7][4], TString xname, TString yname){
   TH2D *hacc_r[6];
   TH2D *hacc_total;
   TH2D *hmain_r[6];
   TH2D *hmain_total;
   
   TList *list = new TList;
   for(int ii=0; ii<6; ii++){

      TList *list_r = new TList;

      for(int jj=0; jj<7; jj++){
         for(int kk=0; kk<4; kk++){

	    list->Add(h2d_main[ii][jj][kk].GetPtr());	
	    list_r->Add(h2d_main[ii][jj][kk].GetPtr());	
         }
      }

      hmain_r[ii]=(TH2D *)h2d_main[ii][0][0].GetPtr()->Clone(Form("hmain_r%d",ii+1));
      hmain_r[ii]->Reset();
      hmain_r[ii]->Merge(list_r); 

      hacc_r[ii]=(TH2D *)hmain_r[ii]->Clone(Form("hacc_r%d",ii+1));
      hacc_r[ii]->Divide(h2d_in.GetPtr());
      delete list_r;
   }

   hmain_total=(TH2D *)h2d_main[0][0][0].GetPtr()->Clone("hmain_total");
   hmain_total->Reset();
   hmain_total->Merge(list); 

   hacc_total=(TH2D *)hmain_total->Clone("hacc_total");
   hacc_total->Divide(h2d_in.GetPtr());

   gStyle->SetOptStat(0);

   TCanvas *c1= new TCanvas("c1");
   c1->Divide(3,2);
   for(int ii=0; ii<6; ii++){
       c1->cd(ii+1);
       hacc_r[ii]->Draw("colz");
       hacc_r[ii]->SetTitle(Form("r%d %s vs %s;%s;%s;",ii+1,yname.Data(),xname.Data(),xname.Data(),yname.Data()));
   } 

   TCanvas *c2= new TCanvas("c2");
   hacc_total->Draw("colz");
   hacc_total->SetTitle(Form("%s vs %s acceptance;%s;%s;",yname.Data(),xname.Data(),xname.Data(),yname.Data())); 

   TString pdfname;
   if(ismoller)
      pdfname=Form("plots/moller_%d_ring_acc2d_%s_%s.pdf",pass,xname.Data(),yname.Data());
   else 
      pdfname=Form("plots/C12el_%d_ring_acc2d_%s_%s.pdf",pass,xname.Data(),yname.Data());

   c1->Print(Form("%s[",pdfname.Data()));
   c1->Print(pdfname);
   c2->Print(pdfname);
   c2->Print(Form("%s]",pdfname.Data()));

   return;
}     

