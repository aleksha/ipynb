from ostap.histos.graphs import makeGraph
def e(a,t):
    A=VE(a,a)
    R=VE(t-a,t-a)
    return ( 1./(1.+R/A) )
def t( T):
    return VE(2.*0.938272*T*0.001,0)

x = [t(0), t(0.5), t(2), t(5), t(10)]

#y = [e(398.,523), e(403.,511.), e(432.,480.), e(495.,502.), e(484.,484.)]
#y = [e(139.,523), e(203.,511.), e(311.,480.), e(451.,502.), e(481.,484.)]
y = [e( 13.,523), e( 42.,511.), e(144.,480.), e(331.,502.), e(449.,484.)]

g=makeGraph(x,y)
g.SetMarkerStyle(24)
g.SetMarkerColor(2)
g.SetLineColor(2)
g.Draw("AP")
tf1 = ROOT.TF1("tf1","1-expo(0)",0,0.04)
tf1.SetLineColor(2)
r = g.Fit("tf1","S")


fl = ROOT.TFile("pdf.root")
hgen = fl["hgen"]
hgen.scale(1./hgen.integral(0.001,0.04))
hgen.Draw()
hgen.integral(0.001,0.04)
hrate=86.6*0.2*0.00174*hgen
hn = hrate.transform( lambda x,y: y*tf1(x) )
hn.Draw()
hn.integral(0.001,0.04)
# Ostap  session by adzyuba   ended at Fri Jul 16 14:52:04 2021 [1429.2s]
