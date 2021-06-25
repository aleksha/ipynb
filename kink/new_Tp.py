#===============================================================================
EVENTS   = 30000
Z_POS    = -380.
T_P_LOW  = 5.0
T_P_HIGH = 5.2
T_P_VALS = [ 0, 0.5, 2.,5.,10.]
E        = 100.
USE_CORE = True
reDirect = True
Zin1     = -5000.
Zin2     = -1000.
Zout     = 5000.
Rsci     = 1.5
#===============================================================================
#rfile = ROOT.TFile('./beamfile_prm_mu100.root', "READ")
#rfile = ROOT.TFile('./output_cedar_mu100_parallel.root', "READ")
rfile = ROOT.TFile('./output_cedar_mu100_focused.root', "READ")
rfile.ls()
tree = rfile["BeamFile"]
#===============================================================================
ev     = 0
length = len( tree )

#===============================================================================
from math import sin, cos, asin, pi, sqrt


m_l = 0.105658
m_p = 0.938272
def calc_theta( TR ):
    return 2.*asin(sqrt( (TR*0.001)*m_p/(2.*E*E)))

def calc_plane( s, p, Z):
    t = (Z-s.Z())/p.Z()
    return ROOT.TVector3( s.X()+t*p.X(), s.Y()+t*p.Y(), Z )

h  = ROOT.TH1F("h" ,";ang,#murad;events",150,0,1500)
h2 = ROOT.TH2F("h2",";X;Y",200,-100,100,200,-100,100)

ent = 0
sca = ROOT.TVector3()
lit = ROOT.TVector3()
lepton = ROOT.TVector3()
trg_in = 0
trg    = 0
trgs_i = [0,0,0,0,0]
trgs_o = [0,0,0,0,0]

while trg_in < 2000 :

    tree.GetEntry( ROOT.gRandom.Integer(length) )
    if USE_CORE:
        while tree.particleFlag!=2:
            tree.GetEntry( ROOT.gRandom.Integer(length) )
    e =  (13, tree.X, tree.Y, tree.Z , tree.dXdZ*0.001, tree.dYdZ*0.001, 100. ) 

#    e = (13, -5+10.*ROOT.gRandom.Rndm(),  -5+10.*ROOT.gRandom.Rndm(), -6299., 0, 0, 100. )

    Z_scat = -400.+800.*ROOT.gRandom.Rndm()
    dZ = Z_scat - e[3]
    X_scat = e[1] + dZ*sin(e[4])
    Y_scat = e[2] + dZ*sin(e[5])
    sca.SetXYZ(  X_scat, Y_scat, Z_scat )

    idx_Tp = ROOT.gRandom.Integer( 5 )

    Tp = T_P_VALS[idx_Tp]
    theta_l = calc_theta( Tp )
    phi_l   = pi*( 2.*ROOT.gRandom.Rndm() - 1. )
    lit.SetXYZ( -100.*e[4], -100.*e[5], -100 )
    direction = ROOT.TVector3(e[4],e[5], cos( asin( sqrt(e[4]**2+e[5]**2) ) ) ).Unit()

    l_p = sqrt( E**2 - m_l**2 )
    lepton.SetMagThetaPhi( l_p, theta_l, phi_l )
    # transforms v1 from the rotated frame (z' parallel to direction, x' in the theta plane 
    #   and y' in the xy plane as well as perpendicular to the theta plane) to the (x,y,z) frame
    lepton.RotateUz(direction)
    lpt = l_p*lepton.Unit()
    h.Fill(1000.*1000.* ( (-lit).Angle(lpt) ) )
    XY  =  calc_plane( sca, lpt, Zout)
    XY1 =  calc_plane( sca, lit, Zin1)
    XY2 =  calc_plane( sca, lit, Zin2)
    h2.Fill(XY2.X(), XY2.Y())
    if XY1.X()**2 + XY1.Y()**2 < Rsci**2 :
        if XY2.X()**2 + XY2.Y()**2 < Rsci**2 :
            trg_in += 1
            print(trg_in)
            trgs_i[idx_Tp] += 1
            if not XY.X()**2 + XY.Y()**2 < Rsci**2 :
                trg += 1
                trgs_o[idx_Tp] += 1

print( "Triggers (in) : " + str(trg_in) )
print( "Triggers (out): " + str(trg) )

print(trgs_i)
print(trgs_o)
rfile.Close()
h2.Draw("col")
