#NUM = 0; nums = [0,5,10,15,20] ; bins = 150 ; minv = 140 ; maxv =170
NUM = 6; nums = [1,6,11,16,21] ; bins = 150 ; minv = 300 ; maxv = 330
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
from ostap.histos.graphs import makeGraph
#===============================================================================
def num2str( i ):
    if i>999 or i<0:
        return str(i)
    if i>99:
        return "0"+str(i)
    if i>9:
        return "00"+str(i)
    return "000"+str(i)
#===============================================================================
with shelve.open("init_db") as db:
    mm = db["mm"]
    ss = db["ss"]
cols = [1,2,3,4,44]
#
charge = ss[NUM]
h = ROOT.TH1F("h_"+str(NUM),";E, a.u.;",bins,minv,maxv)
for s in charge:
    h.Fill(s)
# --- bootstrap
b_means = []; b_medians = []
for i in progress_bar( range(NB) ):
    vals = [] ; nS = len( charge )
    for i in range(nS):
        vals.append( charge[ ROOT.gRandom.Integer(nS) ] )
    b_means  .append( mean  (vals) )
    b_medians.append( median(vals) )
#
Mean   = VE( mean  ( charge ) , (stdev ( charge ) / sqrt( len(charge) ))**2 )
Median = median( charge )
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
#===============================================================================
rfile = ROOT.TFile("~/data/akip/20210511-"+num2str( NUM+1 )+".t1.root","READ")
rfile.ls()
tt = rfile["t1"]
vin25 = [] ; e1 = []
for ev in tt:
    vin25.append( 25.*ev.Vin )
    e1   .append( ev.e1[0] )
g = makeGraph( charge, vin25 )
g.SetMarkerStyle(24)
g.Draw("AP")
rfile.Close()
#===============================================================================
AD = VE( mean( charge ), stdev( charge )**2 )
AI = VE( mean( vin25  ), stdev( vin25  )**2 )
#===============================================================================
print( aa )
print("AD: " + str(100.*AD.prec()))
print("AI: " + str(100.*AI.prec()))
#===============================================================================
gi = makeGraph( vin25, e1 )
gi.SetMarkerStyle(21)
gi.Draw("AP")
#
gd = makeGraph( charge, e1 )
gd.SetMarkerStyle(20)
gd.Draw("AP")
#===============================================================================

