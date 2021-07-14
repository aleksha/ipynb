

prev_ev = -1
n_ev=0
E_lst = []
with open("out.data", "r") as fl:
    totE=0
    for line in fl:
        w = line[:-1].split(" ")
        ev = int( w[0] )
        de = float( w[1] )
        if ev>prev_ev:
            if totE>0.01:
                n_ev+=1
                E_lst.append( totE )
            totE = de
            prev_ev = ev
        else:
            totE += de

print( E_lst )
print( n_ev )
