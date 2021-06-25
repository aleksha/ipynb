E   = 100.
m_p = 0.938272
from math import sin, cos, asin, pi, sqrt
def calc_theta( TR ):
    return 2.*asin(sqrt(TR*m_p/(2.*E*E)))

Tp = []; theta=[]
for i in range(2000):
    val = 0.0005+i*0.00001
    Tp.append(1000.*val)
    theta.append( 1000.*1000.*calc_theta( val ) )

from ostap.histos.graphs import makeGraph
g = makeGraph(Tp, theta)
g.Draw("AL")
