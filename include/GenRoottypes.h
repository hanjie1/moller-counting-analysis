struct detHit{         // hits at the each detector
   double x, y, z;
   double px, py, pz;
   double e, p;
   double r;
   double t;
   int trid;
};

struct tgPart{         // particles at the target from the particle gun
   double th;
   double ph;
   double vz;
   double p;
   int trid;
};

struct event{         // event physics information
   double xs;
   double Q2;
   double W2;
   double beamp;
};
