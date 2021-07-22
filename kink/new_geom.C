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
void new_geom(){

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

  bool firedX1[3];
  bool firedY1[3];
  bool firedX2[3];
  bool firedY2[3];
  bool firedX[3];
  bool firedY[3];

  int t_ini[4]={0,0,0,0};
  int t_out[4]={0,0,0,0};

  TH1F *hX1 = new TH1F("hX1",";;",2000,-100,100);
  TH1F *hX2 = new TH1F("hX2",";;",2000,-100,100);
  TH1F *hY1 = new TH1F("hY1",";;",2000,-100,100);
  TH1F *hY2 = new TH1F("hY2",";;",2000,-100,100);

  TH2F *hXY1 = new TH2F("hXY1",";;",20,-10,10,20,-10,10);
  TH2F *hXY2 = new TH2F("hXY2",";;",20,-10,10,20,-10,10);
  TH2F *hXY  = new TH2F("hXY" ,";;",21,-10.5,10.5,21,-10.5,10.5);

  hXY1->SetStats(0);
  hXY2->SetStats(0);
  hXY->SetStats(0);

  for(int tev=0;tev<tree->GetEntries();tev++){
//    if( !(tev%10000) ) cout << tev << "\t\t"<< t_ini[0] << "  " << t_out[0] << "\n";

    for(int s=0;s<3;s++){
      firedX1[s] = false; firedX2[s] = false; firedX[s] = false;
      firedY1[s] = false; firedY2[s] = false; firedY[s] = false;
    }

    tree->GetEntry( tev );

    ent++;
    e[0]=13; e[1]=X; e[2]=Y; e[3]=Z; e[4]=dXdZ*0.001; e[5]=dYdZ*0.001; e[6]=100.; 

    Z_scat = -400.+800.*gRandom->Rndm();
    dZ = Z_scat - e[3];
    X_scat = e[1] + dZ*sin(e[4]);
    Y_scat = e[2] + dZ*sin(e[5]);
    sca.SetXYZ(  X_scat, Y_scat, Z_scat );

//    idx_Tp = gRandom->Integer( 5 );

    Tp = 0;

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

//    cout << "( " << XY1.X() <<" , " << XY1.Y() << " )\t";
//    cout << "( " << XY2.X() <<" , " << XY2.Y() << " )\n";

    hX1->Fill(XY1.X());
    hY1->Fill(XY1.Y());
    hX2->Fill(XY2.X());
    hY2->Fill(XY2.Y());

    if(XY1.X()>-1 && XY1.X()<0 && XY1.Y()>0 && XY1.Y()<1){
      hXY1->Fill( XY1.X(), XY1.Y() );
      if(XY2.X()>-1 && XY2.X()<0 && XY2.Y()>0 && XY2.Y()<1){
        hXY2->Fill( XY2.X(), XY2.Y() );
        hXY ->Fill( XY.X() , XY.Y() );
      }
    }
/*
    if(XY1.X()>0 && XY1.X()<1 && XY1.Y()>-1 && XY1.Y()<0){
      hXY1->Fill( XY1.X(), XY1.Y() );
      if(XY2.X()>0 && XY2.X()<1 && XY2.Y()>-1 && XY2.Y()<0){
        hXY2->Fill( XY2.X(), XY2.Y() );
        hXY ->Fill( XY.X() , XY.Y() );
      }
    }

    if(XY1.X()>0 && XY1.X()<1 && XY1.Y()>0 && XY1.Y()<1){
      hXY1->Fill( XY1.X(), XY1.Y() );
      if(XY2.X()>0 && XY2.X()<1 && XY2.Y()>0 && XY2.Y()<1){
        hXY2->Fill( XY2.X(), XY2.Y() );
        hXY ->Fill( XY.X() , XY.Y() );
      }
    }

    if(XY1.X()>-1 && XY1.X()<0 && XY1.Y()>-1 && XY1.Y()<0){
      hXY1->Fill( XY1.X(), XY1.Y() );
      if(XY2.X()>-1 && XY2.X()<0 && XY2.Y()>-1 && XY2.Y()<0){
        hXY2->Fill( XY2.X(), XY2.Y() );
        hXY ->Fill( XY.X() , XY.Y() );
      }
    }
*/
    if(XY1.X()>-Lfib && XY1.X()<0   ) firedX1[0]=true;
    if(XY1.X()>0     && XY1.X()<Lfib) firedX1[1]=true;
    if(XY1.Y()>-Lfib && XY1.Y()<0   ) firedY1[0]=true;
    if(XY1.Y()>0     && XY1.Y()<Lfib) firedY1[1]=true;

    if(XY2.X()>-Lfib && XY2.X()<0   ) firedX1[0]=true;
    if(XY2.X()>0     && XY2.X()<Lfib) firedX1[1]=true;
    if(XY2.Y()>-Lfib && XY2.Y()<0   ) firedY1[0]=true;
    if(XY2.Y()>0     && XY2.Y()<Lfib) firedY1[1]=true;

    if(XY.X()>-Lfib*1.5 && XY.X()<-Lfib*0.5) firedX[0]=true;
    if(XY.X()>-Lfib*0.5 && XY.X()< Lfib*0.5) firedX[1]=true;
    if(XY.X()> Lfib*0.5 && XY.X()< Lfib*1.5) firedX[2]=true;
    if(XY.Y()>-Lfib*1.5 && XY.Y()<-Lfib*0.5) firedY[0]=true;
    if(XY.Y()>-Lfib*0.5 && XY.Y()< Lfib*0.5) firedY[1]=true;
    if(XY.Y()> Lfib*0.5 && XY.Y()< Lfib*1.5) firedY[2]=true;

    if(firedX1[0] && firedY1[0] && firedX2[0] && firedY2[0]){
      t_ini[0]++;
      if( !firedX[0] && !firedX[1] && !firedY[0] && !firedY[1]) t_out[0]++;
    }

    if(firedX1[1] && firedY1[0] && firedX2[1] && firedY2[0]){
      t_ini[1]++;
    }

    if(firedX1[0] && firedY1[1] && firedX2[0] && firedY2[1]){
      t_ini[2]++;
    }

    if(firedX1[1] && firedY1[1] && firedX2[1] && firedY2[1]){
      t_ini[3]++;
    }


  }
//  for(int i=0;i<5;i++) cout << T_P_VALS[i] << "  " << trgs_i[i] << " " << trgs_o[i] << "\n";

  for(int s=0;s<4;s++) cout << "0: "<< t_ini[s] << "  " << t_out[s] << "\n";

  TCanvas* canv = new TCanvas("canv","canv",800,800);
  canv->Divide(2,2);
  canv->cd(1);
  hX1->Draw("hist");
  canv->cd(2);
  hX2->Draw("hist");
  canv->cd(3);
  hY1->Draw("hist");
  canv->cd(4);
  hY2->Draw("hist");
  canv->Print("XY.png");
  canv->Close();

  TCanvas* canv1 = new TCanvas("canv1","canv1",800,800);
  hXY1->Draw("colz");
  canv1->Print("XY1.png");
  canv1->Close();

  TCanvas* canv2 = new TCanvas("canv2","canv2",800,800);
  hXY2->Draw("colz");
  canv2->Print("XY2.png");
  canv2->Close();

  TCanvas* canv3 = new TCanvas("canv3","canv3",800,800);
  hXY->Draw("colz");
  canv3->Print("XY3.png");
  canv3->Close();


  cout << hXY1->GetEntries() << "\n";
  cout << hXY2->GetEntries() << "\n";
  cout << hXY->GetEntries() << "\n";


  gSystem->Exit(1);

}




















