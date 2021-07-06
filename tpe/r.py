EV=33000000
N_Bins = 1000

hp = ROOT.TH1F("hp",";;",N_Bins,0.001,0.08);
hm = ROOT.TH1F("hm",";;",N_Bins,0.001,0.08);


with open("out.txt","r") as fl:
    for i in range(EV):
        hp.Fill( float( fl.readline()[:-1] ) )
    for i in range(EV):
        hm.Fill( float( fl.readline()[:-1] ) )

h = hp/hm

tf1 = ROOT.TF1("tf1","(1.+[0]*x)/(1-[0]*x)",0.001,0.08)
tf1.SetLineWidth(3)
tf1.SetLineColor(2)

h.Draw()
r = h.Fit("tf1","S")

