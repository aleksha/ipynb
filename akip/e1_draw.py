import shelve
import numpy as np
from statistics import mean, stdev, median, variance
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
vins = [] ; e1s = []
MeanIn  = []
MeanOut = []
hh = []
for NUM in range(1, 26):
    h = ROOT.TH1F("h_"+num2str(NUM),";;",5000,0,200 )
    rfile = ROOT.TFile("~/data/akip/20210511-"+num2str( NUM )+".t1.root","READ")
    #rfile.ls()
    tt = rfile["t1"]
    vin = [] ; e1 = []
    for ev in tt:
        vin.append( ev.Vin   )
        e1 .append( ev.e1[0] )
        h  .Fill  ( ev.e1[0] )
    vins.append( vin )
    e1s .append( e1 )
    hh.append(h)
    MeanIn .append( VE( mean( vin ), ( stdev( vin )/sqrt(len( vin ) ) )**2 ) )
    MeanOut.append( VE( mean( e1  ), ( stdev( e1  )/sqrt(len( e1  ) ) )**2 ) )
    rfile.Close()

hn = []
hn.append( hh[0] + hh[5] + hh[10] + hh[15] + hh[20] )
hn.append( hh[1] + hh[6] + hh[11] + hh[16] + hh[21] )
hn.append( hh[2] + hh[7] + hh[12] + hh[17] + hh[22] )
hn.append( hh[3] + hh[8] + hh[13] + hh[18] + hh[23] )
hn.append( hh[4] + hh[9] + hh[14] + hh[19] + hh[24] )

en = []
en.append( e1s[0] + e1s[5] + e1s[10] + e1s[15] + e1s[20] )
en.append( e1s[1] + e1s[6] + e1s[11] + e1s[16] + e1s[21] )
en.append( e1s[2] + e1s[7] + e1s[12] + e1s[17] + e1s[22] )
en.append( e1s[3] + e1s[8] + e1s[13] + e1s[18] + e1s[23] )
en.append( e1s[4] + e1s[9] + e1s[14] + e1s[19] + e1s[24] )

