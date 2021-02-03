
#include <iostream>
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TString.h"
#include "TH2F.h"

using namespace std;

const int Nmax = 102;

float u_init = 0.5;
float GND = 0;
float HV  = 1;

void Example_01( float N=101 , int iterMax=10000){

//----- Declare matrixies
  float u[Nmax][Nmax];
  float f[Nmax][Nmax];
  float pre_u;

  TString name;

  gStyle->SetOptStat(0);

  TH2F *h2 = new TH2F("h2","potential;x, mm; y, mm", N,-0.5,100.5, N,-0.5,100.5);
  TCanvas *canv = new TCanvas("canv","canv",600,600);

  h2->GetZaxis()->SetRangeUser(0,1);

//----- Define init
  for(int i=0;i<N;i++){
    for(int j=0;j<N;j++){
      u[i][j] = u_init;
      f[i][j] = 1;
      // Box
      if(i==0 || i==N-1 || j==0 || j==N-1){
        u[i][j] = GND;
        f[i][j] = 0;
      }
      // Anode
      if(i==20 && j>30 && j<70 ){
        u[i][j] = GND;
        f[i][j] = 0;
      }
      // Cathode
      if(i==80 && j>30 && j<70 ){
        u[i][j] = HV;
        f[i][j] = 0;
      }
  }}


//----- Define init
  for(int iter=0;iter<iterMax;iter++){
    for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
        if(f[i][j]){
          //-- eval
          u[i][j]= 0.25*(u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]);
        }
       //-- hist
       h2->SetBinContent(i+1,j+1,u[i][j]);
    }}
    //-- save
    h2->Draw("col");
    if(iter<10)                name.Form("u_000%d.png", iter);
    if(iter>9   && iter<100)   name.Form("u_00%d.png" , iter);
    if(iter>99  && iter<1000)  name.Form("u_0%d.png"  , iter);
    if(iter>999 && iter<10000) name.Form("u_%d.png"   , iter);
    canv->Print(name);
  }

  if(1) cout << N << "\n";

  canv->Close();

  gSystem->Exit(0);

}
