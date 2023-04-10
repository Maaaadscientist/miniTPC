
#ifndef nEXOPrimaryGeneratorAction_h
#define nEXOPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4GeneralParticleSource;
class G4Event;

class nEXOPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  nEXOPrimaryGeneratorAction();
  ~nEXOPrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event* anEvent);

private:
  G4GeneralParticleSource* particleGun;
  
};

#endif



