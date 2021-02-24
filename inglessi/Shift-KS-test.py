#===============================================================================
canvas.Close()
import numpy as np
import scipy.stats as stats
import statistics as py_stat
#===============================================================================
def proj2hist( sample , tname, bins = 100, low = 163, high = 173):
    """This funcion projects a sample into TH1F"""
    hist = ROOT.TH1F(tname,tname+";E, a.u.;N",bins,low,high)
    for ev in sample:
        hist.Fill( ev )
    return hist
#===============================================================================
# Read data into numpy arrays
#
E = []
for ch in range(1,17):
    energy = []
    if ch<10:
        file_name = "20210218-ch0" + str(ch) + ".e.txt"
    else:
        file_name = "20210218-ch"  + str(ch) + ".e.txt"
    with open(file_name,"r") as fl:
        for line in fl:
            energy.append(float(line))

    E.append( np.array(energy) )
#===============================================================================
# Print stat for channel and produce data with median equal 160.
# (no rescaling so far)
#
SE = []
for i in range( 16 ):
    ss = "ch.: "
    if i<10:
        ss += "0"
    ss += str(i) + "  "
    ss += "min/max: " + str( min( E[i] ) ) + "/" + str( max( E[i] ) ) + "  "
    ss += "mean: " + str( py_stat.mean( E[i] ) ) + "  "
    ss += "rms: " + str( py_stat.stdev( E[i] ) ) + "  "
    ss += "median: " + str( py_stat.median( E[i] ) )
    print( ss )
    median = py_stat.median( E[i] )
    SE.append( E[i] - median + 160. )

#===============================================================================
# Draw shifted samples
#
canv = ROOT.TCanvas("canv","canv",1100,1100)
canv.Divide(4,4)
hh = []
ll = []
for i in range( 16 ):
    hh.append( proj2hist( SE[i], tname = "h_"+str(i), bins = 230, low=150, high=173 ) )
    canv.cd(i+1)
    hh[i].GetYaxis().SetRangeUser(0,100)
    hh[i].Draw("hist")
    ll.append( ROOT.TLatex(153,90,"ch.: "+str(i)) )
    ll[i].Draw()

canv.Print("fig_shift.png")


#===============================================================================
# Perform Kolmogorov-Smirnov tests for shifted samples
# In agreement if p-value > 0.0455 (two-sigma-level)
#
for ch1 in range(16):
    for ch2 in range(ch1+1,16):
        ss     =  "Test ch" + str(ch1) + " vs. ch" + str(ch2) 
        answer =  stats.ks_2samp(SE[ch1],SE[ch2])
        ss    +=  "\t Stat: " + str(answer.statistic)
        ss    +=  "\t p-val: " + str(answer.pvalue)
        if answer.pvalue>0.0455:
            print( "GOOD -> " + ss )
        else:
            print( "BAD --> " + ss )

print("\n\n")
#===============================================================================
# Perform Kolmogorov-Smirnov tests for shifted samples
# In agreement if p-value > 0.0027 (three-sigma-level)
#
for ch1 in range(16):
    for ch2 in range(ch1+1,16):
        ss     =  "Test ch" + str(ch1) + " vs. ch" + str(ch2) 
        answer =  stats.ks_2samp(SE[ch1],SE[ch2])
        ss    +=  "\t Stat: " + str(answer.statistic)
        ss    +=  "\t p-val: " + str(answer.pvalue)
        if answer.pvalue>0.0027:
            print( "GOOD -> " + ss )
        else:
            print( "BAD --> " + ss )

