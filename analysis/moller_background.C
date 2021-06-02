void moller_background(){
	const int nn=5;

	int kin[nn]={1,2,3,4,5};
        TString CUT1="ring.r>600";

        TH1F *hmo_r[5];
        TH1F *hp_r[5];
        TH1F *hmo_rp[5];
        TH1F *hp_rp[5];
        TH1F *hmo_ph[5];
        TH1F *hp_ph[5];
        TH1F *hmo_php[5];
        TH1F *hp_php[5];
        TH1F *hmo_p[5];
        TH1F *hp_p[5];

        TH1F *hmo_tg_th[5];
        TH1F *hp_tg_th[5];
        TH1F *hmo_tg_p[5];
        TH1F *hp_tg_p[5];

	double E0[5]={2.2,4.4,6.6,8.8,11};

	for(int ii=0; ii<nn; ii++){
	   TChain *T_el = new TChain("T");
	   T_el->Add(Form("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p%d_*",kin[ii]));

	   TChain *T_mo = new TChain("T");
	   T_mo->Add(Form("../Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_moller_p%d_*",kin[ii]));

	   hmo_r[ii]=new TH1F(Form("hmo_r%d",kin[ii]),"moller events r distribution",400,500,1300);
	   hp_r[ii]=new TH1F(Form("hp_r%d",kin[ii]),"elastic p1 events r distribution",400,500,1300);

	   T_mo->Draw(Form("ring.r>>hmo_r%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_r[ii]->SetLineColor(2);
	   hmo_r[ii]->SetLineWidth(2);

	   T_el->Draw(Form("ring.r>>hp_r%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_r[ii]->SetLineColor(4);
	   hp_r[ii]->SetLineWidth(2);

	   hmo_rp[ii]=new TH1F(Form("hmo_rp%d",kin[ii]),"moller events r' distribution",100,0,0.1);
	   hp_rp[ii]=new TH1F(Form("hp_rp%d",kin[ii]),"elastic p1 events r' distribution",100,0,0.1);

	   T_mo->Draw(Form("(ring.x*ring.px+ring.y*ring.py)/(ring.r*ring.pz)>>hmo_rp%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_rp[ii]->SetLineColor(2);
	   hmo_rp[ii]->SetLineWidth(2);

	   T_el->Draw(Form("(ring.x*ring.px+ring.y*ring.py)/(ring.r*ring.pz)>>hp_rp%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_rp[ii]->SetLineColor(4);
	   hp_rp[ii]->SetLineWidth(2);

	   hmo_p[ii]=new TH1F(Form("hmo_p%d",kin[ii]),"moller events p distribution",400,0,E0[ii]);
	   hp_p[ii]=new TH1F(Form("hp_p%d",kin[ii]),"elastic p1 events p distribution",400,0,E0[ii]);

	   T_mo->Draw(Form("ring.p/1000.0>>hmo_p%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_p[ii]->SetLineColor(2);
	   hmo_p[ii]->SetLineWidth(2);

	   T_el->Draw(Form("ring.p/1000.0>>hp_p%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_p[ii]->SetLineColor(4);
	   hp_p[ii]->SetLineWidth(2);

	   hmo_ph[ii]=new TH1F(Form("hmo_ph%d",kin[ii]),"moller events phi distribution",360,-180,180);
	   hp_ph[ii]=new TH1F(Form("hp_ph%d",kin[ii]),"elastic p1 events phi distribution",360,-180,180);
	   
           T_mo->Draw(Form("atan2(ring.y,ring.x)*180.0/TMath::Pi()>>hmo_ph%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_ph[ii]->SetLineColor(2);
	   hmo_ph[ii]->SetLineWidth(2);

           T_el->Draw(Form("atan2(ring.y,ring.x)*180.0/TMath::Pi()>>hp_ph%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_ph[ii]->SetLineColor(4);
	   hp_ph[ii]->SetLineWidth(2);

	   hmo_php[ii]=new TH1F(Form("hmo_php%d",kin[ii]),"moller events phi' distribution",200,-0.02,0.02);
	   hp_php[ii]=new TH1F(Form("hp_php%d",kin[ii]),"elastic p1 events phi' distribution",200,-0.02,0.02);
	   
           T_mo->Draw(Form("(-ring.y*ring.px+ring.x*ring.py)/(ring.pz*ring.r)>>hmo_php%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_php[ii]->SetLineColor(2);
	   hmo_php[ii]->SetLineWidth(2);

           T_el->Draw(Form("(-ring.y*ring.px+ring.x*ring.py)/(ring.pz*ring.r)>>hp_php%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_php[ii]->SetLineColor(4);
	   hp_php[ii]->SetLineWidth(2);

	   hmo_tg_th[ii]=new TH1F(Form("hmo_tg_th%d",kin[ii]),"moller events tg_th distribution",200,0,0.025);
	   hp_tg_th[ii]=new TH1F(Form("hp_tg_th%d",kin[ii]),"elastic p1 events tg_th distribution",200,0,0.025);
	   
           T_mo->Draw(Form("tg.th>>hmo_tg_th%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_tg_th[ii]->SetLineColor(2);
	   hmo_tg_th[ii]->SetLineWidth(2);

           T_el->Draw(Form("tg.th>>hp_tg_th%d",kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_tg_th[ii]->SetLineColor(4);
	   hp_tg_th[ii]->SetLineWidth(2);

	   hmo_tg_p[ii]=new TH1F(Form("hmo_tg_p%d",kin[ii]),"moller events tg_p distribution",200,0,1);
	   hp_tg_p[ii]=new TH1F(Form("hp_tg_p%d",kin[ii]),"elastic p1 events tg_p distribution",200,0,1);
	   
           T_mo->Draw(Form("(%f-tg.p/1000.)/%f>>hmo_tg_p%d",E0[ii],E0[ii],kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hmo_tg_p[ii]->SetLineColor(2);
	   hmo_tg_p[ii]->SetLineWidth(2);

           T_el->Draw(Form("(%f-tg.p/1000.)/%f>>hp_tg_p%d",E0[ii],E0[ii],kin[ii]),Form("rate*(%s)",CUT1.Data()),"HIST");
	   hp_tg_p[ii]->SetLineColor(4);
	   hp_tg_p[ii]->SetLineWidth(2);

	   delete T_el;
	   delete T_mo;
	}

	TCanvas *c1 = new TCanvas("c1","c1",1500,1500);
	c1->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c1->cd(ii+1);
	  hp_r[ii]->Draw("HIST");
	  hmo_r[ii]->Draw("HIST SAME");
	  hp_r[ii]->SetTitle("main detector r;ring.r;");
	
	  Double_t np=1;
	  Double_t nmoller=1;
	  Double_t ratio=0;
 	  if(ii<2){
  	     np=hp_r[ii]->Integral();
	     nmoller=hmo_r[ii]->Integral();
	     ratio=nmoller/np;

             TLatex lex;
             lex.SetTextSize(0.03);
             lex.DrawLatexNDC(0.2,0.7,Form("moller/elastic=%f",ratio));
	  }
	  if(ii==2){
	     int bin1=hp_r[ii]->FindBin(800);
	     int bin2=hp_r[ii]->FindBin(1000);
  	     np=hp_r[ii]->Integral(bin1,bin2);
	     nmoller=hmo_r[ii]->Integral(bin1,bin2);
	     ratio=nmoller/np;

             TLatex lex;
             lex.SetTextSize(0.03);
             lex.DrawLatexNDC(0.15,0.7,"(moller/elastic)(800,1000)");
             lex.DrawLatexNDC(0.15,0.65,Form("=%f",ratio));
	  }
	  if(ii>2){
	     int bin1=hp_r[ii]->FindBin(700);
	     int bin2=hp_r[ii]->FindBin(900);
  	     np=hp_r[ii]->Integral(bin1,bin2);
	     nmoller=hmo_r[ii]->Integral(bin1,bin2);
	     ratio=nmoller/np;

             TLatex lex;
             lex.SetTextSize(0.03);
             lex.DrawLatexNDC(0.55,0.7,"(moller/elastic)(700,900)");
             lex.DrawLatexNDC(0.55,0.65,Form("=%f",ratio));
	  }
	}

	c1->cd(6);
        TLatex lex1;
        lex1.SetTextSize(0.05);
        lex1.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex1.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");


	TCanvas *c2 = new TCanvas("c2","c2",1500,1500);
	c2->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c2->cd(ii+1);
	  hp_ph[ii]->Draw("HIST");
	  hmo_ph[ii]->Draw("HIST SAME");
	  hmo_ph[ii]->SetTitle("main detector phi;ring.ph;");
	}

	c2->cd(6);
        TLatex lex2;
        lex2.SetTextSize(0.05);
        lex2.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex2.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");


	TCanvas *c3 = new TCanvas("c3","c3",1500,1500);
	c3->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c3->cd(ii+1);
	  hp_php[ii]->Draw("HIST");
	  hmo_php[ii]->Draw("HIST SAME");
	  hp_php[ii]->SetTitle("main detector phi';;");
	}

	c3->cd(6);
        TLatex lex3;
        lex3.SetTextSize(0.05);
        lex3.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex3.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");

	
	TCanvas *c4 = new TCanvas("c4","c4",1500,1500);
	c4->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c4->cd(ii+1);
	  hp_rp[ii]->Draw("HIST");
	  hmo_rp[ii]->Draw("HIST SAME");
	  hp_rp[ii]->SetTitle("main detector r';;");
	}

	c4->cd(6);
        TLatex lex4;
        lex4.SetTextSize(0.05);
        lex4.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex4.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");


	TCanvas *c5 = new TCanvas("c5","c5",1500,1500);
	c5->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c5->cd(ii+1);
	  hp_tg_th[ii]->Draw("HIST");
	  hmo_tg_th[ii]->Draw("HIST SAME");
	  hp_tg_th[ii]->SetTitle("target theta;tg.th;");
	}

	c5->cd(6);
        TLatex lex5;
        lex5.SetTextSize(0.05);
        lex5.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex5.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");


	TCanvas *c6 = new TCanvas("c6","c6",1500,1500);
	c6->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c6->cd(ii+1);
	  hp_tg_p[ii]->Draw("HIST");
	  hmo_tg_p[ii]->Draw("HIST SAME");
	  hp_tg_p[ii]->SetTitle("target (E0-p)/E0;");
	}

	c6->cd(6);
        TLatex lex6;
        lex6.SetTextSize(0.05);
        lex6.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex6.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");


	TCanvas *c7 = new TCanvas("c7","c7",1500,1500);
	c7->Divide(3,2);
	for(int ii=0; ii<nn; ii++){
	  c7->cd(ii+1);
	  hp_p[ii]->Draw("HIST");
	  hmo_p[ii]->Draw("HIST SAME");
	  hp_p[ii]->SetTitle("main detector p;ring.p;");
	}

	c7->cd(6);
        TLatex lex7;
        lex7.SetTextSize(0.05);
        lex7.DrawLatexNDC(0.55,0.7,"#color[2]{moller}");
        lex7.DrawLatexNDC(0.55,0.6,"#color[4]{elastic}");

}
