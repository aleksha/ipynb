from ostap.histos.graphs import makeGraph
def e(a,t):
    A=VE(a,a)
    R=VE(t-a,t-a)
    return ( 1./(1.+R/A) )
def t( T):
    return VE(2.*0.938272*T*0.001,0)

x = [t(0), t(0.5), t(2), t(5), t(10)]

y = [e(83,506), e(124.,502.), e(247.,491.), e(424.,492.), e(503.,509.)]
g=makeGraph(x,y)
g.SetMarkerStyle(24)
g.SetMarkerColor(2)
g.SetLineColor(2)
g.Draw("AP")
tf = ROOT.TF1("tf","1-expo(0)",0,0.04)
tf.SetLineColor(2)
r = g.Fit("tf","S")

y1 = [e(223,506), e(289.,502.), e(387.,491.), e(476.,492.), e(508.,509.)]
g1=makeGraph(x,y1)
g1.SetMarkerStyle(24)
g1.SetMarkerColor(1)
g1.SetLineColor(1)
g1.Draw("AP")
tf1 = ROOT.TF1("tf1","1-expo(0)",0,0.04)
tf1.SetLineColor(1)
r1 = g1.Fit("tf1","S")

y2 = [e(11,506), e(42.,502.), e(134.,491.), e(338.,492.), e(474.,509.)]
g2=makeGraph(x,y2)
g2.SetMarkerStyle(24)
g2.SetMarkerColor(4)
g2.SetLineColor(4)
g2.Draw("AP")
tf2 = ROOT.TF1("tf2","1-expo(0)",0,0.04)
tf2.SetLineColor(4)
r2 = g2.Fit("tf2","S")

g2.Draw("AP")
g1.Draw("P same")
g .Draw("P same")

