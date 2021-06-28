using namespace TMath;

double GetXS(double E, double th){
     th=th/180.0*Pi();  //rad
	
     Double_t MA=12*0.931494; //GeV
     Double_t alpha = 1/137.035999084;
     Double_t hbarc = 197.3269804/1000.;  //GeV*fm
     Double_t e=1.602176634e-19;
     Double_t rho=2.265;  // gcm-3
     Double_t l = 1.0/10.0;  // cm
     Double_t MA_1 = 12.01078; // g*mole-1
     Double_t NA=6.02214076e23;
     Double_t m_e = 0.511/1000.;  // GeV

     Double_t CTH = cos(th);
     Double_t CTH2= cos(th/2.)*cos(th/2.);
     Double_t STH2= sin(th/2.)*sin(th/2.);

     Double_t Ep = E/(1.0+E/MA*(1.0-CTH));

     Double_t sig_mott = pow(6*alpha*cos(th/2.)/(2*E*STH2),2)*Ep/E;
     sig_mott = sig_mott*hbarc*hbarc;   // fm^2

     Double_t Q2 = 4.0*E*Ep*STH2;       // GeV^2
     Double_t q2 = Q2/(hbarc*hbarc);  // fm-2

     Double_t a = 1.65;    // fm
     Double_t FF = (1.0 - (q2*a*a)/9.0)*exp(-(q2*a*a)/4.0);        // Form Factor
     Double_t xs = sig_mott*FF*FF;

     //Double_t SchwingerDeltaE = 15.0/1000.;  // this has to be checked --- hanjie
     Double_t SchwingerDeltaE = 0.0/1000;  // this has to be checked --- hanjie
     Double_t FunctionofTheta = log(STH2)*log(CTH2);
     Double_t delta_Schwinger = 0;
            
     if( SchwingerDeltaE>0) 
	   delta_Schwinger = (-2.0*alpha/Pi()) * ((log(E/SchwingerDeltaE) - 13.0/12.0)
                      *(log(Q2/(m_e*m_e)) - 1.0) + 17.0/36.0 + FunctionofTheta/2.0);

     xs = xs*(1.0 + delta_Schwinger)*1e4;  // 10^-30 cm2

     if(q2>2.5 && q2<4) xs=0;
//cout<<E<<"  "<<th<<"  "<<q2<<"  "<<xs<<endl;
     return xs;

}


void PlotXS_el(){
    
    ifstream file;
    file.open("XS_el.dat");

    if(!file.is_open())return;

    Ssiz_t from=0;
    TString content,tmp;
    int nn=0;

    double E[53]={0},theta[53]={0},xs[53]={0},xs_err[53]={0};

    while(tmp.ReadLine(file)){
	  if(nn==0){nn++; continue;}
          tmp.Tokenize(content,from," ");
          E[nn-1]=atof(content.Data());
          tmp.Tokenize(content,from," ");
          theta[nn-1]=atof(content.Data());
          tmp.Tokenize(content,from," ");
          double tmpxs=atof(content.Data());
	  if(E[nn-1]>188 || theta[nn-1]>90) xs[nn-1]=tmpxs*1e-3;
	  else xs[nn-1]=tmpxs;
          tmp.Tokenize(content,from," ");
          double tmpxs_err=atof(content.Data());
	  if(E[nn-1]>188 || theta[nn-1]>90) xs_err[nn-1]=tmpxs_err*1e-3;
	  else xs_err[nn-1]=tmpxs_err;

          from=0;
          nn++;
    }
    file.close();

    TGraphErrors *gData1=new TGraphErrors();
    TGraphErrors *gData2=new TGraphErrors();
    TGraphErrors *gData3=new TGraphErrors();

    TGraph *gMC1=new TGraph();
    TGraph *gMC2=new TGraph();
    TGraph *gMC3=new TGraph();

    TGraphErrors *gRatio1 = new TGraphErrors();
    TGraphErrors *gRatio2 = new TGraphErrors();
    TGraphErrors *gRatio3 = new TGraphErrors();

    int n1=0, n2=0, n3=0;
    for(int ii=0; ii<53; ii++){
	double xs_mc = GetXS(E[ii]/1000.0,theta[ii]);
	if(xs_mc==0) continue;
	if(E[ii]==187){
	   gData1->SetPoint(n1,theta[ii],xs[ii]);
	   gData1->SetPointError(n1,0,xs_err[ii]);

	   gMC1->SetPoint(n1,theta[ii],xs_mc);
	   gRatio1->SetPoint(n1,theta[ii],xs[ii]/xs_mc);
	   gRatio1->SetPointError(n1,0,xs_err[ii]/xs_mc);
	   n1++;
	}

	if(E[ii]==600){
	   gData2->SetPoint(n2,theta[ii],xs[ii]);
	   gData2->SetPointError(n2,0,xs_err[ii]);

	   gMC2->SetPoint(n2,theta[ii],xs_mc);
	   gRatio2->SetPoint(n2,theta[ii],xs[ii]/xs_mc);
	   gRatio2->SetPointError(n2,0,xs_err[ii]/xs_mc);
	   n2++;
	}

	if(E[ii]==800){
	   gData3->SetPoint(n3,theta[ii],xs[ii]);
	   gData3->SetPointError(n3,0,xs_err[ii]);

	   gMC3->SetPoint(n3,theta[ii],xs_mc);
	   gRatio3->SetPoint(n3,theta[ii],xs[ii]/xs_mc);
	   gRatio3->SetPointError(n3,0,xs_err[ii]/xs_mc);
	   n3++;
	}

    }

    TCanvas *c1=new TCanvas("c1","c1",1500,500);		
/*
    c1->Divide(2,1);
    c1->cd(1);
    TMultiGraph *mg = new TMultiGraph();
    gData1->SetMarkerColor(1);
    gData1->SetMarkerStyle(20);
    gData2->SetMarkerColor(1);
    gData2->SetMarkerStyle(21);
    gData3->SetMarkerColor(1);
    gData3->SetMarkerStyle(22);

    gMC1->SetMarkerColor(2);
    gMC1->SetMarkerStyle(20);
    gMC2->SetMarkerColor(2);
    gMC2->SetMarkerStyle(21);
    gMC3->SetMarkerColor(2);
    gMC3->SetMarkerStyle(22);
    
    mg->Add(gData1);
    mg->Add(gData2);
    mg->Add(gData3);
    mg->Add(gMC1);
    mg->Add(gMC2);
    mg->Add(gMC3);
    mg->Draw("AP");

    c1->cd(2);
*/
    TMultiGraph *mg1 = new TMultiGraph();
    gRatio1->SetMarkerColor(1);
    gRatio1->SetMarkerStyle(20);
    gRatio2->SetMarkerColor(2);
    gRatio2->SetMarkerStyle(21);
    gRatio3->SetMarkerColor(4);
    gRatio3->SetMarkerStyle(22);

    mg1->Add(gRatio1);
    mg1->Add(gRatio2);
    mg1->Add(gRatio3);
    mg1->Draw("AP");
    mg1->SetTitle("xs_data/xs_mc;theta(deg);");

    TLegend *leg = new TLegend(0.6,0.7,0.75,0.85);
    leg->AddEntry(gRatio1,"187 MeV","P");
    leg->AddEntry(gRatio2,"600 MeV","P");
    leg->AddEntry(gRatio3,"800 MeV","P");
    leg->Draw();
}
