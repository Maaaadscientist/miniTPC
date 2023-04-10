#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"

#include "nEXOPrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOPrimaryGeneratorAction::nEXOPrimaryGeneratorAction()
{
  particleGun = new G4GeneralParticleSource ();
}

nEXOPrimaryGeneratorAction::~nEXOPrimaryGeneratorAction()
{
  delete particleGun;
}

void nEXOPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}



