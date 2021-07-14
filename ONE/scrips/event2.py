# ev >> tr >> st >> vol >> dE >> code >> c >> E >> xf >> yf >> zf >> tf >> px >> py >> pz >> m
EVENT = 5
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

ff = open("out.data","r")

xl = [] ; yl = []
xe = [] ; ye = []

for line in ff:
    w = line[:-1].split(" ")
    ev = int(w[0])
    cd = int(w[5])
    if ev==EVENT and cd==11 :
        xe.append( float(w[8]) )
        ye.append( float(w[10]) )
    if ev==EVENT and cd==2212 :
        xl.append( float(w[8]) )
        yl.append( float(w[10]) )

x  = np.array( xl ); y  = np.array( yl )
x2 = np.array( xe ); y2 = np.array( ye )

plt.scatter( x , y )
plt.scatter( x2, y2 , c = "r")
plt.grid(True)
plt.savefig("TEMP.png")
ff.close()
