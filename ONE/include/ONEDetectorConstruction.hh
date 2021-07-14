#ifndef ONEDetectorConstruction_h
#define ONEDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class ONEDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    ONEDetectorConstruction();
    virtual ~ONEDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    G4LogicalVolume* GetLV00() const { return fLV00; }
    G4LogicalVolume* GetLV01() const { return fLV01; }

  protected:
    G4LogicalVolume*  fLV00;
    G4LogicalVolume*  fLV01;

};

#endif

