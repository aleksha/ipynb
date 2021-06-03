#include <iostream>
#include <fstream>

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

void refit2c( int EVENTS = 70000000, int TOYS = 0 ){

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

 ifstream myfile;
 myfile.open("out.txt", ios::in);
 


 float XX[9];
 XX[0] = 0.96;
 XX[1] = 0.97;
 XX[2] = 0.98;
 XX[3] = 0.99;
 XX[4] = 1.00;
 XX[5] = 1.01;
 XX[6] = 1.02;
 XX[7] = 1.03;
 XX[8] = 1.04;


 int evs = 0;
 while( myfile >> x ){
   h4->Fill( XX[0]*x );
   h3->Fill( XX[1]*x );
   h2->Fill( XX[2]*x );
   h1->Fill( XX[3]*x );
   h ->Fill( XX[4]*x );
   h5->Fill( XX[5]*x );
   h6->Fill( XX[6]*x );
   h7->Fill( XX[7]*x );
   h8->Fill( XX[8]*x );
   evs++;
   if( !(evs%7000000) ) cout << evs << "\n";
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

 float YY[9];

 h4->Fit("fXS","R"); YY[0] = fXS->GetParameter(1);
 h3->Fit("fXS","R"); YY[1] = fXS->GetParameter(1);
 h2->Fit("fXS","R"); YY[2] = fXS->GetParameter(1);
 h1->Fit("fXS","R"); YY[3] = fXS->GetParameter(1);
 h ->Fit("fXS","R"); YY[4] = fXS->GetParameter(1);
 h5->Fit("fXS","R"); YY[5] = fXS->GetParameter(1);
 h6->Fit("fXS","R"); YY[6] = fXS->GetParameter(1);
 h7->Fit("fXS","R"); YY[7] = fXS->GetParameter(1);
 h8->Fit("fXS","R"); YY[8] = fXS->GetParameter(1);

 vQ2 = 0.001 - ( (0.04 -0.001)/1000. )*0.5;
 for(int b=1;b<1001;b++){
  vQ2 = vQ2  + ( (0.04 -0.001)/1000. );
  h8p->SetBinContent( b, (h8->GetBinContent(b) - fXS->Eval(vQ2)) / sqrt(h8->GetBinContent(b)) );
 }

 h8p->Draw("hist");
 gPad->SetLogy(0);
 canv->Print("Fig8_pull.png");

 TGraph *gr = new TGraph(9,XX,YY);
 gr->SetTitle(" ");
 gr->GetXaxis()->SetTitle("Q^{2} factor");
 gr->GetYaxis()->SetTitle("Fitted r_{p}, fm");
 gr->GetYaxis()->SetRangeUser(0.82,0.90);
 gPad->SetGridx();
 gPad->SetGridy();
 gr->SetLineWidth(3);
 gr->Draw("AL");
 canv->Print("Fig_graph.png");


 cout << "\n\nCounts: " << evs << "\n\n";

 gSystem->Exit(1);

}
