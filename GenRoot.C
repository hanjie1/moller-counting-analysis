#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <TApplication.h>
#include <TRint.h>
#include <TSystem.h>

#include <TStyle.h>
#include <TPaveStats.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFrame.h>
#include <TObjArray.h>
#include <TVector2.h>
#include <TLatex.h>

#include <TFile.h>
#include <TChain.h>
#include <TH2F.h>
#include <TH2D.h>

#include "TTree.h"

#include "remolltypes.hh"
#include "GenRoottypes.h"

using namespace std;

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

bool comparetrid(detHit h1, detHit h2) 
{ 
    return (h1.trid < h2.trid); 
} 

int main(int argc, char** argv){

     if(argc<2){
	printf("Doesn't have the root file name!\n");
	return 0;
     }

     string filename=argv[1];

     string rootfile=filename;
     size_t sfound=rootfile.find("/");
     if(sfound!=string::npos)
	rootfile.replace(0,sfound+1,"");
      

     int ismoller=0;   // (1=yes, 0=no)
     ismoller=atoi(argv[2]);

     TChain *T = new TChain("T");
     T->AddFile(Form("/home/hanjie/moller/remoll/Rootfiles/%s.root",filename.c_str()));

     const int ndet = 3;
     int valid_det[ndet] = {600, 30, 28};  // detector I want to be fired: sieve: 600, GEM: 30, MainDetector: 28

     vector < remollGenericDetectorHit_t > *fHit = 0;
     vector < remollEventParticle_t > *fPart = 0;
     remollEvent_t *fev=0;
     double fRate;
     T->SetBranchAddress("hit", &fHit);
     T->SetBranchAddress("part", &fPart);
     T->SetBranchAddress("rate", &fRate);
     T->SetBranchAddress("ev", &fev);

     vector<detHit> sieve;
     vector<detHit> ring;
     vector<detHit> gem_f1;  // tracking detecotr front 1 plane
     vector<detHit> gem_f2;  // tracking detecotr front 2 plane
     vector<detHit> gem_b1;  // tracking detecotr back 1 plane
     vector<detHit> gem_b2;  // tracking detecotr back 2 plane
     vector<tgPart> target;
     event thisev;
     int ntrack;
     double rate;

     TFile *newfile = new TFile(Form("/home/hanjie/moller/optics_analysis/Rootfiles/new_fieldmap_new_sieve/trackhits_%s.root",rootfile.c_str()),"RECREATE","hits for valid tracks");
     if(!newfile->IsOpen()) return 0;  
     TTree *newT = new TTree("T","data");
     newT->Branch("sieve", &sieve);
     newT->Branch("ring", &ring);
     newT->Branch("gem_f1", &gem_f1);
     newT->Branch("gem_f2", &gem_f2);
     newT->Branch("gem_b1", &gem_b1);
     newT->Branch("gem_b2", &gem_b2);
     newT->Branch("tg", &target);
     newT->Branch("ev", &thisev);
     newT->Branch("ntrk", &ntrack,"ntrack/I");
     newT->Branch("rate", &rate,"rate/D");
  
     Int_t nentries = T->GetEntries();
     for(Int_t ii=0; ii < nentries; ii++){
         T->GetEntry(ii);
         Int_t nhits = fHit->size();

	 sieve.clear();
	 ring.clear();
	 gem_f1.clear();
	 gem_f2.clear();
	 gem_b1.clear();
	 gem_b2.clear();
	 target.clear();
	 thisev.xs=0;
	 thisev.W2=0;
	 thisev.Q2=0;

	 ntrack=0;
 
        const int ntrk=ismoller+1;      // number of tracks that we care about

	if(fPart->size()!=ntrk){
	   cout<<"Warning: the number of tracks is smaller than the avaliable tracks"<<endl;
	}

         int fire_det[ntrk][8];    // save the fired detector id for each track id
         for(int kk=0; kk<ntrk; kk++){
	   for(int mm=0; mm<8; mm++){
	      fire_det[kk][mm]=0;
	   }
	 }
	 int nfired[ntrk]={0};   // count how many detectors are fired for each track

         for(Int_t jj=0; jj<nhits; jj++){
           remollGenericDetectorHit_t hit = fHit->at(jj);
           if(hit.pid==11 && hit.mtrid==0 && (hit.trid==1 || (hit.trid==2 && ismoller==1)) ){           // two eletrons from the particle gun, for moller events
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

	 //if(total_validtrk>1) cout<<"There are "<<total_validtrk<<" valid tracks for event "<<ii<<endl;

	 if(total_validtrk==0) continue;

	 ntrack = total_validtrk;
	 rate = fRate;
 
 	 thisev.xs=fev->xs;
 	 thisev.Q2=fev->Q2;
 	 thisev.W2=fev->W2;

	 for(int hh =0; hh<ntrk; hh++){
		remollEventParticle_t  part = fPart->at(hh);	     
		if(valid_trk[hh]==1){
		    tgPart apart;
		    apart.trid = part.trid;
		    if(apart.trid != (hh+1)) cout<<"It's weird here"<<endl;
		    apart.th = part.th;
		    apart.ph = part.ph;
		    apart.vz = part.vz;
		    apart.p = part.p;
	 	    target.push_back(apart);
		}
	 }

       


	 int nsieve=0, nring=0, ngem=0;
	 for(Int_t jj=0; jj<nhits; jj++){   // loop all the hits to find the hits that form the valid track
              remollGenericDetectorHit_t hit = fHit->at(jj);

	      int tmptrid = hit.trid-1;
              if(hit.pid==11 && hit.mtrid==0 && valid_trk[tmptrid]==1 ){           // two eletrons from the particle gun, for moller events
		 detHit ahit;
		 ahit.trid = hit.trid;
		 ahit.x = hit.x;
		 ahit.y = hit.y;
	   	 ahit.z = hit.z;
		 ahit.r = hit.r;
		 ahit.e = hit.e;
		 ahit.p = hit.p;
		 ahit.px = hit.px;
		 ahit.py = hit.py;
		 ahit.pz = hit.pz;
		 ahit.t = hit.t;

		 int detid = hit.det;
		 if(detid==28){ ring.push_back(ahit); nring++;}
		 if(detid==600){ sieve.push_back(ahit); nsieve++;}
		 if(detid==30){
		    if(ahit.z==19279.5) gem_f1.push_back(ahit);
		    if(ahit.z==19779.5) gem_f2.push_back(ahit);
		    if(ahit.z==20193.5) gem_b1.push_back(ahit);
		    if(ahit.z==20693.5) gem_b2.push_back(ahit);
		    ngem++;
		 }
	      }
	 }

	if(ntrack>1){
 	  sort(sieve.begin(), sieve.end(), comparetrid);
	  sort(ring.begin(), ring.end(), comparetrid);
	  sort(gem_f1.begin(), gem_f1.end(), comparetrid);
	  sort(gem_f2.begin(), gem_f2.end(), comparetrid);
	  sort(gem_b1.begin(), gem_b1.end(), comparetrid);
	  sort(gem_b2.begin(), gem_b2.end(), comparetrid);
	}

	if(nsieve>ntrack || nring>ntrack || ngem>(4*ntrack))
	  printf("Event %d has multiple hits than expected (nsieve, nring, ngem): %d, %d, %d\n",ii, nsieve, nring, ngem);

	newT->Fill();
     }

     newT->Write(); 
     newfile->Close();
	

}
