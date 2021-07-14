#include "TSystem.h"
#include "TStyle.h"
#include "TString.h"
#include "TLatex.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TVector3.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TLine.h"
#include "TBox.h"
#include "TMath.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TFile.h"

#include <iostream>
#include <fstream>
using namespace std;



void range(){

    int ev, vol, tr, st, code, c;
    double dE, E, xf, yf, zf, tf, px, py, pz ,m;

    TVector3 v_max; v_max.SetXYZ(0,0,0);

//    TH1F* h  = new TH1F("h","; E, MeV; Entries", 300, 8, 11);
    TH1F* hPROTON = new TH1F("hPROTON","; E, MeV; Entries", 11000, 0, 11);
    TH1F* hALL    = new TH1F("hALL"   ,"; E, MeV; Entries", 11000, 0, 11);
    TH1F* hNUCL   = new TH1F("hELEC"  ,"; E, MeV; Entries", 11000, 0, 11);
    TH1F* hELEC   = new TH1F("hNUCL"  ,"; E, MeV; Entries", 11000, 0, 11);

    TH1F* hShape  = new TH1F("hShape"  ,"; z, mm; Entries", 350, 0, 350);
    TH1F* hDelta  = new TH1F("hDelta"  ,"; z, mm; Entries", 350, 0, 350);

    TH1F* hTotl   = new TH1F("hTotl"   ,"; z, mm; Entries", 50, 35, 85);
    TH1F* hProj   = new TH1F("hProj"   ,"; z, mm; Entries", 50, 35, 85);

    hALL->SetLineColor(1);
    hALL->SetFillColor(1);

    hPROTON->SetLineColor(2);
    hPROTON->SetFillColor(2);
    hPROTON->SetFillStyle(3005);

    hShape->SetLineColor(1);
    hDelta->SetLineColor(4);
    hDelta->SetFillColor(4);
    hDelta->SetFillStyle(3005);


    hProj->SetLineColor(2);
    hTotl->SetLineColor(4);

    TCanvas* canv = new TCanvas("canv","canv",600,600);

    std::ifstream fOUT("./out.data" , std::ios::in);

    int EVENT=0;
    double ionization_proton = 0.;
    double ionization_all    = 0.;
    double ionization_nucl   = 0.;
    double ionization_elec   = 0.;

    while( fOUT >> ev >> tr >> st >> vol >> dE >> code >> c >> E >> xf >> yf >> zf >> tf >> px >> py >> pz >> m ){
      if(ev>EVENT){
        hPROTON->Fill( ionization_proton );
        hALL   ->Fill( ionization_all    );
        hNUCL  ->Fill( ionization_nucl   );
        hELEC  ->Fill( ionization_elec   );
        hProj  ->Fill( v_max.z()         );
        hTotl  ->Fill( v_max.Mag()       );

        ionization_proton = 0.;
        ionization_all    = 0.;
        ionization_nucl   = 0.;
        ionization_elec   = 0.;
        v_max.SetXYZ(0,0,0);
        EVENT = ev;
      }

      ionization_all = ionization_all + dE;
      if(tr==1){ ionization_proton = ionization_proton + dE; }
      if(code==2212 && tr>1){ ionization_nucl   = ionization_nucl   + dE; }
      if(code!=2212 && dE>0){
        ionization_elec   = ionization_elec   + dE;
        hDelta->Fill( zf, dE );
      }

      hShape->Fill( zf, dE );

      if(tr==1 && zf > v_max.z() ){ v_max.SetXYZ(xf,yf,zf); }

    }

    fOUT.close();

    cout << "ALL:       " << hALL->GetMean()    << endl;
    cout << "PROTON:    " << hPROTON->GetMean() << endl;
    cout << "PROTONs:   " << hNUCL->GetMean()   << endl;
    cout << "Electrons: " << hELEC->GetMean()   << endl;

    gStyle->SetOptStat(0);
    hALL->Draw();
    hPROTON->Draw("same");
    canv->Print("TEMP.png");

    hShape->Scale(0.001/10.);
    hDelta->Scale(0.001/10.);
    hShape->Draw();
    hDelta->Draw("same");
    canv->Print("TEMP.png");


    gStyle->SetOptFit();
    hProj->Draw();
    hProj->Fit("gaus");
    hTotl->Draw("same");
    canv->Print("TEMP.png");

    cout << hALL->GetMean() << " " << hProj->GetMean() << " " << hProj->GetStdDev() << endl;

    gSystem->Exit(0);

}
