
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nEXOPhysListParticles_h
#define nEXOPhysListParticles_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXOPhysListParticles : public G4VPhysicsConstructor
{
public: 
  nEXOPhysListParticles(const G4String& name = "particles");
  virtual ~nEXOPhysListParticles();

public: 
  // This method will be invoked in the Construct() method. 
  // each particle type will be instantiated
  virtual void ConstructParticle();
 
  // This method is dummy.
  virtual void ConstructProcess() {};

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif








