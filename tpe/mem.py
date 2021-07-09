

EV=33000000
EV=30000000
#N_Bins = 1000
N_Bins = 100

hp = ROOT.TH1F("hp",";;",N_Bins,0.001,0.08);
hm = ROOT.TH1F("hm",";;",N_Bins,0.001,0.08);


fp  = ROOT.TF1("fp" ,"1.+1.*(0.01667*x+0.00388*sqrt(x))", 0.0, 0.08)
fm  = ROOT.TF1("fm" ,"1.-1.*(0.01667*x+0.00388*sqrt(x))", 0.0, 0.08)

#fp  = ROOT.TF1("fp" ,"1.+(0.33*x+0.00388*sqrt(x))", 0.001, 0.08)
#fm  = ROOT.TF1("fm" ,"1.-(0.33*x+0.00388*sqrt(x))", 0.001, 0.08)

#fp  = ROOT.TF1("fp" ,"1.+(0.033*x)", 0.001, 0.08)
#fm  = ROOT.TF1("fm" ,"1.-(0.033*x)", 0.001, 0.08)

fp_max = fp.Eval(0.08)
fm_max = fm.Eval(0.0)

ev=0

lst = []

with open("out.txt","r") as fl:

    run_m = True
    ev_m=0
    while run_m:
        x = float( fl.readline()[:-1] ) 
        ev+=1
        y = fm_max*ROOT.gRandom.Rndm()
        if y<fm.Eval(x):
            if x>0.001:
                hm.Fill( x )
                lst.append( x )
            ev_m+=1
        if ev_m>EV:
            print( str(ev)+"\t"+str(ev_m) )
            run_m=False

    run_p = True
    ev_p=0
    while run_p:
        x = float( fl.readline()[:-1] ) 
        ev+=1
        y = fp_max*ROOT.gRandom.Rndm()
        if y<fp.Eval(x):
            if x>0.001:
                hp.Fill( x )
                lst.append( x )
            ev_p+=1
        if ev_p>EV:
            print( str(ev)+"\t"+str(ev_p) )
            run_p=False




h = hp/( hm *(hp[1].value()/hm[1].value())/(fp.Eval(0.001)/fm.Eval(0.001) ) )

#tf1 = ROOT.TF1("tf1","(1.+[0]*(0.01667*x+0.00388*sqrt(x)))/(1-[0]*(0.01667*x+0.00388*sqrt(x)))",0.001,0.08)
tf1 = ROOT.TF1("tf1","(1.+[0]*(0.01667*x+0.00388*sqrt(x)))/(1-[0]*(0.01667*x+0.00388*sqrt(x)))",0.0,0.08)
tf1.SetLineWidth(3)
tf1.SetLineColor(2)

h.Draw()
r = h.Fit("tf1","S")

