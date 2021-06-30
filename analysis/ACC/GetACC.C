void GetACC(){
	TString filename;
	cout<<"Which root file?  ";
	cin>>filename;

	int ismoller=1;
	cout<<"Is it moller event? (0=no, 1=yes)  ";
	cin>>ismoller;

	TChain *T_old=new TChain("T");
	T_old->Add(Form("/home/hanjie/moller/remoll/Rootfiles/new_fieldmap_new_sieve/remoll_%s*",filename.Data()));

	TChain *T_new=new TChain("T");
	T_new->Add(Form("/home/hanjie/moller/optics_analysis/Rootfiles/new_fieldmap_new_sieve/trackhits_remoll_%s*",filename.Data()));


	TString dpcut1="1";
	if(ismoller==0)dpcut1="(ev.beamp-tg.p)/ev.beamp<0.5";
	TString thcut1="sieve.r>25";

	int nbin=40;

	TH1F *hth_acc[6];    // target theta distribution that being accepted at the main detectors
	TH1F *hth_acc_t=new TH1F("hth_acc_t","total target theta distribution",nbin,0,0.025);    // total target theta distribution that being accepted at the main detectors
	TH1F *hth_in=new TH1F("hth_in","target theta distribution",nbin,0,0.025);     // total target theta distribution 

	//T_old->Draw("part.th>>hth_in",Form("rate*(%s && %s)",dpcut.Data(),thcut.Data()));
	T_old->Draw("part.th>>hth_in","rate");
	T_new->Draw("tg.th>>hth_acc_t",Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));

	int nbinp=50;

	TH1F *hp_acc[6];    // target momentum distribution that being accepted at the main detectors
	TH1F *hp_acc_t=new TH1F("hp_acc_t","total target momentum distribution",nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH1F *hp_in=new TH1F("hp_in","target momentum distribution",nbinp,0,11050);     // total target momentum distribution

	T_old->Draw("part.p>>hp_in","rate");
	T_new->Draw("tg.p>>hp_acc_t",Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));

	TH2F *hacc_t=new TH2F("hacc_t","total target momentum distribution",nbin,0,0.025,nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH2F *hacc_in=new TH2F("hacc_in","target momentum distribution",nbin,0,0.025,nbinp,0,11050);     // total target momentum distribution

	T_old->Draw("part.p:part.th>>hacc_in","rate");
	T_new->Draw("tg.p:tg.th>>hacc_t",Form("rate*(%s && %s)",dpcut1.Data(),thcut1.Data()));


  //0,1,2 == closed, transition, open
     double rMin[7][3]={
      { 640.0,  640.0,  640.0},
      { 680.0,  680.0,  680.0},
      { 750.0,  750.0,  750.0},
      { 855.0,  847.5,  825.0},
      { 935.0,  920.0,  875.0},
      {1075.0, 1080.0, 1090.0},
      {1200.0, 1200.0, 1200.0}
    };
    double rMax[7][3]={
      { 680.0,  680.0,  680.0},
      { 750.0,  750.0,  750.0},
      { 855.0,  847.5,  825.0},
      { 935.0,  920.0,  875.0},
      {1075.0, 1060.0, 1055.0},
      {1190.0, 1190.0, 1190.0},
      {1500.0, 1500.0, 1500.0}
    };

	for(int ii=0; ii<6; ii++){
	   hth_acc[ii]=new TH1F(Form("hth_acc%d",ii+1),"accepted target distribution",nbin,0,0.025);
		
	   T_new->Draw(Form("tg.th>>hth_acc%d",ii+1),Form("rate*(ring.r>%f && ring.r<%f && %s && %s)",rMin[ii][2],rMin[ii+1][2],dpcut1.Data(),thcut1.Data()));

	   hp_acc[ii]=new TH1F(Form("hp_acc%d",ii+1),"accepted target distribution",nbinp,0,11050);
		
	   T_new->Draw(Form("tg.p>>hp_acc%d",ii+1),Form("rate*(ring.r>%f && ring.r<%f && %s && %s)",rMin[ii][2],rMin[ii+1][2],dpcut1.Data(),thcut1.Data()));

	}
	

	TGraphErrors *gthACC_t=new TGraphErrors();
	TGraphErrors *gthACC[6];
	for(int ii=0; ii<6; ii++)
	   gthACC[ii]=new TGraphErrors();

	for(int ii=1; ii<nbin+1; ii++){

	   Double_t th=hth_in->GetBinCenter(ii);

	   Double_t ntotal=hth_in->GetBinContent(ii);
	   Double_t nacc_t=hth_acc_t->GetBinContent(ii);
	   Double_t acc_t = 0;
	   if(nacc_t!=0 && ntotal!=0) acc_t=nacc_t/ntotal;
	   Double_t acc_t_err = 0;
	   if(nacc_t!=0 && ntotal!=0) acc_t_err=sqrt(1./nacc_t-1./ntotal);

	   gthACC_t->SetPoint(ii,th,acc_t);
	   gthACC_t->SetPointError(ii,0,acc_t_err);

	   for(int jj=0; jj<6; jj++){
	      Double_t nacc_s=hth_acc[jj]->GetBinContent(ii);
	      Double_t acc_s = 0;
	      if(nacc_s!=0 && ntotal!=0) acc_s=nacc_s/ntotal;
	      Double_t acc_s_err = 0;
	      if(nacc_s!=0 && ntotal!=0) acc_s_err=sqrt(1./nacc_s-1./ntotal);
	      gthACC[jj]->SetPoint(ii,th,acc_s);
	      gthACC[jj]->SetPointError(ii,0,acc_s_err);
	   }
	}

	TGraphErrors *gpACC_t=new TGraphErrors();
	TGraphErrors *gpACC[6];
	for(int ii=0; ii<6; ii++)
	   gpACC[ii]=new TGraphErrors();

	for(int ii=1; ii<nbinp+1; ii++){

	   Double_t th=hp_in->GetBinCenter(ii);

	   Double_t ntotal=hp_in->GetBinContent(ii);
	   Double_t nacc_t=hp_acc_t->GetBinContent(ii);
	   Double_t acc_t = 0;
	   if(nacc_t!=0 && ntotal!=0) acc_t=nacc_t/ntotal;
	   Double_t acc_t_err = 0;
	   if(nacc_t!=0 && ntotal!=0) acc_t_err=sqrt(1./nacc_t-1./ntotal);

	   gpACC_t->SetPoint(ii,th,acc_t);
	   gpACC_t->SetPointError(ii,0,acc_t_err);

	   for(int jj=0; jj<6; jj++){
	      Double_t nacc_s=hp_acc[jj]->GetBinContent(ii);
	      Double_t acc_s = 0;
	      if(nacc_s!=0 && ntotal!=0) acc_s=nacc_s/ntotal;
	      Double_t acc_s_err = 0;
	      if(nacc_s!=0 && ntotal!=0) acc_s_err=sqrt(1./nacc_s-1./ntotal);
	      gpACC[jj]->SetPoint(ii,th,acc_s);
	      gpACC[jj]->SetPointError(ii,0,acc_s_err);
	   }
	}

	
	TCanvas *c1=new TCanvas("c1","c1",500,1500);
	gthACC_t->SetMarkerStyle(8);	
	gthACC_t->SetMarkerColor(4);
	gthACC_t->Draw("AP");	
	gthACC_t->SetTitle("theta acceptance;tg.th(rad);ACC");

	TCanvas *c2=new TCanvas("c2","c2",1500,1500);
	c2->Divide(2,3);

	int color[6]={1,2,4,6,8,9};
	
	for(int ii=0; ii<6; ii++){
	   c2->cd(ii+1);
	   gthACC[ii]->SetMarkerStyle(8);	
 	   gthACC[ii]->SetMarkerColor(color[ii]);
	   gthACC[ii]->Draw("APL");
	   gthACC[ii]->SetTitle(Form("ring %d theta acceptance;tg.th(rad);ACC;",ii+1));
	}

	TCanvas *c3=new TCanvas("c3","c3",500,1500);
	gpACC_t->SetMarkerStyle(8);	
	gpACC_t->SetMarkerColor(4);
	gpACC_t->Draw("AP");	
	gpACC_t->SetTitle("momentum acceptance;tg.p(MeV);ACC");

	TCanvas *c4=new TCanvas("c4","c4",1500,1500);
	c4->Divide(2,3);

	for(int ii=0; ii<6; ii++){
	   c4->cd(ii+1);
	   gpACC[ii]->SetMarkerStyle(8);	
 	   gpACC[ii]->SetMarkerColor(color[ii]);
	   gpACC[ii]->Draw("APL");
	   gpACC[ii]->SetTitle(Form("ring %d momentum acceptance;tg.p (MeV);ACC;",ii+1));
	}


	TCanvas *c5=new TCanvas("c5","c5",500,1500);
        TH2F *hacc = (TH2F*)hacc_t->Clone();
   	hacc->GetXaxis()->SetTitle("tg.th(rad)");
   	hacc->GetYaxis()->SetTitle("tg.p(MeV)");
   	hacc->SetTitle("acceptance");
   	hacc->Divide(hacc_in);
   	hacc->Draw("COLZ");

}
