
from ostap.histos.graphs import makeGraph

x = []
y = []

with open("dmu42.txt","r") as fl:
    for line in fl:
        w = line[:-1].split(" ") 
        print( w )
        x.append( float(w[0]) )
        y.append( float(w[3]) )

g = makeGraph(x,y)
g.SetMarkerStyle(24)
g.Draw("AP")

tf1 = ROOT.TF1("tf1","[0]*x+[1]*sqrt(x)",0.001,0.08)
#tf1 = ROOT.TF1("tf1","[0]*x+[1]*sqrt([2]*x)",0.001,0.08)
#tf1 = ROOT.TF1("tf1","[0]*x+[1]*pow(x,[2])",0.001,0.08)

tf1a = ROOT.TF1("tf1a","0.01667*x",0.001,0.08)
tf1b = ROOT.TF1("tf1b","0.00388*sqrt(x)",0.001,0.08)
tf1a.SetLineColor(2)
tf1b.SetLineColor(4)

r = g.Fit("tf1","S")
tf1a.Draw("same")
tf1b.Draw("same")


