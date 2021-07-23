void MollerTheoEtheta(){
	TGraph *gpth[5];
	double thmax=150;   //deg
	double thmin=15;   // deg
	double E[5]={11000,8800,6600,4400,2200};   //MeV
	double me=0.511;  //MeV

	double beta[5]={0},gamma[5]={0};
	double Eout_com[5]={0},pout_com[5]={0};

	for(int ii=0; ii<5; ii++){
	   gpth[ii]=new TGraph();

	   beta[ii]=sqrt((E[ii]-me)/(E[ii]+me));
	   gamma[ii]=1.0/sqrt(1-beta[ii]*beta[ii]);
	   Eout_com[ii]=gamma[ii]*me;
	   pout_com[ii]=beta[ii]*gamma[ii]*me;
	}

	for(int ii=0; ii<100; ii++){

	    double th=thmin+(thmax-thmin)/100.0*ii;
	    double thrad=th/180*3.1415926;  // rad

	    for(int jj=0; jj<5; jj++){
	       double Eout=sqrt(pow(pout_com[jj]*sin(thrad),2)+pow(beta[jj]*gamma[jj]*Eout_com[jj]+gamma[jj]*pout_com[jj]*cos(thrad),2));
	       double tanthlab=pout_com[jj]*sin(thrad)/gamma[jj]/(beta[jj]*Eout_com[jj]+pout_com[jj]*cos(thrad));
	       double thlab=atan(tanthlab)*180.0/3.1415926;
	       gpth[jj]->SetPoint(ii,thlab,Eout);
	    }
	}

	int color[5]={1,2,4,6,8};
	TMultiGraph *mg=new TMultiGraph();
	for(int ii=0; ii<5; ii++){
	   gpth[ii]->SetMarkerStyle(8);
	   gpth[ii]->SetMarkerColor(color[ii]);
	   mg->Add(gpth[ii]);
	}
	mg->Draw("AP");
	mg->SetTitle("moller E' vs. theta;theta(deg);E'(MeV);");

	TLegend *leg=new TLegend(0.5,0.6,0.75,0.8);
	for(int ii=0; ii<5; ii++)
	   leg->AddEntry(gpth[ii],Form("pass%d",5-ii),"PL");

	leg->Draw();

}
