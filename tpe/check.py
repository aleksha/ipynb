

EV=33000000
EV=33000
N_Bins = 1000

hp = ROOT.TH1F("hp",";;",N_Bins,0.001,0.08);
hm = ROOT.TH1F("hm",";;",N_Bins,0.001,0.08);


fp  = ROOT.TF1("fp" ,"1.+(0.01667*x+0.00388*sqrt(x))", 0.001, 0.08)
fm  = ROOT.TF1("fm" ,"1.-(0.01667*x+0.00388*sqrt(x))", 0.001, 0.08)

fp_max = fp.Eval(0.08)
fm_max = fm.Eval(0.001)

ev=0

with open("out.txt","r") as fl:
    run_p = True
    ev_p=0
    while run_p:
        x = 0.001+0.079*ROOT.gRandom.Rndm()
        ev+=1
        y = fp_max*ROOT.gRandom.Rndm()
        if y<fp.Eval(x):
            hp.Fill( x )
            ev_p+=1
        if ev_p>EV:
            print( str(ev)+"\t"+str(ev_p) )
            run_p=False

    run_m = True
    ev_m=0
    while run_m:
        x = 0.001+0.079*ROOT.gRandom.Rndm()
        ev+=1
        y = fm_max*ROOT.gRandom.Rndm()
        if y<fm.Eval(x):
            hm.Fill( x )
            ev_m+=1
        if ev_m>EV:
            print( str(ev)+"\t"+str(ev_m) )
            run_m=False



h = hp/hm

tf1 = ROOT.TF1("tf1","(1.+[0]*x)/(1-[0]*x)",0.001,0.08)
tf1.SetLineWidth(3)
tf1.SetLineColor(2)

h.Draw()
r = h.Fit("tf1","S")

