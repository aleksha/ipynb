

y1 = [ 8.40562e-01,  8.45339e-01,  8.50050e-01,  8.54752e-01,  8.59376e-01,  8.64032e-01,  8.68617e-01,  8.73157e-01,  8.77641e-01]
y2 = [ 8.59901e-01,  8.59751e-01,  8.59621e-01,  8.59521e-01,  8.59376e-01,  8.59251e-01,  8.59144e-01,  8.59030e-01,  8.58911e-01]
y3 = [ 8.40052e-01,  8.44962e-01,  8.49800e-01,  8.54603e-01,  8.59376e-01,  8.64151e-01,  8.68845e-01,  8.73536e-01,  8.78148e-01 ]

x = [-4.,-3.,-2.,-1.,0.,1.,2.,3.,4.]

import ROOT
from ostap.histos.graphs import makeGraph

canvas.Close()

canv = ROOT.TCanvas("canv","canv",800,800)

g1 = makeGraph(x,y1)
g2 = makeGraph(x,y2)
g3 = makeGraph(x,y3)

g1.GetXaxis().SetTitle("Q^{2} bias, GeV^{2}#times10^{-6}")
g1.GetYaxis().SetTitle("Extracted r_{p}, fm")

g1.SetLineWidth(3)
g2.SetLineWidth(3)
g3.SetLineWidth(3)

g1.SetLineColor(2)
g2.SetLineColor(1)
g3.SetLineColor(4)

g1.Draw("AL")
g2.Draw("same L")
g3.Draw("same L")

ROOT.gPad.SetGridx()
ROOT.gPad.SetGridy()

canv.Print("Bias.png")
