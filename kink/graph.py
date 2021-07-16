from ostap.histos.graphs import makeGraph
def e(a,t):
    A=VE(a,a)
    R=VE(t-a,t-a)
    return ( 1./(1.+R/A) )
def t( T):
    return VE(2.*0.938272*T*0.001,0)

x = [t(0), t(0.5), t(2), t(5), t(10)]

y = [e(139.,523), e(203.,511.), e(311.,480.), e(451.,502.), e(481.,484.)]
g=makeGraph(x,y)
g.SetMarkerStyle(24)
g.SetMarkerColor(2)
g.SetLineColor(2)
g.Draw("AP")
tf = ROOT.TF1("tf","1-expo(0)",0,0.04)
tf.SetLineColor(2)
r = g.Fit("tf","S")

y1 = [e(398.,523), e(403.,511.), e(432.,480.), e(495.,502.), e(484.,484.)]
g1=makeGraph(x,y1)
g1.SetMarkerStyle(24)
g1.SetMarkerColor(1)
g1.SetLineColor(1)
g1.Draw("AP")
tf1 = ROOT.TF1("tf1","1-expo(0)",0,0.04)
tf1.SetLineColor(1)
r1 = g1.Fit("tf1","S")

y2 = [e(13.,523), e(42.,511.), e(144.,480.), e(331.,502.), e(449.,484.)]
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

