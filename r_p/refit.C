#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGaxis.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TMath.h"
#include "TSystem.h"
#include "TStyle.h"

#include "XS.hh"

void refit(){

 gStyle->SetOptFit(1111);

 fXS->FixParameter( 0, 0.72 );
 fXS->SetParLimits( 1, 0, 2.0 );
 fXS->SetParameter( 1, 0.86 );
 fXS->SetParameter( 2, 1.00 );

 fXS->SetParName( 0, "E" );
 fXS->SetParName( 1, "r_{p}" );
 fXS->SetParName( 2, "scale" );

 fXS->SetTitle(" ");

 double y_scale = 1./fXS->Eval(0.001);

 fXS->SetParameter( 2, y_scale );

 TCanvas *canv = new TCanvas("canv","fig1",900,600);
 canv->SetLogy();
 fXS->Draw();
 canv->Print("Fig1_func.png");

// TRandom2 *rx = new TRandom2( 71258 );
// TRandom2 *ry = new TRandom2( 71258 );

 TH1F *h = new TH1F("toy data",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

// for(int i=0;i<7000000;i++){
 for(int i=0;i<7000000;i++){
   h->Fill( fXS->GetRandom() );
 }

 fXS->SetParameter( 2, 550 );
 h->Fit("fXS");
// fXS->FixParameter( 2 , fXS->GetParameter(2) );
// h->Fit("fXS");
 h->Draw();
 canv->Print("Fig1_hist.png");

 TH1F *ht = new TH1F("toy fit",";r_{p}, fm; Entiries",1000,0.8,0.9);
 for(int toy=0;toy<1000;toy++){
  h->Reset();
  fXS->SetParameter( 1, 0.86 );
  fXS->SetParameter( 2, y_scale );
  for(int i=0;i<7000000;i++){
   h->Fill( fXS->GetRandom() );
  }

  fXS->SetParameter( 2, 550 );
  h->Fit("fXS","Q");
  ht->Fill( fXS->GetParameter(1) );
 }

 canv->SetLogy(0);
 ht->Draw();
 canv->Print("Fig1_bias.png");

 gSystem->Exit(1);

}
