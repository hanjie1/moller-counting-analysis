void CheckCfoil_kin(){
     TChain *T_e[5];  // elastic
     TChain *T_q[5];  // quasi
     TChain *T_in[5]; // inelasitc

     for(int ii=0; ii<5; ii++){
       T_e[ii] = new TChain("T");
       T_e[ii]->Add(Form("/home/hanjie/moller/remoll/Rootfiles/remoll_C12_elastic_p%d_long.root",ii+1));

       T_q[ii] = new TChain("T");
       T_q[ii]->Add(Form("/home/hanjie/moller/remoll/Rootfiles/remoll_C12_quasielastic_p%d_long.root",ii+1));

       T_in[ii] = new TChain("T");
       T_in[ii]->Add(Form("/home/hanjie/moller/remoll/Rootfiles/remoll_C12_inelastic_p%d_long.root",ii+1));
     }

// momentum distributions
     TH1F *hp_e[5]; TH1F *hp_q[5]; TH1F *hp_in[5];
     TH1F *hth_e[5]; TH1F *hth_q[5]; TH1F *hth_in[5];
     TH1F *hw2_q[5]; TH1F *hw2_in[5];
     TH1F *hq2_e[5]; TH1F *hq2_q[5]; TH1F *hq2_in[5];

     double beamE[5]={2.2, 4.4, 6.6, 8.8, 11.0};

     for(int ii=0; ii<5; ii++){
	hp_e[ii] = new TH1F(Form("hp_e%d",ii+1),"elastic momentum distribution",200,beamE[ii]-0.5,beamE[ii]+0.5);
	hp_q[ii] = new TH1F(Form("hp_q%d",ii+1),"quasielastic momentum distribution",200,beamE[ii]-0.5,beamE[ii]+0.5);
	hp_in[ii] = new TH1F(Form("hp_in%d",ii+1),"inelastic momentum distribution",200,beamE[ii]-0.5,beamE[ii]+0.5);

	hth_e[ii] = new TH1F(Form("hth_e%d",ii+1),"elastic theta distribution",200,-0.1,2.5);
	hth_q[ii] = new TH1F(Form("hth_q%d",ii+1),"quasielastic theta distribution",200,-0.1,2.5);
	hth_in[ii] = new TH1F(Form("hth_in%d",ii+1),"inelastic theta distribution",200,-0.1,2.5);

	hq2_e[ii] = new TH1F(Form("hq2_e%d",ii+1),"elastic Q2 distribution",200,0,0.05);
	hq2_q[ii] = new TH1F(Form("hq2_q%d",ii+1),"quasielastic Q2 distribution",200,0,0.05);
	hq2_in[ii] = new TH1F(Form("hq2_in%d",ii+1),"inelastic Q2 distribution",200,0,0.05);

	hw2_q[ii] = new TH1F(Form("hw2_q%d",ii+1),"quasielastic W2 distribution",200,0,2);
	hw2_in[ii] = new TH1F(Form("hw2_in%d",ii+1),"inelastic W2 distribution",200,0,2);
     }

     

     TCanvas *c1 = new TCanvas("c1","c1",1200,800);
     c1->Divide(5,1,0.005,0.005);
     for(int ii=0; ii<5; ii++){
       c1->cd(ii+1);
       T_e[ii]->Draw(Form("part.p/GeV>>hp_e%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hp_e[ii]->SetTitle(Form("pass%d;part.p;",ii+1));
 
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c2 = new TCanvas("c2","c2",1200,800);
     c2->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c2->cd(ii+1);
       T_q[ii]->Draw(Form("part.p/GeV>>hp_q%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hp_q[ii]->SetTitle(Form("pass%d;part.p;",ii+1));
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Quasi-elastic");
       }
       gPad->SetLogy();
     }


     TCanvas *c3 = new TCanvas("c3","c3",1200,800);
     c3->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c3->cd(ii+1);
       T_in[ii]->Draw(Form("part.p/GeV>>hp_in%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hp_in[ii]->SetTitle(Form("pass%d;part.p;",ii+1));

       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Inelastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c4 = new TCanvas("c4","c4",1200,800);
     c4->Divide(5,1,0.005,0.005);
     for(int ii=0; ii<5; ii++){
       c4->cd(ii+1);
       T_e[ii]->Draw(Form("part.th*180.0/TMath::Pi()>>hth_e%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hth_e[ii]->SetTitle(Form("pass%d;part.th;",ii+1));
 
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c5 = new TCanvas("c5","c5",1200,800);
     c5->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c5->cd(ii+1);
       T_q[ii]->Draw(Form("part.th*180.0/TMath::Pi()>>hth_q%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hth_q[ii]->SetTitle(Form("pass%d;part.th;",ii+1));
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Quasi-elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c6 = new TCanvas("c6","c6",1200,800);
     c6->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c6->cd(ii+1);
       T_in[ii]->Draw(Form("part.th*180.0/TMath::Pi()>>hth_in%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hth_in[ii]->SetTitle(Form("pass%d;part.th;",ii+1));

       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Inelastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c7 = new TCanvas("c7","c7",1200,800);
     c7->Divide(5,1,0.005,0.005);
     for(int ii=0; ii<5; ii++){
       c7->cd(ii+1);
       T_e[ii]->Draw(Form("ev.Q2/GeV/GeV>>hq2_e%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hq2_e[ii]->SetTitle(Form("pass%d;ev.Q2;",ii+1));
 
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c8 = new TCanvas("c8","c8",1200,800);
     c8->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c8->cd(ii+1);
       T_q[ii]->Draw(Form("ev.Q2/GeV/GeV>>hq2_q%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hq2_q[ii]->SetTitle(Form("pass%d;ev.Q2;",ii+1));
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Quasi-elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c9 = new TCanvas("c9","c9",1200,800);
     c9->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c9->cd(ii+1);
       T_in[ii]->Draw(Form("ev.Q2/GeV/GeV>>hq2_in%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hq2_in[ii]->SetTitle(Form("pass%d;ev.Q2;",ii+1));

       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Inelastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c10 = new TCanvas("c10","c10",1200,800);
     c10->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c10->cd(ii+1);
       T_q[ii]->Draw(Form("ev.W2/GeV/GeV>>hw2_q%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hw2_q[ii]->SetTitle(Form("pass%d;ev.W2;",ii+1));
       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Quasi-elastic");
       }
       gPad->SetLogy();
     }

     TCanvas *c11 = new TCanvas("c11","c11",1200,800);
     c11->Divide(5,1);
     for(int ii=0; ii<5; ii++){
       c11->cd(ii+1);
       T_in[ii]->Draw(Form("ev.W2/GeV/GeV>>hw2_in%d",ii+1),Form("rate*(ev.beamp/1000.0>%f)",beamE[ii]-2),"hist");
       hw2_in[ii]->SetTitle(Form("pass%d;ev.W2;",ii+1));

       if(ii==0){
	 TLatex lex;
         lex.SetTextSize(0.075);
         lex.SetTextAlign(13);  //align at top
         lex.DrawLatexNDC(.2,.8,"Inelastic");
       }
       gPad->SetLogy();
     }

    c1->Print("CheckGenC12.pdf[");
    c1->Print("CheckGenC12.pdf");
    c2->Print("CheckGenC12.pdf");
    c3->Print("CheckGenC12.pdf");
    c4->Print("CheckGenC12.pdf");
    c5->Print("CheckGenC12.pdf");
    c6->Print("CheckGenC12.pdf");
    c7->Print("CheckGenC12.pdf");
    c8->Print("CheckGenC12.pdf");
    c9->Print("CheckGenC12.pdf");
    c10->Print("CheckGenC12.pdf");
    c11->Print("CheckGenC12.pdf");
    c11->Print("CheckGenC12.pdf]");


}
