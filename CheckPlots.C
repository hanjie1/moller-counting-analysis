//#include "remolltypes.hh"
int CheckExist( int det[], int thisdet, int nsize  ){
     int is_exist=0;
     for(int ii=0; ii<nsize; ii++){
	if(thisdet == det[ii] ) {
	   is_exist=1;
	   break;
	}
     }

     return is_exist;
}


void CheckPlots(){
     TChain *T = new TChain("T");
     T->AddFile("/home/hanjie/moller/remoll/remoll_sievein.root");

     const int ntrk = 2;  // number of tracks that we care about
     const int ndet = 3;
     int valid_det[ndet] = {60, 30, 28};  // detector I want to be fired: sieve: 60, GEM: 30, MainDetector: 28

     vector < remollGenericDetectorHit_t > *fHit = 0;
     vector < remollEventParticle_t > *fPart = 0;
     T->SetBranchAddress("hit", &fHit);
     T->SetBranchAddress("part", &fPart);

     int thistrid=-1, thisdet=-1;
     double thisx=-333, thisy=-333, thisz=-333, thise=-333, thisp=-333, thist=-333, thisr=-333;
     double thispx=-333, thispy=-333, thispz=-333, thispr=-333;
     double thisth_tg=-333, thisph_tg=-333;
     TFile *newfile = new TFile("trackhits.root","RECREATE","hits for valid tracks");
     if(!newfile->IsOpen()) return;  
     TTree *newT = new TTree("T","data");
     newT->Branch("trid", &thistrid, "thistrid/I");
     newT->Branch("det", &thisdet, "thisdet/I");
     newT->Branch("x", &thisx, "thisx/D");
     newT->Branch("y", &thisy, "thisy/D");
     newT->Branch("z", &thisz, "thisz/D");
     newT->Branch("r", &thisr, "thisr/D");
     newT->Branch("e", &thise, "thise/D");   // energy
     newT->Branch("p", &thisp, "thisp/D");   // momentum
     newT->Branch("px", &thispx, "thispx/D");   // momentum x
     newT->Branch("py", &thispy, "thispy/D");   // momentum y
     newT->Branch("pz", &thispz, "thispz/D");   // momentum z
     newT->Branch("pr", &thispr, "thispr/D");   // momentum z
     newT->Branch("t", &thist, "thist/D");   // time
     newT->Branch("th_tg", &thisth_tg, "thisth_tg/D");
     newT->Branch("ph_tg", &thisph_tg, "thisph_tg/D");
  
     Int_t nentries = T->GetEntries();
     for(Int_t ii=0; ii < nentries; ii++){
         T->GetEntry(ii);
         Int_t nhits = fHit->size();

         int fire_det[ntrk][8];    // save the fired detector id for each track id
         for(int kk=0; kk<ntrk; kk++){
	   for(int mm=0; mm<8; mm++){
	      fire_det[kk][mm]=0;
	   }
	 }
	 int nfired[ntrk]={0};   // count how many detectors are fired for each track

         for(Int_t jj=0; jj<nhits; jj++){
           remollGenericDetectorHit_t hit = fHit->at(jj);
           if(hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || hit.trid==2) ){           // two eletrons from the particle gun, for moller events
		int tmpDetID = hit.det;
		int tmptrkid = hit.trid-1;
		int is_exist = CheckExist(fire_det[tmptrkid], tmpDetID, 8);
		if(is_exist==0){
		  int tmpN = nfired[tmptrkid];
		  fire_det[tmptrkid][tmpN]=tmpDetID;       // save the fired detector ID
		  nfired[tmptrkid]=nfired[tmptrkid]+1;
		}
           }
         }

	 int nfound[ntrk]={0};
	 int valid_trk[ntrk]={-1};
	 int total_validtrk=0;
	 for(int nn=0; nn<ntrk; nn++){    // only the two main trk id are considered
	   for(int kk=0; kk<ndet; kk++){
	     for( int mm=0; mm<nfired[nn]; mm++){
		if( fire_det[nn][mm]==valid_det[kk]) nfound[nn]++;
	    }
	   }
	   if( nfound[nn]==ndet ){ valid_trk[nn]=1; total_validtrk++;}
	   else valid_trk[nn]=0;
	 }

	 if(total_validtrk>1) cout<<"There are "<<total_validtrk<<" valid tracks for event "<<ii<<endl;

	 for(Int_t jj=0; jj<nhits; jj++){   // loop all the hits to find the hits that form the valid track
              remollGenericDetectorHit_t hit = fHit->at(jj);
	      int tmptrid = hit.trid-1;
              if(hit.pid==11 && hit.mtrid==0 && valid_trk[tmptrid]==1 ){           // two eletrons from the particle gun, for moller events
		   thistrid = hit.trid;
		   thisdet = hit.det;
		   thisx = hit.x;
		   thisy = hit.y;
	   	   thisz = hit.z;
		   thisr = hit.r;
		   thise = hit.e;
		   thisp = hit.p;
		   thispx = hit.px;
		   thispy = hit.py;
		   thispz = hit.pz;
		   thispr = sqrt(thispx*thispx + thispy*thispy);
		   thist = hit.t;

		   remollEventParticle_t part = fPart->at(tmptrid);
		   if(part.trid==thistrid){
	              thisth_tg = part.th;
		      thisph_tg = part.ph;
		   }
		   else{
	              cout<<"Somehting wrong with the particles trid "<<part.trid<<"  "<<thistrid<<"  "<<ii<<endl;

		   }

		   newT->Fill();
	      }
	 }
     }

     newT->Write(); 
     newfile->Close();
	

}
