void GetACC_allkin(){
	TChain *Tm_old=new TChain("T");
	Tm_old->Add("/home/hanjie/moller/remoll/Rootfiles/new_fieldmap_new_sieve/remoll_H1_moller_p5_newfield*");

	TChain *Tm_new=new TChain("T");
	Tm_new->Add("/home/hanjie/moller/optics_analysis/Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_H1_moller_p5_newfield*");

	TChain *Tp_old[5];
	TChain *Tp_new[5];
	
	for(int ii=0; ii<5; ii++){
	  Tp_old[ii]=new TChain("T");
	  Tp_old[ii]->Add(Form("/home/hanjie/moller/remoll/Rootfiles/new_fieldmap_new_sieve/remoll_C12_elastic_p%d_*",ii+1));
	
	  Tp_new[ii]=new TChain("T");
	  Tp_new[ii]->Add(Form("/home/hanjie/moller/optics_analysis/Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_C12_elastic_p%d_*",ii+1));
	}

	//TString dpcut1="(ev.beamp-tg.p)/ev.beamp<0.5";
	TString dpcut1="1";
	TString thcut1="sieve.r>25";

	int nbin=40;
	int nbinp=50;
// moller pass 5 distributions
	TH1F *hm_th_acc=new TH1F("hm_th_acc","accepted target theta distribution",nbin,0,0.025);    // total target theta distribution that being accepted at the main detectors
	TH1F *hm_th_in=new TH1F("hm_th_in","incident target theta distribution",nbin,0,0.025);     // total target theta distribution 

	Tm_old->Draw("part.th>>hm_th_in","rate");
	Tm_new->Draw("tg.th>>hm_th_acc",Form("rate*(%s)",thcut1.Data()));

	TH1F *hm_p_acc=new TH1F("hm_p_acc","accepted target momentum distribution",nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH1F *hm_p_in=new TH1F("hm_p_in","incident momentum distribution",nbinp,0,11050);     // total target momentum distribution

	Tm_old->Draw("part.p>>hm_p_in","rate");
	Tm_new->Draw("tg.p>>hm_p_acc",Form("rate*(%s)",thcut1.Data()));

	TH2F *hm_acc=new TH2F("hm_acc","accepted target momentum and theta distribution",nbin,0,0.025,nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH2F *hm_in=new TH2F("hm_in","incident momentum and theta distribution",nbin,0,0.025,nbinp,0,11050);     // total target momentum distribution

	Tm_old->Draw("part.p:part.th>>hm_in","rate");
	Tm_new->Draw("tg.p:tg.th>>hm_acc",Form("rate*(%s)",thcut1.Data()));

// five passes elastic events distribution

	TH1F *he_th_acc[5];
	TH1F *he_th_in[5];
	TH1F *he_p_acc[5];
	TH1F *he_p_in[5];

	TH2F *he_acc[5];
	TH2F *he_in[5];

	for(int ii=0; ii<5; ii++){
	   he_th_acc[ii]=new TH1F(Form("he_th_acc_p%d",ii+1),"accepted target theta distribution",nbin,0,0.025);
	   he_th_in[ii]=new TH1F(Form("he_th_in_p%d",ii+1),"incident target theta distribution",nbin,0,0.025);

	   Tp_old[ii]->Draw(Form("part.th>>he_th_in_p%d",ii+1),"rate");
	   Tp_new[ii]->Draw(Form("tg.th>>he_th_acc_p%d",ii+1),Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));

	   he_p_acc[ii]=new TH1F(Form("he_p_acc_p%d",ii+1),"accepted target momentum distribution",nbinp,0,11050);
	   he_p_in[ii]=new TH1F(Form("he_p_in_p%d",ii+1),"incident target momentum distribution",nbinp,0,11050);

	   Tp_old[ii]->Draw(Form("part.p>>he_p_in_p%d",ii+1),"rate");
	   Tp_new[ii]->Draw(Form("tg.p>>he_p_acc_p%d",ii+1),Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));

	   he_acc[ii]=new TH2F(Form("he_acc_p%d",ii+1),"accepted target momentum and theta distribution",nbin,0,0.025,nbinp,0,11050);
	   he_in[ii]=new TH2F(Form("he_in_p%d",ii+1),"incident momentum and theta distribution",nbin,0,0.025,nbinp,0,11050);

	   Tp_old[ii]->Draw(Form("part.p:part.th>>he_in_p%d",ii+1),"rate");
	   Tp_new[ii]->Draw(Form("tg.p:tg.th>>he_acc_p%d",ii+1),Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));
	}


        TH1F *hm_th_accfunc = (TH1F*)hm_th_acc->Clone();
        hm_th_accfunc->GetXaxis()->SetTitle("tg.th(rad)");
        hm_th_accfunc->GetYaxis()->SetTitle("ACC");
        hm_th_accfunc->SetTitle("theta acceptance function");
        hm_th_accfunc->Divide(hm_th_in);

        TH1F *hm_p_accfunc = (TH1F*)hm_p_acc->Clone();
        hm_p_accfunc->GetXaxis()->SetTitle("tg.p(MeV)");
        hm_p_accfunc->GetYaxis()->SetTitle("ACC");
        hm_p_accfunc->SetTitle("momentum acceptance function");
        hm_p_accfunc->Divide(hm_p_in);

	TH1F *he_th_accfunc[5];
	TH1F *he_p_accfunc[5];

	for(int ii=0; ii<5; ii++){
	    he_th_accfunc[ii]=(TH1F*)he_th_acc[ii]->Clone();
            he_th_accfunc[ii]->GetXaxis()->SetTitle("tg.th(rad)");
            he_th_accfunc[ii]->GetYaxis()->SetTitle("ACC");
            he_th_accfunc[ii]->SetTitle("theta acceptance function");
            he_th_accfunc[ii]->Divide(he_th_in[ii]);

	    he_p_accfunc[ii]=(TH1F*)he_p_acc[ii]->Clone();
            he_p_accfunc[ii]->GetXaxis()->SetTitle("tg.p(MeV)");
            he_p_accfunc[ii]->GetYaxis()->SetTitle("ACC");
            he_p_accfunc[ii]->SetTitle("momentum acceptance function");
            he_p_accfunc[ii]->Divide(he_p_in[ii]);
	}

	
	TCanvas *c1=new TCanvas("c1","c1",1500,1500);
	hm_th_accfunc->SetLineColor(2);
	hm_th_accfunc->SetLineWidth(2);
	hm_th_accfunc->Draw("HIST");

	int color[5]={1,4,6,8,46};
	
	for(int ii=0; ii<5; ii++){
	   he_th_accfunc[ii]->SetLineWidth(2);	
 	   he_th_accfunc[ii]->SetLineColor(color[ii]);
	   he_th_accfunc[ii]->Draw("HIST same");
	}

	TLegend *leg=new TLegend(0.15,0.65,0.3,0.8);
	for(int ii=0; ii<5; ii++)
	   leg->AddEntry(he_th_accfunc[ii],Form("pass%d elastic",ii+1),"L");

	leg->Draw();

	TCanvas *c2=new TCanvas("c2","c2",1500,1500);
	hm_p_accfunc->SetLineColor(2);
	hm_p_accfunc->SetLineWidth(2);
	hm_p_accfunc->Draw("HIST");

	for(int ii=0; ii<5; ii++){
	   he_p_accfunc[ii]->SetLineWidth(2);	
 	   he_p_accfunc[ii]->SetLineColor(color[ii]);
	   he_p_accfunc[ii]->Draw("HIST same");
	}

	TLegend *leg1=new TLegend(0.15,0.65,0.3,0.8);
	for(int ii=0; ii<5; ii++)
	   leg1->AddEntry(he_p_accfunc[ii],Form("pass%d elastic",ii+1),"L");

	leg1->Draw();


}
