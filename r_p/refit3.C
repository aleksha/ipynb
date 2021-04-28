#include <iostream>

using namespace std;
#include "TAxis.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TGraph.h"
#include "TGaxis.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TMath.h"
#include "TRandom2.h"
#include "TSystem.h"
#include "TStyle.h"

#include "XS.hh"

void refit3( int EVENTS = 70000000, int TOYS = 0 ){

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

 TRandom2 *rx = new TRandom2( 71258 );
 TRandom2 *ry = new TRandom2( 34785 );
 double x,y;

 TH1F *h  = new TH1F("toy data",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 TH1F *h1 = new TH1F("shift(1)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h2 = new TH1F("shift(2)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h3 = new TH1F("shift(3)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h4 = new TH1F("shift(4)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 TH1F *h5 = new TH1F("shift(5)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h6 = new TH1F("shift(6)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h7 = new TH1F("shift(7)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h8 = new TH1F("shift(8)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);



 for(int i=0;i<EVENTS;i++){
   do{ x = 0.0009 + rx->Rndm()*0.04; y = ry->Rndm(); } while( y>fXS->Eval(x));
   h->Fill( x );
   h1->Fill( x - 0.000001*(x-0.001)/0.039);
   h2->Fill( x - 0.000002*(x-0.001)/0.039);
   h3->Fill( x - 0.000003*(x-0.001)/0.039);
   h4->Fill( x - 0.000004*(x-0.001)/0.039);
   h5->Fill( x + 0.000001*(x-0.001)/0.039);
   h6->Fill( x + 0.000002*(x-0.001)/0.039);
   h7->Fill( x + 0.000003*(x-0.001)/0.039);
   h8->Fill( x + 0.000004*(x-0.001)/0.039);
 }

 fXS->SetParameter( 2, 550 );
 h->Fit("fXS");
 h->Draw();
 canv->Print("Fig1_hist.png");

 h1->Fit("fXS");
 h1->Draw();
 canv->Print("Fig1_Slow.png");

 h2->Fit("fXS");
 h3->Fit("fXS");
 h4->Fit("fXS");
 h5->Fit("fXS");
 h6->Fit("fXS");
 h7->Fit("fXS");
 h8->Fit("fXS");


 TH1F *ht = new TH1F("toy fit",";r_{p}, fm; Entiries",1000,0.8,0.9);
 for(int toy=0;toy<TOYS;toy++){
  h->Reset();
  fXS->SetParameter( 1, 0.86 );
  fXS->SetParameter( 2, y_scale );
  for(int i=0;i<EVENTS;i++){
   do{ x = 0.001 + rx->Rndm()*0.039; y = ry->Rndm(); } while( y>fXS->Eval(x));
   h->Fill( x );
  }

  fXS->SetParameter( 2, 550 );
  h->Fit("fXS","Q");
  ht->Fill( fXS->GetParameter(1) );
  cout << "toy: " << toy+1 << "\t" << ht->GetMean() << "\n";
 }

 canv->SetLogy(0);
 ht->Draw();
 canv->Print("Fig1_bias.png");

 gSystem->Exit(1);

}
