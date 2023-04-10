#ifndef nEXOPrimaryGeneratorMessenger_h
#define nEXOPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

class nEXOPrimaryGeneratorAction;

class nEXOPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  nEXOPrimaryGeneratorMessenger(nEXOPrimaryGeneratorAction*);
  
  void SetNewValue(G4UIcommand*, G4String);

private:
  nEXOPrimaryGeneratorAction*    nEXOAction;
  G4UIdirectory                  fDirectory;
  G4UIcmdWithAString             GenCmd;
  G4UIcmdWithAString             nCaptureXeSimCmd;
  G4UIcmdWithAString             XeComponentCmd;
  G4UIcmdWithAnInteger           CuIsoCmd;
  G4UIcmdWithAString             CuComponentCmd;
};

#endif

