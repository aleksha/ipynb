#include <iostream>
#include <fstream>

using namespace std;
#include "TAxis.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGaxis.h"
#include "TH1F.h"
#include "TLatex.h"
#include "TMath.h"
#include "TPad.h"
#include "TRandom2.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TTree.h"

#include "XS4.hh"

void gen( int EVENTS = 70000000, int TOYS = 0 ){

 gStyle->SetOptFit(1111);

 fXS->FixParameter( 0, 0.72 );
 fXS->SetParLimits( 1, 0, 2.0 );
 fXS->SetParameter( 1, 0.86 );
 fXS->SetParameter( 2, 1.00 );
 fXS->SetParameter( 3, 2.63 );
 fXS->SetParName( 0, "E" );
 fXS->SetParName( 1, "r_{p}" );
 fXS->SetParName( 2, "scale" );
 fXS->SetParName( 3, "R_{4}" );
 fXS->SetTitle(" ");
 double y_scale = 1./fXS->Eval(0.0009);
 fXS->SetParameter( 2, y_scale );




 fXSg->FixParameter( 0, 0.72 );
 fXSg->SetParLimits( 1, 0, 2.0 );
 fXSg->SetParameter( 1, 0.86 );
 fXSg->SetParameter( 2, 1.00 );
 fXSg->SetParameter( 3, 2.63 );
 fXSg->SetParName( 0, "E" );
 fXSg->SetParName( 1, "r_{p}" );
 fXSg->SetParName( 2, "scale" );
 fXSg->SetParName( 3, "R_{4}" );
 fXSg->SetTitle(" ");
 double yg_scale = 1./fXSg->Eval(0.0009);
 fXSg->SetParameter( 2, yg_scale );




 TRandom2 *rx = new TRandom2( 71258 );
 TRandom2 *ry = new TRandom2( 34785 );
// double x,y;
 Double_t x,y;

 TH1D* hgen = new TH1D("hgen",";Q^{2}, GeV^{2};pdf",390, 0.001,0.04);

 int counts = 0;
 int TODO = int( EVENTS );
 for(int i=0;i<TODO;i++){
   do{ x = 0.00095 + rx->Rndm()*0.0405; y = ry->Rndm(); } while( y>fXSg->Eval(x));
   if( x >0.001 && x<0.04 ) counts++;
   hgen->Fill( x );
 }

 hgen->Scale(1./hgen->Integral() );

 TCanvas *canv = new TCanvas("canv","fig1",900,600);
 canv->SetLogy();
 hgen->Draw();
 canv->Print("pdf.png");

 TFile* fl = new TFile("pdf.root","RECREATE");
 hgen->Write();
 fl->Write();
 fl->Close();

 cout << "\n\nCounts: " << counts << "\n\n";

 gSystem->Exit(1);

}
