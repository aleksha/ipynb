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
#include "TPad.h"
#include "TRandom2.h"
#include "TSystem.h"
#include "TStyle.h"

#include "XS.hh"

void refit2a( int EVENTS = 70000000, int TOYS = 0 ){

 gStyle->SetOptFit(1111);

 fXS->FixParameter( 0, 0.72 );
 fXS->SetParLimits( 1, 0, 2.0 );
 fXS->SetParameter( 1, 0.86 );
 fXS->SetParameter( 2, 1.00 );
 fXS->SetParName( 0, "E" );
 fXS->SetParName( 1, "r_{p}" );
 fXS->SetParName( 2, "scale" );
 fXS->SetTitle(" ");
 double y_scale = 1./fXS->Eval(0.0009);
 fXS->SetParameter( 2, y_scale );




 fXSg->FixParameter( 0, 0.72 );
 fXSg->SetParLimits( 1, 0, 2.0 );
 fXSg->SetParameter( 1, 0.86 );
 fXSg->SetParameter( 2, 1.00 );
 fXSg->SetParName( 0, "E" );
 fXSg->SetParName( 1, "r_{p}" );
 fXSg->SetParName( 2, "scale" );
 fXSg->SetTitle(" ");
 double yg_scale = 1./fXSg->Eval(0.0009);
 fXSg->SetParameter( 2, yg_scale );



 TCanvas *canv = new TCanvas("canv","fig1",900,600);
 canv->SetLogy();
 fXS->Draw();
 canv->Print("Fig1_func.png");

 TRandom2 *rx = new TRandom2( 71258 );
 TRandom2 *ry = new TRandom2( 34785 );
 double x,y;

 TH1F *h  = new TH1F("toy data"  ,";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *hp = new TH1F("pull hist.",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 TH1F *h1 = new TH1F("shift(1)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h2 = new TH1F("shift(2)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h3 = new TH1F("shift(3)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h4 = new TH1F("shift(4)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 TH1F *h5 = new TH1F("shift(5)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h6 = new TH1F("shift(6)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h7 = new TH1F("shift(7)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);
 TH1F *h8 = new TH1F("shift(8)",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 TH1F *h8p= new TH1F("pull hist8",";Q^{2}, GeV^{2}; Entiries",1000,0.001,0.04);

 int counts = 0;
 int TODO = int( EVENTS*(7000./6315.) );
 for(int i=0;i<TODO;i++){
   do{ x = 0.0009 + rx->Rndm()*0.05; y = ry->Rndm(); } while( y>fXSg->Eval(x));
   if( x >0.001 && x<0.04 ) counts++;
   if( x >0.001 && x<0.04 ) h->Fill( x );
   h1->Fill( x - 0.000001);
   h2->Fill( x - 0.000002);
   h3->Fill( x - 0.000003);
   h4->Fill( x - 0.000004);
   h5->Fill( x + 0.000001);
   h6->Fill( x + 0.000002);
   h7->Fill( x + 0.000003);
   h8->Fill( x + 0.000004);
 }


 fXS->SetParameter( 2, 550 );
 h->Fit("fXS","R");
 h->Draw();
 gPad->SetLogy();
 canv->Print("Fig1_hist.png");

 double vQ2;
 vQ2 = 0.001 - ( (0.04 -0.001)/1000. )*0.5;
 for(int b=1;b<1001;b++){
  vQ2 = vQ2  + ( (0.04 -0.001)/1000. );
  hp->SetBinContent( b, (h->GetBinContent(b) - fXS->Eval(vQ2)) / sqrt(h->GetBinContent(b)) );
 }

 hp->Draw("hist");
 gPad->SetLogy(0);
 canv->Print("Fig1_pull.png");

// fXS->FixParameter( 2 ,  fXS->GetParameter(2) );


 h4->Fit("fXS","R");
 h3->Fit("fXS","R");
 h2->Fit("fXS","R");
 h1->Fit("fXS","R");
 h5->Fit("fXS","R");
 h6->Fit("fXS","R");
 h7->Fit("fXS","R");
 h8->Fit("fXS","R");

 vQ2 = 0.001 - ( (0.04 -0.001)/1000. )*0.5;
 for(int b=1;b<1001;b++){
  vQ2 = vQ2  + ( (0.04 -0.001)/1000. );
  h8p->SetBinContent( b, (h8->GetBinContent(b) - fXS->Eval(vQ2)) / sqrt(h8->GetBinContent(b)) );
 }

 h8p->Draw("hist");
 gPad->SetLogy(0);
 canv->Print("Fig8_pull.png");


 cout << "\n\nCounts: " << counts << "\n\n";

 gSystem->Exit(1);

}
