struct newHit{    // hits 
   int trid;
   int det;
   double x, y, z;
   double px, py, pz;
   double pr;
   double e, p;
   double t;
   double r;
};

struct newPart{   // particle at the target
   int trid;
   double th;
   double ph;
   double vz;
};

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
   int trid;
};
