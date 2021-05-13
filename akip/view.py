def load_event( fname , hname="h" ):
    i=0
    h_in  = ROOT.TH1F(hname + "_in" , " ;t, ns; U, mV", 2008, 0, 50200)
    h_out = ROOT.TH1F(hname + "_out", " ;t, ns; U, mV", 2008, 0, 50200)
    hq    = ROOT.TH1F(hname + "_c" , " ;t, ns; q, au", 2007, 25./2., 50200-25./2.)
    hq   .SetLineColor(1)
    h_in .SetLineColor(2)
    h_out.SetLineColor(4)
    with open(fname, "r") as fl:
        for line in fl:
            if i>2:
                w = line[:-1].split("\t")
                h_in [ i-2 ] = VE(float(w[2]),0)
                h_out[ i-2 ] = VE(float(w[1]),0)
#                print( str(i-2) + "  " + str( 25*(i-2) ) +  "\t" + str(w) )
            i+=1
    for b in range(1,2008):
        hq[b] = VE( -25.*(h_in[b+1].value()-h_in[b].value()) , 0)
    return h_in, h_out, hq

def get_base( h , window = 20):
    b_max = hq.findBin( hq.find_X( hq.maxv() ) )
    sum_b = 0.
    num = 0.
    for b in range(1,len(h)-2):
        if b < b_max-window/2 or b >b_max+window/2:
            sum_b += h[b].value()
            num += 1.
    if num!=0.:
        return sum_b/num
    return -999999.


from ostap.histos.graphs import makeGraph
def get_signal( h ):
    hs = h.Clone()
    hs.Reset()
    base = get_base( h )
    xx = []; yy = []
    b_max = hq.findBin( hq.find_X( hq.maxv() ) )
    go_left = True
    ib = b_max
    while go_left:
        ib-=1
        if h[ib].value()>base:
            xx.append( h.GetBinCenter( ib ) )
            yy.append( h[ib].value()        )
            hs[ib] = h[ib]
        else:
            go_left = False
    xx.reverse(); yy.reverse()
    go_right = True
    ib = b_max
    while go_right:
        if h[ib].value()>base:
            xx.append( h.GetBinCenter( ib ) )
            yy.append( h[ib].value()        )
            hs[ib] = h[ib]
        else:
            go_right = False
        ib+=1
    gs = makeGraph(xx,yy)
    return gs, hs


def num2str( i ):
    if i>999 or i<0:
        return str(i)
    if i>99:
        return "0"+str(i)
    if i>9:
        return "00"+str(i)
    return "000"+str(i)


from ostap.utils.progress_bar import progress_bar
from statistics import mean, stdev

fff = "20210511-0001_0001.txt"
h_in, h_out, hq = load_event( fff )
gs, hs = get_signal( hq )

canvas.Divide(1,2)
canvas.cd(1)
h_in.Draw("hist")
canvas.cd(2)
hq.Draw("hist")

#canvas >> "init_pulse"
#h_out.Draw("hist")
#canvas >> "init_AND_out"

