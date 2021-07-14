{

    double T, Mean, Sigma, Pstar, Totl;
    std::ifstream fOUT("./Tab.txt" , std::ios::in);

    double x[7],y[7],ey[7],ex[7],p[7],t[7];
    int ii =0;
    while( fOUT >> T >> Mean >> Sigma >> Totl >> Pstar ){
      x[ii]  = T;
      y[ii]  = Mean;
      ey[ii] = Sigma;
      ex[ii] = 0;
      p[ii] = Pstar;
      t[ii] = Totl;
      ii++;
    }

    gt = new TGraph (7,x,t);
    gp = new TGraph (7,x,p);
    gy = new TGraphErrors (7,x,y,ex,ey);

    gy->SetMarkerStyle(20);
    gt->SetMarkerStyle(24);
    gy->SetMarkerColor(2);
    gy->SetLineColor(2);
    gp->SetLineColor(4);

    gy->SetTitle("H_{2}, Normal pressure");

    gy->GetXaxis()->SetTitle("T_{p}, MeV");
    gy->GetYaxis()->SetTitle("Projected range, mm");

    TCanvas* canv = new TCanvas("canv","canv",600,600);
    gy->Draw("AP");
    gt->Draw("P same");
    gp->Draw("L same");
    canv->Print("RANGE.png");
}
