using namespace TMath;
void EstimateXS(){

     Double_t E=3.7715/1000.0;  // GeV
     //Double_t th=0.0029/180.*Pi(); //rad
     Double_t th=0.0202954; //rad
     Double_t I = 10.0e-6;  // uA current


     Double_t MA=12*0.931494; //GeV
     Double_t alpha = 1/137.035999084;
     Double_t hbarc = 197.3269804/1000.;  //GeV*fm
     Double_t e=1.602176634e-19;
     Double_t rho=2.265;  // gcm-3
     Double_t l = 1.0/10.0;  // cm
     Double_t MA_1 = 12.01078; // g*mole-1
     Double_t NA=6.02214076e23;

     Double_t CTH = cos(th);
     Double_t CTH2= cos(th/2.)*cos(th/2.);
     Double_t STH2= sin(th/2.)*sin(th/2.);

     Double_t Ep = E/(1.0+E/MA*(1.0-CTH));
     
     Double_t sig_mott = pow(6*alpha*cos(th/2.)/(2*E*STH2),2)*Ep/E;
     sig_mott = sig_mott*hbarc*hbarc;   // fm^2
  
     Double_t Lum = I/e*rho*l/MA_1*NA;   // cm-2
   
     Double_t rate_mott = (sig_mott*pow(1e-13,2))*Lum;
     Double_t Q2 = 4.0*E*Ep*STH2;       // GeV^2
     Double_t q2 = Q2/(hbarc*hbarc);  // fm-2

     Double_t a = 1.65; 
     Double_t FF = (1.0 - (q2*a*a)/9.0)*exp(-(q2*a*a)/4.0);        // Form Factor
     Double_t xs = sig_mott*FF*FF;
     Double_t rate = rate_mott*FF*FF;

     Double_t m_e = 0.511/1000.;
     Double_t SchwingerDeltaE = 15.0/1000.;  // this has to be checked --- hanjie
     Double_t FunctionofTheta = log(STH2)*log(CTH2);
     Double_t delta_Schwinger = (-2.0*alpha/Pi()) * ((log(E/SchwingerDeltaE) - 13.0/12.0)
                      *(log(Q2/(m_e*m_e)) - 1.0) + 17.0/36.0 + FunctionofTheta/2.0);

     Double_t phase = 2.0*Pi()*(cos(0.1/180.*Pi())-cos(2./180.*Pi()));


     cout<<"E' (GeV):   "<<Ep<<endl;
     cout<<"q (fm-1):   "<<sqrt(q2)<<"  "<<Ep<<endl;
     cout<<"mott rate:  "<<rate_mott<<endl;
     cout<<"(F(q))^2:   "<<FF*FF<<endl;
     cout<<"delta_Sch   "<<delta_Schwinger<<endl;
     cout<<"phase       "<<phase<<endl;
     cout<<"xs          "<<xs*phase<<endl;
     cout<<"final rate  "<<phase*rate*(1+delta_Schwinger)<<endl;
}
