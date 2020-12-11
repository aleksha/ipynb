//------------------------------------------------------------------------------
#include "EPSDetectorConstruction.hh"
//------------------------------------------------------------------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
EPSDetectorConstruction::EPSDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0), fLV02(0), fLV03(0), fLV04(0),
  fLV05(0), fLV06(0), fLV07(0), fLV08(0), fLV09(0),
  fLV10(0), fLV11(0), fLV12(0), fLV13(0), fLV14(0),
  fLV15(0), fLV16(0)
{ }
//------------------------------------------------------------------------------
EPSDetectorConstruction::~EPSDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* EPSDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();

  G4String name;
  G4double z, a, density;
  //G4double temperature, pressure;
  G4int ncomponents, natoms;
  G4double fractionmass;

//------------------------------------------
// Elements

  G4Element* H  = new G4Element("Hydrogen", "H",  z=  1, a= 1.008*g/mole);
  G4Element* C  = new G4Element("Carbon",   "C",  z=  6, a= 12.00*g/mole);
  //G4Element* N  = new G4Element("Nitrogen", "N",  z=  7, a= 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",   "O",  z=  8, a= 16.00*g/mole);
  //G4Element* Al = new G4Element("Aluminium","Al", z= 13, a= 26.9815385*g/mole);
  //G4Element* Ar = new G4Element("Argon",    "Ar", z= 18, a= 39.95*g/mole);
  //G4Element* Cu = new G4Element("Copper",   "Cu", z= 29, a= 63.546*g/mole);

  G4Material* scinc = new G4Material(name="scinc", density = 1.032*g/cm3, ncomponents=2);
  scinc->AddElement(C, natoms=9);
  scinc->AddElement(H, natoms=10);

//------------------------------------------
// Gases

  G4Material *ArGas   = new G4Material("ArGas"  , 18, 39.948*g/mole, 33.213 *kg/m3 );
//  G4Material *H2Gas = new G4Material("H2Gas", 1, 1.008*g/mole, 0.25*1.6347*kg/m3 );
  G4Material *H2Gas = new G4Material("H2Gas", 1, 1.008*g/mole, 1.6347*kg/m3 );

  G4Material* CH4Gas = new G4Material(name="CH4Gas",density=13.661*kg/m3,ncomponents=2);
  CH4Gas->AddElement(H,4);
  CH4Gas->AddElement(C,1);

  // Use 95% Ar, 5% Methane for electron detector gas. Percentage per volume
//  G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 0.25*32.2354*kg/m3, ncomponents=2);
  G4Material* ArCH4 = new G4Material(name="ArCH4"  , density = 32.2354*kg/m3, ncomponents=2);
  ArCH4->AddMaterial (  ArGas,  fractionmass = 0.978811);
  ArCH4->AddMaterial( CH4Gas,  fractionmass = 0.021189);


