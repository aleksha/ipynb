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
EVENT = 1000
for NUM in range(1, 26):
    rfile = ROOT.TFile("~/data/akip/20210511-"+num2str( NUM )+".t1.root","READ")
    #rfile.ls()
    tt = rfile["t1"]
    vin = [] ; e1 = []
    ii = 0
    for ev in tt:
       if ii<EVENT:
          vin.append( ev.Vin   )
          e1 .append( ev.e1[0] )
       ii+=1
    vins.append( vin )
    e1s .append( e1 )
    MeanIn .append( VE( mean( vin ), ( stdev( vin )/sqrt(len( vin ) ) )**2 ) )
    MeanOut.append( VE( mean( e1  ), ( stdev( e1  )/sqrt(len( e1  ) ) )**2 ) )
    rfile.Close()
#===============================================================================
print( len(MeanIn) )
#===============================================================================
AvMeanIn = [] ; AvMeanOut = []
AvMeanIn .append( (MeanIn [0] + MeanIn [5] + MeanIn [10] + MeanIn [15] + MeanIn [20] )/5. )
AvMeanOut.append( (MeanOut[0] + MeanOut[5] + MeanOut[10] + MeanOut[15] + MeanOut[20] )/5. )

AvMeanIn .append( (MeanIn [1] + MeanIn [6] + MeanIn [11] + MeanIn [16] + MeanIn [21] )/5. )
AvMeanOut.append( (MeanOut[1] + MeanOut[6] + MeanOut[11] + MeanOut[16] + MeanOut[21] )/5. )

AvMeanIn .append( (MeanIn [2] + MeanIn [7] + MeanIn [12] + MeanIn [17] + MeanIn [22] )/5. )
AvMeanOut.append( (MeanOut[2] + MeanOut[7] + MeanOut[12] + MeanOut[17] + MeanOut[22] )/5. )

AvMeanIn .append( (MeanIn [3] + MeanIn [8] + MeanIn [13] + MeanIn [18] + MeanIn [23] )/5. )
AvMeanOut.append( (MeanOut[3] + MeanOut[8] + MeanOut[13] + MeanOut[18] + MeanOut[23] )/5. )

AvMeanIn .append( (MeanIn [4] + MeanIn [9] + MeanIn [14] + MeanIn [19] + MeanIn [24] )/5. )
AvMeanOut.append( (MeanOut[4] + MeanOut[9] + MeanOut[14] + MeanOut[19] + MeanOut[24] )/5. )
#===============================================================================
g = makeGraph( AvMeanIn, AvMeanOut )
g.SetMarkerStyle(24)
g.Draw("AP")
r = g.Fit("pol1","SE")
print( EVENT*5 )
print( r.Chi2()/r.Ndf() )
#===============================================================================
ini = [] ; res = []
for a in range(1,24):
    Syst = VE( 0, (a*0.005)**2 )
    AvMeanOutSyst = []
    for b in AvMeanOut:
        AvMeanOutSyst.append( b+Syst )
    g = makeGraph( AvMeanIn, AvMeanOutSyst )
    g.Draw("AP")
    r = g.Fit("pol1","SE")
    ini.append( a*0.005 )
    res.append(  r.Chi2()/r.Ndf() )
#===============================================================================
for i in range(len(res)):
    print( str(ini[i]*5000./191.9) + "\t" + str(res[i]))
###In [3]: 0.11*5000./191.9
###Out[3]: 2.8660760812923396


