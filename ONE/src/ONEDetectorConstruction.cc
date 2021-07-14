//------------------------------------------------------------------------------
#include "ONEDetectorConstruction.hh"
//------------------------------------------------------------------------------
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
ONEDetectorConstruction::ONEDetectorConstruction()
: G4VUserDetectorConstruction(),
  fLV00(0), fLV01(0)
{ }
//------------------------------------------------------------------------------
ONEDetectorConstruction::~ONEDetectorConstruction(){ }
//------------------------------------------------------------------------------
G4VPhysicalVolume* ONEDetectorConstruction::Construct()
{
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();


  G4String name;
  G4double density;
  G4int ncomponents, natoms;


  G4Element* H  = nist->FindOrBuildElement(1);
  G4Element* C  = nist->FindOrBuildElement(6);

  G4Material* sci = new G4Material(name="sci", density = 1.032*g/cm3, ncomponents=2);
  sci->AddElement(C, natoms=9);
  sci->AddElement(H, natoms=10);


  G4Material* w_mat = nist->FindOrBuildMaterial("G4_Galactic");
  G4Material* tun   = nist->FindOrBuildMaterial("G4_W");


  // World
  G4double w_xy = 102.0*mm;
  G4double w_z  = 102.0*mm;
  G4Box* solidWorld = new G4Box("World", 0.5*w_xy, 0.5*w_xy, 0.5*w_z);

  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, w_mat, "World");

  // Layer (LV) geometrical parameters
  G4double l00_x = 20.000*mm;
  G4double l00_y = 50.000*mm;
  G4double l00_z = 50.000*mm;
  G4double l01_r =  0.015*mm;

  // LVs
  G4Box*  solidLV00 =  new G4Box("LV00", 0.5*l00_x, 0.5*l00_y, 0.5*l00_z);
  G4Tubs* solidLV01 =  new G4Tubs("LV01", 0, l01_r, 0.5*l00_z,  0.*deg, 360.*deg);

  //G4Material* l00_mat = nist->FindOrBuildMaterial("G4_Galactic");

  G4LogicalVolume* logicLV00 = new G4LogicalVolume(solidLV00, sci , "LV00");
  G4LogicalVolume* logicLV01 = new G4LogicalVolume(solidLV01, tun , "LV01");

  G4ThreeVector l00_pos; l00_pos.set(0 ,-25.0, 0 );
  G4ThreeVector l01_pos; l01_pos.set(0 , 20.0, 0 );

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0, G4ThreeVector(), logicWorld,
                         "World", 0, false, checkOverlaps);

  new G4PVPlacement(0, l00_pos, logicLV00, "LV00", logicWorld, false, 0, checkOverlaps);
  new G4PVPlacement(0, l01_pos, logicLV01, "LV01", logicWorld, false, 0, checkOverlaps);

  fLV00 = logicLV00;
  fLV01 = logicLV01;

  return physWorld;
}
//------------------------------------------------------------------------------
