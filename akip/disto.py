#nums = [0,5,10,15,20] ; bins = 150 ; minv = 140 ; maxv =170
#nums = [1,6,11,16,21] ; bins = 150 ; minv = 300 ; maxv = 330
#nums = [2,7,12,17,22] ; bins = 200 ; minv = 445 ; maxv = 485
#nums = [3,8,13,18,23] ; bins = 200 ; minv = 600 ; maxv = 650
nums = [4,9,14,19,24] ; bins = 200 ; minv = 750 ; maxv = 800


import shelve
with shelve.open("init_db") as db:
    mm = db["mm"]
    ss = db["ss"]
cols = [1,2,3,4,44]
hh = []
i=0
for n in nums:
    h = ROOT.TH1F("h_"+str(n),";E, a.u.;",bins,minv,maxv)
    for s in ss[n]:
        h.Fill(s)
        h.SetLineColor( cols[i] )
    i+=1
    hh.append( h )

f=True
for h in hh:
    if f:
        h.Draw("hist")
        f=False
    else:
        h.Draw("hist same")

import numpy as np
import scipy.stats as stats


for i in range(len(nums)):
    for j in range(i+1,len(nums)):
        print( stats.ks_2samp(ss[nums[i]],ss[nums[j]]) )
