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
void trg(){

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


  for(int tev=0;tev<tree->GetEntries();tev++){
    tree->GetEntry( tev );
    hXYp->Fill(X,Y);
  }

  for(int tev=0;tev<tree->GetEntries();tev++){
    free->GetEntry( tev );
    hXYf->Fill(fX,fY);
  }


  hXYf->GetZaxis()->SetRangeUser(0,1100);
  hXYp->GetZaxis()->SetRangeUser(0,1100);

  TCanvas* canv1 = new TCanvas("canv1","canv1",1000,700);
  hXYp->Draw("colz");
  canv1->Print("XYp.png");
  canv1->Close();

  TCanvas* canv2 = new TCanvas("canv2","canv2",1000,700);
  hXYf->Draw("colz");
  canv2->Print("XYf.png");
  canv2->Close();

  gSystem->Exit(1);

}




















