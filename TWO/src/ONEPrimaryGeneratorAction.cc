#include "ONEPrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
//------------------------------------------------------------------------------
ONEPrimaryGeneratorAction::ONEPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="mu-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(10000.*MeV);
}
//------------------------------------------------------------------------------
ONEPrimaryGeneratorAction::~ONEPrimaryGeneratorAction(){ delete fParticleGun; }
//------------------------------------------------------------------------------
void ONEPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  double cosAlpha = G4UniformRand();
  double sinAlpha  = sqrt(1. - cosAlpha*cosAlpha);
  double psi = G4UniformRand()*2.*3.141592;

  fParticleGun->SetParticleMomentumDirection( G4ThreeVector(sinAlpha*std::cos(psi),sinAlpha*std::sin(psi),cosAlpha) );
  fParticleGun->SetParticlePosition( G4ThreeVector(5,5,-49) );
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
//------------------------------------------------------------------------------

