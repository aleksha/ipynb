nums = [0,5,10,15,20] ; bins = 150 ; minv = 140 ; maxv =170
#nums = [1,6,11,16,21] ; bins = 150 ; minv = 300 ; maxv = 330
#nums = [2,7,12,17,22] ; bins = 200 ; minv = 445 ; maxv = 485
#nums = [3,8,13,18,23] ; bins = 200 ; minv = 600 ; maxv = 650
#nums = [4,9,14,19,24] ; bins = 200 ; minv = 750 ; maxv = 800; 
NB = 1000 ; 
#
import shelve
import numpy as np
from statistics import mean, stdev, median
import scipy.stats as stats
from math import sqrt
from ostap.utils.progress_bar import progress_bar
#
with shelve.open("init_db") as db:
    mm = db["mm"]
    ss = db["ss"]
cols = [1,2,3,4,44]
#
strs = []
for n in nums:
    # --- histo
    h = ROOT.TH1F("h_"+str(n),";E, a.u.;",bins,minv,maxv)
    for s in ss[n]:
        h.Fill(s)
    # --- bootstrap
    b_means = []; b_medians = []
    for i in progress_bar( range(NB) ):
        vals = [] ; nS = len(ss[n])
        for i in range(nS):
            vals.append( ss[n][ ROOT.gRandom.Integer(nS) ] )
        b_means  .append( mean  (vals) )
        b_medians.append( median(vals) )
    #
    Mean   = VE( mean  ( ss[n] ) , (stdev ( ss[n] ) / sqrt( len(ss[n]) ))**2 )
    Median = median( ss[n] )
    #
    hMean   = h.mean()
    #
    bMean   = VE( mean  ( b_means  ) , stdev( b_means   )**2)
    bMedian = VE( median( b_medians) , stdev( b_medians )**2)
    #
    aa  = " | "
    aa += "{:5.2f}".format(Mean.value()) + " +/- " + "{:5.2f}".format(Mean.error()) + " | "
    #aa += "{:5.2f}".format( hMean.value() ) + "  " + "{:5.2f}".format(hMean.error()) + " || "
    aa += "{:5.2f}".format( bMean.value() ) + " +/- " + "{:5.2f}".format(bMean.error()) + " || "
    aa += "{:5.2f}".format(Median) + " | "
    aa += "{:5.2f}".format( bMedian.value() ) + " +/- " + "{:5.2f}".format(bMedian.error()) + " || "
    strs.append(aa)

#
for aa in strs:
    print(aa)

