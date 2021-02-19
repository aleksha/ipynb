# Ostap  session by adzyuba started at Fri Feb 19 15:57:18 2021
# Command from CWD=/home/adzyuba/energy 
# ostap KS-test.py
E[0].min()
E[0].max()
E[1].min()
E[1].max()
for ch in range(16):
    E[ch].min()
    
for ch in range(16):
    print( E[ch].min() )
    
    
for ch in range(16):
    print( E[ch].max() )
    
hh = []
for ch in range(16):
    hh.append( ROOT.TH1F("h_"+str(ch),";E;N" ,100,163,173) )
    
for ch in range(16):
    for ev in E[ch]:
        hh[ch].Fill( ev )
    
hh[1].red()
hh[0].Draw()
hh[1].Draw("same")
hh[2].blue()
hh[2].Draw("same")
canvas >> "fig012"
.q
# Ostap  session by adzyuba   ended at Fri Feb 19 16:07:32 2021 [613.9s]
