import numpy as np
import scipy.stats as stats

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

for ch1 in range(16):
    for ch2 in range(ch1+1,16):
        ss     =  "Test ch" + str(ch1) + " vs. ch" + str(ch2) 
        answer =  stats.ks_2samp(E[ch1],E[ch2])
        ss    +=  "\t Stat: " + str(answer.statistic)
        ss    +=  "\t p-val: " + str(answer.pvalue)
        print( ss )

