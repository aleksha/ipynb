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
double Zin1     = -3000.;
double Zin2     = -1000.;
double Zout     = 5000.;
double Lfib     = 2.;
double Rsci     = 1.5;

double m_l = 0.105658;
double m_p = 0.938272;

double calc_theta( double TR ){
    return 2.*asin(sqrt( (TR*0.001)*m_p/(2.*E*E)));
}

TVector3 calc_plane( TVector3 s, TVector3 p, double Z){
    return TVector3( s.X()+((Z-s.Z())/p.Z())*p.X(), s.Y()+((Z-s.Z())/p.Z())*p.Y(), Z );
}
//==============================================================================
void fibre(){

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

  int ent = 0 ;
  TVector3 sca , lit , lpt, lepton ;

  int trg_in = 0;
  int trg    = 0;
  int trgs_i[5] = {0,0,0,0,0};
  int trgs_o[5] = {0,0,0,0,0};

  int length = tree->GetEntries();
  cout << "Tree length : " << length << "\n";

  double e[7];
  double X_scat, Y_scat, Z_scat, dZ;
  int idx_Tp; double Tp, theta_l, phi_l, l_p;

  double pi = TMath::Pi();
  TVector3  direction, XY, XY1, XY2;


  while( trg_in < STAT ){

    tree->GetEntry( gRandom->Integer(length) );
    if( USE_CORE ){
      while( particleFlag !=2 ){
            tree->GetEntry( gRandom->Integer(length) );
      }
    }

    ent++;
    e[0]=13; e[1]=X; e[2]=Y; e[3]=Z; e[4]=dXdZ*0.001; e[5]=dYdZ*0.001; e[6]=100.; 

    Z_scat = -400.+800.*gRandom->Rndm();
    dZ = Z_scat - e[3];
    X_scat = e[1] + dZ*sin(e[4]);
    Y_scat = e[2] + dZ*sin(e[5]);
    sca.SetXYZ(  X_scat, Y_scat, Z_scat );

    idx_Tp = gRandom->Integer( 5 );

    Tp = T_P_VALS[ idx_Tp ];
    theta_l = calc_theta( Tp );
    phi_l   = pi*( 2.*gRandom->Rndm() - 1. );

    lit.SetXYZ( -100.*e[4], -100.*e[5], -100 );
    direction.SetXYZ(e[4],e[5], cos( asin( sqrt( pow(e[4],2) + pow(e[5],2) ) ) ) );
    direction = direction.Unit() ;

    l_p = sqrt( E*E - m_l*m_l );
    lepton.SetMagThetaPhi( l_p, theta_l, phi_l );
    lepton.RotateUz( direction );
    lpt = l_p*lepton.Unit();

    XY  =  calc_plane( sca, lpt, Zout);
    XY1 =  calc_plane( sca, lit, Zin1);
    XY2 =  calc_plane( sca, lit, Zin2);


    if( fabs(XY1.X())<Lfib/2. && fabs(XY1.Y())<Lfib/2. ){
      if( fabs(XY2.X())<Lfib/2. && fabs(XY2.Y())<Lfib/2. ){
        trg_in++;
        trgs_i[idx_Tp]++;
        if(trg_in>0 ) cout << trg_in << "\t" << ent << "\t" << 100.*float(trg_in)/float(ent) << "\t\t" << 2000000.*float(trg_in)/float(ent) << " +- " << 2000000.*sqrt(float(trg_in))/float(ent) << endl;
        if( !( fabs(XY.X())<Lfib*1.5 && fabs(XY.Y())<Lfib*1.5)  ){
          trg++;
          trgs_o[idx_Tp]++;
        }
      }
    }
  }
/*
    if( pow(XY1.X(),2) + pow(XY1.Y(),2) < pow(Rsci,2) ){
      if( pow(XY2.X(),2) + pow(XY2.Y(),2) < pow(Rsci,2) ){
        trg_in++;
        trgs_i[idx_Tp]++;
        if(trg_in>0 ) cout << trg_in << "\t" << ent << "\t" << 100.*float(trg_in)/float(ent) << "\t\t"
           << 2000000.*float(trg_in)/float(ent) << " +- " << 2000000.*sqrt(float(trg_in))/float(ent) << endl;
        if( !( pow(XY.X(),2) + pow(XY.Y(),2) < pow(Rsci,2) ) ){
          trg++;
          trgs_o[idx_Tp]++;
        }
      }
    }
  }
*/
  for(int i=0;i<5;i++) cout << T_P_VALS[i] << "  " << trgs_i[i] << " " << trgs_o[i] << "\n";

  gSystem->Exit(1);

}




















