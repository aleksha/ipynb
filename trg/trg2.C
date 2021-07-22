#include <iostream>
#include <fstream>

using namespace std;
#include "TAxis.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGaxis.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLatex.h"
#include "TMath.h"
#include "TPad.h"
#include "TRandom.h"
#include "TRandom2.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TTree.h"
#include "TVector3.h"

//==============================================================================
double T_P_VALS[5] = { 0, 0.5, 2.,5.,10.};
double E        = 100.;
int STAT        = 2500;
bool  USE_CORE = true;
double Zin1     = -6000.;
double Zin2     = -1000.;
double Zout     =  2000.;
double Lfib     = 1.;

double m_l = 0.105658;
double m_p = 0.938272;

double calc_theta( double TR ){
    return 2.*asin(sqrt( (TR*0.001)*m_p/(2.*E*E)));
}

TVector3 calc_plane( TVector3 s, TVector3 p, double Z){
    return TVector3( s.X()+((Z-s.Z())/p.Z())*p.X(), s.Y()+((Z-s.Z())/p.Z())*p.Y(), Z );
}
//==============================================================================
void trg2(){

  TFile* rfile = new TFile("./output_cedar_mu100_parallel.root", "READ");
  rfile->ls();
  TTree* tree;
  tree = (TTree*)rfile->Get("BeamFile");
  tree->Print();
  cout << "Done!\n" ;

  int particleFlag;  tree->SetBranchAddress( "particleFlag", &particleFlag );
  double X   ;  tree->SetBranchAddress( "X"   , &X    );
  double Y   ;  tree->SetBranchAddress( "Y"   , &Y    );
  double Z   ;  tree->SetBranchAddress( "Z"   , &Z    );
  double dXdZ;  tree->SetBranchAddress( "dXdZ", &dXdZ );
  double dYdZ;  tree->SetBranchAddress( "dYdZ", &dYdZ );


  TFile* ffile = new TFile("./output_cedar_mu100_focused.root", "READ");
  ffile->ls();
  TTree* free;
  free = (TTree*)ffile->Get("BeamFile");
  free->Print();
  cout << "Done!\n" ;

  int fparticleFlag;  free->SetBranchAddress( "fparticleFlag", &fparticleFlag );
  double fX   ;  free->SetBranchAddress( "X"   , &fX    );
  double fY   ;  free->SetBranchAddress( "Y"   , &fY    );
  double fZ   ;  free->SetBranchAddress( "Z"   , &fZ    );
  double fdXdZ;  free->SetBranchAddress( "dXdZ", &fdXdZ );
  double fdYdZ;  free->SetBranchAddress( "dYdZ", &fdYdZ );

  int length = tree->GetEntries();
  cout << "Tree length : " << length << "\n";
  double pFactor = 2000000. / length;

  int fength = free->GetEntries();
  cout << "Free length : " << fength << "\n";
  double fFactor = 2000000. / fength;

  TH2F *hXYf = new TH2F("hXYf" ,";;",200,-100,100,200,-100,100);
  TH2F *hXYp = new TH2F("hXYp" ,";;",200,-100,100,200,-100,100);

  hXYf->SetStats(0);
  hXYp->SetStats(0);

  double vR[14],fRate[14],pRate[14];


  for(int r=0;r<14;r++){

    vR[r] = 0.5+r*0.5;


    pRate[r]=0.;
    for(int tev=0;tev<tree->GetEntries();tev++){
      tree->GetEntry( tev );
      if( (X*X+Y*Y)<vR[r]*vR[r] ) pRate[r] = pRate[r]+1.;
    }
    pRate[r] = pRate[r]*pFactor*0.001;

    fRate[r]=0.;
    for(int tev=0;tev<free->GetEntries();tev++){
      free->GetEntry( tev );
      if( (fX*fX+fY*fY)<vR[r]*vR[r] ) fRate[r] = fRate[r]+1.;
    }
    fRate[r] = fRate[r]*fFactor*0.001;


    cout << "  " << vR[r] << "\t" << fRate[r] << "\t" << pRate[r] << "\n";

  }

  TGraph* gf = new TGraph(14,vR,fRate);
  TGraph* gp = new TGraph(14,vR,pRate);

  gf->SetLineColor(2);
  gp->SetLineColor(4);

  gf->SetLineWidth(3);
  gp->SetLineWidth(3);

  gf->SetMinimum(0);

  gf->SetTitle("");

  gf->GetXaxis()->SetTitle("R, mm");
  gf->GetYaxis()->SetTitle("Rate, kHz");


  TCanvas* canv1 = new TCanvas("canv1","canv1",800,800);
  gf->Draw("AC");
  gp->Draw("C same");
  canv1->Print("Rate.png");
  canv1->Close();

  gSystem->Exit(1);

}




