//------------------------------------------
// NIST materials

  G4Material* w_mat   = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* air_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* steel   = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Material* BeSolid = nist->FindOrBuildMaterial("G4_Be");
  G4Material* AlSolid = nist->FindOrBuildMaterial("G4_Al");
  G4Material* TiSolid = nist->FindOrBuildMaterial("G4_Ti");
  G4Material* CuSolid = nist->FindOrBuildMaterial("G4_Cu");
  G4Material* WSolid  = nist->FindOrBuildMaterial("G4_W" );
  G4Material* Kapton  = nist->FindOrBuildMaterial("G4_KAPTON" );
  G4Material* Mylar   = nist->FindOrBuildMaterial("G4_MYLAR" );




  // World
  G4double w_xy = 1000.0*mm;
  G4double w_z  = 4000.0*mm;
  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // Layer (LV) geometrical parameters
  G4double l_xy = 999.000*mm;
  G4double s_xy = 998.000*mm;

  G4double l00_z = 1000.000*mm; // Vacuum
  G4double l01_z =   50.000*mm; // H2
  G4double l02_z =  800.000*mm; // H2 TPC
  G4double l03_z =  800.000*mm; // Ar + CH4
  G4double l04_z =  105.000*mm; // Air

  G4double l05_z =  0.020*mm;   // Mylar
  G4double l06_z =  0.100*mm;   // Be window
  G4double l07_z =  0.020*mm;   // Be anode

  G4double l08_z =  0.01*mm;   // W grid
  G4double l09_z =  0.050*mm;   // Al cathode

  G4double l10_z =  0.050*mm;   // Mylar

  G4double l11_z =  5.000*mm;   // Ti

  G4double l12_z =  0.028*mm;   // 8 CSCs

  G4double l13_z =  0.001*mm;
  G4double l14_z =  0.001*mm;
  G4double l15_z =  0.001*mm;
  G4double l16_z =  0.001*mm;

  // LVs
  G4Box* solidLV00 =  new G4Box("LV00", 0.5*l_xy, 0.5*l_xy, 0.5*l00_z);
  G4Box* solidLV01 =  new G4Box("LV01", 0.5*l_xy, 0.5*l_xy, 0.5*l01_z);
  G4Box* solidLV02 =  new G4Box("LV02", 0.5*l_xy, 0.5*l_xy, 0.5*l02_z);
  G4Box* solidLV03 =  new G4Box("LV03", 0.5*l_xy, 0.5*l_xy, 0.5*l03_z);
  G4Box* solidLV04 =  new G4Box("LV04", 0.5*l_xy, 0.5*l_xy, 0.5*l04_z);
  G4Box* solidLV05 =  new G4Box("LV05", 0.5*s_xy, 0.5*s_xy, 0.5*l05_z);
  G4Box* solidLV06 =  new G4Box("LV06", 0.5*s_xy, 0.5*s_xy, 0.5*l06_z);
  G4Box* solidLV07 =  new G4Box("LV07", 0.5*s_xy, 0.5*s_xy, 0.5*l07_z);
  G4Box* solidLV08 =  new G4Box("LV08", 0.5*s_xy, 0.5*s_xy, 0.5*l08_z);
  G4Box* solidLV09 =  new G4Box("LV09", 0.5*s_xy, 0.5*s_xy, 0.5*l09_z);
  G4Box* solidLV10 =  new G4Box("LV10", 0.5*s_xy, 0.5*s_xy, 0.5*l10_z);
  G4Box* solidLV11 =  new G4Box("LV11", 0.5*s_xy, 0.5*s_xy, 0.5*l11_z);
  G4Box* solidLV12 =  new G4Box("LV12", 0.5*s_xy, 0.5*s_xy, 0.5*l12_z);
  G4Box* solidLV13 =  new G4Box("LV13", 0.5*s_xy, 0.5*s_xy, 0.5*l13_z);
  G4Box* solidLV14 =  new G4Box("LV14", 0.5*s_xy, 0.5*s_xy, 0.5*l14_z);
  G4Box* solidLV15 =  new G4Box("LV15", 0.5*s_xy, 0.5*s_xy, 0.5*l15_z);
  G4Box* solidLV16 =  new G4Box("LV16", 0.5*s_xy, 0.5*s_xy, 0.5*l16_z);

  //G4Material* l00_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l01_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l02_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l03_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l04_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l05_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l06_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l07_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l08_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l09_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l10_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l11_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l12_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l13_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l14_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l15_mat = nist->FindOrBuildMaterial("G4_Galactic");
  //G4Material* l16_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00, w_mat   , "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01, H2Gas   , "LV01");
  G4LogicalVolume* logicLV02 = new G4LogicalVolume(solidLV02, H2Gas   , "LV02");
  G4LogicalVolume* logicLV03 = new G4LogicalVolume(solidLV03, ArCH4   , "LV03");
  G4LogicalVolume* logicLV04 = new G4LogicalVolume(solidLV04, air_mat , "LV04");

  G4LogicalVolume* logicLV05 = new G4LogicalVolume(solidLV05, Mylar   , "LV05");

  G4LogicalVolume* logicLV06 = new G4LogicalVolume(solidLV06, BeSolid , "LV06");

  G4LogicalVolume* logicLV07 = new G4LogicalVolume(solidLV07, BeSolid , "LV07");
  G4LogicalVolume* logicLV08 = new G4LogicalVolume(solidLV08, WSolid  , "LV08");
  G4LogicalVolume* logicLV09 = new G4LogicalVolume(solidLV09, AlSolid , "LV09");

  G4LogicalVolume* logicLV10 = new G4LogicalVolume(solidLV10, Mylar   , "LV10");

  G4LogicalVolume* logicLV11 = new G4LogicalVolume(solidLV11, TiSolid , "LV11");

  G4LogicalVolume* logicLV12 = new G4LogicalVolume(solidLV12, WSolid  , "LV12");

  G4LogicalVolume* logicLV13 = new G4LogicalVolume(solidLV13, steel , "LV13");
  G4LogicalVolume* logicLV14 = new G4LogicalVolume(solidLV14, steel , "LV14");
  G4LogicalVolume* logicLV15 = new G4LogicalVolume(solidLV15, scinc , "LV15");
  G4LogicalVolume* logicLV16 = new G4LogicalVolume(solidLV16, scinc , "LV16");


  G4ThreeVector l00_pos; l00_pos.set(0,0,-l00_z*0.5-l01_z      );
  G4ThreeVector l01_pos; l01_pos.set(0,0,-l01_z*0.5            );
  G4ThreeVector l02_pos; l02_pos.set(0,0, l02_z*0.5            );
  G4ThreeVector l03_pos; l03_pos.set(0,0, l02_z+l03_z*0.5      );
  G4ThreeVector l04_pos; l04_pos.set(0,0, l02_z+l03_z+l04_z*0.5);

  G4ThreeVector l05_pos; l05_pos.set(0,0,0.5*l05_z-0.5*l00_z);
  G4ThreeVector l06_pos; l06_pos.set(0,0,0.5*l06_z-0.5*l01_z);

  G4double l_grid    =  10.*mm;
  G4double l_cathode = 400.*mm;
  G4double l_t = 0.01*mm;
  G4ThreeVector l07_pos; l07_pos.set(0,0,0.5*l07_z-0.5*l02_z);
  G4ThreeVector l08_pos; l08_pos.set(0,0,0.5*l08_z+l_grid-0.5*l02_z);
  G4ThreeVector l09_pos; l09_pos.set(0,0,0.5*l09_z+l_cathode-0.5*l02_z);

  G4ThreeVector l10_pos; l10_pos.set(0,0,0.5*l10_z-0.5*l03_z+l_t);

  G4ThreeVector l11_pos; l11_pos.set(0,0,0.5*l11_z-0.5*l04_z+l_t);

  G4ThreeVector l12_pos; l12_pos.set(0,0,0.5*l12_z-0.5*l03_z+l10_z+l_t);

  G4cout << "!!!!   " << l03_pos << G4endl;
  G4cout << "!!!!   " << l10_pos << G4endl;

  G4double l_dummy = 2.*mm;
  G4ThreeVector l13_pos; l13_pos.set(0,0,0.5*w_z-l_dummy*13.);
  G4ThreeVector l14_pos; l14_pos.set(0,0,0.5*w_z-l_dummy*14.);
  G4ThreeVector l15_pos; l15_pos.set(0,0,0.5*w_z-l_dummy*15.);
  G4ThreeVector l16_pos; l16_pos.set(0,0,0.5*w_z-l_dummy*16.);

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0, l00_pos, logicLV00, "pLV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "pLV01", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l02_pos, logicLV02, "pLV02", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l03_pos, logicLV03, "pLV03", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l04_pos, logicLV04, "pLV04", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l05_pos, logicLV05, "pLV05", logicLV00 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l06_pos, logicLV06, "pLV06", logicLV01 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l07_pos, logicLV07, "pLV07", logicLV02 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l08_pos, logicLV08, "pLV08", logicLV02 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l09_pos, logicLV09, "pLV09", logicLV02 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l10_pos, logicLV10, "pLV10", logicLV03 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l11_pos, logicLV11, "pLV11", logicLV04 , false, 0, checkOverlaps);
  new G4PVPlacement(0, l12_pos, logicLV12, "pLV12", logicLV03 , false, 0, checkOverlaps);

  new G4PVPlacement(0, l13_pos, logicLV13, "pLV13", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l14_pos, logicLV14, "pLV14", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l15_pos, logicLV15, "pLV15", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l16_pos, logicLV16, "pLV16", logicWorld, false, 0, checkOverlaps);

  fLV00 = logicLV00;
  fLV01 = logicLV01;
  fLV02 = logicLV02;
  fLV03 = logicLV03;
  fLV04 = logicLV04;
  fLV05 = logicLV05;
  fLV06 = logicLV06;
  fLV07 = logicLV07;
  fLV08 = logicLV08;
  fLV09 = logicLV09;
  fLV10 = logicLV10;
  fLV11 = logicLV11;
  fLV12 = logicLV12;
  fLV13 = logicLV13;
  fLV14 = logicLV14;
  fLV15 = logicLV15;
  fLV16 = logicLV16;

  return physWorld;
}
//------------------------------------------------------------------------------
