void MollerElastic_kin(){

	double thcom_max=150;   //deg
	double thcom_min=30;   // deg

	double th_min=0.1; //deg
	double th_max=2; //deg

	double E[5]={11000,8800,6600,4400,2200};   //MeV
	double me=0.511;  //MeV
	double Mp=931.494; //MeV

	double beta=0,gamma=0;
	double Eout_com=0,pout_com=0;


	TGraph *gpth_moller=new TGraph();	
	beta=sqrt((E[0]-me)/(E[0]+me));
	gamma=1.0/sqrt(1-beta*beta);
	Eout_com=gamma*me;
	pout_com=beta*gamma*me;

	TGraph *gpth_el[5];
	for(int ii=0; ii<5; ii++){
	   gpth_el[ii]=new TGraph();
	}

	for(int ii=0; ii<100; ii++){
	    double th=thcom_min+(thcom_max-thcom_min)/100.0*ii;
	    double thrad=th/180*3.1415926;  // rad

	    double Eout=sqrt(pow(pout_com*sin(thrad),2)+pow(beta*gamma*Eout_com+gamma*pout_com*cos(thrad),2));
	    double tanthlab=pout_com*sin(thrad)/gamma/(beta*Eout_com+pout_com*cos(thrad));
	    double thlab=atan(tanthlab)*180.0/3.1415926;
	    gpth_moller->SetPoint(ii,thlab,Eout);
	}

	for(int ii=0; ii<100; ii++){
	   double th=th_min+(th_max-th_min)/100.0*ii;
	   double thrad=th/180*3.1415926;  // rad

	   for(int jj=0; jj<5; jj++){
	      double eout=E[jj]/(1.0+E[jj]/(12.0*Mp)*(1-cos(thrad)));
	      gpth_el[jj]->SetPoint(ii,th,eout);
	   }
	}


	TCanvas *c1=new TCanvas("c1","c1",1500,1500);

	int color[5]={1,2,4,6,8};
	TMultiGraph *mg=new TMultiGraph();

	gpth_moller->SetMarkerStyle(22);
        gpth_moller->SetMarkerColor(46);
	mg->Add(gpth_moller);
	for(int ii=0; ii<5; ii++){
	   gpth_el[ii]->SetMarkerStyle(8);
	   gpth_el[ii]->SetMarkerColor(color[ii]);
	   mg->Add(gpth_el[ii]);
	}
	mg->Draw("AP");
	mg->SetTitle("E' vs. theta;theta(deg);E'(MeV);");

	TLegend *leg=new TLegend(0.5,0.6,0.75,0.8);
	leg->AddEntry(gpth_moller,"moller pass5","PL");
	for(int ii=0; ii<5; ii++)
	   leg->AddEntry(gpth_el[ii],Form("carbon elastic pass%d",5-ii),"PL");

	leg->Draw();

	double sieve_rmin=35;  // mm
	double target_z=-4500; // mm
	double cfoil_z1=-600; // mm
	double cfoil_z2=-300; // mm
	double cfoil_z3=300; // mm
	double cfoil_z4=600; // mm
	double sieve_z=-1375+2000; // mm

	double delta_z1 = sieve_z-(target_z+cfoil_z1);
	double theta_min1=atan(sieve_rmin/delta_z1)*180.0/3.1415926; // deg

	double delta_z2 = sieve_z-(target_z+cfoil_z2);
	double theta_min2=atan(sieve_rmin/delta_z2)*180.0/3.1415926; // deg

	double delta_z3 = sieve_z-(target_z+cfoil_z3);
	double theta_min3=atan(sieve_rmin/delta_z3)*180.0/3.1415926; // deg

	double delta_z4 = sieve_z-(target_z+cfoil_z4);
	double theta_min4=atan(sieve_rmin/delta_z4)*180.0/3.1415926; // deg

        TLine *l1 = new TLine(theta_min1,0,theta_min1,E[0]);
        l1->SetLineColor(1);
        l1->SetLineStyle(9);
        l1->Draw();

        TLine *l2 = new TLine(theta_min2,0,theta_min2,E[0]);
        l2->SetLineColor(2);
        l2->SetLineStyle(9);
        l2->Draw();

        TLine *l3 = new TLine(theta_min3,0,theta_min3,E[0]);
        l3->SetLineColor(4);
        l3->SetLineStyle(9);
        l3->Draw();

        TLine *l4 = new TLine(theta_min4,0,theta_min4,E[0]);
        l4->SetLineColor(6);
        l4->SetLineStyle(9);
        l4->Draw();

	double sieve_rmax=101;  // mm

	double theta_max1=atan(sieve_rmax/delta_z1)*180.0/3.1415926; // deg
	double theta_max2=atan(sieve_rmax/delta_z2)*180.0/3.1415926; // deg
	double theta_max3=atan(sieve_rmax/delta_z3)*180.0/3.1415926; // deg
	double theta_max4=atan(sieve_rmax/delta_z4)*180.0/3.1415926; // deg

        TLine *l5 = new TLine(theta_max1,0,theta_max1,E[0]);
        l5->SetLineColor(1);
        l5->SetLineStyle(9);
        l5->Draw();

        TLine *l6 = new TLine(theta_max2,0,theta_max2,E[0]);
        l6->SetLineColor(2);
        l6->SetLineStyle(9);
        l6->Draw();

        TLine *l7 = new TLine(theta_max3,0,theta_max3,E[0]);
        l7->SetLineColor(4);
        l7->SetLineStyle(9);
        l7->Draw();

        TLine *l8 = new TLine(theta_max4,0,theta_max4,E[0]);
        l8->SetLineColor(6);
        l8->SetLineStyle(9);
        l8->Draw();

        TAxis *axis1 = mg->GetXaxis();
	double xmin = axis1->GetXmin();
	double xmax = axis1->GetXmax();
	double ypos = c1->GetFrame()->GetY2();
	double ndiv = axis1->GetNdivisions();
 
	TGaxis *x_axis2 = new TGaxis(xmin,ypos,xmax,ypos,xmin/180.0*3.1415926,xmax/180.0*3.1415926,ndiv,"-");
	x_axis2->SetTitle("theta(rad)");
	x_axis2->SetLabelFont(42);
	x_axis2->SetLabelSize(0.02);
        x_axis2->SetTitleSize(0.03);
        //x_axis2->SetTitleOffset(1.2);
	x_axis2->SetTitleFont(42);
	x_axis2->Draw();

	c1->Update();
}
