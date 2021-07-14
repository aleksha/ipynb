# ev >> tr >> st >> vol >> dE >> code >> c >> E >> xf >> yf >> zf >> tf >> px >> py >> pz >> m
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

from matplotlib.pyplot import figure
figure(num=None, figsize=(6, 6), dpi=80, facecolor='w', edgecolor='k')


xl = [] ; yl = []
xe = [] ; ye = []

theta = []

EVENT = 0
n_e=0
e_flag = False
ev=0
theta_mu=0

ff = open("out.data","r")
for line in ff:
    if ev>EVENT:
#        if e_flag and theta_mu*1000.*1000.>200. :
        if e_flag :
            #theta.append( theta_mu )
            n_e +=1
            #print(str(n_e)+"\t"+str(theta_mu*1000.*1000.))
        e_flag = False
        EVENT += 1

    w = line[:-1].split(" ")
    ev = int(w[0])
    st = int(w[2])
    cd = int(w[5])
    E = float(w[7])
    z = float(w[10])
    px = float(w[12])
    py = float(w[13])
    pz = float(w[14])
    pp = np.sqrt(px**2+py**2+pz**2)
    pt = np.sqrt(px**2+py**2)
    if st==1 and cd==11:
        if E>10:
            e_flag = True

    if st==2 and cd==13:
        theta_mu = pt/pz

print("Fraction of events with electrons (E>10MeV) :" + str(100.*float(n_e)/float(EVENT)) + " %")
print(n_e)
ff.close()

#x  = np.array( xl ); y  = np.array( yl )
#x2 = np.array( xe ); y2 = np.array( ye )
#plt.scatter( x , y )
#plt.scatter( x2, y2 , c = "r")
#plt.axis([-5, 5, -5, 5])
#plt.grid(True)
#plt.xlabel('x, mm')
#plt.ylabel('y, mm')
#plt.savefig("TEMP.png")
