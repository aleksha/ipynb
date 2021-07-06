#include "TF1.h"

//----------------------------------------------------------------
//
// Goal   : Rosenbluth's cross section for mu p-scattering
// Author : Alexey Dzyuba, PNPI
// E-Mail : a.dzyuba@gmail.com
// Date   : 2017-07-14
//
// Tested with CERN ROOT v5.34/32
//
//----------------------------------------------------------------


//----------------------------------------------------------------
// Proton electric form factor squared as a function of
// Mandelstam t-invariant and effective radius of proton
//
double GE2(double t, double r, double R4 ){
    double GeV2fm = 0.19733 ; // inverse GeV to fm  : 0.19733 fm = 1/GeV
    double Ge = 1. + pow(r/GeV2fm,2)*t/6.; // as t = -Q^2
    Ge = Ge + R4*pow(1./GeV2fm,4)*t*t/120.; // as t = -Q^2 
    return pow(Ge,2) ;
}

//----------------------------------------------------------------
// Proton magnetic form factor squared as a function of
// Mandelstam t-invariant and effective radius of proton
//
double GM2(double t, double r, double R4 ){
    // Dipole paramettrization for G_m
    return pow(sqrt(GE2(t,r, R4))*2.79,2);
}

//----------------------------------------------------------------
// Rosenbluth cross section (Landau, Lifshits IV, Eq 139.9, p.685)
//
double epXS( double E, double t, double r, double R4 ){

    double PI = TMath::Pi()  ; // pi constant.
    double alpha  = 1./137.  ; // fine structure constatn.
    //double m      = 0.1056584; // mass of electron (not needed fere in fact).
    double M      = 0.938272 ; // mass of proton.
    double M2 = M*M          ; // squared mass of proton.
    double GeV2mb = 0.389379  ; // inverse GeV^2 to mb  : 0.38939 mb = 1/GeV^2

    //-------------------------------------------------------
    // Proton electric and magnetic form factors squared
    //
    double Ge2,Gm2;
    Ge2 = GE2( t, r, R4 );
    Gm2 = GM2( t, r, R4 );

    double sig_ns ; // no structure cross section from Ref. Eq.2
    sig_ns = PI* pow( alpha / (t*E) , 2 ) ;

    double Rm, Re;
    Re = Ge2 * ( pow( 4.*M*E + t ,2)/( 4.*M2 - t ) + t )           ;
    Rm = Gm2 * ( pow( 4.*M*E + t ,2)/( 4.*M2 - t ) - t ) * t / (4.*M2) ;

    double sig = GeV2mb * sig_ns * ( Re - Rm ) ;
    return sig;
}


/*
const int N = 220   ; // number of poins.
double t            ; // running t-invariant GeV^2.
double T            ; // running recoil proton kinetic energy GeV.
double E = 0.720    ; // Energy of el beam.
double M = 0.938272 ; // mass of proton, GeV.
*/

Double_t myXS(Double_t *x, Double_t *par){
  return par[2]*epXS( par[0], -x[0], par[1], par[3] );
}

TF1 *fXSg =  new TF1("fXSg", myXS, 0.0009, 0.05, 4);
TF1 *fXS  =  new TF1("fXS" , myXS, 0.0010, 0.02, 4);
//TF1 *fXS  =  new TF1("fXS" , myXS, 0.0010, 0.04, 3);


/*
     T = 0.0001 + 0.0001 * i ;
     t = - 2. * M * T        ;
     x[i] = T*1000. ; // Recoil kinetic energy, MeV.
     y1[i] = epXS( E , t , 0.84 ) ; // XS with R_proton = 0.84 fm.
     y2[i] = epXS( E , t , 0.88 ) ; // XS with R_proton = 0.8 fm.
     y3[i] = epXS( E , t , 0.   ) ; // XS with R_proton = 0.8 fm.
*/
