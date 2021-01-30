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
#include "TFile.h"
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

int main(){
     TChain *T = new TChain("T");
     T->AddFile("/home/hanjie/moller/remoll/remoll_sievein.root");

     const int ndet = 3;
     int valid_det[ndet] = {60, 30, 28};  // detector I want to be fired: sieve: 60, GEM: 30, MainDetector: 28

     vector < remollGenericDetectorHit_t > *fHit = 0;
     vector < remollEventParticle_t > *fPart = 0;
     T->SetBranchAddress("hit", &fHit);
     T->SetBranchAddress("part", &fPart);

     vector <newHit> thishit;
     vector <newPart> thispart;

     TFile *newfile = new TFile("trackhits.root","RECREATE","hits for valid tracks");
     if(!newfile->IsOpen()) return 0;  
     TTree *newT = new TTree("T","data");
     newT->Branch("hit", &thishit);
     newT->Branch("part", &thispart);
  
     Int_t nentries = T->GetEntries();
     for(Int_t ii=0; ii < nentries; ii++){
         T->GetEntry(ii);
         Int_t nhits = fHit->size();

	 thishit.clear();
	 thispart.clear();
 
         const int ntrk = 2;      // number of tracks that we care about
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

	 for(int hh =0; hh<ntrk; hh++){
		remollEventParticle_t  part = fPart->at(hh);	     
		if(valid_trk[hh]==1){
		    newPart apart;
		    apart.trid = part.trid;
		    apart.th = part.th;
		    apart.ph = part.ph;
		    apart.vz = part.vz;
	 	    thispart.push_back(apart);
		}
	 }

	 for(Int_t jj=0; jj<nhits; jj++){   // loop all the hits to find the hits that form the valid track
              remollGenericDetectorHit_t hit = fHit->at(jj);

	      newHit ahit;
	      newPart apart;

	      int tmptrid = hit.trid-1;
              if(hit.pid==11 && hit.mtrid==0 && valid_trk[tmptrid]==1 ){           // two eletrons from the particle gun, for moller events
		   ahit.trid = hit.trid;
		   ahit.det = hit.det;
		   ahit.x = hit.x;
		   ahit.y = hit.y;
	   	   ahit.z = hit.z;
		   ahit.r = hit.r;
		   ahit.e = hit.e;
		   ahit.p = hit.p;
		   ahit.px = hit.px;
		   ahit.py = hit.py;
		   ahit.pz = hit.pz;
		   ahit.pr = sqrt(ahit.px*ahit.px + ahit.py*ahit.py);
		   ahit.t = hit.t;
		   thishit.push_back(ahit);
	      }
	 }

	newT->Fill();
     }

     newT->Write(); 
     newfile->Close();
	

}
