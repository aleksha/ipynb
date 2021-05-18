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
db = shelve.open("db_e1")
Means    = db["Means"   ]
bMeans   = db["bMeans"  ]
bMedians = db["bMedians"]
db.close()

X  = [ VE(1,0), VE(2,0), VE(3,0), VE(4,0), VE(5,0) ]
#Y0 = [ Means[0] , Means[5] , Means[10] , Means[15] , Means[20] ]
#Y1 = [ Means[1] , Means[6] , Means[11] , Means[16] , Means[21] ]
#Y2 = [ Means[2] , Means[7] , Means[12] , Means[17] , Means[22] ]
#Y3 = [ Means[3] , Means[8] , Means[13] , Means[18] , Means[23] ]
#Y4 = [ Means[4] , Means[9] , Means[14] , Means[19] , Means[24] ]

#Y0 = [ bMeans[0] , bMeans[5] , bMeans[10] , bMeans[15] , bMeans[20] ]
#Y1 = [ bMeans[1] , bMeans[6] , bMeans[11] , bMeans[16] , bMeans[21] ]
#Y2 = [ bMeans[2] , bMeans[7] , bMeans[12] , bMeans[17] , bMeans[22] ]
#Y3 = [ bMeans[3] , bMeans[8] , bMeans[13] , bMeans[18] , bMeans[23] ]
#Y4 = [ bMeans[4] , bMeans[9] , bMeans[14] , bMeans[19] , bMeans[24] ]

Y0 = [ bMedians[0] , bMedians[5] , bMedians[10] , bMedians[15] , bMedians[20] ]
Y1 = [ bMedians[1] , bMedians[6] , bMedians[11] , bMedians[16] , bMedians[21] ]
Y2 = [ bMedians[2] , bMedians[7] , bMedians[12] , bMedians[17] , bMedians[22] ]
Y3 = [ bMedians[3] , bMedians[8] , bMedians[13] , bMedians[18] , bMedians[23] ]
Y4 = [ bMedians[4] , bMedians[9] , bMedians[14] , bMedians[19] , bMedians[24] ]

g0 = makeGraph(X,Y0) ; r0 = g0.Fit("pol0","SE") ; print( r0 )
g1 = makeGraph(X,Y1) ; r1 = g1.Fit("pol0","SE") ; print( r1 )
g2 = makeGraph(X,Y2) ; r2 = g2.Fit("pol0","SE") ; print( r2 )
g3 = makeGraph(X,Y3) ; r3 = g3.Fit("pol0","SE") ; print( r3 )
g4 = makeGraph(X,Y4) ; r4 = g4.Fit("pol0","SE") ; print( r4 )


