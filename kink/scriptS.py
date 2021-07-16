from ostap.histos.graphs import makeGraph
def e(a,t):
    A=VE(a,a)
    R=VE(t-a,t-a)
    return ( 1./(1.+R/A) )
def t( T):
    return VE(2.*0.938272*T*0.001,0)

x = [t(0), t(0.5), t(2), t(5), t(10)]

#y = [e(223,506), e(289.,502.), e(387.,491.), e(476.,492.), e(508.,509.)]
#y = [e( 83,506), e(124.,502.), e(247.,491.), e(424.,492.), e(503.,509.)]
y = [e( 11,506), e( 42.,502.), e(134.,491.), e(338.,492.), e(474.,509.)]

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
hrate=86.6*0.2*0.00092*hgen
hn = hrate.transform( lambda x,y: y*tf1(x) )
hn.Draw()
hn.integral(0.001,0.04)
# Ostap  session by adzyuba   ended at Fri Jul 16 14:52:04 2021 [1429.2s]
