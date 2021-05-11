//oooooooooooooooooooooo000ooooooooooooooooooooooooo
// Qweak Quasi Elastic part of the code
//oooooooooooooooooooooo000ooooooooooooooooooooooooo

void F1F2QE09(int Z, int IA, double QSQ,
              double wsq, double &F1, double &F2)
{
//=======================================================================
//      SUBROUTINE F1F2QE09(Z, A, QSQ, wsq, F1, F2)
//
// Calculates quasielastic A(e,e')X structure functions F1 and F2 PER NUCLEUS
// for A>2 uses superscaling from Sick, Donnelly, Maieron, nucl-th/0109032
// for A=2 uses pre-integrated Paris wave function (see ~bosted/smear.f)
// coded by P. Bosted August to October, 2006
//
// input: Z, A  (real*8) Z and A of nucleus (shoud be 2.0D0 for deueron)
//        Qsq (real*8) is 4-vector momentum transfer squared (positive in
//                     chosen metric)
//        Wsq (real*8) is invarinat mass squared of final state calculated
//                     assuming electron scattered from a free proton
//                 
// outputs: F1, F2 (real*8) are structure functions per nucleus
//
// Note: Deuteron agrees well with Laget (see ~bosted/eg1b/laget.f) for
// a) Q2<1 gev**2 and dsig > 1% of peak: doesnt describe tail at high W
// b) Q2>1 gev**2 on wings of q.e. peak. But, this model is up
//    to 50% too big at top of q.e. peak. BUT, F2 DOES agree very
//    nicely with Osipenko et al data from CLAS, up to 5 GeV**2

  //cout << "Z, A, Q2, W2: " << Z << ", " << IA << ", " << QSQ << ", " << wsq << endl;

  double avgN, Pauli_sup1, Pauli_sup2, GEP, GEN, GMP, GMN, Q, Q3, Q4;
  double amp = 0.93827231;
  double RMUP = 2.792782;
  double RMUN = -1.913148;
  double Nu;
  double QV, TAU, FY;
  double kappa, lam, lamp, taup, squigglef, psi, psip, nuL, nuT;
  double kf, Es, GM2bar, GE2bar, W2bar, Delta, GL, GT;

  // Peter Bosted's correction params
  /*
  double pb[20] = {
    0.1023E+02, 0.1052E+01, 0.2485E-01, 0.1455E+01,
    0.5650E+01,-0.2889E+00, 0.4943E-01,-0.8183E-01,
    -0.7495E+00, 0.8426E+00,-0.2829E+01, 0.1607E+01,
    0.1733E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00,
    0.0000E+00, 0.0000E+00, 0.0000E+00, 0.0000E+00};
  */
  double y,R;

  double P[24] = {
     5.1377e-03,   9.8071e-01,   4.6379e-02,   1.6433e+00,
     6.9826e+00,  -2.2655e-01,   1.1095e-01,   2.7945e-02,
     4.0643e-01,   1.6076e+00,  -7.5460e+00,   4.4418e+00,
     -3.7464e-01,   1.0414e-01,  -2.6852e-01,   9.6653e-01,
     -1.9055e+00,   9.8965e-01,   2.0613e+02,  -4.5536e-02,
     2.4902e-01,  -1.3728e-01,   2.9201e+01,   4.9280e-03};

  // return if proton: future change this to allow for
  // equivalent W resolution
  F1 = 0.;
  F2 = 0.;
  avgN = IA - Z;
  if (IA==1) return;

  // some kinematic factors. Return if Nu or QSQ is negative
  Nu = (wsq - amp*amp + QSQ) / 2. / amp;

  //G4cout << "In call... IA, Nu, QSQ = " << IA << ", " << Nu << ", " << QSQ << G4endl;
  if(Nu <= 0.0 || QSQ < 0.) return;
  TAU   = QSQ / 4.0 / amp / amp;
  QV = sqrt(Nu*Nu + QSQ);

  // Bosted fit for nucleon form factors Phys. Rev. C 51, p. 409 (1995)
  Q = sqrt(QSQ);
  Q3 = QSQ * Q;
  Q4 = QSQ*QSQ;
  GEP = 1./  (1. + 0.14 * Q + 3.01 * QSQ + 0.02 * Q3 + 1.20 * Q4 + 0.32 * pow(Q,5));
  GMP = RMUP * GEP;
  GMN = RMUN / (1.- 1.74 * Q + 9.29 * QSQ - 7.63 * Q3 + 4.63 * Q4);
  GEN = 1.25 * RMUN * TAU / (1. + 18.3 * TAU) / pow((1. + QSQ / 0.71),2);

  //G4cout << "Form Factors: " << GEP << ", " << GMP << ", " << GEN << ", " << GMN << G4endl;

  // Get kf and Es from superscaling from Sick, Donnelly, Maieron,
    // nucl-th/0109032
    if(IA==2) kf=0.085;
    if(IA==2) Es=0.0022;
    // changed 4/09
    if(IA==3) kf=0.115;
    if(IA==3) Es=0.001 ;
    // changed 4/09
    if(IA>3) kf=0.19;
    if(IA>3) Es=0.017;
    if(IA>7) kf=0.228;
    if(IA>7) Es=0.020;
    // changed 5/09
    if(IA>7) Es=0.0165;
    if(IA>16) kf=0.230;
    if(IA>16) Es=0.025;
    if(IA>25) kf=0.236;
    if(IA>25) Es=0.018;
    if(IA>38) kf=0.241;
    if(IA>38) Es=0.028;
    if(IA>55) kf=0.241;
    if(IA>55) Es=0.023;
    if(IA>60) kf=0.245;
    if(IA>60) Es=0.028;
    // changed 5/09 
    if(IA>55) Es=0.018;

  // Pauli suppression model from Tsai RMP 46,816(74) eq.B54
  if ((QV > 2.* kf) || (IA == 1)) {
    Pauli_sup2 =1.0;
  } else {
    Pauli_sup2 = 0.75 * (QV / kf) * (1.0 - (pow((QV / kf),2))/12.);
  }
  Pauli_sup1 = Pauli_sup2;

  //G4cout << "kf, Es, Paulisup1,2: " << kf << ", " << Es << ", " << Pauli_sup1 << ", " << Pauli_sup2 << G4endl;

  // structure functions with off shell factors
  kappa = QV / 2. / amp;
  lam = Nu / 2. / amp;
  lamp = lam - Es / 2. / amp;
  taup = kappa*kappa - lamp*lamp;
  squigglef = sqrt(1. + pow((kf/amp),2)) -1.;

  // Very close to treshold, could have a problem
  if(1.+lamp <= 0.) return;
  if(taup * (1. + taup) <= 0.) return;

  psi =  (lam  - TAU ) / sqrt(squigglef) / sqrt((1.+lam )* TAU + kappa * sqrt(TAU * (1. + TAU)));
  psip = (lamp - taup) / sqrt(squigglef) / sqrt((1.+lamp)*taup + kappa * sqrt(taup * (1. + taup)));
  nuL = pow((TAU / kappa / kappa),2);

  // changed definition of nuT from
  // nuT = TAU / 2. / kappa**2 + tan(thr/2.)**2
  // to this, in order to separate out F1 and F2 (F1 prop. to tan2 term)
  nuT = TAU / 2. / kappa / kappa;

  GM2bar = Pauli_sup1 * (Z * GMP*GMP + avgN * GMN*GMN);
  GE2bar = Pauli_sup2 * (Z * GEP*GEP + avgN * GEN*GEN);
  //double W1bar = TAU * GM2bar;
  W2bar = (GE2bar + TAU * GM2bar) / (1. + TAU);

  Delta = squigglef * (1. - psi*psi) * (sqrt(TAU * (1.+TAU)) / kappa + squigglef/3. *
     (1. - psi*psi) * TAU / kappa / kappa);
  GL = kappa*kappa / TAU * (GE2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef *
     (1. + psi*psi) / 2.);
  GT = (2. * TAU * GM2bar + Delta * W2bar) / 2. / kappa / (1. + squigglef *
     (1. + psi*psi) / 2.);

  //G4cout << "nuL, nuT, GL, GT: " << nuL << ", " << nuT << ", " << GL << ", " << GT << G4endl;

  // added to prevent negative xsections:
  if (GT < 0) {
    GT = 0;
    //G4cout << "Reset GT to zero" << G4endl;
  }

  // from Maria Barbaro: see Amaro et al., PRC71,015501(2005).
  FY = 1.5576 / (1. + 1.7720*1.7720 * pow((psip + 0.3014),2)) / (1. + exp(-2.4291 * psip)) / kf;

  // final results
  F2 = Nu * FY * (nuL * GL + nuT * GT);
  F1 = amp * FY * GT / 2.;

  //G4cout << "nu, Fy, nuL, GL, nuT, GT, amp: " << G4endl;
  //G4cout << Nu << ", " << FY << ", " << nuL << ", " << GL << ", " << nuT << ", " << GT << ", " << amp << G4endl;

  if (F1 < 0.0) F1 = 0.;
  if (Nu > 0. && F1 > 0.) R = (F2 / Nu) / (F1 / amp) * (1. + Nu*Nu / QSQ) - 1.0;
  else R = 0.4/QSQ;


  // apply correction factors
  if ( IA > 2 ) {
    y = (wsq -amp*amp) / QV;
    //         F1 = F1 * (1. + pb(8) + pb(9) * y +
    //     >        pb(10)*y**2 + pb(11)*y**3 + pb(12)*y**4 )
    //         R = R * (1. + pb(13))
    //         F2 = Nu * F1/amp * (1. + R) / (1. + Nu**2/QSQ)

    // correction to correction Vahe
    if (wsq > 0.0) {
      F1=F1*(1.0+P[7]+P[8]*y+P[9]*y*y +P[10]*pow(y,3) +P[11]*pow(y,4));
      R = R * ( 1.0 + P[12] );
      F2 = Nu * F1/amp * (1. + R) / (1. + Nu*Nu/QSQ);
      if (F1 < 0.0) F1=0.0;
    }
  }
}

