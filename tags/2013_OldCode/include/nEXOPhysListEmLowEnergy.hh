
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nEXOPhysListEmLowEnergy_h
#define nEXOPhysListEmLowEnergy_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXOPhysListEmLowEnergy : public G4VPhysicsConstructor
{
public: 
  nEXOPhysListEmLowEnergy(const G4String& name = "lowenergy");
  virtual ~nEXOPhysListEmLowEnergy();

public: 
  // This method is dummy for physics
  virtual void ConstructParticle() {};
 
  // This method will be invoked in the Construct() method.
  // each physics process will be instantiated and
  // registered to the process manager of each particle type 
  virtual void ConstructProcess();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif








