void GetACC(TString origfile, TString accfile, double rmin, double rmax, double phmin, double phmax, int ismoller){

	TChain *T_old=new TChain("T");
	T_old->Add(Form("/home/hanjie/moller/remoll/Rootfiles/sieve1/remoll_%s_*",origfile.Data()));

	TChain *T_new=new TChain("T");
	T_new->Add(Form("/home/hanjie/moller/optics_analysis/Rootfiles/sieve1/trackhits_remoll_%s_allSD*",accfile.Data()));


//	TString dpcut1="1";
//	if(ismoller==0)dpcut1="(ev.beamp-tg.p)/ev.beamp<0.5";
//	TString thcut1="sieve.r>25";
//	TString totalcut=Form("");
	TString rcut = Form("ring.r>%f && ring.r<%f",rmin,rmax);
	TString phcut = Form("ring.ph>%f && ring.ph<%f",phmin,phmax);
	TString totalcut = Form("%s && %s",rcut.Data(),phcut.Data());

	int nbin=40;

	TH1F *hth_acc=new TH1F("hth_acc","total target theta distribution",nbin,0,0.025);    // total target theta distribution that being accepted at the main detectors
	TH1F *hth_in=new TH1F("hth_in","target theta distribution",nbin,0,0.025);     // total target theta distribution 

	T_old->Draw("part.th>>hth_in","rate");
	T_new->Draw("tg.th>>hth_acc",Form("rate*(%s)",totalcut.Data()));

	int nbinp=50;

	TH1F *hp_acc=new TH1F("hp_acc","total target momentum distribution",nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH1F *hp_in=new TH1F("hp_in","target momentum distribution",nbinp,0,11050);     // total target momentum distribution

	T_old->Draw("part.p>>hp_in","rate");
	T_new->Draw("tg.p>>hp_acc",Form("rate*(%s)",totalcut.Data()));

	TH2F *hpth_acc=new TH2F("hpth_acc","accepted p vs theta distribution",nbin,0,0.025,nbinp,0,11050);    // total target momentum distribution that being accepted at the main detectors
	TH2F *hpth_in=new TH2F("hpth_in","incident p vs theta distribution",nbin,0,0.025,nbinp,0,11050);     // total target momentum distribution

	T_old->Draw("part.p:part.th>>hpth_in","rate");
	T_new->Draw("tg.p:tg.th>>hpth_acc",Form("rate*(%s)",totalcut.Data()));


	TGraphErrors *gthACC=new TGraphErrors();

	for(int ii=1; ii<nbin+1; ii++){

	   Double_t th=hth_in->GetBinCenter(ii);

	   Double_t ntotal=hth_in->GetBinContent(ii);
	   Double_t nacc=hth_acc->GetBinContent(ii);
	   Double_t tmp_acc = 0;
	   if(nacc!=0 && ntotal!=0) tmp_acc=nacc/ntotal;
	   Double_t tmp_acc_err = 0;
	   if(nacc!=0 && ntotal!=0) tmp_acc_err=sqrt(1./nacc-1./ntotal);

	   gthACC->SetPoint(ii,th,tmp_acc);
	   gthACC->SetPointError(ii,0,tmp_acc_err);

	}

	TGraphErrors *gpACC=new TGraphErrors();

	for(int ii=1; ii<nbin+1; ii++){

	   Double_t p=hp_in->GetBinCenter(ii);

	   Double_t ntotal=hp_in->GetBinContent(ii);
	   Double_t nacc=hp_acc->GetBinContent(ii);
	   Double_t tmp_acc = 0;
	   if(nacc!=0 && ntotal!=0) tmp_acc=nacc/ntotal;
	   Double_t tmp_acc_err = 0;
	   if(nacc!=0 && ntotal!=0) tmp_acc_err=sqrt(1./nacc-1./ntotal);

	   gpACC->SetPoint(ii,p,tmp_acc);
	   gpACC->SetPointError(ii,0,tmp_acc_err);

	}

	
	TCanvas *c1=new TCanvas("c1","c1",500,1500);
	c1->Divide(3,1);
	c1->cd(1);
	gthACC->SetMarkerStyle(8);	
	gthACC->SetMarkerColor(4);
	gthACC->Draw("AP");	
	gthACC->SetTitle("theta acceptance;tg.th(rad);ACC");

	c1->cd(2);
	gpACC->SetMarkerStyle(8);	
	gpACC->SetMarkerColor(4);
	gpACC->Draw("AP");	
	gpACC->SetTitle("momentum acceptance;tg.p(MeV);ACC");

	c1->cd(3);
        TH2F *hpth = (TH2F*)hpth_acc->Clone();
   	hpth->GetXaxis()->SetTitle("tg.th(rad)");
   	hpth->GetYaxis()->SetTitle("tg.p(MeV)");
   	hpth->SetTitle("acceptance");
   	hpth->Divide(hpth_in);
   	hpth->Draw("COLZ");

	TCanvas *c2=new TCanvas("c2","c2",500,1500);
	c2->Divide(2,2);
	c2->cd(1);
	hth_acc->Draw("HIST");
	c2->cd(2);
	hp_in->Draw("HIST");
	c2->cd(3);
	hp_acc->Draw("HIST");
	c2->cd(4);
	hth_in->Draw("HIST");
	
	
	c1->Print("plots/");


}
